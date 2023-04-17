
#ifndef ___boolean___h____
#define ___boolean___h____

/*
* Type: bool
* ----------
* This type has two values, FALSE and TRUE, which are equal to 0
* and 1, respectively.  Most of the advantage of defining this type
* comes from readability because it allows the programmer to
* provide documentation that a variable will take on only one of
* these two values.  Designing a portable representation, however,
* is surprisingly hard, because many libraries and some compilers
* define these names.  The definitions are usually compatible but
* may still be flagged as errors.
*/

#ifdef THINK_C
   typedef int bool;
#else
#  ifdef TRUE
#    ifndef bool
#      define bool int
#    endif
#  else
#    ifdef bool
#      define FALSE 0
#      define TRUE 1
#    else
       typedef enum {FALSE, TRUE} bool;
#    endif
#  endif
#endif

#endif // #ifndef ___boolean___h____
