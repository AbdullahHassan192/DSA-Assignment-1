# Task 1: Simple Process Scheduling Algorithm
## Approach
I went with making classes for each important aspect of the code, which included a Process class which creates a process, followed by a separate Node class whose “data” is a pointer to a process. I then created the CircularLinkedList class, which creates the circular linked list that stores all the processes at its nodes. Finally, I implemented the Scheduler class which has functions to run a new cycle, and also to dynamically add a new process while the program is running as mentioned in the optional task.
## Assumptions
Unlike the given example output in the task, my program’s output differs in the way that it shows the cycles running. For each cycle, it separately shows each process running, at the end of which only that process’s remaining time is updated. This goes on for each process in a cycle, after which the next cycle starts. 
## Challenges Faced
One of the initial hurdles was understanding the problem and creating the initial outline of the code. One approach I took at the start involved the Node being a Process itself, but after encountering some issues, in the end I decided to create separate classes and make the node store a process instead.
<br/>Another big challenge was the runCycle() function. After a lot of trial and error and configuring different if-else statements, I ended up with a function that worked. One of the issues in this function other than the constant trial and error included the cycles not getting removed and instead going into negative remaining time and the program running infinitely. This was due to an oversight on my end, where I was just checking whether remaining time was == 0, instead of <= 0 which would mean a process on remaining time 2, during the next cycle would go to -1 and not get removed as it was never equal to 0.
## Output Screenshots

![image](https://github.com/user-attachments/assets/bfaffd01-5366-4266-8a74-d32a0a2842a9)
![image](https://github.com/user-attachments/assets/4743be98-4c49-4325-8736-4459f07af45f)

# Task 2: Very large Prime Number Calculation
## Approach
: I started by first writing the code that would take a string of a big number, split it into chunks of 64 bit each, and store them in the nodes of a linked list. This included creating the Node and LargeNumberLinkedList, along with the splitNumber() function.
<br/>For the primality test part, I searched various primality tests online and ended up deciding on using the Miller-Rabin primality test. To understand it, I used the following resource:
<br/>https://www.youtube.com/watch?v=8i0UnX7Snkc&ab_channel=NesoAcademy
<br/>I did use help from ChatGPT to understand how to apply this logic on a linked list, especially the unsigned long mod(unsigned long modFactor) function to get started. After that, it was just about coding the rest of the functions, which was still challenging since despite them being similar to what my understanding of the algorithm was, converting it to code was difficult.
## Assumptions
The assumption I made was that the number to be checked for primality will not be negative. This allowed me to use unsigned numbers to increase the range of values the program could hold.
<br/>Another assumption was in choosing the modFactor. The modFactor has to be a very large prime number, which is why I ended up choosing 1,000,000,007 after some searching online.
## Challenges Faced
One challenge I faced early on was while deciding on the approach to split the big number into smaller chunks to be added to the linked list. At the end, I decided to go with the substr() function in a for loop to split the number into a chunk, and then add it to the linked list in each iteration of the for loop.
<br/>The main challenge was the primality test. Once I decided on using the Miller Rabin test, I was having trouble getting started with implementing it on a linked list. I had to use ChatGPT for understanding the outline of how to apply the logic to a linked list. 
<br/>Some other problems that I faced included having to increase my range of available numbers by using unsigned longs, having to use very abstract naming conventions (variable names in the millerRabin() function now include d,r,x), finding prime numbers to test the code on, and figuring out that the millerRabin() function had to go outside the LargeNumberLinkedList class.
## Output Screenshot
![image](https://github.com/user-attachments/assets/d83f3275-e6f1-40b4-ac5d-a2fa7c395c7b)
