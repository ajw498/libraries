#ifndef x_H
#define x_H

/* x.h - exception handling header */
// Revision History:
//    	      From OSLib
// 970926 TV  Strongarm Compatible version
//

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>

#ifndef os_H
   #include "oslib/os.h"
#endif

#define x_MAXDEPTH 256
//#define TRACE 0

typedef struct x_exception
{
  void (*previous [3]) (int);
  os_error *error;
  jmp_buf buf;
}
x_exception;

#ifdef __cplusplus
extern "C"
{
#endif

/* (Pseudo-)function to be called before a group of statements which
 * could throw an exception.
 */

#define x_TRY(x) \
      if (x__try (x), setjmp ((x)->buf) == NULL)
extern void x__try (x_exception *);

/* Function to allow the exception type to be examined. MUST be
 * called to balance a call to x_TRY.
 */

#define x_CATCH(x) \
      if (x__catch (x), (x)->error != NULL)
extern void x__catch (x_exception *);

/* Function to re-throw exceptions. Used in exception handlers or in tidy-
 * up code to throw the error to the next-higher level that needs it. If
 * there was no exception, this does nothing.
 */

#define x_RETHROW(x) \
      (((x)->error) != NULL ? ((void)os_generate_error((x)->error)):((void) SKIP))

/* Strange pseudo-declaration thing to make an |os_error *| from an error
 * number and a message. Declares |id| to be an |os_error *| pointing at the
 * block {num, mess}, without wasting 252 bytes of empty error block. Can
 * also be used if you want an international message that will be passed to
 * messagetrans_error_lookup.
 */

#define x_LOCAL_ERROR(id, num, mess) \
   static struct {int errnum; char errmess [sizeof mess + 1];} id ## _ = \
         {num, mess}; \
   static os_error *id = (os_error *) &id ## _

/* Another declaration, to make an |os_error *| from an error
 * number and a message. Declares |id| to be an |os_error *| pointing at the
 * block {num, mess}, without wasting 252 bytes of empty error block. Can
 * also be used if you want an international message that will be passed to
 * messagetrans_error_lookup.
 */

#define x_GLOBAL_ERROR(id, num, mess) \
   static struct {int errnum; char errmess [sizeof mess + 1];} id ## _ = \
         {num, mess}; \
   os_error *id = (os_error *) &id ## _;

/* Function to throw exceptions. Used anywhere that obtains an
 * |os_error *| (usually from x_LOCAL_ERROR), and wants to turn it into an
 * exception. Undefined if its argument is NULL.
 */

#define x_THROW(error) \
   os_generate_error (error)

/* Function to throw an error after one has been detected by the run-time
 * system. Use after (e g) fopen, printf fail.
 */

#define x_THROW_LAST_ERROR() \
   os_generate_error (x__last_error ())
extern os_error *x__last_error (void);

/* Function to give the error responsible. Useful only at the top, where the
 * error is be reported.
 */

#define x_ERROR(x) ((x)->error)

/* Function to exit from the programme, with an appropriate message and
 * return value (not useful for desktop programmes).
 */

#define x_EXIT(x) \
   (  (x)->error != NULL? \
      (  fprintf (stderr, "%s\n", (x)->error->errmess), \
         exit (EXIT_FAILURE) \
      ): \
      exit (0) \
   )

/* Function to exit from a desktop programme with an appropriate message and
 * return value.
 */

#define x_REPORT_EXIT(x, programme) \
   (  (x)->error != NULL? \
      (  wimp_report_error ((x)->error, NONE, programme), \
         exit (EXIT_FAILURE) \
      ): \
      exit (0) \
   )

/* A set of functions to do exception-throwing memory allocation. If they
 * return, they have succeeded, so they can be used in expressions, etc.
 */

extern os_error *x_no_memory;

#if 0
#if TRACE
   #define x_ALLOC(size)                  x__alloc (size)
   #define x_CALLOC(count, size)          x__calloc (count, size)
   #define x_FREE(ptr, size)              x__free (ptr, size)
   #define x_REALLOC(ptr, old_size, size) x__realloc (ptr, old_size, size)
#endif
#else
   #define x_ALLOC(size)                  x__alloc (size)
   #define x_CALLOC(count, size)          x__calloc (count, size)
   #define x_FREE(ptr)                	  x__free (ptr, 0)
   #define x_REALLOC(ptr, size)       	  x__realloc (ptr, 0, size)
#endif

extern void *x__alloc (int size);
extern void *x__calloc (int count, int size);
extern void x__free (void *ptr, int size);
extern void *x__realloc (void *ptr, int old_size, int size);

#ifdef __cplusplus
}
#endif

#endif
