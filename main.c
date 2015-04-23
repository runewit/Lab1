#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char translate(FILE *file2, char *line) {
	char command[100];
	char A;char B;char C;char D;char E;
	A='0';B='0';C='0';D='0';E='\n';
	
	sscanf(line,"%c",command);
	if(strncmp(&command[0],";",1)!=0){
		//don't continue if line begins with a ;
		if(strncmp(&command[0],"\n",1)!=0){
			//don't continue if line begins with a newline
			if(strncmp(&command[0],"N",1)==0){
				A='0';
			}else if(strncmp(&command[0],"L",1)==0){
					if(strncmp(&command[2],"D",1)==0){
//why doesn't space 2 work while space 0 does?
						A='1';
						B=command[6];
						C=command[10];
						D=command[11];
					}else if(strncmp(&command[2],"X",1)==0){
						A='D';
						B=command[6];
						C=command[10];
						D=command[11];
					}else if(strncmp(&command[2],"I",1)==0){
						A='2';
						B=command[6];
						C=command[11];
					}
					
			}else if(strncmp(&command[0],"S",1)==0){
						if(strncmp(&command[2],"O",1)==0){
						A='3';
						B='C';
						C=command[10];
						D=command[11];
						}else{
							A='E';
							B=command[6];
							C=command[10];
						}
			}else if(strncmp(&command[0],"M",1)==0){
						A='4';
						B=command[6];
						C=command[10];
			}else if(strncmp(&command[0],"A",1)==0){
						if(strncmp(&command[2],"I",1)==0){
							A='5';
							B=command[6];
							C=command[10];
							D=command[14];
						}else{
							if(strncmp(&command[0],"F",1)==0){
								A='6';
								B=command[6];
								C=command[10];
								D=command[14];
							}else{
								A='8';
								B=command[6];
								C=command[10];
								D=command[14];
							}
						}
			}else if(strncmp(&command[0],"O",1)==0){
						A='7';
						B=command[6];
						C=command[10];
						D=command[14];
			}else if(strncmp(&command[0],"X",1)==0){
						A='9';
						B=command[6];
						C=command[10];
						D=command[14];
			}else if(strncmp(&command[0],"R",1)==0){
						A='A';
						B=command[6];
						C='0';
						D=command[10];
			}else if(strncmp(&command[0],"J",1)==0){
						A='B';
						B=command[6];
						C=command[10];
						D=command[14];
			}else if(strncmp(&command[0],"H",1)==0){
						A='C';
			}
		}
	}
	printf("%s ", &A); //prints A, but is printing some crazy stuff such as E?{>]? or E??V\? instead of E like it's supposed to.
	printf("%c ",command[2]); //apparantly there is nothing in command[int] except for command[0] which contains the first character in the string. (observed through testing)
	fputs(&A,file2);fputs(&B,file2);fputs(&C,file2);fputs(&D,file2);fputs(line,file2);fputs(&E,file2);
	//fputs is returning some crazy stuff here, such as "0000êÎ§]ˇ0êÎ§]ˇ00êÎ§]ˇ000êÎ§]ˇ0000êÎ§]ˇ"
	return(*command);
}

int main(){
	char document_from[10];
	char document_to[10];
	char line[100];
	FILE *file1,*file2;
	int l,m;
	
	printf("What file would you like me to translate? (please use full name. eg: test.txt)");
	scanf("%s" , &document_from[0]);
	
	printf("What would you like the translated document to be called? (please use full name. eg: file.txt)");
	scanf("%s" , &document_to[0]);
	
	file1=fopen(document_from,"r");
	if(file1==NULL){
		perror("error opening file1");
		exit(0);
	}
	
	file2=fopen(document_to,"w");
	if(file2==NULL){
		perror("error creating file2");
		exit(0);
	}
	
	for(m=0;m<100;m++){
		if(fgets(line,100,file1)!=NULL){
			printf("line: %i.  ", m);
			translate(file2, line);
			puts(line);
		}
	}
	
	fclose(file1);
	fclose(file2);
}