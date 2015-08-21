#ifndef QTKVIRTUALMIDI_STRUCTS_H
#define QTKVIRTUALMIDI_STRUCTS_H
#define MIDI_MESSAGE_LENGTH 3


#define MM_NOTE_OFF    0x08 //[data1]=Note Number, [data2]=Velocity
#define MM_NOTE_ON     0x09 //[data1]=Note Number, [data2]=Velocity
#define MM_AFTERTOUCH  0x0A //[data1]=Note Number, [data2]=Pressure
#define MM_CONTROL_CH  0x0B //[data1]=Controller Number, [data2]=Data
#define MM_PROGRAM_CH  0x0C //[data1]=Program number
#define MM_AFTERTC_CH  0x0D //[data1]=Pressure
#define MM_PTCH_WHEEL  0x0E //[data1]=LSByte, [data2]=MSByte

struct midiMessage
{
    quint8 m_channel :4,
            m_status :4;
	quint8 m_data1;	
	quint8 m_data2;
	quint8 align__;
};

static char* status2string[] =
{
"Undefined0       ",
"Undefined1       ",
"Undefined2       ",
"Undefined3       ",
"Undefined4       ",
"Undefined5       ",
"Undefined6       ",
"Undefined7       ",
"NoteOff          ",
"NoteOn           ",
"Aftertouch       ",
"ControlChange    ",
"ProgramChange    ",
"ChannelAftertouch",
"PitchWheel       ",
"SySex            "
};


//Q_DECLARE_METATYPE(midiMessage)

#endif
