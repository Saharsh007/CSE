# NOT WORKING YET

idea is to use select linux command.  
We won't use threads mainly because of     
1.	Threads are difficult to code, debug and sometimes they have unpredictable results.  	
2.	Overhead switching of context  

3.	Not scalable for large number of clients  
4.	Deadlocks can occur  


WHY SELECT   
1.	Select command allows to monitor multiple file descriptors, waiting until one of the file descriptors become active.
	For example, if there is some data to be read on one of the sockets select will provide that information.
3.	Select works like an interrupt handler, which gets activated as soon as any file descriptor sends any data.

Data structure used for select is df_set   
It contains a list of file desciptors.

# In a NUTSHELL
1.	Created a array of sockets initialized with zero
2.	Created a master socket for accepting requests from other sockets
3.	Listens to all the sockets , if any reply broadcast it to all of them.
4.	In case of termination and connection print the same in server terminal