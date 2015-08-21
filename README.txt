This Qt style class implements a simple interface to use Tobias Erichsen VirtualMIDI driver for Windows.
Tobias do not allow to use his driver without explicit authorization, so please ask him if you plan to 
distribute some appication that uses virtualMIDI interface. You can get all information here: 
http://www.tobias-erichsen.de/software/virtualmidi.html

From my side (Oscar Sanz) qtkVirtualMIDI class can be freely used in any way according to MIT license.

You can check how it works in my 'discoFever' application. This app gets MIDI data from virtualMIDI driver ad sends
it via UDP to configured host. In the other side there is 'toniManero' app that will dance with the MIDI data received...

https://github.com/oskrs111/pimcw/tree/master/discoFever
https://github.com/oskrs111/pimcw/tree/master/toniManero

How to compile it with virtualMIDI driver:
1-Get virtualMIDI SDK from Tobias site http://www.tobias-erichsen.de/software/virtualmidi/virtualmidi-sdk.html
2-Configure QtCreator project in order to set include path for 'teVirtualMIDI.h' header (from virtualMIDI SDK). 
3-Configure QtCreator project in order to add virtualMIDI libraries 'teVirtualMIDI32.lib' or 'teVirtualMIDI64.lib'
4-Add virtualMIDI driver interface source 'teVirtualMIDITest.c' to the project.

How to make it work:
1-You have to download and install virtualMIDI app from Tobias Erichsen. You will not use the virtualMIDI
application directly (qtkVirtualMIDI will do the job) but is need in order to driver be installed in you system.
2-Compile your application and enjoy.
