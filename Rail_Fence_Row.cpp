//Implement the following Transposition Techniques concepts: Rail fence row.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define DEPTH 3
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
int length = strlen(line);
int i,j,k,l;
char (*cipher)[length];
//printf("Enter the depth of the array-> ");
//scanf("%d",&depth);
//printf("%d %d \n",depth, length);
cipher=(char(*)[length])malloc(DEPTH*length*sizeof(char));
for(i=0;i<DEPTH;i++)
{
for(j=0;j<length;j++)
{
cipher[i][j]= '0';
}
}

k=0;
j=0;
for(i=0;line[i]!='\0';i++)
{
if(line[i]=='\n')
{
cipher[k][j] = '0';
}
else
{
cipher[k][j] = line[i];
}
k++;
j++;
if(k == DEPTH)
{
k = DEPTH - 2;
for(l=i+1;line[l]!='\0';l++)
{
if(line[l]=='\n')
{
cipher[k][j] = '0';
}
else
{
cipher[k][j] = line[l];
}

k--;
j++;
if(k == -1)
{
i=l;
k=1;
break;
}
}
}
}

char *message = (char*)malloc(strlen(line)+1);
k = 0;
for(i=0;i<DEPTH;i++)
{

for(j=0;j<length;j++)
{
printf("%c",cipher[i][j]);
if(cipher[i][j]!='0')
{
message[k++] = cipher[i][j];
}

}
printf("\n");
}

message[k]='\0';
return message;

}

char* decryptedMessage(char *line)
{
int length = strlen(line)+1;
//printf("%d \n",length);
int i,j,k,l;
char (*decipher)[length];
char *message = (char*)malloc(strlen(line)+1);
decipher=(char(*)[length])malloc(DEPTH*length*sizeof(char));
for(i=0;i<DEPTH;i++)
{
for(j=0;j<length;j++)
{
decipher[i][j]= '0';
}
}
k=0;
j=0;
//puts(line);
for(i=0;line[i]!='\0';i++)
{

if(k==0)
{

decipher[k][j++] = line[i];
for(l=1;l<=3;l++)
{
decipher[k][j++]= '0';

if(j==length-1)
{
decipher[k][j]= '0';
j=0;
k++;
break;
}
}
}
else if(k==1)
{
decipher[k][j++] = '0';
decipher[k][j++] = line[i];
if(j == length-1)
{
// printf("Hello world\n");
j=0;
k++;
}
}
else if(k==2)
{
if(j==0)
{

decipher[k][j++] = '0';
decipher[k][j++] = '0';
decipher[k][j++] = line[i];
}
else
{
for(l=1;l<=3;l++)
{
decipher[k][j++]= '0';
if(j==length-1)
{
decipher[k][j]= '0';
j=0;
k++;
break;
}
}
decipher[k][j++] = line[i];
}
}
}
for(i=0;i<DEPTH;i++)
{

for(j=0;j<length;j++)
{

printf("%c",decipher[i][j]);
}
printf("\n");
}
k=0;
for(j=0;j<length;j++)
{
for(i=0;i<DEPTH;i++)
{
if(decipher[i][j]!='0')
{
message[k++] = decipher[i][j];
}
}
}
message[k] = '\0';
return message;
}
