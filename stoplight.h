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
/*
 * Number of cars (threads) in the system
 */
int num_cars = 0;

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
 * Turn left
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
int turn_left(car_direction_t car_approach, car_direction_t car_dest, int car_id);

/*
 * Turn right
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
int turn_right(car_direction_t car_approach, car_direction_t car_dest, int car_id);

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
