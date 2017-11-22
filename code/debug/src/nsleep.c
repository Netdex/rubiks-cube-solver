#include "nsleep.h"
#include <stddef.h>
void nsleep(long long n) {
    long long s = n / 1000000000L;
    long long ns = n % 1000000000L;

    const struct timespec delay = {s, ns};

    nanosleep(&delay, NULL);
}
