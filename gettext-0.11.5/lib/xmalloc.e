# 1 "xmalloc.c"
 
# 17 "xmalloc.c"


# 1 "../config.h" 1
 
 


 











 


 


 

 
 

 
 

 



 


 


 
 

 


 


 

 

 



 


 
 

 
 

 


 


 
 

 


 
 

 
 

 
 

 
 

 


 
 

 


 


 


 


 


 


 


 
 

 


 


 
 

 


 


 

 

 


 


 
 

 
 

 
 

 


 


 


 


 


 


 


 


 


 


 


 
 

 


 
 

 
 

 


 
 

 
 

 


 


 
 

 


 
 

 


 


 
 

 


 


 


 

 

 
 

 


 


 



 


 


 


 


 


 


 


 


 


 


 


 


 
 

 
 

 


 


 


 


 


 
 

 


 
 

 


 


 


 


 


 
 

 
 

 


 
 

 


 


 


 
 

 


 
 

 


 
 

 
 

 
 

 
 

 
 

 


 


 
 

 


 





 

 
 

 


 


 


 
 

 


 


 

 

 
 

 
 

 
 

 
 

 
 

 
 

 

 

 
 


 







 








 





 




# 19 "xmalloc.c" 2



 
# 1 "xmalloc.h" 1
 
# 18 "xmalloc.h"




# 1 "/home/riscos/cross-7.7.2002/include/unixlib/stddef.h" 1
 
# 10 "/home/riscos/cross-7.7.2002/include/unixlib/stddef.h"
















 






typedef int ptrdiff_t;



 












typedef unsigned int size_t;





 








typedef int wchar_t;










typedef unsigned int wint_t;



 











typedef void *ptr_t;

 











# 22 "xmalloc.h" 2



 

 
extern void *xmalloc (size_t size);

 
extern void *xcalloc (size_t nmemb, size_t size);

 

extern void *xrealloc (void *ptr, size_t size);


 

 
extern char *xstrdup (const char *string);



# 23 "xmalloc.c" 2


# 1 "/home/riscos/cross-7.7.2002/include/unixlib/stdlib.h" 1
 
# 10 "/home/riscos/cross-7.7.2002/include/unixlib/stdlib.h"

 





# 1 "/home/riscos/cross-7.7.2002/include/unixlib/unixlib/features.h" 1
 
# 10 "/home/riscos/cross-7.7.2002/include/unixlib/unixlib/features.h"

 



 
# 37 "/home/riscos/cross-7.7.2002/include/unixlib/unixlib/features.h"





 
# 103 "/home/riscos/cross-7.7.2002/include/unixlib/unixlib/features.h"


 




















 

# 138 "/home/riscos/cross-7.7.2002/include/unixlib/unixlib/features.h"


 







 



















 









 








 

# 197 "/home/riscos/cross-7.7.2002/include/unixlib/unixlib/features.h"





































































 



 



 




 

















 




 




 







 








 








 








 










 







 




 






 










 











 

















 

 



 



 





 




 





 




 




 




 




 


extern int __feature_imagefs_is_file;


# 17 "/home/riscos/cross-7.7.2002/include/unixlib/stdlib.h" 2






# 1 "/home/riscos/cross-7.7.2002/include/unixlib/stddef.h" 1
 
# 10 "/home/riscos/cross-7.7.2002/include/unixlib/stddef.h"

# 99 "/home/riscos/cross-7.7.2002/include/unixlib/stddef.h"







# 23 "/home/riscos/cross-7.7.2002/include/unixlib/stdlib.h" 2


 
  
 
typedef struct
  {
    int quot;	 
    int rem;	 
  } div_t;

 
typedef struct
  {
    long int quot;	 
    long int rem;	 
  } ldiv_t;


 
__extension__
typedef struct
  {
    long long int quot;	 
    long long int rem;	 
  } lldiv_t;


 



 

 


 


 
extern void abort (void)  ;

 
extern int atexit (void (*__atexit_function) (void));

 

extern void exit (int __status)  ;

 
extern char *getenv (const char *__name);

 

extern int setenv (const char *__name, const char *__value, int __replace);

 
extern void unsetenv (const char *__name);

 


extern int clearenv (void);

 
extern int putenv (const char *__string);

 
extern int system (const char *__command);

 
extern char *realpath (const char *__file_name, char *__resolved_name);

# 107 "/home/riscos/cross-7.7.2002/include/unixlib/stdlib.h"


 

extern void *calloc (size_t __nmemb, size_t __size);

 
extern void free (void *__ptr);

 
extern void *malloc (size_t __size);

 

extern void *realloc (void *__ptr, size_t __size);

 
extern void *valloc (size_t __bytes);

 
extern void *memalign (size_t __alignment, size_t __bytes);
extern void cfree (void *__mem);
extern int malloc_trim (size_t);

 
extern int rand (void);

 
extern void srand (long __seed);

 
extern long int random (void);

 
extern void srandom (unsigned int __seed);

 



extern char *initstate (unsigned int __seed, char *__statebuf,
                        size_t __statelen);

 

extern char *setstate (char *__statebuf);

 
extern int abs (int __x)  ;
extern long int	labs (long int __x)  ;

 
extern div_t div (int __numer, int __denom)  ;
extern ldiv_t ldiv (long __numer, long __denom)  ;

__extension__
extern lldiv_t lldiv (long long __numer, long long __denom)  ;


 
extern double atof (const char *__string);


 
extern int atoi (const char *__string);


 
extern long atol (const char *__string);


 
extern double strtod (const char *__string, char **__end);

 
extern long strtol (const char *__nptr, char **__endptr, int __base);

 
extern unsigned long strtoul (const char *__nptr,
			      char **__endptr, int __base);


 
__extension__
extern long long strtoll (const char *__nptr, char **__endptr, int __base);

 
__extension__
extern unsigned long long strtoull (const char *__nptr,
				    char **__endptr, int __base);


 


extern void *bsearch (const void *__key, const void *__base,
		      size_t __nmemb, size_t __size,
		      int (*__compare)(const void *, const void *));

 

extern void qsort (void *__base, size_t __nmemb, size_t __size,
		   int (*__compare)(const void *,const void *));

 

extern int mblen (const char *__s, size_t __n);
extern size_t mbstowcs (wchar_t *__wchar, const char *__s, size_t __n);
extern int mbtowc (wchar_t *__wchar, const char *__s, size_t __n);
extern size_t wcstombs (char *__s, const wchar_t *__wchar, size_t __n);
extern int wctomb (char *__s, wchar_t __wchar);


# 1 "/home/riscos/cross-7.7.2002/include/unixlib/alloca.h" 1
 
# 10 "/home/riscos/cross-7.7.2002/include/unixlib/alloca.h"












 

 
extern void *alloca (size_t);

 


# 220 "/home/riscos/cross-7.7.2002/include/unixlib/stdlib.h" 2



 
extern char *__dtoa(double __d, int __mode, int __ndigits,
		    int *__decpt, int *__sign, char **__rve);

 

extern int getsubopt (char **__option, const char *const *__tokens,
		      char **__value);
extern char *suboptarg;

 

 

extern double drand48 (void);
extern double erand48 (unsigned short int __xsubi[3]);

 
extern long int lrand48 (void);
extern long int nrand48 (unsigned short int __xsubi[3]);

 
extern long int mrand48 (void);
extern long int jrand48 (unsigned short int __xsubi[3]);

 
extern void srand48 (long int __seedval);
extern unsigned short int *seed48 (unsigned short int __seed16v[3]);
extern void lcong48 (unsigned short int __param[7]);

 


# 25 "xmalloc.c" 2


# 1 "error.h" 1
 
# 22 "error.h"




# 37 "error.h"








 



extern void error (int status, int errnum, const char *format, ...)
      ;

extern void error_at_line (int status, int errnum, const char *fname,
			   unsigned int lineno, const char *format, ...)
      ;

 


extern void (*error_print_progname) (void);







 
extern unsigned int error_message_count;

 

extern int error_one_per_line;






# 27 "xmalloc.c" 2

# 1 "exit.h" 1
 
# 17 "exit.h"




 


 








# 28 "xmalloc.c" 2

# 1 "gettext.h" 1
 
# 18 "gettext.h"




 


 
# 1 "../intl/libintl.h" 1
 
# 18 "../intl/libintl.h"




# 1 "/home/riscos/cross-7.7.2002/include/unixlib/locale.h" 1
 
# 10 "/home/riscos/cross-7.7.2002/include/unixlib/locale.h"

 








 

 


 

 


 

 

 

 

 


 




extern char *setlocale (int __category, const char *__locale);

struct lconv
{
   
  char *decimal_point;
   

  char *thousands_sep;
   

  char *grouping;
   
  char *int_curr_symbol;
   
  char *currency_symbol;
   
  char *mon_decimal_point;
   

  char *mon_thousands_sep;
   

  char *mon_grouping;
   
  char *positive_sign;
   
  char *negative_sign;
   


  char int_frac_digits;
  char frac_digits;
   

  char p_cs_precedes;
   

  char p_sep_by_space;
   

  char n_cs_precedes;
   

  char n_sep_by_space;
   
  char p_sign_posn;
   
  char n_sign_posn;
};

 
extern struct lconv *localeconv(void);

# 109 "/home/riscos/cross-7.7.2002/include/unixlib/locale.h"


 


# 22 "../intl/libintl.h" 2


 










 



 




 





 














 
# 91 "../intl/libintl.h"

 













 








 












extern char *gettext (const char *__msgid)
       __asm__ ("\015"  "libintl_gettext");


 











extern char *dgettext (const char *__domainname,
				     const char *__msgid)
# 146 "../intl/libintl.h"
       __asm__ ("\015"  "libintl_dgettext");


 

# 159 "../intl/libintl.h"




extern char *dcgettext (const char *__domainname,
				      const char *__msgid,
				      int __category)
# 166 "../intl/libintl.h"
       __asm__ ("\015"  "libintl_dcgettext");



 

# 180 "../intl/libintl.h"




extern char *ngettext (const char *__msgid1,
				     const char *__msgid2,
				     unsigned long int __n)
# 187 "../intl/libintl.h"
       __asm__ ("\015"  "libintl_ngettext");


 

# 200 "../intl/libintl.h"




extern char *dngettext (const char *__domainname,
				      const char *__msgid1,
				      const char *__msgid2,
				      unsigned long int __n)
# 208 "../intl/libintl.h"
       __asm__ ("\015"  "libintl_dngettext");


 

# 223 "../intl/libintl.h"




extern char *dcngettext (const char *__domainname,
				       const char *__msgid1,
				       const char *__msgid2,
				       unsigned long int __n,
				       int __category)
# 232 "../intl/libintl.h"
       __asm__ ("\015"  "libintl_dcngettext");



 












extern char *textdomain (const char *__domainname)
       __asm__ ("\015"  "libintl_textdomain");


 

# 263 "../intl/libintl.h"




extern char *bindtextdomain (const char *__domainname,
					   const char *__dirname)
# 269 "../intl/libintl.h"
       __asm__ ("\015"  "libintl_bindtextdomain");


 

# 282 "../intl/libintl.h"




extern char *bind_textdomain_codeset (const char *__domainname,
						    const char *__codeset)
# 288 "../intl/libintl.h"
       __asm__ ("\015"  "libintl_bind_textdomain_codeset");








# 26 "gettext.h" 2


# 58 "gettext.h"


 









# 29 "xmalloc.c" 2





 

static void *fixup_null_alloc (size_t n);


 

int xmalloc_exit_failure = 1;

static void *
fixup_null_alloc (n)
     size_t n;
{
  void *p;

  p = 0;
  if (n == 0)
    p = malloc ((size_t) 1);
  if (p == (0))
    error (xmalloc_exit_failure, 0, gettext ("memory exhausted"));
  return p;
}

 

void *
xmalloc (n)
     size_t n;
{
  void *p;

  p = malloc (n);
  if (p == (0))
    p = fixup_null_alloc (n);
  return p;
}

 

void *
xcalloc (n, s)
     size_t n, s;
{
  void *p;

  p = calloc (n, s);
  if (p == (0))
    p = fixup_null_alloc (n);
  return p;
}

 



void *
xrealloc (p, n)
     void *p;
     size_t n;
{
  if (p == (0))
    return xmalloc (n);
  p = realloc (p, n);
  if (p == (0))
    p = fixup_null_alloc (n);
  return p;
}
