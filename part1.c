#include <stdio.h>
#include <stdlib.h>
#include <string.h>
    int labelCount=0;
    char label[12][2][18];
    
char *decimal_to_binary(int len,int n){
    int c, d, count;
    char *pointer;
    count = 0;
    pointer = (char *)malloc((len+1)*sizeof(char));
    for ( c = len-1 ; c >= 0 ; c-- ){
        d = n >> c;

        if ( d & 1 )
            *(pointer+count) = 1 + '0';
        else
            *(pointer+count) = 0 + '0';

        count++;
    }
    *(pointer+count) = '\0';
    return  pointer;
}

char *getLabel(char *str){
    int i;
    for(i=0;i<labelCount;i++){
      if(strcmp(str,label[i][0])==0){
        return (label[i][1]);
      }
    }
    labelCount++;
    strcpy(label[labelCount][0],str);
    int ans=20+labelCount;
    strcpy(label[labelCount][1],decimal_to_binary(5,ans));
    return (decimal_to_binary(5,ans));
}
char opcodes[18][2][32]={
    {"IN","000000000001110000000000001"},
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
    {"HLT","00000000000000000000000000000000"}
    };

char** str_split(char* a_str, const char a_delim){
    char** result= 0;
    size_t count= 0;
    char* tmp= a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;
    while (*tmp){
        if (a_delim == *tmp){
            count++;
            last_comma = tmp;
        }
        tmp++;
    }
    count += last_comma < (a_str + strlen(a_str) - 1);
    count++;
    result = malloc(sizeof(char*) * count);
    if (result){
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }
    return result;
}
char *register_2_address(char *str){
    int i,j=0;
    char c,*n;
    char New[3];
    for(i=0;i<strlen(str);i++){
        c=str[i];
        if(c>=48 && c<=57){
            New[j++]=c;
        }
    }
    int num=atoi(New);
    n=decimal_to_binary(5,num);
    return n;
}

int main( void ){
    FILE *fp,*out;
    int inpt;
    char string[255];
    printf("enter 1-armstrong 0-prime number\n" );
    scanf("%d",&inpt);
    if(inpt)
    fp = fopen("binary1.txt", "r+");
    else
    fp = fopen("binary2.txt", "r+");

    out= fopen("output.txt","w+");
    char output[32];
    while (fgets(string,255,fp)!=NULL) {
      int i,k=0,j=0;

      char **tokens;
      tokens=str_split(string,' ');
      if (tokens){
          int i,j=0;
          for(i=0;i<16;i++){
              if(strcmp(opcodes[i][0],tokens[0])==0){
                  for(j=0;j<strlen(opcodes[i][1]);j++){
                      output[j]=opcodes[i][1][j];

                  }
              }
          }

          if(strcmp(tokens[0],"CMPI")==0){
            char *str2;
            str2=decimal_to_binary(8,atoi(tokens[1]));
            printf("string%s\n", str2);
            for(k=0;k<strlen(str2);k++,j++){
                output[j]=str2[k];
            }
              char *lab2=getLabel(tokens[2]);
              int k;
              for(k=0;j<32;k++,j++){
                  output[j]=lab2[k];
              }
          }

          else if(strcmp(tokens[0],"JNE")==0 || strcmp(tokens[0],"JLE")==0 || strcmp(tokens[0],"JEQ")==0 || strcmp(tokens[0],"JMP")==0){
                char *lab=getLabelInt(tokens[1]);
                printf("lab\t%s\n", lab);
                int k;
                for(k=0;k<strlen(lab);k++,j++){
                    output[j]=lab[k];
                  }
          }
          else{
            for (i = 1; *(tokens + i); i++)
            {
                char *regis=register_2_address(tokens[i]);
                int k;
                for(k=0;k<strlen(regis);k++,j++){
                    output[j]=regis[k];
                    // printf("%c\n", output[j]);
                }
              }
          }
          char save[35];
          strncpy(save,output,32);
          // printf("%s\n", save);
        //  printf("%s\n", output);
          printf("%s\n",save );
          fputs(save,out);
          fputc('\n',out);
        }
    }
}
