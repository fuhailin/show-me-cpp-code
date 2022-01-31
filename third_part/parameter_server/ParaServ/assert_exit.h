#include <assert.h>

#ifndef ASSERT_EXIT
#define ASSERT_EXIT

static void assert_exit(int code) {
  fflush(nullptr);
  assert(0);
  exit(code);
}

#endif