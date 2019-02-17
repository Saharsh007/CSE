# **Threading**
The POSIX thread libraries are a standards based thread API for C/C++.  
 It is most effective on multi-processor or multi-core systems where the process flow can be scheduled to run on another processor thus gaining speed through parallel or distributed processing. Threads require less overhead than "forking" or spawning a new process because the system does not initialize a new system virtual memory space and environment for the process.   
 All threads within a process share the same address space.  
 The purpose of using the POSIX thread library in your software is to execute software faster. 


 ### pthread_t - an opaque type which acts as a handle for the new thread.  

 ## joins
 A join is performed when one wants to wait for a thread to finish. A thread calling routine may launch multiple threads then wait for them to finish to get the results. One wait for the completion of the threads with a join.   
 **pthread_join( thread, NULL);**  

## MUTEX
sem_t mutex -- definition  
sem_init(&mutex, 0, 1) -- initialization  

## sem_post(&mutex)
increase the value of mutex ,thats it!
## sem_wait(&mutex)
decrease the value of mutex !!  
[Full Tutorial](https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html)