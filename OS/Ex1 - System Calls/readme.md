# **System Calls**


# creat
fd = creat(filename, **S_IRWXU**);  
	if(fd<0)  
&nbsp; &nbsp;		printf("Error\n");  
	else  
&nbsp; &nbsp;	printf("\nCreated file.txt\n") ;  

char *filename = "file.txt";  
if file.txt is in the same directory as program  
man creat for all access keywords

# open
fd = open(filename, O_CREAT | O_RDWR,S_IRWXU);  
	if(fd<0)  
&nbsp; &nbsp;		printf("Error\n");  
	else  
	&nbsp; &nbsp;	printf("File opened.\n");  
in this example if filename is already there give it read write  accesss and then execute access to user