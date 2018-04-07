
#ifndef TLOG_H_
#define TLOG_H_

#define TLOG_LEVEL_ERR    0x00
#define TLOG_LEVEL_WAR    0x01
#define TLOG_LEVEL_INFO   0x02
#define TLOG_LEVEL_DEBUG  0x03

#define TLOG_ROOT_LEVEL   TLOG_LEVEL_DEBUG

#ifndef TLOG_LEVEL
#define TLOG_LEVEL    TLOG_LEVEL_DEBUG
#endif

#ifndef TLOG_TAG
#define TLOG_TAG  "TLOG"
#endif

#define TLOG_NONE       "\033[0m\r"
#define TLOG_RED        "\033[1;31m[E "
#define TLOG_YELLOW     "\033[1;33m[W "
#define TLOG_GREEN      "\033[1;32m[I "
#define TLOG_DEBUG      "\033[0m[D "

#if (TLOG_ROOT_LEVEL >= TLOG_LEVEL_ERR)
#define tprintf_e(tag, fmt, arg...)    printf((char *)TLOG_RED tag " %s:%d] " fmt TLOG_NONE, __FILE__, __LINE__, ##arg)
#else
#define tprintf_e(tag, fmt, arg...)
#endif

#if (TLOG_ROOT_LEVEL >= TLOG_LEVEL_WAR)
#define tprintf_w(tag, fmt, arg...)    printf((char *)TLOG_YELLOW tag " %s:%d] " fmt TLOG_NONE, __FILE__, __LINE__, ##arg)
#else
#define tprintf_w(tag, fmt, arg...)
#endif

#if (TLOG_ROOT_LEVEL >= TLOG_LEVEL_INFO)
#define tprintf_i(tag, fmt, arg...)    printf((char *)TLOG_GREEN tag " %s:%d] " fmt TLOG_NONE, __FILE__, __LINE__, ##arg)
#else
#define tprintf_i(tag, fmt, arg...)
#endif

#if (TLOG_ROOT_LEVEL >= TLOG_LEVEL_DEBUG)
#define tprintf_d(tag, fmt, arg...)    printf((char *)TLOG_DEBUG tag " %s:%d] " fmt TLOG_NONE, __FILE__, __LINE__, ##arg)
#else
#define tprintf_d(tag, fmt, arg...)
#endif

#if (TLOG_LEVEL >= TLOG_LEVEL_ERR)
#define tlog_e(fmt, arg...)   tprintf_e(TLOG_TAG, fmt, ##arg)
#else
#define tlog_e(fmt, arg...)
#endif

#if (TLOG_LEVEL >= TLOG_LEVEL_WAR)
#define tlog_w(fmt, arg...)   tprintf_w(TLOG_TAG, fmt, ##arg)
#else
#define tlog_w(fmt, arg...)
#endif

#if (TLOG_LEVEL >= TLOG_LEVEL_INFO)
#define tlog_i(fmt, arg...)   tprintf_i(TLOG_TAG, fmt, ##arg)
#else
#define tlog_i(fmt, arg...)
#endif

#if (TLOG_LEVEL >= TLOG_LEVEL_DEBUG)
#define tlog_d(fmt, arg...)   tprintf_d(TLOG_TAG, fmt, ##arg)
#else
#define tlog_d(fmt, arg...)
#endif

#define TLOG_E  0x00
#define TLOG_W  0x10
#define TLOG_I  0x20
#define TLOG_D  0x30

#define tlog(_f, tag, level, fmt, arg...) do{                                         \
    if((((level) & 0xF0) >> 4) <= ((level) & 0x0F)) tprintf_##_f(tag, fmt, ##arg);    \
}while(0)

#endif

