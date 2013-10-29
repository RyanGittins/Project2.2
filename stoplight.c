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
	struct timeval start;
	struct timeval end;

	semaphore_create(&NW, 1);
	semaphore_create(&NE, 1);
	semaphore_create(&SW, 1);
	semaphore_create(&SE, 1);
	
	semaphore_create(&XX, 3);

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
     * Get time for total_time
     */
	gettimeofday(&start, NULL);
	
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
	 * Calculate total_time
	 */
	gettimeofday(&end, NULL);

	total_time = get_timeval_diff_as_double(start, &end);

    /*
     * Print timing information
     */
    print_footer(min_time, max_time, total_time, num_cars);

    /*
     * Cleanup
     *  - Finalize support library
     */
    if( NULL != car_threads ) {
        free(car_threads);
        car_threads = NULL;
    }

    support_finalize();
	
	semaphore_destroy(&NW);
	semaphore_destroy(&NE);
	semaphore_destroy(&SW);
	semaphore_destroy(&SE);

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
	semaphore_wait(&XX);
	
	print_state(car_id, car_approach, car_dest,
			"Go Straight",
			get_timeval_diff_as_double(per_thread_start_timer[car_id], NULL));
	
	switch(car_approach)
	{
		case NORTH:
			semaphore_wait(&NW);
			semaphore_wait(&SW);
			semaphore_post(&XX);
			semaphore_post(&NW);
			semaphore_post(&SW);
			break;
		case WEST:
			semaphore_wait(&SW);
			semaphore_wait(&SE);
			semaphore_post(&XX);
			semaphore_post(&SW);
			semaphore_post(&SE);
			break;
		case EAST:
			semaphore_wait(&NE);
			semaphore_wait(&NW);
			semaphore_post(&XX);
			semaphore_post(&NE);
			semaphore_post(&NW);
			break;
		case SOUTH:
			semaphore_wait(&SE);
			semaphore_wait(&NE);
			semaphore_post(&XX);
			semaphore_post(&SE);
			semaphore_post(&NE);
	}

    return 0;
}

/*
 * Go left
 * TODO: Write this function
 */
int go_left(car_direction_t car_approach, car_direction_t car_dest, int car_id)
{
	semaphore_wait(&XX);
	
    print_state(car_id, car_approach, car_dest,
                "Go Left",
                get_timeval_diff_as_double(per_thread_start_timer[car_id], NULL));
	
	switch(car_approach)
	{
		case NORTH:
			semaphore_wait(&NW);
			semaphore_wait(&SW);
			semaphore_post(&NW);
			semaphore_wait(&SE);
			semaphore_post(&XX);
			semaphore_post(&SW);
			semaphore_post(&SE);
			break;
		case WEST:
			semaphore_wait(&SW);
			semaphore_wait(&SE);
			semaphore_post(&SW);
			semaphore_wait(&NE);
			semaphore_post(&XX);
			semaphore_post(&SE);
			semaphore_post(&NE);
			break;
		
		case EAST:
			semaphore_wait(&NE);
			semaphore_wait(&NW);
			semaphore_post(&NE);
			semaphore_wait(&SW);
			semaphore_post(&XX);
			semaphore_post(&NW);
			semaphore_post(&SW);
			break;
		
		case SOUTH:
			semaphore_wait(&SE);
			semaphore_wait(&NE);
			semaphore_post(&SE);
			semaphore_wait(&NW);
			semaphore_post(&XX);
			semaphore_post(&NE);
			semaphore_post(&NW);
	}

    return 0;
}

/*
 * Go right
 * TODO: Write this function
 */
int go_right(car_direction_t car_approach, car_direction_t car_dest, int car_id)
{

    print_state(car_id, car_approach, car_dest,
                "Go Right",
                get_timeval_diff_as_double(per_thread_start_timer[car_id], NULL));

	switch(car_approach)
	{
		case NORTH:
			semaphore_wait(&NW);
			semaphore_post(&NW);
			break;
		case WEST:
			semaphore_wait(&SW);
			semaphore_post(&SW);
			break;
		case EAST:
			semaphore_wait(&NE);
			semaphore_post(&NE);
			break;
		case SOUTH:
			semaphore_wait(&SE);
			semaphore_post(&SE);
	}

    return 0;
}

int enter_intersection(car_direction_t car_approach, car_direction_t car_dest, int car_id)
{
	switch(car_approach)
	{
		case NORTH:
			switch(car_dest)
			{
				printf("NORTH!! %d\n", car_dest);
				case NORTH:
					return -1; // Error: Illegal U-Turn!
				case WEST:
					go_right(car_approach, car_dest, car_id); break;
				case EAST:
					go_left(car_approach, car_dest, car_id); break;
				case SOUTH:
					go_straight(car_approach, car_dest, car_id);
			}
			break;
		case WEST:
			switch(car_dest)
			{
				printf("WEST!!\n");
				case NORTH:
					go_left(car_approach, car_dest, car_id); break;
				case WEST:
					return -1; // Error: Illegal U-Turn!
				case EAST:
					go_straight(car_approach, car_dest, car_id); break;
				case SOUTH:
					go_right(car_approach, car_dest, car_id);
			}
			break;
		
		case EAST:
			switch(car_dest)
			{
				printf("EAST!!\n");
				case NORTH:
					go_right(car_approach, car_dest, car_id); break;
				case WEST:
					go_straight(car_approach, car_dest, car_id); break;
				case EAST:
					return -1; // Error: Illegal U-Turn!
				case SOUTH:
					go_left(car_approach, car_dest, car_id); break;
			}
			break;
		
		case SOUTH:
			switch(car_dest)
			{
				printf("SOUTH!!\n");
				case NORTH:
					go_straight(car_approach, car_dest, car_id); break;
				case WEST:
					go_left(car_approach, car_dest, car_id); break;
				case EAST:
					go_right(car_approach, car_dest, car_id);
				case SOUTH:
					return -1; // Error: Illegal U-Turn!
			}
	}

	return 0;
}

/*
 * Approach intersection
 * param = Car Number (car_id)
 */
void *approach_intersection(void *param)
{
    int car_id = (intptr_t)param;
    car_direction_t car_approach;
    car_direction_t car_dest;
	double car_time = 0;

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
     */
	gettimeofday(&per_thread_start_timer[car_id], NULL);

    print_state(car_id, car_approach, car_dest,
                "Approach",
                get_timeval_diff_as_double(per_thread_start_timer[car_id], NULL));

	/*
	 * Start the attempt to secure the path through the intersection
	 */
	enter_intersection(car_approach, car_dest, car_id);

    /*
     * Mark leave time for car
     */
	gettimeofday(&per_thread_end_timer[car_id], NULL);
	
	/*
	 * Get the car's time, update min/max
	 */
	car_time = get_timeval_diff_as_double(per_thread_start_timer[car_id], &(per_thread_end_timer[car_id]));

    print_state(car_id, car_approach, car_dest,
                "Leave",
                car_time );

    /*
     * Record Global timing information before exiting
     */
	
	if(car_time < min_time || min_time == -1.0){
		min_time = car_time;
	}
	
	if(car_time > max_time || max_time == -1.0){
		max_time = car_time;
	}

    /*
     * All done
     */
    pthread_exit((void *) 0);
    return NULL;
}
