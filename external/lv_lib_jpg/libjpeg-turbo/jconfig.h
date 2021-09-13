/* Version ID for the JPEG library.
 * Might be useful for tests like "#if JPEG_LIB_VERSION >= 60".
 */
#define JPEG_LIB_VERSION  62

/* libjpeg-turbo version */
#define LIBJPEG_TURBO_VERSION  2.0.2

/* libjpeg-turbo version in integer form */
#define LIBJPEG_TURBO_VERSION_NUMBER  2000002

/* Support arithmetic encoding */
#define C_ARITH_CODING_SUPPORTED 0

/* Support arithmetic decoding */
#define D_ARITH_CODING_SUPPORTED 1

/* Support in-memory source/destination managers */
#define MEM_SRCDST_SUPPORTED 1

/* Use accelerated SIMD routines. */
// #cmakedefine WITH_SIMD 1

/*
 * Define BITS_IN_JSAMPLE as either
 *   8   for 8-bit sample values (the usual setting)
 *   12  for 12-bit sample values
 * Only 8 and 12 are legal data precisions for lossy JPEG according to the
 * JPEG standard, and the IJG code does not support anything else!
 * We do not support run-time selection of data precision, sorry.
 */

#define BITS_IN_JSAMPLE  8      /* use 8 or 12 */

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1
#if HAVE_LOCALE_H
#include <locale.h>
#endif

/* Define to 1 if you have the <stddef.h> header file. */
#define HAVE_STDDEF_H 1
#if HAVE_STDDEF_H
#include <stddef.h>
#endif

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1
#if HAVE_STDLIB_H
#include <stdlib.h>
#include <stdio.h>
#endif

/* Define if you need to include <sys/types.h> to get size_t. */
#define NEED_SYS_TYPES_H 1
#if NEED_SYS_TYPES_H
#include <sys/types.h>
#endif

/* Define if you have BSD-like bzero and bcopy in <strings.h> rather than
   memset/memcpy in <string.h>. */
//#undef NEED_BSD_STRINGS 0
//#if NEED_BSD_STRINGS
//#include <string.h>
//#endif

/* Define to 1 if the system has the type `unsigned char'. */
#define HAVE_UNSIGNED_CHAR 1

/* Define to 1 if the system has the type `unsigned short'. */
#define HAVE_UNSIGNED_SHORT 1

/* Compiler does not support pointers to undefined structures. */
// #cmakedefine INCOMPLETE_TYPES_BROKEN 1

/* Define if your (broken) compiler shifts signed values as if they were
   unsigned. */
// #cmakedefine RIGHT_SHIFT_IS_UNSIGNED 1

/* Define to 1 if type `char' is unsigned and you are not using gcc.  */
#ifndef __CHAR_UNSIGNED__
  // #cmakedefine __CHAR_UNSIGNED__ 1
#endif

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

#define QGLOBAL_H

