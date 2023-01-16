#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Displays the welcome message for the shell

void DisplaySh(void){ 
	char* message="$./enseash\nWelcome to ENSEA Tiny Shell.\nPour quitter, tapez 'exit'.\nenseash % \n";
	write(STDOUT_FILENO,message,strlen(message));
}	

int main(){
	DisplaySh();
	
	while(1){
	
	}
	return EXIT_SUCCESS;
}
