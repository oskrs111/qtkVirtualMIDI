#include "qtkvirtualmidi.h"
#include <QDebug>
#include <QMetaType>

qtkVirtualMIDI* qtkVirtualMIDI::p_this = 0;
qtkVirtualMIDI::qtkVirtualMIDI(QObject *parent) : QObject(parent)
{
    qDebug() << "qtkVirtualMIDI, driver version: " << virtualMIDIGetVersion( NULL, NULL, NULL, NULL );
    qRegisterMetaType<midiMessage>("midiMessage");



    this->m_status = stUnknown;
    this->m_midiPort = virtualMIDICreatePortEx2( L"discoFever", qtkVirtualMIDI::teVMCallback, 0, MAX_SYSEX_BUFFER, TE_VM_FLAGS_PARSE_RX );
    if(this->m_midiPort)
    {
        this->m_status = stReady;
        p_this = this;
        qDebug() << "qtkVirtualMIDI, driver started";
    }
    else
    {
        qDebug() << "qtkVirtualMIDI, driver error: " << GetLastError();
        this->m_status = stError;
    }
}


qtkVirtualMIDI::~qtkVirtualMIDI()
{
    if(this->m_midiPort)
    {
        virtualMIDIClosePort(this->m_midiPort);
        this->m_status = stClosed;
        qDebug() << "qtkVirtualMIDI, driver closed";
    }
}

quint16 qtkVirtualMIDI::getStatus()
{
    return this->m_status;
}

char* qtkVirtualMIDI::binToStr( const unsigned char *data, DWORD length )
{
    static char dumpBuffer[ MAX_SYSEX_BUFFER * 3 ];
    DWORD index = 0;

    while ( length-- ) {
        sprintf( dumpBuffer+index, "%02x", *data );
        if ( length ) {
            strcat( dumpBuffer, ":" );
        }
        index+=3;
        data++;
    }
    return dumpBuffer;
}

char* qtkVirtualMIDI::midiMessageToStr(struct midiMessage* message)
{
    static char dumpBuffer[1024];
    sprintf(dumpBuffer, "%s, channel=%02d, Data1=%03d, Data2=%03d",
            status2string[message->m_status],
            message->m_channel,
            message->m_data1,
            message->m_data2);

    return dumpBuffer;
}

void CALLBACK qtkVirtualMIDI::teVMCallback( LPVM_MIDI_PORT midiPort, LPBYTE midiDataBytes, DWORD length, DWORD_PTR dwCallbackInstance ) {

    if ( ( NULL == midiDataBytes ) || ( 0 == length ) ) {
        qDebug() << "qtkVirtualMIDI::teVMCallback, empty command - driver was probably shut down!\n";
        return;
    }
    else
    {
		LPBYTE p = midiDataBytes;
        struct midiMessage message;
        for(int t = 0; t < length; t++)
        {
            memset(&message, 0x00, sizeof(message));
            memcpy(&message, p, MIDI_MESSAGE_LENGTH);
            t += MIDI_MESSAGE_LENGTH;
			p += MIDI_MESSAGE_LENGTH;

            if(p_this)
            {
                emit p_this->midiReceived(message);
                //qDebug() << "qtkVirtualMIDI::teVMCallback, rxData: " << qtkVirtualMIDI::binToStr((unsigned char*)&message, sizeof(message));
            }

        }

        if ( !virtualMIDISendData( midiPort, midiDataBytes, length ))
        {
            qDebug() << "qtkVirtualMIDI::teVMCallback, error sending data: " <<  GetLastError();
            return;
        }
    }

}
