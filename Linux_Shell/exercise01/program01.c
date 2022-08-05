#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int signal_number) {
    // Write your code here.
    
    if(signal_number==SIGINT){
    printf("\n Interrupt SIGINT received \n ");printf("Do u really want to quit(y|n)? \n ");
    
    char c;
    scanf("%c",&c);
    if(c=='y'){
    printf("Terminated");
    exit(0);
    }
    
    else if(c=='n')
    {
     return;
    }
    }
    
    if(signal_number==SIGTERM){
    printf("\n Interrupt SIGTERM received \n ");printf("Do u really want to quit(y|n)? \n ");
    
    char c;
    scanf("%c",&c);
    if(c=='y'){
    printf("Terminated \n");
    exit(0);
    }
    
    else if(c=='n')
    {
     return;
    }
    }
}

int main() {
	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);

	printf("%d\n", getpid());
	while (1);
}
