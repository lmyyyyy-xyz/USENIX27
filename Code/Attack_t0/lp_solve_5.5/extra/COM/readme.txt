This is the COM interface to lpsolve version 5.
Note that this COM object is only an interface.
The COM dll is lpsolve55COM.dll, but it also needs the
lpsolve dll lpsolve55.dll to access the lpsolve functions.
This COM interface is written in VB, but the lpsolve55 dll
that contains the executable code is written in C. So the
performance of this COM object should be as good as directly
calling the lpsolve55 dll, except maybe if you do many calls
to the COM object, but that is then only because of the fact
that calling COM objects is slightly slower than directly
calling routines, but in 99.9% of the cases you will not
notice this.

To use this object, it must first be registered.
This can be done via the command
regsvr32 lpsolve55COM.dll

Default, the COM object looks for lpsolve55.dll in the same
directory as where the COM object is located. This can be
overruled by calling the Init Method of the object, but
this is optional.
