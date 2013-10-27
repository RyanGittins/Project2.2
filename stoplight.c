/*
 * Ryan Gittins
 * Phil Sime
 * 2013-10-26
 *
 * CS 441/541 : Project 2 Part 2
 *
 */
#include "stoplight.h"

int main(int argc, char * argv[]) {
    int ret, i;
    pthread_t *car_threads = NULL;

    /*
     * Parse Command Line arguments
     */
    if( 0 != (ret = parse_args(argc, argv)) ) {
        return -1;
    }

    /*
     * Initialize:
     * - random number generator
     */
    srandom(time(NULL));

    /*
     * Create Car Thread(s)
     */
    car_threads = (pthread_t*)malloc(sizeof(pthread_t) * num_cars);
    for(i = 0; i < num_cars; ++i ) {
        if( 0 != (ret = pthread_create(&(car_threads[i]), NULL, approach_intersection, (void*)(intptr_t)i)) ) {
            fprintf(stderr, "Error: Failed to create a car thread! Ret = %d\n", ret);
            return -1;
        }
    }

    /*
     * Reap threads
     */
    for(i = 0; i < num_cars; ++i ) {
        pthread_join(car_threads[i], NULL);
    }

    /*
     * Print timing information
     */
    print_footer();

    /*
     * Cleanup
     *  - Finalize support library
     */
    if( NULL != car_threads ) {
        free(car_threads);
        car_threads = NULL;
    }

    support_finalize();

    return 0;
}

int parse_args(int argc, char **argv)
{
    /*
     * Check for NumCars argument
     */
    if( argc < 2 ) {
        printf("Usage: %s NumCars\n", argv[0]);
        return -1;
    }

    /*
     * Arg. 1 = Number of cars to pass through intersection
     */
    num_cars = atoi(argv[1]);
    if( num_cars <= 0 ) {
        printf("Error: The number of cars threads must be greater than 0\n");
        return -1;
    }

    /*
     * Initialize support library
     */
    support_init();

    /*
     * Display header
     */
    printf("Number of Cars: %3d\n", num_cars);
    print_header();

    return 0;
}

/*
 * Go straight
 * TODO: Write this function
 */
int go_straight(car_direction_t car_approach, car_direction_t car_dest, int car_id)
{
    /* For example:
    print_state(car_id, car_approach, car_dest,
                "Go Straight",
                get_timeval_diff_as_double(per_thread_start_timer[car_id], NULL));
    */

    return 0;
}

/*
 * Go left
 * TODO: Write this function
 */
int go_left(car_direction_t car_approach, car_direction_t car_dest, int car_id)
{
    /* For example:
    print_state(car_id, car_approach, car_dest,
                "Go Left",
                get_timeval_diff_as_double(per_thread_start_timer[car_id], NULL));
    */

    return 0;
}

/*
 * Go right
 * TODO: Write this function
 */
int go_right(car_direction_t car_approach, car_direction_t car_dest, int car_id)
{
    /* For example:
    print_state(car_id, car_approach, car_dest,
                "Go Right",
                get_timeval_diff_as_double(per_thread_start_timer[car_id], NULL));
    */

    return 0;
}

/*
 * Approach intersection
 * param = Car Number (car_id)
 */
void *approach_intersection(void *param) {
    int car_id = (intptr_t)param;
    car_direction_t car_approach;
    car_direction_t car_dest;

    (void) car_id; /* To silence the compiler */

    /* Car approaches randomly from one direction */
    car_approach    = random()%4;

    /* Car travels randomly to another direction, but not the approaching
     * direction since U-turns are prohibited */
    do {
        car_dest = random()%4;
    } while(car_dest == car_approach);

    /*
     * Sleep for a bounded random amount of time before approaching the
     * intersection
     */
    usleep(random()%TIME_TO_SLEEP);

    /*
     * Mark start time for the car (thread)
     * - man gettimeofday
     * TODO: Finish writing this section of the function
     */

    /* Print state example:
    print_state(car_id, car_approach, car_dest,
                "Approach",
                get_timeval_diff_as_double(per_thread_start_timer[car_id], NULL));
    */

    /*
     * Mark leave time for car
     * - man gettimeofday
     * TODO: Finish writing this section of the function
     */

    /* Print state example:
    print_state(car_id, car_approach, car_dest,
                "Leave",
                get_timeval_diff_as_double(per_thread_start_timer[car_id], &(per_thread_end_timer[car_id])) );
    */

    /*
     * Record Global timing information before exiting
     * TODO: Finish writing this section of the function
     */


    /*
     * All done
     */
    pthread_exit((void *) 0);
    return NULL;
}
