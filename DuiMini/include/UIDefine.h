/** @file
 * Define macro.
 *
 * @author  MXWXZ
 * @date    2019/03/09
 */
#ifndef DUI_UIDEFINE_H_
#define DUI_UIDEFINE_H_

#include <cstring>

/**
 * Library export/import define.
 * Add [UILIB_STATIC] as a preprocessor definition if you use static library.
 * @warning     Never add definition [UILIB_EXPORT] in your program!
 */
#ifdef UILIB_STATIC
#    define DUIMINI_API
#else
#    ifdef WIN32
#        if defined(UILIB_EXPORT)
#            define DUIMINI_API __declspec(dllexport)
#        else
#            define DUIMINI_API __declspec(dllimport)
#        endif
#    else  // Linux, FreeBSD, Mac OS X
#        if __GNUC__ >= 4
#            define DUIMINI_API __attribute__((__visibility__("default")))
#        else
#            define DUIMINI_API
#        endif
#    endif
#endif

#define DUIMINI_VERSION "0.1.0"                  //!< UI library version
#define DUIMINI_DEFAULT_CONFIGFILE "config.xml"  //!< default config file

typedef unsigned int uint;

#define CMPSTR(x, y) strcmp(x, y) == 0

#endif  // !DUI_UIDEFINE_H_
