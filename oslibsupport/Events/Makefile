# Project:   EvLib


# Toolflags:
CCflags = -c -depend !Depend -IC: -throwback 
C++flags = -c -depend !Depend -IC: -throwback
Linkflags = -aif -c++ -o $@
ObjAsmflags = -throwback -NoCache -depend !Depend
CMHGflags = 
LibFileflags = -c $@
Squeezeflags = -o $@

EVENTS = obj.event obj.tbevent obj.wimpevent obj.wimpmsg
 
# Final targets:
o.EvLib:   ${EVENTS}
      	 LibFile $(LibFileflags) ${EVENTS}
      	 @echo <sys$Time> "Event" Made


# User-editable dependencies:
.SUFFIXES:  .obj .c

.c.obj:
        cc $(ccflags) -o $@ $< 


# Static dependencies:

# Dynamic dependencies:
obj.event:	c.event
obj.event:	C:oslib.h.wimp
obj.event:	C:oslib.h.types
obj.event:	C:oslib.h.os
obj.event:	C:oslib.h.osspriteop
obj.event:	C:oslib.h.font
obj.event:	C:oslib.h.toolbox
obj.event:	C:oslib.h.messagetrans
obj.event:	h.tbevent
obj.event:	C:h.event
obj.event:	h.wimpevent
obj.event:	h.wimpmsg
obj.tbevent:	c.tbevent
obj.tbevent:	C:oslib.h.messagetrans
obj.tbevent:	C:oslib.h.types
obj.tbevent:	C:oslib.h.os
obj.tbevent:	h.tbevent
obj.tbevent:	C:oslib.h.wimp
obj.tbevent:	C:oslib.h.osspriteop
obj.tbevent:	C:oslib.h.font
obj.tbevent:	C:oslib.h.toolbox
obj.tbevent:	C:h.event
obj.tbevent:	C:h.x
obj.wimpevent:	c.wimpevent
obj.wimpevent:	C:oslib.h.os
obj.wimpevent:	C:oslib.h.types
obj.wimpevent:	h.wimpevent
obj.wimpevent:	C:oslib.h.wimp
obj.wimpevent:	C:oslib.h.osspriteop
obj.wimpevent:	C:oslib.h.font
obj.wimpevent:	C:oslib.h.toolbox
obj.wimpevent:	C:oslib.h.messagetrans
obj.wimpevent:	C:h.event
obj.wimpevent:	C:h.x
obj.wimpmsg:	c.wimpmsg
obj.wimpmsg:	C:oslib.h.os
obj.wimpmsg:	C:oslib.h.types
obj.wimpmsg:	h.wimpmsg
obj.wimpmsg:	C:oslib.h.wimp
obj.wimpmsg:	C:oslib.h.osspriteop
obj.wimpmsg:	C:oslib.h.font
obj.wimpmsg:	C:oslib.h.toolbox
obj.wimpmsg:	C:oslib.h.messagetrans
obj.wimpmsg:	C:h.event
obj.wimpmsg:	C:h.x
