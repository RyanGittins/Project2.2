##########################################
# Authors: Phillip Sime and Ryan Gittins #
##########################################

from subprocess import call
import sys

# Default to 1 execution
a = 1

# Check for command line arguments
if len(sys.argv) > 1:
  # Ensure that a valid number was entered
  try:
    a = int(sys.argv[1])
  except ValueError:
    # Print usage and exit if invalid number
    print("Usage: python ./stoplight.c <number-of-runs>")
    exit(-1)
    
# Execute program with 10 cars for the provided number of times.
for i in range(0, a):
  call(["./stoplight", "10"])
  