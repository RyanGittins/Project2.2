#### CS 441 Project 2 Part 2 ####

__Authors__

Ryan Gittins and Phillip Sime

2013-10-24

__Summary__

This software implements a solution to the bounded-buffer problem.  It uses semaphores to ensure that multiple threads do not access the same pieces of data concurrently.  It is called from the command line and provided with the time to run, number of producer threads, number of consumer threads, and an optional buffer size.  When the program executes it begins by creating producer and consumer threads which will begin interacting with the buffer.  A producer will select a random number between 0-9 and then place that number into the buffer in the next open position.  A consumer will consume the next item in the buffer.  Both the producer and the consumer ensure they do not interfere with each other by utilizing semaphores. 

__Build__

To build this software, simply navigate to the directory containing the Makefile and all other included files on a unix-based machine or virtual machine. Type the command `make` into the terminal to trigger the build. This will cause the gcc build commands listed in the Makefile to execute, compiling the source code into an executable file.

__Usage__

To use this software, simply run the command `./bounded-buffer <time-to-live> <producers> <consumers> [buffer-size]`  Where items in '<>' are required and items in '[]' are optional.  The first argument is the length, in seconds, you wish the program to run for.  The second argument is the number of producer threads you wish the program to create and use.  The third argument is the number of consumer threads you wish the program to create and use.  The final argument, which is optional, is the size of the buffer.

__Test Cases__

TODO

__Examples__

TODO

__Question Answers__

_Before Coding_

>Assume that the residents of Smallville are exceptional and follow the old (and widely ignored) convention that whoever arrives at the intersection first proceeds first. Using the language of synchronization primitives describe the way this intersection is controlled. In what ways is this method suboptimal?

A: In the case that our intersection were to follow the old convention of first arrived is the first to leave we would need to have a lock on the intersection so that only one car would be able to pass through the intersection at one time.  A simple mutex would do this job as only one car would be allowed to travel through the intersection at one time.  Since semaphores are normally FIFO structures this would meet are requirements in that whoever arrives first will be allowed to proceed through the intersection also first. 

>Now, assume that the residents of Smallville are like most people and do not follow the convention described above. In what one instance can this four-way-stop intersection produce a deadlock? (It will be helpful to think of this in terms of the model we are using instead of trying to visualize an actual intersection).

A: If there was a lack of a convention for how to behave at our intersection we would have the possibility that our intersection could become deadlocked.  The case that will cause a deadlock is that all four cars enter the intersection concurrently.  Since all four of our inner quadrants would now have a car inside them there would be no way for the cars to proceed without “backing” out of the intersection and allowing another car to proceed first.

_After Coding_

>Describe your solution and why it meets the goals of this part of the assignment, namely: does not deadlock, prevents accidents, addresses starvation, improves traffic flow, and fairness.



__Known Bugs and Problem Areas__
* No bugs or problem areas are known at this time.
