/*
 * Copyright (c) 2009-2011, The Regents of the University of California,
 * through Lawrence Berkeley National Laboratory (subject to receipt of any
 * required approvals from the U.S. Dept. of Energy).  All rights reserved.
 *
 * This code is distributed under a BSD style license, see the LICENSE file
 * for complete information.
 *
 * Based on timers.h by Jef Poskanzer. Used with permission.
 */

#ifndef __TIMER_H
#define __TIMER_H

#include <sys/time.h>

/* TimerClientData is an opaque value that tags along with a timer.  The
** client can use it for whatever, and it gets passed to the callback when
** the timer triggers.
*/
typedef union
{
    void* p;
    int i;
    long l;
} TimerClientData;

extern TimerClientData JunkClientData;	/* for use when you don't care */

/* The TimerProc gets called when the timer expires.  It gets passed
** the TimerClientData associated with the timer, and a timeval in case
** it wants to schedule another timer.
*/
typedef void TimerProc( TimerClientData client_data, struct timeval* nowP );

/* The Timer struct. */
typedef struct TimerStruct
{
    TimerProc* timer_proc;
    TimerClientData client_data;
    int64_t usecs;
    int periodic;
    struct timeval time;
    struct TimerStruct* prev;
    struct TimerStruct* next;
    int hash;
} Timer;

/* Set up a timer, either periodic or one-shot. Returns (Timer*) 0 on errors. */
extern Timer* tmr_create(
    struct timeval* nowP, TimerProc* timer_proc, TimerClientData client_data,
    int64_t usecs, int periodic );

/* Returns a timeout indicating how long until the next timer triggers.  You
** can just put the call to this routine right in your select().  Returns
** (struct timeval*) 0 if no timers are pending.
*/
extern struct timeval* tmr_timeout( struct timeval* nowP );

/* Run the list of timers. Your main program needs to call this every so often,
** or as indicated by tmr_timeout().
*/
extern void tmr_run( struct timeval* nowP );

/* Reset the clock on a timer, to current time plus the original timeout. */
extern void tmr_reset( struct timeval* nowP, Timer* timer );

/* Deschedule a timer.  Note that non-periodic timers are automatically
** descheduled when they run, so you don't have to call this on them.
*/
extern void tmr_cancel( Timer* timer );

/* Clean up the timers package, freeing any unused storage. */
extern void tmr_cleanup( void );

/* Cancel all timers and free storage, usually in preparation for exitting. */
extern void tmr_destroy( void );

#endif /* __TIMER_H */
