/*
 * Ryan Gittins
 * Phil Sime
 * 2013-10-26
 *
 * CS 441/541 : Project 2 Part 2
 */
#include "support.h"


/*****************************
 * Defines
 *****************************/
#define XSECT_NW 0
#define XSECT_NE 1
#define XSECT_SE 2
#define XSECT_SW 3


/*****************************
 * Structures
 *****************************/


/*****************************
 * Global Variables
 *****************************/
// Number of cars (threads) in the system
int num_cars = 0;

// Global statistics
double min_time = -1.0;
double max_time = -1.0;
double total_time = -1.0;

// Start and end times for each car
struct timeval per_thread_start_timer[1000];
struct timeval per_thread_end_timer[1000];

// Semaphores to lock each quadrant
semaphore_t NW;
semaphore_t NE;
semaphore_t SW;
semaphore_t SE;

/*****************************
 * Function Declarations
 *****************************/
/*
 * Parse command line arguments
 */
int parse_args(int argc, char **argv);

/*
 * Go straight
 * This function implements passing straight through the intersection from
 * any direction.
 *
 * Write and comment this function
 *
 * Arguments:
 *   car_approach: Direction from which the car approaches the intersection.
 *   car_id: The car ID number for printing purposes
 *
 * Returns:
 *    0 on Success
 *   -1 on Error
 */
int go_straight(car_direction_t car_approach, car_direction_t car_dest, int car_id);

/*
 * Go left
 * This function implements turning to the left through the intersection from
 * any direction.
 *
 * Write and comment this function
 *
 * Arguments:
 *   car_approach: Direction from which the car approaches the intersection.
 *   car_id: The car ID number for printing purposes
 *
 * Returns:
 *    0 on Success
 *   -1 on Error
 */
int go_left(car_direction_t car_approach, car_direction_t car_dest, int car_id);

/*
 * Go right
 * This function implements turning to the right through the intersection from
 * any direction.
 *
 * Write and comment this function
 *
 * Arguments:
 *   car_approach: Direction from which the car approaches the intersection.
 *   car_id: The car ID number for printing purposes
 *
 * Returns:
 *    0 on Success
 *   -1 on Error
 */
int go_right(car_direction_t car_approach, car_direction_t car_dest, int car_id);

/*
 * TODO
 */
int enter_intersection(car_direction_t car_approach, car_direction_t car_dest, int car_id);

/*
 * Approach intersection
 * Main thread function that picks an arbitrary direction to approach from,
 * and to travel to for each car.
 *
 * Write and comment this function
 *
 * Arguments:
 *   param = The car ID number for printing purposes
 *
 * Returns:
 *   NULL
 */
void *approach_intersection(void *param);
