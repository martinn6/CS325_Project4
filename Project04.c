/*********************************************************************************************
 * Developers: Nick Martin (martinn6)
 *             Xisheng
 * 			   
 * Date: 20160422
 * Project: Project 04
 * Description: Implement a greedy algorithm.
 * *******************************************************************************************/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct cities {
	int id;
	int x;
	int y;
};

/**********************************************************
Name: printResults()
Description: outputs the results to screen in the format:
	[ArrayName] = [n0, n1, ... n[Array.Length]]
**********************************************************/
int printResults(struct cities *city, int length)
{
	for (int n = 0; n < length; n++)
	{
		printf("city[%d].id=%d; ", n, city[n].id);
		printf("city[%d].x=%d; ", n, city[n].x);
		printf("city[%d].y=%d\n", n, city[n].y);
	}

	return 0;
}

/**********************************************************
Name: parseNumLine()
Description: outputs the results to a file in the format:
	[ArrayName] = [n0, n1, ... n[Array.Length]]
**********************************************************/
int parseLine(struct cities *city, int n, char line[1024])
{
	int x = 0;
	int v[1000];
	
	//parse numbers from lines into array
	char *pt;
	pt = strtok(line," ");
	while (pt != NULL) {
		if(x==0)
			city[n].id = atoi(pt);
		else if(x==1)
			city[n].x = atoi(pt);
		else if(x==2)
			city[n].y = atoi(pt);
		
		pt = strtok (NULL, " ");
		x++;
	}

	return(0);
}

/**********************************************************
Name: main()
Description: runs the main program
**********************************************************/
int main()
{
	//Declare Variables
	struct cities city[1000];
	FILE *fp;
	char *line;
    size_t len = 0;
    ssize_t read;
	char filename[99];
	char numLine[1024];
	char *userInput = (char*) malloc(100);
	int value;
	int n = 0;

	//ask user for file or random generator
	printf("Enter filename: ");
	fgets(filename, 99, stdin);
	char *p = strchr(filename, '\n'); // p will point to the newline in filename
	if(p) *p = 0; // if p is not null, terminate filename at p
	
	//open file read-only
	fp = fopen(filename, "r");
	
	//check to make sure file is open
	if(!fp)
		perror("File not found");
	else
	{
		size_t len = 0;
		//ssize_t read;

		printf("opening file: %s...\n", filename);
		int n = 0;
		while ((read = getline(&line, &len, fp)) != -1) {
			parseLine(&city, n, line);
			n++;
		}
		//print city array test
		printResults(&city, n);
			
		//close file
		fclose(fp);
	}
	
	//Exit
	printf("\nHave a nice day.\n");
	return 0;
}

