
/*
    Copyright 2008 (c) by Cesar Rodriguez Ortega,
    Space Research Group,
    University of Alcala.

    For further information, please visit http://srg.aut.uah.es

    This software is provided under the terms of the GNU General Public v2
    Licence. A full copy of the GNU GPL is provided in the file COPYING
    found in the development root of ERCOS-RT.
*/

#ifndef _EDROOMBP_POSIX_TIMESPEC_H_
#define _EDROOMBP_POSIX_TIMESPEC_H_

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

void timespec_normalize (struct timespec * t);
void timespec_add (struct timespec * t, const struct timespec * u);
void timespec_sub (struct timespec * t, const struct timespec * u);
int timespec_nz (const struct timespec * t);
int timespec_lt (const struct timespec * t, const struct timespec * u);
int timespec_gt (const struct timespec * t, const struct timespec * u);
int timespec_le (const struct timespec * t, const struct timespec * u);
int timespec_ge (const struct timespec * t, const struct timespec * u);
int timespec_eq (const struct timespec * t, const struct timespec * u);
void timespec_from_us (struct timespec * t, unsigned long us);
unsigned long timespec_to_us (const struct timespec * t);

#ifdef __cplusplus
}
#endif

#endif

