# Project:   x

# Toolflags:
CCflags = -c -depend !Depend -I^.,C: -throwback 
C++flags = -c -depend !Depend -IC: -throwback
Linkflags = -aif -c++ -o $@
ObjAsmflags = -throwback -NoCache -depend !Depend
CMHGflags = 
LibFileflags = -c -o $@
Squeezeflags = -o $@

X = obj.X

# Final targets:
o.xLib:   ${X}
        libfile $(libfileflags) ${X}

# User-editable dependencies:
.SUFFIXES:  .obj .c

.c.obj:
        cc $(ccflags) -o $@ $< 

# Static dependencies:

# Dynamic dependencies:
obj.X:	c.X
obj.X:	C:h.kernel
obj.X:	C:oslib.h.macros
obj.X:	C:oslib.h.messagetrans
obj.X:	C:oslib.h.types
obj.X:	C:oslib.h.os
obj.X:	C:oslib.h.os
obj.X:	^.h.x
