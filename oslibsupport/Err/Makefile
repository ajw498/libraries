# Project:   ErrLib


# Toolflags:
CCflags = -c -depend !Depend -I^.,C: -throwback 
C++flags = -c -depend !Depend -IC: -throwback
Linkflags = -aif -c++ -o $@
ObjAsmflags = -throwback -NoCache -depend !Depend
CMHGflags = 
LibFileflags = -c $@
Squeezeflags = -o $@

ERR = obj.MakeError obj.NoMem obj.OsError obj.ReportErr 

# Final targets:
o.ErrLib:   ${ERR} 
         LibFile $(LibFileflags) ${ERR}
      	 @echo <sys$Time> "Err" Made

# User-editable dependencies:
.SUFFIXES:  .obj .c

.c.obj:
        cc $(ccflags) -o $@ $< 

# Dynamic dependencies:
obj.MakeError:	c.MakeError
obj.MakeError:	^.h.err
obj.MakeError:	C:oslib.h.os
obj.MakeError:	C:oslib.h.types
obj.MakeError:	C:oslib.h.toolbox
obj.MakeError:	C:oslib.h.wimp
obj.MakeError:	C:oslib.h.osspriteop
obj.MakeError:	C:oslib.h.font
obj.MakeError:	C:oslib.h.messagetrans
obj.OsError:	c.OsError
obj.OsError:	C:oslib.h.os
obj.OsError:	C:oslib.h.types
obj.OsError:	^.h.Task
obj.OsError:	C:oslib.h.os
obj.OsError:	C:oslib.h.wimp
obj.OsError:	C:oslib.h.osspriteop
obj.OsError:	C:oslib.h.font
obj.OsError:	^.h.Err
obj.ReportErr:	c.ReportErr
obj.ReportErr:	C:oslib.h.os
obj.ReportErr:	C:oslib.h.types
obj.ReportErr:	C:oslib.h.wimp
obj.ReportErr:	C:oslib.h.osspriteop
obj.ReportErr:	C:oslib.h.font
obj.ReportErr:	^.h.Task
obj.ReportErr:	C:oslib.h.os
obj.ReportErr:	^.h.Err
