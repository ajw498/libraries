# Project:   Choices


# Toolflags:
CCflags = -c -depend !Depend -I@.^.,C: -throwback 
C++flags = -c -depend !Depend -IC: -throwback
Linkflags = -aif -c++ -o $@
ObjAsmflags = -throwback -NoCache -depend !Depend
CMHGflags = 
LibFileflags = -c $@
Squeezeflags = -o $@

CHOICES = obj.Choices

# Final targets:
o.ChoicesLib:   ${CHOICES} 
         LibFile $(LibFileflags) ${CHOICES} 
      	 @echo <sys$Time> "Choices" Made

# User-editable dependencies:

.SUFFIXES:  .obj .c

.c.obj:
        cc $(ccflags) -o $@ $* 

# Dynamic dependencies:
obj.Choices:	c.Choices
obj.Choices:	C:h.kernel
obj.Choices:	C:oslib.h.toolbox
obj.Choices:	C:oslib.h.types
obj.Choices:	C:oslib.h.os
obj.Choices:	C:oslib.h.wimp
obj.Choices:	C:oslib.h.osspriteop
obj.Choices:	C:oslib.h.font
obj.Choices:	C:oslib.h.messagetrans
obj.Choices:	C:oslib.h.osfscontrol
obj.Choices:	C:oslib.h.fileswitch
obj.Choices:	^.h.x
obj.Choices:	^.h.Choices
obj.Choices:	C:oslib.h.types
