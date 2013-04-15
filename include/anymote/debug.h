#ifndef _MPILOTE_DEBUG__
#define _MPILOTE_DEBUG__

#ifndef log
#ifdef DEBUG
#define log printf
#else
#define log(...)
#endif
#endif

#endif
