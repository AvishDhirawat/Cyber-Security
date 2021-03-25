// Implement the following Substitution: Caesar Cipher

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<iostream>
#include<cctype>
#define KEY 3
char* encryptedMessage(char*);
char* decryptedMessage(char*);
char *cipher;
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
char *line = (char*)malloc(len);
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
if((line = (char*)realloc(line, len)) == NULL)
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
printf("Plain text message-> ");
puts(line);
message = encryptedMessage(line);

printf("Encrypted message-> ");
puts(message);
fputs(message, fpOut);
message = decryptedMessage(message);
printf("Decrypted message-> ");
puts(message);
fputs(message, fpOut);
}
}
fclose(fp);
free(line);
}
char* encryptedMessage(char *line)
{
int length = strlen(line);
char *cipher=(char*)malloc(strlen(line)+1);
int i=0;
char ch;
int asciiValue;
int findChar;
for(i=0;i<length;i++)
{
ch = line[i];
if(isupper(ch))
{
asciiValue = ch;
cipher[i] = fmod((asciiValue - 65 + KEY),26)+65;
}
else if(islower(ch))

{
asciiValue = ch;
cipher[i] = fmod((asciiValue - 97 + KEY),26)+97;
}
else
{
cipher[i] = ch;
}
}
cipher[i] = '\0';
return cipher;

}

char* decryptedMessage(char *line)
{
int length = strlen(line);
char *decipher=(char*)malloc(strlen(line)+1);
int i=0;
char ch;
int asciiValue;
int findCorrect;
for(i=0;i<length;i++)
{
ch = line[i];
if(isupper(ch))
{
asciiValue = ch;
findCorrect = asciiValue - 65 - KEY;
if(findCorrect<0)
{
findCorrect = 26 + findCorrect + 65;

decipher[i] = findCorrect;
}
else
{
decipher[i] = fmod((asciiValue - 65 - KEY),26)+65;
}
//decipher[i] = fmod((asciiValue - 65 - KEY),26)+65;
}
else if(islower(ch))
{
asciiValue = ch;
findCorrect = asciiValue - 97 - KEY;
if(findCorrect<0)
{
findCorrect = 26 + findCorrect + 97;
decipher[i] = findCorrect;
}
else
{
decipher[i] = fmod((asciiValue - 97 - KEY),26)+97;
}

}
else
{
decipher[i] = ch;
}
}
decipher[i] = '\0';
return decipher;

}
