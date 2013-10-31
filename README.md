#### CS 441 Project 2 Part 2 ####

__Authors__

Ryan Gittins and Phillip Sime

2013-10-24

__Summary__

This software solves a traffic direction problem for the town of Smallville, WI.  By harnessing the power of semaphores the software is able to synchronize traffic at the intersection in order to allow traffic to run at very efficient pace.  For a more technical description of how this works see below.

__Build__

To build this software, simply navigate to the directory containing the Makefile and all other included files on a unix-based machine or virtual machine. Type the command `make` into the terminal to trigger the build. This will cause the gcc build commands listed in the Makefile to execute, compiling the source code into an executable file.

__Usage__

To use this software, simply run the command `./stoplight <number-of-cars>`  Where items in '<>' are required parameters.  The argument <number-of-cars> is simply the number of cars you would like the program to use for simulation.  Each car is a separate  thread so this number is limited by each individual's hardware limitations.  The number of cars must be greater than 0.

__Test Cases__

TODO

__Examples__

TODO

__Question Answers__

_Before Coding_

>Assume that the residents of Smallville are exceptional and follow the old (and widely ignored) convention that whoever arrives at the intersection first proceeds first. Using the language of synchronization primitives describe the way this intersection is controlled. In what ways is this method suboptimal?

In the case that our intersection were to follow the old convention of first arrived is the first to leave we would need to have a lock on the intersection so that only one car would be able to pass through the intersection at one time.  A simple mutex would do this job as only one car would be allowed to travel through the intersection at one time.  Since semaphores are normally FIFO structures this would meet are requirements in that whoever arrives first will be allowed to proceed through the intersection also first. 

>Now, assume that the residents of Smallville are like most people and do not follow the convention described above. In what one instance can this four-way-stop intersection produce a deadlock? (It will be helpful to think of this in terms of the model we are using instead of trying to visualize an actual intersection).

If there was a lack of a convention for how to behave at our intersection we would have the possibility that our intersection could become deadlocked.  The case that will cause a deadlock is that all four cars enter the intersection concurrently.  Since all four of our inner quadrants would now have a car inside them there would be no way for the cars to proceed without “backing” out of the intersection and allowing another car to proceed first.

_After Coding_

>Describe your solution and why it meets the goals of this part of the assignment, namely: does not deadlock, prevents accidents, addresses starvation, improves traffic flow, and fairness.



__Known Bugs and Problem Areas__
* No bugs or problem areas are known at this time.
