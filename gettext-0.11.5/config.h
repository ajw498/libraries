/* config.h.  Generated automatically by configure.  */
/* config.h.in.  Generated automatically from configure.in by autoheader.  */


/* Default value for alignment of strings in .mo file.  */
#define DEFAULT_OUTPUT_ALIGNMENT 1

#ifndef PARAMS
# if __STDC__ || defined __GNUC__ || defined __SUNPRO_C || defined __cplusplus || __PROTOTYPES
#  define PARAMS(args) args
# else
#  define PARAMS(args) ()
# endif
#endif


/* Define if the `closedir' function returns void instead of `int'. */
#define CLOSEDIR_VOID 1

/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
/* #undef CRAY_STACKSEG_END */

/* Define if using `alloca.c'. */
/* #undef C_ALLOCA */

/* Define to 1 if libexpat shall be dynamically loaded via dlopen(). */
/* #undef DYNLOAD_LIBEXPAT */

/* Define to 1 if translation of program messages to the user's native
   language is requested. */
#define ENABLE_NLS 1

/* Define if you have `alloca', as a function or macro. */
#define HAVE_ALLOCA 1

/* Define if you have <alloca.h> and it should be used (not on Ultrix). */
#define HAVE_ALLOCA_H 1

/* Define if you have the <argz.h> header file. */
/* #undef HAVE_ARGZ_H */

/* Define if you have the <arpa/inet.h> header file. */
#define HAVE_ARPA_INET_H 1

/* Define if backslash-a works in C strings. */
#define HAVE_C_BACKSLASH_A 1

/* Define if the GNU dcgettext() function is already present or preinstalled.
   */
/* #undef HAVE_DCGETTEXT */

/* Define to 1 if you have the declaration of wcwidth(), and to 0 otherwise.
   */
#define HAVE_DECL_WCWIDTH 1

/* Define if you have the <dirent.h> header file, and it defines `DIR'. */
#define HAVE_DIRENT_H 1

/* Define if you have the <dlfcn.h> header file. */
/* #undef HAVE_DLFCN_H */

/* Define if you don't have `vprintf' but do have `_doprnt.' */
/* #undef HAVE_DOPRNT */

/* Define if you have the declaration of environ. */
#define HAVE_ENVIRON_DECL 1

/* Define if you have the declaration of errno. */
#define HAVE_ERRNO_DECL 1

/* Define to 1 if you have the functions error() and error_at_line(). */
/* #undef HAVE_ERROR_AT_LINE */

/* Define if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define if you have the `feof_unlocked' function. */
/* #undef HAVE_FEOF_UNLOCKED */

/* Define if you have the `fgets_unlocked' function. */
/* #undef HAVE_FGETS_UNLOCKED */

/* Define if you have <fnmatch.h> and a working fnmatch() function. */
/* #undef HAVE_FNMATCH */

/* Define if you have the `fork' function. */
/* #undef HAVE_FORK */

/* Define if you have the `getcwd' function. */
#define HAVE_GETCWD 1

/* Define if you have the `getc_unlocked' function. */
/* #undef HAVE_GETC_UNLOCKED */

/* Define if you have the `getdelim' function. */
#define HAVE_GETDELIM 1

/* Define if you have the `getegid' function. */
#define HAVE_GETEGID 1

/* Define if you have the `geteuid' function. */
#define HAVE_GETEUID 1

/* Define if you have the `getgid' function. */
#define HAVE_GETGID 1

/* Define if you have the `gethostbyname' function. */
#define HAVE_GETHOSTBYNAME 1

/* Define if you have the `gethostname' function. */
#define HAVE_GETHOSTNAME 1

/* Define if you have the `getpagesize' function. */
#define HAVE_GETPAGESIZE 1

/* Define if the GNU gettext() function is already present or preinstalled. */
/* #undef HAVE_GETTEXT */

/* Define if you have the `gettimeofday' function. */
#define HAVE_GETTIMEOFDAY 1

/* Define if you have the `getuid' function. */
#define HAVE_GETUID 1

/* Define if you have the iconv() function. */
/* #undef HAVE_ICONV */

/* Define if you have the `inet_ntop' function. */
#define HAVE_INET_NTOP 1

/* Define if <inttypes.h> exists and doesn't clash with <sys/types.h>. */
#define HAVE_INTTYPES_H 1

/* Define if <inttypes.h> exists, doesn't clash with <sys/types.h>, and
   declares uintmax_t. */
/* #undef HAVE_INTTYPES_H_WITH_UINTMAX */

/* Define if <sys/socket.h> defines AF_INET6. */
#define HAVE_IPV6 1

/* Define if you have the `isascii' function. */
#define HAVE_ISASCII 1

/* Define if you have the `iswcntrl' function. */
/* #undef HAVE_ISWCNTRL */

/* Define if you have the `iswprint' function. */
/* #undef HAVE_ISWPRINT */

/* Define if you have <langinfo.h> and nl_langinfo(CODESET). */
/* #undef HAVE_LANGINFO_CODESET */

/* Define if your <locale.h> file defines LC_MESSAGES. */
#define HAVE_LC_MESSAGES 1

/* Define if you have the expat library. */
#define HAVE_LIBEXPAT 1

/* Define if you have the <limits.h> header file. */
#define HAVE_LIMITS_H 1

/* Define if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define if you support file names longer than 14 characters. */
#define HAVE_LONG_FILE_NAMES 1

/* Define if you have the <malloc.h> header file. */
#define HAVE_MALLOC_H 1

/* Define if you have the `mblen' function. */
#define HAVE_MBLEN 1

/* Define to 1 if mbrtowc and mbstate_t are properly declared. */
#define HAVE_MBRTOWC 1

/* Define if you have the `mbsinit' function. */
#define HAVE_MBSINIT 1

/* Define if you have the `memcpy' function. */
#define HAVE_MEMCPY 1

/* Define if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define if you have the `mempcpy' function. */
/* #undef HAVE_MEMPCPY */

/* Define if you have the `memset' function. */
#define HAVE_MEMSET 1

/* Define if you have the `mkdtemp' function. */
/* #undef HAVE_MKDTEMP */

/* Define if you have a working `mmap' system call. */
/* #undef HAVE_MMAP */

/* Define if you have the `munmap' function. */
#define HAVE_MUNMAP 1

/* Define if you have the <ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_NDIR_H */

/* Define if you have the <nl_types.h> header file. */
/* #undef HAVE_NL_TYPES_H */

/* Define if you have the `pathconf' function. */
#define HAVE_PATHCONF 1

/* Define to 1 if you have the sigset_t type and the sigprocmask function. */
#define HAVE_POSIX_SIGNALBLOCKING 1

/* Define if you have the `posix_spawn' function. */
/* #undef HAVE_POSIX_SPAWN */

/* Define if the system has the type `ptrdiff_t'. */
#define HAVE_PTRDIFF_T 1

/* Define if you have the `putc_unlocked' function. */
/* #undef HAVE_PUTC_UNLOCKED */

/* Define if you have the `putenv' function. */
#define HAVE_PUTENV 1

/* Define if you have the `raise' function. */
#define HAVE_RAISE 1

/* Define if you have the <search.h> header file. */
/* #undef HAVE_SEARCH_H */

/* Define if you have the `select' function. */
#define HAVE_SELECT 1

/* Define if you have the `setenv' function. */
#define HAVE_SETENV 1

/* Define if you have the `setlocale' function. */
#define HAVE_SETLOCALE 1

/* Define to 1 if <signal.h> defines the siginfo_t type, and struct sigaction
   has the sa_sigaction member and the SA_SIGINFO flag. */
/* #undef HAVE_SIGINFO */

/* Define if you have a working <stdbool.h> header file. */
/* #undef HAVE_STDBOOL_H */

/* Define if you have the <stddef.h> header file. */
#define HAVE_STDDEF_H 1

/* Define if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define if <stdint.h> exists, doesn't clash with <sys/types.h>, and declares
   uintmax_t. */
#define HAVE_STDINT_H_WITH_UINTMAX 1

/* Define if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define if you have the `stpcpy' function. */
#define HAVE_STPCPY 1

/* Define if you have the `strcasecmp' function. */
#define HAVE_STRCASECMP 1

/* Define if you have the `strcspn' function. */
#define HAVE_STRCSPN 1

/* Define if you have the `strdup' function. */
#define HAVE_STRDUP 1

/* Define if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define if you have the `strncasecmp' function. */
#define HAVE_STRNCASECMP 1

/* Define if you have the `strpbrk' function. */
#define HAVE_STRPBRK 1

/* Define if you have the `strstr' function. */
#define HAVE_STRSTR 1

/* Define if you have the `strtoul' function. */
#define HAVE_STRTOUL 1

/* Define if you have the <sys/dir.h> header file, and it defines `DIR'. */
/* #undef HAVE_SYS_DIR_H */

/* Define if you have the <sys/ndir.h> header file, and it defines `DIR'. */
/* #undef HAVE_SYS_NDIR_H */

/* Define if you have the <sys/param.h> header file. */
#define HAVE_SYS_PARAM_H 1

/* Define if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define if you have the <time.h> header file. */
#define HAVE_TIME_H 1

/* Define if you have the `tsearch' function. */
/* #undef HAVE_TSEARCH */

/* Define if you have the `uname' function. */
#define HAVE_UNAME 1

/* Define if <sys/wait.h> defines the 'union wait' type. */
/* #undef HAVE_UNION_WAIT */

/* Define if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define if you have the `unsetenv' function. */
#define HAVE_UNSETENV 1

/* Define if you have the unsigned long long type. */
#define HAVE_UNSIGNED_LONG_LONG 1

/* Define if you have the `utime' function. */
#define HAVE_UTIME 1

/* Define if you have the `utimes' function. */
#define HAVE_UTIMES 1

/* Define if you have the <values.h> header file. */
/* #undef HAVE_VALUES_H */

/* Define if you have the `vasprintf' function. */
/* #undef HAVE_VASPRINTF */

/* Define if you have the `vfork' function. */
#define HAVE_VFORK 1

/* Define if you have the <vfork.h> header file. */
/* #undef HAVE_VFORK_H */

/* Define if you have the `vprintf' function. */
#define HAVE_VPRINTF 1

/* Define if you have the `waitpid' function. */
#define HAVE_WAITPID 1

/* Define if you have the <wchar.h> header file. */
#define HAVE_WCHAR_H 1

/* Define if you have the <wctype.h> header file. */
/* #undef HAVE_WCTYPE_H */

/* Define if you have the `wcwidth' function. */
#define HAVE_WCWIDTH 1

/* Define if `fork' works. */
/* #undef HAVE_WORKING_FORK */

/* Define if `vfork' works. */
#define HAVE_WORKING_VFORK 1

/* Define if you have the `__argz_count' function. */
/* #undef HAVE___ARGZ_COUNT */

/* Define if you have the `__argz_next' function. */
/* #undef HAVE___ARGZ_NEXT */

/* Define if you have the `__argz_stringify' function. */
/* #undef HAVE___ARGZ_STRINGIFY */

/* Define if you have the `__secure_getenv' function. */
/* #undef HAVE___SECURE_GETENV */

/* Define as const if the declaration of iconv() needs const. */
/* #undef ICONV_CONST */

/* Define if integer division by zero raises signal SIGFPE. */
#define INTDIV0_RAISES_SIGFPE 0

/* Name of package */
#define PACKAGE "gettext"

/* Define if <inttypes.h> exists and defines unusable PRI* macros. */
/* #undef PRI_MACROS_BROKEN */

/* Define as const if the declaration of setlocale() needs const. */
#define SETLOCALE_CONST const

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at run-time.
        STACK_DIRECTION > 0 => grows toward higher addresses
        STACK_DIRECTION < 0 => grows toward lower addresses
        STACK_DIRECTION = 0 => direction of growth unknown */
/* #undef STACK_DIRECTION */

/* Define if the `S_IS*' macros in <sys/stat.h> do not work properly. */
/* #undef STAT_MACROS_BROKEN */

/* Define if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "0.11.5"

/* Make sure we see all GNU extensions. */
#define _GNU_SOURCE 1

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to a replacement function name for fnmatch(). */
#define fnmatch posix_fnmatch

/* Define to a replacement function name for getline(). */
#define getline gnu_getline

/* Define as `__inline' if that's what the C compiler calls it, or to nothing
   if it is not supported. */
/* #undef inline */

/* Define to a type if <wchar.h> does not define. */
/* #undef mbstate_t */

/* Define to `long' if <sys/types.h> does not define. */
/* #undef off_t */

/* Define to `int' if <sys/types.h> does not define. */
/* #undef pid_t */

/* Define to empty if the C compiler doesn't support this keyword. */
/* #undef signed */

/* Define to `unsigned' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define as a signed type of the same size as size_t. */
/* #undef ssize_t */

/* Define to unsigned long or unsigned long long if <inttypes.h> and
   <stdint.h> don't define. */
/* #undef uintmax_t */

/* Define as `fork' if `vfork' does not work. */
/* #undef vfork */


/* We don't test for the basename function but still want to use the
   version in the libc when compiling for a system using glibc.  Likewise
   for stpncpy.  */
#ifdef __GNU_LIBRARY__
# define HAVE_BASENAME	1
# define HAVE_STPNCPY	1
#endif

/* A file name cannot consist of any character possible.  INVALID_PATH_CHAR
   contains the characters not allowed.  */
#ifndef MSDOS
# define	INVALID_PATH_CHAR "\1\2\3\4\5\6\7\10\11\12\13\14\15\16\17\20\21\22\23\24\25\26\27\30\31\32\33\34\35\36\37 \177/"
#else
/* Something like this for MSDOG.  */
# define	INVALID_PATH_CHAR "\1\2\3\4\5\6\7\10\11\12\13\14\15\16\17\20\21\22\23\24\25\26\27\30\31\32\33\34\35\36\37 \177\\:."
#endif

/* This is the page width for the message_print function.  It should
   not be set to more than 79 characters (Emacs users will appreciate
   it).  It is used to wrap the msgid and msgstr strings, and also to
   wrap the file position (#:) comments.  */
#define PAGE_WIDTH 79

/* Extra OS/2 (emx+gcc) defines.  */
#ifdef __EMX__
# include "intl/os2compat.h"
#endif

