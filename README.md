#### CS 441 Project 2 Part 2 ####

__Authors__

Ryan Gittins and Phillip Sime

2013-10-24

__Summary__

This software solves a traffic direction problem for the town of Smallville, WI.  By harnessing the power of semaphores the software is able to synchronize traffic at the intersection in order to allow traffic to run at very efficient pace.  For a more technical description of how this works see below.

__Build__

To build this software, simply navigate to the directory containing the Makefile and all other included files on a unix-based machine or virtual machine. Type the command `make` into the terminal to trigger the build. This will cause the gcc build commands listed in the Makefile to execute, compiling the source code into an executable file.

__Usage__

To use this software, simply run the command `./stoplight <number-of-cars>`.  Where items in '<>' are required parameters.  The argument <number-of-cars> is simply the number of cars you would like the program to use for simulation.  Each car is a separate  thread so this number is limited by each individual's hardware limitations.  The number of cars must be greater than 0.

__Test Cases__

`./stoplight` This test will will display usage information.  

`./stoplight 5` This test will run the program with 5 cars (threads) producing similiar output to the example given in the project PDF.

`./stoplight 100` This test will run the program with 100 cars (threads) to stress the program with a large number of threads.

`python test.py 100000 > test.txt` This test will execute a python script which simply runs the command `./stoplight.c 10` 100,000 times and outputs the information to test.txt for review.  The test was able to run to completion without deadlocking at any point.  From this test we have a good indication that there is a low likely hood of the program ever deadlocking.

__Examples__

This example runs the program with `./stoplight 5` to show how the program will execute with the same number of cars as the example in the project PDF.

````
shell$ ./stoplight 10
Number of Cars:   5
Number of Cars:  10
-------------------------------
 Car ID |   Approach from |       Travel to |           State | Time (msec)
--------+-----------------+-----------------+-----------------+--------------
      5 |           South |            East |        Approach |      0.000
      5 |           South |            East |        Go Right |      0.037
      5 |           South |            East |           Leave |      0.043
      7 |            East |           South |        Approach |      0.000
      1 |            West |            East |        Approach |      0.000
      1 |            West |            East |     Go Straight |      0.006
      7 |            East |           South |         Go Left |      0.004
      7 |            East |           South |           Leave |      0.014
      1 |            West |            East |           Leave |      0.008
      2 |           South |            East |        Approach |      0.001
      2 |           South |            East |        Go Right |      0.004
      2 |           South |            East |           Leave |      0.006
      3 |            West |           South |        Approach |      0.001
      3 |            West |           South |        Go Right |      0.004
      3 |            West |           South |           Leave |      0.006
      4 |           South |            East |        Approach |      0.001
      4 |           South |            East |        Go Right |      0.016
      4 |           South |            East |           Leave |      0.023
      6 |           South |            East |        Approach |      0.001
      6 |           South |            East |        Go Right |      0.003
      6 |           South |            East |           Leave |      0.004
      0 |            West |           North |        Approach |      0.000
      0 |            West |           North |         Go Left |      0.016
      0 |            West |           North |           Leave |      0.023
      9 |            East |           North |        Approach |      0.000
      9 |            East |           North |        Go Right |      0.011
      9 |            East |           North |           Leave |      0.015
      8 |           South |            West |        Approach |      0.000
      8 |           South |            West |         Go Left |      0.003
      8 |           South |            West |           Leave |      0.004
--------+-----------------+-----------------+-----------------+--------------
Min.  Time :    0.004000 msec
Avg.  Time :    0.014600 msec
Max.  Time :    0.043000 msec
Total Time :    0.146000 msec
--------+-----------------+-----------------+-----------------+--------------

````

This example runs the program with `./stoplight 50` to show how the program will execute with a larger number of cars.  Note: The output was split in order to allow the output to fit on a single page. 

````
shell$ ./stoplight 50
Number of Cars:  50
-------------------------------
 Car ID |   Approach from |       Travel to |           State | Time (msec)
--------+-----------------+-----------------+-----------------+--------------
      4 |           South |            West |        Approach |      0.001
      4 |           South |            West |         Go Left |      0.122
      4 |           South |            West |           Leave |      0.152
      9 |            East |           South |        Approach |      0.001
      9 |            East |           South |         Go Left |      0.040
      9 |            East |           South |           Leave |      0.057
      3 |            West |           North |        Approach |      0.000
      3 |            West |           North |         Go Left |      0.038
      3 |            West |           North |           Leave |      0.075
      8 |            West |           South |        Approach |      0.001
      8 |            West |           South |        Go Right |      0.151
      8 |            West |           South |           Leave |      0.168
     12 |            West |           South |        Approach |      0.000
     12 |            West |           South |        Go Right |      0.069
     12 |            West |           South |           Leave |      0.116
      7 |            West |           South |        Approach |      0.001
      7 |            West |           South |        Go Right |      0.139
      7 |            West |           South |           Leave |      0.148
      2 |           North |            West |        Approach |      0.000
      2 |           North |            West |        Go Right |      0.029
      2 |           North |            West |           Leave |      0.042
      6 |            West |           North |        Approach |      0.001
      6 |            West |           North |         Go Left |      0.027
      6 |            West |           North |           Leave |      0.045
**** SPLIT **** SPLIT **** SPLIT **** SPLIT **** SPLIT **** SPLIT ****
     40 |            East |            West |           Leave |      0.380
     39 |            East |           South |        Approach |      0.000
     39 |            East |           South |         Go Left |      0.508
     39 |            East |           South |           Leave |      0.537
     21 |           North |            West |        Approach |      0.000
     21 |           North |            West |        Go Right |      1.487
     21 |           North |            West |           Leave |      1.519
     44 |           North |            East |        Approach |      0.001
     44 |           North |            East |         Go Left |      0.248
     44 |           North |            East |           Leave |      0.283
--------+-----------------+-----------------+-----------------+--------------
Min.  Time :    0.042000 msec
Avg.  Time :    0.481240 msec
Max.  Time :    2.484998 msec
Total Time :   24.061976 msec
--------+-----------------+-----------------+-----------------+--------------
````


__Question Answers__

_Before Coding_

>Assume that the residents of Smallville are exceptional and follow the old (and widely ignored) convention that whoever arrives at the intersection first proceeds first. Using the language of synchronization primitives describe the way this intersection is controlled. In what ways is this method suboptimal?

In the case that our intersection were to follow the old convention of first arrived is the first to leave we would need to have a lock on the intersection so that only one car would be able to pass through the intersection at one time.  A simple mutex would do this job as only one car would be allowed to travel through the intersection at one time.  Since semaphores are normally FIFO structures this would meet are requirements in that whoever arrives first will be allowed to proceed through the intersection also first. 

>Now, assume that the residents of Smallville are like most people and do not follow the convention described above. In what one instance can this four-way-stop intersection produce a deadlock? (It will be helpful to think of this in terms of the model we are using instead of trying to visualize an actual intersection).

If there was a lack of a convention for how to behave at our intersection we would have the possibility that our intersection could become deadlocked.  The case that will cause a deadlock is that all four cars enter the intersection concurrently.  Since all four of our inner quadrants would now have a car inside them there would be no way for the cars to proceed without “backing” out of the intersection and allowing another car to proceed first.

_After Coding_

>Describe your solution and why it meets the goals of this part of the assignment, namely: does not deadlock, prevents accidents, addresses starvation, improves traffic flow, and fairness.

The solution we chose to solve this problem was to handle each car on a case by case basis.  That is, depending on which direction a car would travel a different scenario would take place in order to ensure that accidents were prevented.  In order to do this we needed to use 5 semaphores total.  4 of the semaphores represented the 4 quadrants (NW, NE, SW, SE) of the intersection.  The other semaphore acted as lock to prevent more than 3 cars, which are not in a position from which they can exit, from ever being in the intersection at the same time.  The reason this is necessary is that at any point there is a car in every quadrant, depending on the car's direction, we have the possibility of deadlock if none of the cars will be immediately exiting.

Not only does this solution prevent deadlock, but it will also ensure that the intersection is fair and that no car is starved.  Since semaphores work on a first-in-first-out basis we can ensure that once a car is stopped and waiting at a certain point they will be waiting for the semaphore to signal that the intersection is clear.  This will be done in the order that the cars arrived at the intersection.

Overall the traffic flow of this intersection is improved because of the implementation mentioned above.  As mentioned, depending on the destination of a given car we can allow 4 cars to be in the intersection at one time.  However, if there are 3 cars in the intersection and none of the cars will be immediately exiting we will not allow anymore cars to enter the intersection.  This allows the intersection to handle cars at near maximum capacity while ensuring we do not have a deadlock.



__Known Bugs and Problem Areas__
* No bugs or problem areas are known at this time.
