# Scheduler and System Calls

In this assignment you will be implementing a lottery scheduler, the user program _ps_, and a number of system calls.

## System Calls

### int setColor(enum COLOR )
You will implement a system call that will set an attribute, color, of a process.  The valid colors a process can be assigned are RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, and VIOLET.  You will store the color of a process in its process control block.  This routine should return 0 if successful, and -1 otherwise (if, for example, the caller passes in an invalid color).

### int setTickets(int)
This system call sets the number of tickets of the calling process. By default, each process should get one ticket; calling this routine makes it such that a process can raise the number of tickets it receives, and thus receive a higher proportion of CPU cycles. This routine should return 0 if successful, and -1 otherwise (if, for example, the caller passes in a number less than one). The number of tickets a process can have an integer value of the range 1 to 256.

You'll need to assign tickets to a process when it is created. Specfically, you'll need to make sure a child process inherits the same number of tickets as its parents. Thus, if the parent has 10 tickets, and calls fork() to create a child process, the child should also get 10 tickets.

### int getpinfo(struct pstat *)
The second is int getpinfo(struct pstat *). This routine returns some information about all running processes, including how many times each has been chosen to run and the process ID of each. You will use this system call to build a variant of the command line program ps, which can then be called to see what is going on. The structure pstat is defined below; note, you cannot change this structure, and must use it exactly as is. This routine should return 0 if successful, and -1 otherwise (if, for example, a bad or NULL pointer is passed into the kernel).

Good examples of how to pass arguments into the kernel are found in existing system calls. In particular, follow the path of read(), which will lead you to sys_read(), which will show you how to use argptr() (and related calls) to obtain a pointer that has been passed into the kernel. Note how careful the kernel is with pointers passed from user space -- they are a security threat, and thus must be checked very carefully before usage.

### Pseudo random number generator

You'll need to add a function to generate random numbers in the kernel; some searching should lead you to a simple pseudo-random number generator, which you can then include in the kernel and use as appropriate.  This is the only code you may use from an external source.

### ps

Your ps application will print the following:

```
NAME    PID     STATUS      COLOR    TICKETS
init    1       SLEEPING    RED      10    
sh      2       SLEEPING    ORANGE   2
test    4       SLEEPING    RED      4
ps      6       RUNNING     INDIGO   1
```

### The scheduler

Most of the code for the scheduler is quite localized and can be found in proc.c; the associated header file, proc.h is also quite useful to examine. To change the scheduler, not much needs to be done; study its control flow and then try some small changes.

You'll need to assign tickets to a process when it is created. Specfically, you'll need to make sure a child process inherits the same number of tickets as its parents. Thus, if the parent has 10 tickets, and calls fork() to create a child process, the child should also get 10 tickets.

You'll also need to figure out how to generate random numbers in the kernel; some searching should lead you to a simple pseudo-random number generator, which you can then include in the kernel and use as appropriate.

Finally, you'll need to understand how to fill in the structure pstat in the kernel and pass the results to user space. The structure should look like what you see here, in a file you'll have to include called pstat.h:


```c
#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "param.h"

struct pstat {
  char name[NPROC][16];        // name of the process
  enum procstate state[NPROC]; // state of the process   
  int inuse[NPROC];            // whether this slot of the process table is in use (1 or 0)
  int tickets[NPROC];          // the number of tickets this process has
  int pid[NPROC];              // the PID of each process
  enum COLOR color[NPROC];     // the color of the proces
  int ticks[NPROC];            // the number of ticks each process has accumulated 
};

#endif // _PSTAT_H_
```
## Graph and Test Application

You'll have to make a graph for this assignment. The graph should show the number of time slices a set of three processes receives
over time, where the processes have a 3:2:1 ratio of tickets (e.g., process A might have 30 tickets, process B 20, and process C 10). The graph is likely to be pretty boring, but should clearly show that your lottery scheduler works as desired.  The graph must be submitted as a PDF file at the top level of your repo.

To gather this data you will need to write an application that forks three children and each child runs measuring the amount of the processor time each gets.

## SUBMITTING

Push all your changes to your main branch.  

## BUILDING AND RUNNING XV6

### Setting up the cross-compiling environment
```
source source_me.sh
```

### To build the kernel:
```
make
```

### To build the userspace applications and run the OS
```
make qemu
```

### To exit xv6
```
ctrl-a x
```

## Administrative

This assignment must be coded in C. Any other language will result in 0 points. Your programs will be compiled and graded on the course GitHub Codespace. Code that does not compile with the provided makefile will result in a 0.

There are coding resources and working code you may use in the course GitHub repositories.  You are free to use any of that code in your program if needed. You may use no other outside code.

## Academic Integrity
This assignment must be 100% your own work. No code may be copied from friends,  previous students, books, web pages, etc. All code submitted is automatically checked 
against a database of previous semester’s graded assignments, current student’s code and common web sources. By submitting your code on GitHub you are attesting that 
you have neither given nor received unauthorized assistance on this work. Code that is copied from an external source or used as inspiration, excluding the 
course github, will result in a 0 for the assignment and referral to the Office of Student Conduct.

