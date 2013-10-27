/*
 * Josh Hursey
 * Oct. 10, 2013
 *
 * CS 441/541 : Project 2 Part 2 Template
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include "semaphore_support.h"

/*****************************
 * Defines
 *****************************/
#define TRUE  1
#define FALSE 0

/* Bound for random sleep time before approaching the intersection */
#define TIME_TO_SLEEP 4000

/* Time to cross one portion of the intersection */
#define TIME_TO_CROSS 2000

/* Microsecond: 1 second = 1000000 usec */
#define TIME_USEC     1000000

/* Millisecond: 1 second = 1000 msec */
#define TIME_MSEC     1000


/*****************************
 * Structures
 *****************************/
/* Type to encode the direction of a traveling car */
typedef enum {
    NORTH = 0,
    WEST  = 1,
    EAST  = 2,
    SOUTH = 3
} car_direction_t;


/*****************************
 * Global Variables
 *****************************/
/*
 * Lock to protect printf()
 */
semaphore_t support_print_lock;


/*****************************
 * Function Declarations
 *****************************/
/*
 * Initialize support library.
 *
 * Arguments:
 *   None
 *
 * Returns:
 *   0 on success
 *  -1 on error
 */
int support_init(void);

/*
 * Finalize support library
 *
 * Arguments:
 *   None
 *
 * Returns:
 *   0 on success
 *  -1 on error
 */
int support_finalize(void);

/*
 * Print a header to match output of print_state
 *
 * Arguments:
 *   None
 *
 * Returns:
 *   Nothing
 */
void print_header(void);

/*
 * Print a footer to match output of print_state
 *
 * Arguments:
 *   None
 *
 * Returns:
 *   Nothing
 */
void print_footer(void);

/*
 * Print the state of the car.
 *
 * Arguments:
 *   car_id       = Car Identifier
 *   car_approach = Direction that the car approaches from
 *   car_dest     = Direction that the car is traveling to
 *   state        = String describing the state of the car
 *   timer        = time value in milliseconds
 *
 * Returns:
 *   Nothing.
 */
void print_state(int car_id, car_direction_t car_approach, car_direction_t car_dest, char * state, double timer);

/*
 * Convert 'struct timeval' to double representing time in milliseconds
 *
 * Arguments:
 *   ctime = Time structure to convert
 *
 * Returns:
 *   Time in milliseconds
 */
double timeval_to_double(struct timeval ctime);

/*
 * Take the difference between two timeval structures
 *
 * Arguments:
 *   start  = Start time (must be smaller than End time)
 *   end    = End time (must be larger than Start time)
 *
 * Returns:
 *   timeval structure containing the difference between the two times.
 */
struct timeval get_timeval_diff_as_timeval(struct timeval start, struct timeval end);

/*
 * Take the difference between two timeval structures
 *
 * Arguments:
 *   start  = Start time (must be smaller than End time)
 *   end    = Reference to End time (must be larger than Start time or NULL)
 *            If end == NULL, then the current gettimeofday() value will be used.
 *
 * Returns:
 *   Time in milliseconds
 */
double get_timeval_diff_as_double(struct timeval start, struct timeval *given_end);
