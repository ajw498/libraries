# Project:   TaskLib


# Toolflags:
CCflags = -c -depend !Depend -IC: -throwback 
C++flags = -c -depend !Depend -IC: -throwback
Linkflags = -aif -c++ -o $@
ObjAsmflags = -throwback -NoCache -depend !Depend
CMHGflags = 
LibFileflags = -c $@
Squeezeflags = -o $@

TASK = obj.TaskGetName

# Final targets:
o.TaskLib:   ${TASK}
        LibFile $(LibFileflags) ${TASK} 
      	 @echo <sys$Time> "Task" Made


# User-editable dependencies:
.SUFFIXES:  .obj .c

.c.obj:
        cc $(ccflags) -o $@ $< 


# Static dependencies:


# Dynamic dependencies:
obj.TaskGetName:	c.TaskGetName
obj.TaskGetName:	C:oslib.h.os
obj.TaskGetName:	C:oslib.h.types
obj.TaskGetName:	C:oslib.h.toolbox
obj.TaskGetName:	C:oslib.h.wimp
obj.TaskGetName:	C:oslib.h.osspriteop
obj.TaskGetName:	C:oslib.h.font
obj.TaskGetName:	C:oslib.h.messagetrans
obj.TaskGetName:	C:h.Task
obj.TaskGetName:	C:oslib.h.os
