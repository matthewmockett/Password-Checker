Purpose: The aim of this assignment was to create a program that utilized forking to solve an unknown password. Given a function "checkPassword"
that is able to check 3 characters at a time, I implemented the method solvePassword that uses a nested for loop to iterate through each possible combination
of characters that could be equivalent to part of the unknown (3 characters) password. If the guess is correct, the function begins attempting to solve the next 3
characters in the password until it sequentially finishes. However, with the option of forking, I implemented a forking process that allows 4
child processes to concurrently solve the password at once separating the password into 4 sections of 3 characters. This improves the solve-time
significantly.
