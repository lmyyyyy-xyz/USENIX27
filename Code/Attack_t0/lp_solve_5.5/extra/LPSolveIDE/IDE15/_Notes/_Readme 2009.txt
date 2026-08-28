Readme Aug 23, 2009  William Patton

This is the only Delphi project I have ever tried.

Henri made a wounderful implementation. 
In 2008 some pepole made very large models the Ihe ide could not load.
Peter then made a lrarge address aware version of the lp_solve5.5.012 dll.
It made available 3.5G memory but used Vsiual studio 2007 mcvcrt7 references.
The stream passing usec by the IDE failed to be delt with by the msvcrt7 connection.
See the note in the LargeAddressAware folder.

When the sources got posted to the sourceforge site in mid 2008, I gave a shot at compiling them.
It was a kind of adventure.  
See the subdirectory How to build for notes on geting a free Delphi environment created.

I have populated the IDE13\bin directory with some test files and a choice of the largeaddressaware dll
or the 5.5.014 dll. The build process will place the IDE.exe and .Map file there for testing.

Delphi Units are kind of like libraries or Java and C# interfaces.
I am not entirely sure the critical external components
        Synedit: http://synedit.sourceforge.net/
        VirtualTreeView: http://www.delphi-gems.com/VirtualTreeview
        XPMenu: http://www.shagrouni.com/english/software/xpmenu.html
                This disappeared in late 2007. I have a site copy from the interne Archive in
                F:\Delphi\IDE13\dcu\XPmenu. Henri left all its pieces in the source and 
                I am sure it is compiled each time.
are entirely found via the pieces in the \dcu subdirectory
or via the hidden links to earlier seperate builds kept by the Borland environment.

I kept a listing of the contents and moved the structure locally.
It actually resides on The localuser MY Documents tree
C:\Documents and Settings\MRP\My Documents\Borland Studio Projects
 Directory of F:\Delphi\IDE13\Borland Studio Projects

08/22/2009  07:10 PM    <DIR>          Bpl
08/08/2008  02:47 PM                49 Lpobject.identcache
03/19/2009  11:11 PM             1,895 lpobjectD.dcu
03/20/2009  12:30 AM             2,403 Package1.dcu
03/19/2009  11:07 PM                48 Package1.identcache
03/18/2009  12:03 PM                99 Project1.bdsproj.local
03/18/2009  12:05 PM                96 Project1.identcache
08/22/2009  07:44 PM                 0 Projects
03/20/2009  12:36 AM             2,297 VLPSynedit1.dcu
03/19/2009  10:18 AM             2,157 XPmenu1.dcu
               9 File(s)          9,044 bytes

 Directory of F:\Delphi\IDE13\Borland Studio Projects\Bpl

03/18/2009  01:03 PM           315,392 LPSynedt_1.bpl
03/18/2009  01:03 PM           550,124 LPSynedt_1.dcp
03/20/2009  12:30 AM           315,904 Package1.bpl
03/20/2009  12:30 AM           549,854 Package1.dcp
03/19/2009  10:39 PM            93,696 SynEdit_D2006.bpl
03/19/2009  10:39 PM            35,863 SynEdit_D2006.dcp
03/18/2009  09:29 PM         1,617,920 SynEdit_R2006.bpl
03/21/2009  03:39 PM         2,993,596 SynEdit_R2006.dcp
03/18/2009  09:26 PM         1,616,896 SynEdit_R7.bpl
03/18/2009  09:26 PM         2,993,259 SynEdit_R7.dcp
08/08/2008  05:12 PM           411,648 VirtualTreesD10.bpl
08/08/2008  05:12 PM           394,388 VirtualTreesD10.dcp
08/08/2008  05:12 PM            66,048 VirtualTreesD10D.bpl
08/08/2008  05:12 PM            22,331 VirtualTreesD10D.dcp
08/08/2008  05:12 PM           468,992 VirtualTreesD9.bpl
08/08/2008  05:12 PM           427,773 VirtualTreesD9.dcp
03/20/2009  12:36 AM            24,064 VLPSynedit1.bpl
03/20/2009  12:36 AM             7,970 VLPSynedit1.dcp
03/19/2009  10:18 AM            67,584 XPmenu1.bpl
03/19/2009  10:18 AM            70,758 XPmenu1.dcp
              20 File(s)     13,044,060 bytes

Have a nice adventure when you try your own modifications.

Free Pascal and the Lazarus project provides hope for a 64 bit and linux 
common port.  I might finish it by the end of the year. 
It is more of an adventure. The forms converter is touchy and there is some stuff
about Ansi and wide strings.
If I find the machine and directory I was working on it in April. 
        OK, I found it on my mediaCenter machine.
        
FPC-Lazarus Project www.lazarus.freepascal.org/ 

William Patton  Chicago, Illinois USA.
