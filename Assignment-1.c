/*
Author: Matthew Lee-Mockett
ID: 251203400
Date created: Sep 30, 2024
Course: CS 3305 assignment #1

Purpose: The aim of this assignment was to create a program that utilized forking to solve an unknown password. Given a function "checkPassword"
that is able to check 3 characters at a time, I implemented the method solvePassword that uses a nested for loop to iterate through each possible combination
of characters that could be equivalent to part of the unknown (3 characters) password. If the guess is correct, the function begins attempting to solve the next 3
characters in the password until it sequentially finishes. However, with the option of forking, I implemented a forking process that allows 4
child processes to concurrently solve the password at once separating the password into 4 sections of 3 characters. This improves the solve-time
significantly.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "checkPassword.h"

// Function given by instructor which checks the password 3 characters at a time and returns 0 if is equivalent
int checkPassword(const char *password, int start);

// Method which guesses the password in the current position
void solvePassword(int start){

    // Initialize an array to store the password guess
    char guess[4] = {0};
    guess[3] = '\0';

    // Nested for loop to iterate through all possible ASCII symbols (range 33-126) to find the correct password in the current position.
    for (char ch1 = 33; ch1 <= 126; ch1 ++){
        for (char ch2 = 33; ch2 <= 126; ch2 ++){
            for (char ch3 = 33; ch3 <=126; ch3 ++){

                // Guess based off current combination
                guess[0] = ch1;
                guess[1] = ch2;
                guess[2] = ch3;

                // Call the checkPassword method to check if current guess is correct. Start is used to specify which part of the password is being checked.
                if (checkPassword(guess, start) == 0){
                    printf("Process %d with parent %d finds %d-%d: %s\n", getpid(), getppid(), start, start +2, guess);
                    return;
               }
            }
        }
    }
}

int main (int argc, char *argv[]) {

    // initialize forking and processes ID variable
    int forking = 0;
    pid_t pid;

    // initialize the positions of which the password checks.
    int positions[4] = {0, 3, 6, 9};
    

    // Checks if -f is included in the command line by checking if the number of arguments is greater than one and if the string matches
    if (argc > 1 && strcmp(argv[1], "-f") == 0){
        forking = 1; // activates forking
    }

    // forking is activated by the user
    if (forking){
        printf("Process %d with parent %d cracking the password...\n", getpid(), getppid());
        for (int i = 0; i < 4; i++){
            pid = fork();

            // error handling if forking is unsuccessful
            if (pid <0 ){
                printf("fork unsuccessful");
                exit(1);
            }

            // child process
            if (pid == 0){
                
                // Call the solvePassword function to using forking to solve the password quicker using multiple child processes.
                solvePassword(positions[i]);
                
                // Exit the child process once the task is complete
                exit(0);
            }
        }

        // parent process waits until all child process are complete.
        for (int i = 0; i < 4; i ++){
            wait(NULL); // ensure that all child process have finished running.
        }

    // if no forking is used, the password will be solved sequentially.
    }else{
        printf("Process %d with parent %d cracking the password...\n", getpid(), getppid());
        for (int i = 0; i < 4; i ++){
            solvePassword(positions[i]);
        }
    }

    return 0;
}
