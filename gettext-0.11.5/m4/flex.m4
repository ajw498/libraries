# flex.m4 serial 1 (gettext-0.11)
dnl Copyright (C) 2001-2002 Free Software Foundation, Inc.
dnl This file is free software, distributed under the terms of the GNU
dnl General Public License.  As a special exception to the GNU General
dnl Public License, this file may be distributed as part of a program
dnl that contains a configuration script generated by Autoconf, under
dnl the same distribution terms as the rest of that program.

# Check for flex.

AC_DEFUN([gt_PROG_LEX],
[
  dnl Don't use AC_PROG_LEX or AM_PROG_LEX; we insist on flex.
  dnl Thus we don't need LEXLIB.
  AC_CHECK_PROG(LEX, flex, flex, :)

  dnl The next line is a workaround against an automake warning.
  undefine([AC_DECL_YYTEXT])
  dnl Replacement for AC_DECL_YYTEXT.
  LEX_OUTPUT_ROOT=lex.yy
  AC_SUBST(LEX_OUTPUT_ROOT)
])
