
#define __iconv__ 1
#pragma nomargins nosequence
#pragma checkout(suspend)

  /***************************************************************
  * <iconv.h> header file                                        *
  *                                                              *
  * LICENSED MATERIALS - PROPERTY OF IBM                         *
  *                                                              *
  * 5655-ZOS                                                     *
  *                                                              *
  * COPYRIGHT IBM CORP. 1998, 2023                               *
  *                                                              *
  * US GOVERNMENT USERS RESTRICTED RIGHTS - USE,                 *
  * DUPLICATION OR DISCLOSURE RESTRICTED BY GSA ADP              *
  * SCHEDULE CONTRACT WITH IBM CORP.                             *
  *                                                              *
  * STATUS = HLE77E0                                             *
  ***************************************************************/

  #if defined(__IBM_METAL__) 

    #error Language Environment standard C headers \
cannot be used when METAL option is used. \
Correct your header search path.

  #endif /* __IBM_METAL__ */

  #ifdef __cplusplus
  extern "C" {
  #endif


  #ifndef __EDC_LE
    #define __EDC_LE 0x10000000
  #endif

  #if (defined(__clang__) && !defined(__ibmxl__)) || \
      __TARGET_LIB__ >= __EDC_LE 
    #if !defined(__features_h)  || defined(__inc_features)
      #include <features.h>
    #endif
  #endif


  #ifndef __size_t
    #ifdef _LP64
      typedef unsigned long size_t;
    #else
      typedef unsigned int size_t;
    #endif /* _LP64 */
    #define __size_t 1
  #endif

  #ifndef __lc_object
    #define __lc_object 1
    typedef struct {
       #ifdef  _ALL_SOURCE
          unsigned short type_id,
                         magic;
          unsigned int   version;
          size_t         size;
       #else
          unsigned short __type_id,
                         __magic;
          unsigned int   __version;
          size_t         __size;
       #endif
    } _LC_object_t;
  #endif

  /* definition of iconv_t type. */

  typedef struct  __iconv_rec     *iconv_t;

  struct __iconv_rec {
     #ifdef  _ALL_SOURCE
        _LC_object_t hdr;
        void        *data;
        iconv_t     (*open)(const char *, const char *);
        int         (*exec)(iconv_t, char **, size_t *,
                                     char **, size_t *);
        int         (*close)(iconv_t);
     #else
        _LC_object_t __hdr;
        void        *__data;
        iconv_t     (*__open)(const char *, const char *);
        int         (*__exec)(iconv_t, const char **, size_t *,
                              char **, size_t *);
        int         (*__close)(iconv_t);
     #endif
  };

  #ifdef  _ALL_SOURCE

     typedef struct  __iconv_rec     iconv_rec;
     typedef struct _LC_core_iconv_type _LC_core_iconv_t;
     struct _LC_core_iconv_type {

        _LC_object_t      hdr;

        /* implementation initialization */
        void             *data;
        _LC_core_iconv_t *(*init)();
        int              (*exec)();
        int              (*close)();
     };

     #define ICONV_FAILED   ((iconv_t)-1)

  #endif      /*  _ALL_SOURCE  */


  /* methods */

  #ifdef __AE_BIMODAL_F
    #pragma map(__iconv_open_a, "\174\174A00119")
    #pragma map(__iconv_open_e, "\174\174ICONVO")
  #endif  /* __AE_BIMODAL_F */


  #ifdef __NATIVE_ASCII_F

    #pragma map(iconv_open,   "\174\174A00119")

    #ifndef _NO_PRAGMA
      #pragma map (iconv_close, "\174\174ICONVC")
    #endif /* _NO_PRAGMA */

  #else

    #ifndef _NO_PRAGMA
      #pragma map (iconv_open,  "\174\174ICONVO")
      #pragma map (iconv_close, "\174\174ICONVC")
    #endif  /* _NO_PRAGMA */

  #endif  /* __NATIVE_ASCII_F */

  #ifdef __AE_BIMODAL_F
    __new4102(iconv_t, __iconv_open_a,(const char *, const char *));
    __new4102(iconv_t, __iconv_open_e,(const char *, const char *));
  #endif  /* __AE_BIMODAL_F */

  #ifdef _NO_PROTO
    extern iconv_t iconv_open();
    extern size_t  iconv();
    extern int     iconv_close();
  #else
    extern iconv_t iconv_open(const char *, const char *);
   #ifdef ICONV_SENDPARM_CONST
    extern size_t iconv(iconv_t, const char **,
                        size_t *,char **, size_t *);
   #else
    extern size_t iconv(iconv_t, char **__restrict__, size_t *__restrict__,
                        char **__restrict__, size_t *__restrict__); 

   #endif
    extern int     iconv_close(iconv_t);
  #endif

  #define _LC_ICONV     12


  #ifdef __cplusplus
  }
  #endif

#pragma checkout(resume)
