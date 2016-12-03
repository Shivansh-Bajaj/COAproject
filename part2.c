#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
int values[16];
char opcodes[18][2][32]={

{"JNE","010100000000000000000000"},
{"JLE","011000000000000000000000"},
{"JEQ","011100000000000000000000"},
{"JMP","001000000000000000000000"},
{"MUL","10000000000000001"},
{"REM","10000000000000010"},
{"CMPI","0000000011000000110"},
{"SQRT","10000000000000111"},
{"DIV","1000000000000000000011"},
{"CMP","1000000000000000000001"},
{"MOV","1000000000000000000010"},
{"ADD","1000000000000000000101"},
{"MOVI","1000000000000000001110"},
{"INC","000000000000000000000001001"},
{"DEC","000000000000000000000001111"},
{"PRINT","000000000000000000000001110"},
{"IN","000000000001110000000000001"},
{"HLT","00000000000000000000000000000000"}
};
int index1;
char symbolTable[20][2][20];
int bstr_to_dec(char * str)
{
    int n = 0;
  int size = strlen(str) - 1;
        int count = 0;
  while ( *str != '\0' ) {
  if ( *str == '1' )
      n = n + pow(2, size - count );
  count++;
  str++;
  }
  return n;
}
char* opcode_conv(char* op,int ind){
	int i,j,k;
	char* opcode;
  int len1;
	for(i=0;i<18;i++){
		for(j=0;j<strlen(opcodes[i][1]);j++){
			if(opcodes[i][1][j]!=op[j])
			break;
			else if(j==strlen(opcodes[i][1])-1){
				opcode=opcodes[i][0];
				len1=j;
			}
		}
	}
  strcpy(symbolTable[ind][0],opcode);

   k=0;
   strncpy(symbolTable[ind][1],op+(len1+1),strlen(op)-len1);
	return opcode;
}

void MUL(int a,int b,int c){
    values[a]=values[b]*values[c];
}
void REM(int a,int b,int c){
    //printf("%d%d%d\n", values[c],values[a],values[b]);
    if(values[c]!=0)
    values[a]=values[b]%values[c];
}
void DIVI(int a,int b){
  if(values[b]!=0)
    values[a]=values[a]/values[b];
}
void CMP(int a,int b){
    if(values[a]>values[b])
    values[15]=1;
    else if(values[a]=values[b])
    values[15]=0;
    else
    values[15]=-1;
}
void MOVI(int a,int b){
    values[a]=b;
}
void MOV(int a,int b){
    values[a]=values[b];
}
void ROOT(int a,int b){
    values[a]=sqrt(b);
}
void IN(int a){
    printf("enter input\n" );
    scanf("%d",&values[a]);
}
void ADD(int a,int b){
    values[a]=values[a]+values[b];
}
void INC(int a)
{
    values[a]++;
}
void JNE(int a){
    if(values[15]!=0)
    index1=a;
      printf("index change %d\t%d\n",index1,a);
}
void JLE(int a){
    if(values[15]<=0)
      index1=a;
      printf("index change %d\t%d\n",index1,a);
}
void JEQ(int a){
    if(values[15]==0)
    index1=a;
          printf("index change %d\t%d\n",index1,a);
}
void JMP(int a){
    index1=a;
          printf("index change %d\t%d\n",index1,a);
}
void Dec(int a){
    values[a]=values[a]-1;
}
void PRINT(int a){
    if(a)
      printf("True\n" );
    else
      printf("false\n" );
}
void CMPI(int a,int b){
      //printf("in cmpi%d%d\n",values[a],b );
	if(values[a]>b){
    values[15]=1;}
    else if(values[a]==b)
    values[15]=0;
    else{
    values[15]=-1;
  }//printf("%d\n", values[15]);
}
void initLine(){
  int val1,val2,i;
	char value1[10],value2[10],value3[10];
  // switch(symbolTable[index1][0]){

     if(strcmp(symbolTable[index1][0],"IN")==0){
       val1=bstr_to_dec(symbolTable[index1][1]);
       IN(val1);
    }
    else if(strcmp(symbolTable[index1][0],"CMPI")==0){
    	strncpy(value1,symbolTable[index1][1],5==0);
    	strncpy(value2,symbolTable[index1][1]+5,8);
    	val1=bstr_to_dec(value1);
    	val2=bstr_to_dec(value2);

    	CMPI(val1,val2);
	}
	else if(strcmp(symbolTable[index1][0],"JNE")==0){
	  	val1=bstr_to_dec(symbolTable[index1][1]);
		JNE(val1);
	}
	else if(strcmp(symbolTable[index1][0],"JLE")==0){
    val1=bstr_to_dec(symbolTable[index1][1]);
    JLE(val1);
	}
	else if(strcmp(symbolTable[index1][0],"JEQ")==0){
		val1=bstr_to_dec(symbolTable[index1][1]);
		JEQ(val1);
	}
	else if(strcmp(symbolTable[index1][0],"JMP")==0){
		val1=bstr_to_dec(symbolTable[index1][1]);
		JMP(val1);
	}
	else if(strcmp(symbolTable[index1][0],"MUL")==0){
		strncpy(value1,symbolTable[index1][1],5);
		strncpy(value2,symbolTable[index1][1]+5,5);
		strncpy(value3,symbolTable[index1][1]+10,5);
		MUL(bstr_to_dec(value1),bstr_to_dec(value2),bstr_to_dec(value3));
	}
	else if(strcmp(symbolTable[index1][0],"REM")==0){
		strncpy(value1,symbolTable[index1][1],5);
		strncpy(value2,symbolTable[index1][1]+5,5);
		strncpy(value3,symbolTable[index1][1]+10,5);
		REM(bstr_to_dec(value1),bstr_to_dec(value2),bstr_to_dec(value3));
	}
	else if(strcmp(symbolTable[index1][0],"DIV")==0){
		strncpy(value1,symbolTable[index1][1],5);
		strncpy(value2,symbolTable[index1][1]+5,5);
		DIVI(bstr_to_dec(value1),bstr_to_dec(value2));
	}
	else if(strcmp(symbolTable[index1][0],"CMP")==0){
    	strncpy(value1,symbolTable[index1][1],5);
    	strncpy(value2,symbolTable[index1][1]+5,5);
    	CMPI(bstr_to_dec(value1),bstr_to_dec(value2));
	}
	else if(strcmp(symbolTable[index1][0],"MOV")==0){
		strncpy(value1,symbolTable[index1][1],5);
		strncpy(value2,symbolTable[index1][1]+5,5);
		MOV(bstr_to_dec(value1),bstr_to_dec(value2));
	}
	else if(strcmp(symbolTable[index1][0],"SQRT")==0){
		strncpy(value1,symbolTable[index1][1],5);
		strncpy(value2,symbolTable[index1][1]+5,5);
		ROOT(bstr_to_dec(value1),bstr_to_dec(value2));
	}
	else if(strcmp(symbolTable[index1][0],"ADD")==0){
		strncpy(value1,symbolTable[index1][1],5);
		strncpy(value2,symbolTable[index1][1]+5,5);
		ADD(bstr_to_dec(value1),bstr_to_dec(value2));
	}
	else if(strcmp(symbolTable[index1][0],"INC")==0){
		strncpy(value1,symbolTable[index1][1],5);
		INC(bstr_to_dec(value1));
	}
	else if(strcmp(symbolTable[index1][0],"DEC")==0){
		strncpy(value1,symbolTable[index1][1],5);
		Dec(bstr_to_dec(value1));
	}
	else if(strcmp(symbolTable[index1][0],"PRINT")==0){
		strncpy(value1,symbolTable[index1][1],5);
		PRINT(bstr_to_dec(value1));
	}
}
int main()
{
  FILE *fp;
	int i=0,j;
	char *op;
  char string[40];
  fp= fopen("output.txt","r+");
  while (fgets(string,40,fp)!=NULL){
    op=opcode_conv(string,i);
    i++;
  }
  while (1) {
    initLine();
    //printf("%d\n", strcmp("HLT",symbolTable[index1][0]));
    if(strcmp("HLT",symbolTable[index1][0])==0)
      break;
    //printf("%d\t%s its\n", index1,symbolTable[index1][0]);
    index1++;
  }
  return 0;
}
