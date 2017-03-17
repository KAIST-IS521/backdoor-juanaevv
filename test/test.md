## Description of test program

- [./test.mini](https://github.com/KAIST-IS521/backdoor-juanaevv/tree/master/test/test.mini) 
Test program asks simple quiz to user. However, this quiz is non-sense. User must guess answer.
If user inputs wrong answer, program prints "Nop!" message and asks same quiz again.
If user inputs correct answer, program prints "Sense guy!" message and terminates itself.

## Pseudocode of test program

void main(){
	char * buf = malloc(/*some amount*/);
	while(1){	
                printf("1+1=\n");
        	gets(buf);
		if(!strcmp(buf,"window")||!strcmp(buf,"Window")){
			printf("Sense guy!");
			break;
		}
		else
			printf("Nop!\n");

	}
	exit(0);
}
