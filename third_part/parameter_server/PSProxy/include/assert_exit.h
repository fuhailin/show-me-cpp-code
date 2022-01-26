
#ifndef ASSERT_EXIT
#define ASSERT_EXIT

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <assert.h>

#define SRV_ASSERT(X)\
  do {\
  __assert__(X,__FILE__,__LINE__);\
  } while (0)

inline void __assert__(bool _X_, const char* file, int line)
{
    if (!(_X_))
    {
        //assertPrepare();
#ifdef WIN32
        __asm { int 3}
#else
        raise(SIGABRT);
#endif
    }
}

void assert_exit(int code) {
    fflush(nullptr);
    SRV_ASSERT(0);
    exit(code);
}

#endif
