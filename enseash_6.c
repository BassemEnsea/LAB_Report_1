#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>


// Displays the welcome message for the shell
void DisplaySh(void){
	char* message="$./enseash\nWelcome to ENSEA Tiny Shell.\nPour quitter, tapez 'exit'.\n";
	write(STDOUT_FILENO,message,strlen(message));
}	
// Displays the byebye message 
void DisplayBye(void){
	write(STDOUT_FILENO, "Bye bye...\n$\n", strlen("Bye bye...\n$\n"));
}	

// Execute the command that is entered
int executeCommand(char* buf){
	int pid,status;

	char Time[100];
	struct timespec t_start;
	struct timespec t_end;
	clock_gettime(CLOCK_MONOTONIC, &t_start);  //Clock starts 
	
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
		clock_gettime(CLOCK_MONOTONIC, &t_end);  //clock ends
		int sec_difference=t_end.tv_sec-t_start.tv_sec;
		int nsec_difference=t_end.tv_nsec-t_start.tv_nsec;
		int msec_difference=1000*sec_difference + nsec_difference/1000000;
		
		sprintf(Time,"%d",msec_difference);
		
		//Verification of the command type + Display the time
		if(WIFEXITED(status)==1){
			
			sprintf(Status,"%d",status);
			write(STDOUT_FILENO, "enseash % [exit:",strlen("enseash % [exit:"));
			write(STDOUT_FILENO,Status,strlen(Status));
			write(STDOUT_FILENO," | ",strlen(" | "));               
			write(STDOUT_FILENO,Time,strlen(Time));  
			write(STDOUT_FILENO, " ms",strlen(" ms"));	
			write(STDOUT_FILENO, "]\n",strlen("]\n"));
		}
		else{
			
			sprintf(Status,"%d",status);
			write(STDOUT_FILENO, "enseash % [sign:",strlen("enseash % [exit:"));
			write(STDOUT_FILENO,Status,strlen(Status));
			write(STDOUT_FILENO," | ",strlen(" | "));
			write(STDOUT_FILENO,Time,strlen(Time));
			write(STDOUT_FILENO, " ms",strlen(" ms"));
			write(STDOUT_FILENO, "]\n",strlen("]\n"));
		}
	
	
	}

}


int main(){
	DisplaySh();
	int maxSize=100; //Maximum length of input command
	char command[100];
	char* command_and_Arguments[maxSize];
	char* separator=" ";
	char * strToken;
	int index=0;
	
	
	
	while(1){
		write(STDOUT_FILENO, "enseash % ", strlen("enseash % "));
		
		int size=read(STDIN_FILENO,command,maxSize);
		char * strToken = strtok ( command, separator);
		
		while(strToken!=NULL){  //Seperation of the command and arguments entered by the user
			command_and_Arguments[index]=strToken;
			index++; 
			strToken = strtok(NULL, separator);	
		}
		buf[size-1]='\0';
		if(strcmp(buf,"exit")==0){ //Exit from the shell
			DisplayBye();
			return EXIT_SUCCESS;
		}
	
		executeCommand(buf);

	}
	return EXIT_SUCCESS;
}
