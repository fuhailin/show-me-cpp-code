#ifndef CCTEST_H_
#define CCTEST_H_

#include <stdio.h>
#include <string.h>

#include "double-conversion/utils.h"

#ifndef TEST
#define TEST(Name)                                                       \
  static void Test##Name();                                              \
  CcTest register_test_##Name(Test##Name, __FILE__, #Name, NULL, true);  \
  static void Test##Name()
#endif

#ifndef DEPENDENT_TEST
#define DEPENDENT_TEST(Name, Dep)                                        \
  static void Test##Name();                                              \
  CcTest register_test_##Name(Test##Name, __FILE__, #Name, #Dep, true);  \
  static void Test##Name()
#endif

#ifndef DISABLED_TEST
#define DISABLED_TEST(Name)                                              \
  static void Test##Name();                                              \
  CcTest register_test_##Name(Test##Name, __FILE__, #Name, NULL, false); \
  static void Test##Name()
#endif

#define CHECK(condition) CheckHelper(__FILE__, __LINE__, #condition, condition)
#define CHECK_GE(a, b) CHECK((a) >= (b))

static inline void CheckHelper(const char* file,
                               int line,
                               const char* source,
                               bool condition) {
  if (!condition) {
    printf("%s:%d:\n CHECK(%s) failed\n", file, line, source);
    abort();
  }
}

#define CHECK_EQ(a, b) CheckEqualsHelper(__FILE__, __LINE__, #a, a, #b, b)

static inline void CheckEqualsHelper(const char* file, int line,
                                     const char* expected_source,
                                     const char* expected,
                                     const char* value_source,
                                     const char* value) {
  if ((expected == NULL && value != NULL) ||
      (expected != NULL && value == NULL)) {
    abort();
  }

  if ((expected != NULL && value != NULL && strcmp(expected, value) != 0)) {
    printf("%s:%d:\n CHECK_EQ(%s, %s) failed\n"
           "#  Expected: %s\n"
           "#  Found:    %s\n",
           file, line, expected_source, value_source, expected, value);
    abort();
  }
}

static inline void CheckEqualsHelper(const char* file, int line,
                                     const char* expected_source,
                                     int expected,
                                     const char* value_source,
                                     int value) {
  if (expected != value) {
    printf("%s:%d:\n CHECK_EQ(%s, %s) failed\n"
           "#  Expected: %d\n"
           "#  Found:    %d\n",
           file, line, expected_source, value_source, expected, value);
    abort();
  }
}

static inline void CheckEqualsHelper(const char* file, int line,
                                     const char* expected_source,
                                     double expected,
                                     const char* value_source,
                                     double value) {
  // If expected and value are NaNs then expected != value.
  if (expected != value && (expected == expected || value == value)) {
    printf("%s:%d:\n CHECK_EQ(%s, %s) failed\n"
           "#  Expected: %.30e\n"
           "#  Found:    %.30e\n",
           file, line, expected_source, value_source, expected, value);
    abort();
  }
}


class CcTest {
 public:
  typedef void (TestFunction)();
  CcTest(TestFunction* callback, const char* file, const char* name,
         const char* dependency, bool enabled);
  void Run() { callback_(); }
  static int test_count();
  static CcTest* last() { return last_; }
  CcTest* prev() { return prev_; }
  const char* file() const { return file_; }
  const char* name() const { return name_; }
  const char* dependency() const { return dependency_; }
  bool enabled() const { return enabled_; }
 private:
  TestFunction* callback_;
  const char* file_;
  const char* name_;
  const char* dependency_;
  bool enabled_;
  static CcTest* last_;
  CcTest* prev_;
};

#endif  // ifndef CCTEST_H_