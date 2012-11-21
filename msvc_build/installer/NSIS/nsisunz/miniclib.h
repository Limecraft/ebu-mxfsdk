/* Public Domain [mini] c runtime library replacements for Win32 */

/* include this file before or instead of <windows.h>
   as its string functions conflict with string.h
 */

#ifndef _MINI_CRT_LIB_
#define _MINI_CRT_LIB_

#ifdef __cplusplus
extern "C" {
#endif

/* you must call this before using any other function!!! */
void mCRTinit(void);

typedef unsigned long time_t;
typedef unsigned size_t;

extern int errno;

#ifndef NULL
#ifdef  __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

void * malloc(size_t size);
void * calloc(size_t num, size_t size);
void free(void *ptr);
void * realloc(void *ptr, size_t size);
char * strdup(const char *str);
char * strrchr(const char *str, int c);
char *strstr(const char *str, const char *substr);

#define strlen lstrlen
#define strcpy lstrcpy
#define strcat lstrcat
#define strcmp lstrcmp

// MSVC [6&7] Professional+ these are intrinsic
// and this causes a duplicate function error,
// but on Standard they are not intrinsic or if
// forced as functions then these are needed.
#define NO_INTRINSIC_MEMFUNCS 1
#if defined(_MSC_VER) && defined(NO_INTRINSIC_MEMFUNCS)
/* Ensure these are treated as functions and not inlined as intrinsics, or disable /Oi */
#pragma warning(disable:4164)  // intrinsic function not declared
#pragma function(memcpy, memset, memcmp)
#endif
void * memmove(void *s1, const void *s2, size_t n);
void *memcpy(void *s1, const void *s2, size_t n);
void *memset(void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

#define ESUCCESS 0
#define ENOMEM 12
#define EACCES 13
#define EEXIST 17
#define EINVAL 22

#define EOF -1

typedef struct FILE
{ 
  /*HANDLE*/void * handle;
  int eof;        /* used by feof macro to determine if read ended with error or end of file */
  int err;        /* used by ferror macro to indicate error condition encountered */
} FILE;

extern FILE *stdin, *stdout, *stderr;

#define feof(f) f->eof
#define ferror(f) f->err

/* fopen, only r[b],w[b],r[b]+,w[b]+ supported, that is a (append is not) */
FILE * fopen(const char *filename, const char *mode);
size_t fwrite(const void *buffer, long size, long count, FILE *f);
size_t fread(const void *buffer, long size, long count, FILE *f);
int fclose(FILE *f);

int fprintf(FILE *f, const char *format, ...);
int sprintf(char *buf, const char *format, ...);
#define vsprintf wvsprintf
int fputc(int c, FILE *f);

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

int fseek(FILE *f, long offset, int origin);
long ftell(FILE *f);
void rewind(FILE *f);

/* just stubs */
int fflush(FILE *f);
FILE *_fdopen(int handle, const char *mode);

#ifdef __cplusplus
}
#endif

#define WIN32_LEAN_AND_MEAN
#define _INC_STRING		/* don't allow windows.h to include MS clib's string.h */
#define _INC_MEMORY
#include <windows.h>

#endif /* _MINI_CRT_LIB_ */
