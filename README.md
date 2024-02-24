# pphw2
Parellel Processing hw assignment 2


mino.cpp is a simulation of problem 1

vase.cpp is a simulation of problem 2

A copy of my written explanations are in the solutions.txt file

The steps to run my code are in the runcode.txt file


Explanations:
Problem  1 Explanation:

In this problem I assigned one of the n threads to be in charge of replacing the cupcake. 
The other threads are cannot replace the cupcakes. Each thread has a boolean to keep track of whether they eat the cupcake. 
When the thread eats a cupcake boolean becomes true they are not allowed to eat the cupcake again even if they are selected multiple times by the minotaur.
The thread in charge of replacing the cupcake with replace it everytime it is eaten up to n-1 times. (n-1 because the counter thread doesn't count itself.)
When the thread replaces it n-1 times it knows all the guests have been to the maze and the program terminates.

Problem 2 Explanation:

Chosen answer: Strategy 3

In this problem I went with the 2nd solution. 
I determined the first solution was unefficient because threads will have to constantly check the showroom door to see if its occupied.
It also states in the prompt there are no guarantees a particular thread that wants to see the vase would get to see it.
In this solution multiple guest might also check the door at the same time leading to a race condition.

For Strategy 2 while the sign on the door does help prevent race conditions caused by multiple threads. 
It still doesnt guarantee every thread that wants to see the vase will see it. Part of the reason is because a thread can just be unlucky and have bad timing.

I chose strategy 3 because it upholds the fairness and liveness principle. All threads that want to see the vase have a fair shot of seeing the vase.
And if a thread wants to see the vase again then it can. The only con to this is that the threads are contrained to a Queue (instead of partying) 
and have to notify the thread at front when they exit. However I see it better than the cons of the other solutions.
