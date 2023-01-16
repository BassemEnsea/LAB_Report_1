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
void DisplayBye(void){
	write(STDOUT_FILENO, "Bye bye...\n$\n", strlen("Bye bye...\n$\n"));
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
		
		write(STDOUT_FILENO,"Command not found\n", strlen("Command not found\n"));	
		return EXIT_FAILURE;
		
	}
	else{
		char Status[100];
		wait(&status);
		
		//Verification of the command type
		
		if(WIFEXITED(status)==1){ 
			
			sprintf(Status,"%d",status);
			write(STDOUT_FILENO, "enseash % [exit:",strlen("enseash % [exit:")); 
			write(STDOUT_FILENO,Status,strlen(Status));
			write(STDOUT_FILENO, "]\n",strlen("]\n"));
		}
		else{
			
			sprintf(Status,"%d",status);
			write(STDOUT_FILENO, "enseash % [sign:",strlen("enseash % [exit:"));
			write(STDOUT_FILENO,Status,strlen(Status));
			write(STDOUT_FILENO, "]\n",strlen("]\n"));
		}
	}
}


int main(){
	DisplaySh();
	int maxSize=100; //Maximum length of input command
	char buf[maxSize];
	
	
	while(1){
		write(STDOUT_FILENO, "enseash % ", strlen("enseash % "));
		int size=read(STDIN_FILENO,buf,maxSize);
		buf[size-1]='\0';
		if(strcmp(buf,"exit")==0){ //Exit from the shell
			DisplayBye();
			return EXIT_SUCCESS;
		}
	
		executeCommand(buf);
				
	
	}
	return EXIT_SUCCESS;
}
