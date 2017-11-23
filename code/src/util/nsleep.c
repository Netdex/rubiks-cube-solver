#include "util/nsleep.h"

// Provides an easier way to call nanosleep without having to mess with
// timespec objects in code
void nsleep(long long n) {
    long long s = n / 1000000000L;
    long long ns = n % 1000000000L;

    const struct timespec delay = {s, ns};

    nanosleep(&delay, NULL);
}
