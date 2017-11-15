/* precompiled header */

#ifndef STDAFX_H
#define STDAFX_H

#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <math.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "util/log.h"

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

#define randr(a,b) (rand() % (b - a) + a)
#define randf() (((float) rand() / (float) (RAND_MAX)))

#endif