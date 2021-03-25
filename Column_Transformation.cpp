//Implement the following Transposition Techniques concepts: Column
Transformation
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define COLUMN 5
char* encryptedMessage(char*);
char* decryptedMessage(char*);
//char *cipher;
int main()
{
FILE *fp;
fp= fopen("input.txt","r");

FILE *fpOut;
fpOut = fopen("output.txt", "w");
if(!fpOut)
{
printf("File does not exist");
exit(0);
}

if(!fp)
{
printf("File does not exist");
exit(0);
}
char partOfLine[128];
size_t len = sizeof(partOfLine);

char *line = malloc(len);
if(line == NULL)
{
perror("Unable to allocate memory for the line buffer.");
exit(1);
}
line[0] = '\0';
while(fgets(partOfLine, sizeof(partOfLine), fp) != NULL)
{
size_t len_used = strlen(line);
size_t chunk_used = strlen(partOfLine);
if(len - len_used < chunk_used)
{
len *= 2;
if((line = realloc(line, len)) == NULL)
{
perror("Unable to reallocate memory for the line buffer.");

free(line);
exit(1);
}
}
strncpy(line + len_used, partOfLine, len - len_used);
len_used += chunk_used;
if(line[len_used - 1] == '\n')
{
char *message = (char*)malloc(len_used+1);
puts(line);
message = encryptedMessage(line);
printf("\nEncrypted message-> ");
puts(message);
printf("\n");

fputs(message, fpOut);
fputs("\n",fpOut);
message = decryptedMessage(message);
printf("\nDecrypted message-> ");
puts(message);
fputs(message, fpOut);
fputs("\n",fpOut);
}
}
fclose(fp);
fclose(fpOut);
free(line);
}
char* encryptedMessage(char *line)
{
int length = strlen(line)+1;
int i,j,k,l;
char (*cipher)[COLUMN];
int noOfRows = length / COLUMN;
k = 0;
cipher=(char(*)[length])malloc(noOfRows*COLUMN*sizeof(char));
for(i=0;i<noOfRows;i++)
{
for(j=0;j<COLUMN;j++)
{
cipher[i][j]= line[k++];
}

if(line[k]=='\0')
{
break;
}
}
for(i=0;i<noOfRows;i++)
{
for(j=0;j<COLUMN;j++)
{
printf("%c ",cipher[i][j]);
}
printf("\n");
}
char *message = (char*)malloc(strlen(line)+1);
k=0;
for(j=0;j<COLUMN;j++)
{
for(i=0;i<noOfRows;i++)
{
message[k++] = cipher[i][j];
}
}
return message;

}

char* decryptedMessage(char *line)
{

int length = strlen(line)+1;
int i,j,k,l;
char (*decipher)[COLUMN];
int noOfRows = length / COLUMN;
k = 0;
decipher=(char(*)[length])malloc(noOfRows*COLUMN*sizeof(char));
for(j=0;j<COLUMN;j++)
{
for(i=0;i<noOfRows;i++)
{
decipher[i][j]= line[k++];
}
if(line[k]=='\0')
{
break;
}
}
char *message = (char*)malloc(strlen(line)+1);
k=0;
for(i=0;i<noOfRows;i++)
{
for(j=0;j<COLUMN;j++)
{
message[k++] = decipher[i][j];
}
}
message[k] = '\0';

return message;
}
