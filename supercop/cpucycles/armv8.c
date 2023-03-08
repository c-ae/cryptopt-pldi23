/*
cpucycles/armv8.c version 20211110
D. J. Bernstein
Public domain.
*/

#include <time.h>
#include <sys/time.h>
#include <sys/types.h>

long long cpucycles_armv8(void)
{
  long long result;
  asm volatile("mrs %0, PMCCNTR_EL0" : "=r" (result));
  return result;
}

static long long microseconds(void)
{
  struct timeval t;
  gettimeofday(&t,(struct timezone *) 0);
  return t.tv_sec * (long long) 1000000 + t.tv_usec;
}

static double guessfreq(void)
{
  long long tb0; long long us0;
  long long tb1; long long us1;

  tb0 = cpucycles_armv8();
  us0 = microseconds();
  do {
    tb1 = cpucycles_armv8();
    us1 = microseconds();
  } while (us1 - us0 < 10000 || tb1 - tb0 < 1000);
  if (tb1 <= tb0) return 0;
  tb1 -= tb0;
  us1 -= us0;
  return ((double) tb1) / (0.000001 * (double) us1);
}

static long long cpufrequency = 0;

static void init(void)
{
  double guess1;
  double guess2;
  int loop;

  for (loop = 0;loop < 100;++loop) {
    guess1 = guessfreq();
    guess2 = guessfreq();
    if (guess1 > 1.01 * guess2) continue;
    if (guess2 > 1.01 * guess1) continue;
    cpufrequency = 0.5 * (guess1 + guess2);
    break;
  }
}

long long cpucycles_armv8_persecond(void)
{
  if (!cpufrequency) init();
  return cpufrequency;
}
