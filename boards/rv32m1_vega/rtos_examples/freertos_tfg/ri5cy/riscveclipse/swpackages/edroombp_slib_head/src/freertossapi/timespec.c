
/*
    Copyright 2008 (c) by Cesar Rodriguez Ortega,
    Copyright 2004-2005 (c) by Aitor Viana Sanchez,
    Space Research Group,
    University of Alcala.

    For further information, please visit http://srg.aut.uah.es

    This software is provided under the terms of the GNU General Public v2
    Licence. A full copy of the GNU GPL is provided in the file COPYING
    found in the development root of ERCOS-RT.
*/

#include <basic_types.h>
#include <edroombp_slib/freertosapi/timespec.h>

/* number of nanoseconds per second (10^9) */
#define NPS 1000000000ul

void timespec_normalize (struct timespec * t) {
	
	/* more than NPS nanoseconds in the tv_nsec field ? */
	if (t->tv_nsec >= NPS) {
		t->tv_nsec -= NPS;
		t->tv_sec++;

	/* less than 0 nanoseconds in the tv_nsec field ? */
	} else if ((int32_t) t->tv_nsec < 0) {
		t->tv_nsec += NPS;
		t->tv_sec--;
	}

	/* if data is now normalized, the work is done */
	if (t->tv_nsec < NPS) return;

	/* in the opposite case, fall into the division method */
	t->tv_sec += t->tv_nsec / NPS;
	t->tv_nsec %= NPS;
}

void timespec_add (struct timespec * t, const struct timespec * u) {
	t->tv_sec += u->tv_sec;
	t->tv_nsec += u->tv_nsec;
	timespec_normalize (t);
}

void timespec_sub (struct timespec * t, const struct timespec * u) {
	t->tv_sec -= u->tv_sec;
	t->tv_nsec -= u->tv_nsec;
	timespec_normalize (t);
}

int timespec_nz (const struct timespec * t) {
	return t->tv_sec || t->tv_nsec;
}

int timespec_lt (const struct timespec * t, const struct timespec * u) {
	if (t->tv_sec < u->tv_sec) return 1;
	return t->tv_sec == u->tv_sec && t->tv_nsec < u->tv_nsec;
}

int timespec_gt (const struct timespec * t, const struct timespec * u) {
	return timespec_lt (u, t);
}

int timespec_le (const struct timespec * t, const struct timespec * u) {
	return ! timespec_gt (t, u);
}

int timespec_ge (const struct timespec * t, const struct timespec * u) {
	return ! timespec_lt (t, u);
}

int timespec_eq (const struct timespec * t, const struct timespec * u) {
	return t->tv_sec == u->tv_sec && t->tv_nsec == u->tv_nsec;
}

void timespec_from_us (struct timespec * t, unsigned long us) {
	t->tv_sec += us / (NPS / 1000);
	t->tv_nsec += us % (NPS / 1000);
	timespec_normalize (t);
}

unsigned long timespec_to_us (const struct timespec * t) {
	return t->tv_sec * (NPS / 1000) + t->tv_nsec / (NPS / 1000);
}

