# Copyright (C) 2001-2002 Joe Orton <joe@manyfish.co.uk>    -*- autoconf -*-
#
# This file is free software; you may copy and/or distribute it with
# or without modifications, as long as this notice is preserved.
# This software is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even
# the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
# PURPOSE.

# The above license applies to THIS FILE ONLY, the neon library code
# itself may be copied and distributed under the terms of the GNU
# LGPL, see COPYING.LIB for more details

# This file is part of the neon HTTP/WebDAV client library.
# See http://www.webdav.org/neon/ for the latest version. 
# Please send any feedback to <neon@webdav.org>

# Tests needed for the neon-test common test code.

AC_DEFUN([NEON_TEST], [

AC_REQUIRE([NEON_COMMON_CHECKS])

AC_REQUIRE([AC_TYPE_PID_T])
AC_REQUIRE([AC_HEADER_TIME])

AC_CHECK_HEADERS(sys/time.h)

# hstrerror() is probably in -lresolv, which may or may not already
# be in LIBS; don't bother picking up libresolv just for hstrerror.
AC_CHECK_FUNCS(pipe isatty usleep hstrerror)

AC_REQUIRE([NE_FIND_AR])

NEON_FORMAT(time_t, [
#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#endif])

])
