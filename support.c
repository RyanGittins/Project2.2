/*
 * Josh Hursey
 * Oct. 10, 2013
 *
 * CS 441/541 : Project 2 Part 2 Template
 *
 */
#include "support.h"

static int initialized = FALSE;

int support_init(void) {
    int ret;

    ret = semaphore_create(&support_print_lock,  1);
    initialized = TRUE;

    return ret;
}

int support_finalize(void) {
    int ret;

    ret = semaphore_destroy(&support_print_lock);
    initialized = FALSE;

    return ret;
}

void print_footer(double min_time, double max_time, double total_time, int num_cars) {
    if( FALSE == initialized ) {
        fprintf(stderr, "Warning: You forgot to call support_init() before calling print_footer()\n");
        support_init();
    }

    printf("--------+-----------------+-----------------+-----------------+--------------\n");
	printf("Min.  Time : %12f msec\n", min_time);
	printf("Avg.  Time : %12f msec\n", total_time / num_cars);
	printf("Max.  Time : %12f msec\n", max_time);
	printf("Total Time : %12f msec\n", total_time);
	printf("--------+-----------------+-----------------+-----------------+--------------\n");
}

void print_header(void) {
    if( FALSE == initialized ) {
        fprintf(stderr, "Warning: You forgot to call support_init() before calling print_header()\n");
        support_init();
    }

    printf("-------------------------------\n");
    printf("%7s | %15s | %15s | %15s | %10s\n", "Car ID", "Approach from", "Travel to", "State", "Time (msec)");
    printf("--------+-----------------+-----------------+-----------------+--------------\n");
}

void print_state(int car_id, car_direction_t car_approach, car_direction_t car_dest, char * state, double timer) {
    if( FALSE == initialized ) {
        fprintf(stderr, "Warning: You forgot to call support_init() before calling print_state()\n");
        support_init();
    }

    semaphore_wait(&support_print_lock);

    printf("%7d | %15s | %15s | %15s | %10.3f\n",
           car_id,
           (car_approach == NORTH ? "North" :
            (car_approach == WEST ? "West" :
             (car_approach == EAST ? "East" :
              (car_approach == SOUTH ? "South" : "?")))),
           (car_dest == NORTH ? "North" :
            (car_dest == WEST ? "West" :
             (car_dest == EAST ? "East" :
              (car_dest == SOUTH ? "South" : "?")))),
           state,
           timer*TIME_MSEC);

    semaphore_post(&support_print_lock);

    return;
}

double timeval_to_double(struct timeval ctime) {
    if( FALSE == initialized ) {
        fprintf(stderr, "Warning: You forgot to call support_init() before calling timeval_to_double()\n");
        support_init();
    }

    return (ctime.tv_sec + (ctime.tv_usec/(1.0 + TIME_USEC)));
}

struct timeval get_timeval_diff_as_timeval(struct timeval start, struct timeval end) {
    struct timeval loc_diff;

    if( FALSE == initialized ) {
        fprintf(stderr, "Warning: You forgot to call support_init() before calling get_timeval_diff_as_timeval()\n");
        support_init();
    }

    /* Check to see if we have to carry a second over */
    if( end.tv_usec < start.tv_usec ) {
        loc_diff.tv_usec = (TIME_USEC - start.tv_usec) + end.tv_usec;
        end.tv_sec -= 1;
    } else {
        loc_diff.tv_usec = end.tv_usec - start.tv_usec;
    }

    loc_diff.tv_sec = end.tv_sec - start.tv_sec;

    return loc_diff;
}

double get_timeval_diff_as_double(struct timeval start, struct timeval *given_end) {
    struct timeval loc_diff, end;

    if( FALSE == initialized ) {
        fprintf(stderr, "Warning: You forgot to call support_init() before calling get_timeval_diff_as_double()\n");
        support_init();
    }

    if( NULL == given_end ) {
        gettimeofday(&end, NULL);
    } else {
        end.tv_sec  = given_end->tv_sec;
        end.tv_usec = given_end->tv_usec;
    }

    loc_diff = get_timeval_diff_as_timeval(start, end);

    return timeval_to_double(loc_diff);
}
