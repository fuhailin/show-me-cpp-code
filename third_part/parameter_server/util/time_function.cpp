
#include "time_function.h"

#include <sys/timeb.h>
#include <time.h>

#include <chrono>
#include <iostream>
char* log_Time(void) {
  struct tm* ptm;
  struct timeb stTimeb;
  static char szTime[19];

  ftime(&stTimeb);
  ptm = localtime(&stTimeb.time);
  sprintf(szTime, "%02d-%02d %02d:%02d:%02d.%03d", ptm->tm_mon + 1,
          ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec,
          stTimeb.millitm);
  szTime[18] = 0;
  return szTime;
}

double Time_tag(void) {
  return (double)std::chrono::duration_cast<std::chrono::duration<double>>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}