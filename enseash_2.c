#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


// Displays the welcome message for the shell

void DisplaySh(void){
	char* message="$./enseash\nWelcome to ENSEA Tiny Shell.\nPour quitter, tapez 'exit'.\n";
	write(STDOUT_FILENO,message,strlen(message));
}	

// Execute the command that is entered

int executeCommand(char* buf){
	int pid,status;
	pid=fork();
	
	if (pid==-1){
		perror("Fork impossible \n");
		return EXIT_FAILURE;
	}
	else if (pid==0){		
		execlp(buf,buf,(char*)NULL);
		
	}
	else{
		wait(&status);
	}

}
#Define MAXSIZE 100;

int main(){
	DisplaySh();
	int maxSize=100;  //Maximum length of input command
	char buf[maxSize];
		
	while(1){
		write(STDOUT_FILENO, "enseash % ", strlen("enseash % "));
		int size=read(STDIN_FILENO,buf,maxSize);
		buf[size-1]='/0';      

		executeCommand(buf);
	}
	return EXIT_SUCCESS;
}
