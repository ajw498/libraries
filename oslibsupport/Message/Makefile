# Project:   Message


# Toolflags:
CCflags = -c -depend !Depend -IC: -throwback 
C++flags = -c -depend !Depend -IC: -throwback
Linkflags = -aif -c++ -o $@
ObjAsmflags = -throwback -NoCache -depend !Depend
CMHGflags = 
LibFileflags = -c $@
Squeezeflags = -o $@

MESSAGE = obj.Message

# Final targets:
o.MessageLib:   ${MESSAGE} 
        LibFile $(LibFileflags) ${MESSAGE}
      	 @echo <sys$Time> "Message" Made


# User-editable dependencies:
.SUFFIXES:  .obj .c

.c.obj:
        cc $(ccflags) -o $@ $< 


# Static dependencies:


# Dynamic dependencies:
obj.Message:	c.Message
obj.Message:	C:oslib.h.os
obj.Message:	C:oslib.h.types
obj.Message:	C:oslib.h.wimp
obj.Message:	C:oslib.h.osspriteop
obj.Message:	C:oslib.h.font
obj.Message:	C:h.Message
obj.Message:	C:oslib.h.types
obj.Message:	C:oslib.h.os
obj.Message:	C:oslib.h.messageTrans
