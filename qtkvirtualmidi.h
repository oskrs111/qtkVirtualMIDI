#ifndef QTKVIRTUALMIDI_H
#define QTKVIRTUALMIDI_H

#include <QObject>
#include "qtkvirtualmidistructs.h"
#include "teVirtualMIDI.h"
#define MAX_SYSEX_BUFFER	65535

enum virtualPortState
{
    stUnknown = 0,
    stReady,
    stClosed,
    stError = 100
};


class qtkVirtualMIDI : public QObject
{
    Q_OBJECT
public:
    explicit qtkVirtualMIDI(QObject *parent = 0);
    ~qtkVirtualMIDI();
    static char* binToStr(const unsigned char *data, DWORD length);
    static char* midiMessageToStr(struct midiMessage* message);
    static void CALLBACK teVMCallback( LPVM_MIDI_PORT midiPort, LPBYTE midiDataBytes, DWORD length, DWORD_PTR dwCallbackInstance );
    static qtkVirtualMIDI* p_this;
    quint16 getStatus();

private:    

    quint16 m_status;
    LPVM_MIDI_PORT m_midiPort;

signals:
    void midiReceived(struct midiMessage message);

public slots:    
};

#endif // QTKVIRTUALMIDI_H
