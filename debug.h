#ifndef __DEBUG_H__
#define __DEBUG_H__

#define DEBUG_ENABLED 0

#define DEBUG(x) do { if (DEBUG_ENABLED) dbg_printf x; } while (0)

void dbg_printf(const char *fmt, ...);

#endif // __DEBUG_H__
