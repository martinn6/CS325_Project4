/*********************************************************************************************
 * Developers: Nick Martin (martinn6)
 *             Xisheng
 * 			   
 * Date: 20160526
 * Project: Project 04
 * Description: Implement an algorithim that approximates TSP.
 * *******************************************************************************************/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAXCITIES 1000

//track city and coordinates from input file.
struct Cities {
	int id;
	int x;
	int y;
};

//track 
struct Paths {
	int distance;
	int citya;
	int cityb;
};

struct TourStruct {
	int cityLength;
	int pathLength;
	int totalDistance;
	struct Cities city[MAXCITIES];
	struct Paths path[MAXCITIES];
	
};

/**********************************************************
Name: printResults()
Description: outputs the results to screen in the format:
	[ArrayName] = [n0, n1, ... n[Array.Length]]
**********************************************************/
int printResults(struct TourStruct *tour)
{
	for (int n = 0; n < tour->cityLength; n++)
	{
		printf("tour->city[%d].id=%d; ", n, tour->city[n].id);
		printf("tour->city[%d].x=%d; ", n, tour->city[n].x);
		printf("tour->city[%d].y=%d\n", n, tour->city[n].y);
	}

	return 0;
}

/**********************************************************
Name: parseNumLine()
Description: outputs the results to a file in the format:
	[ArrayName] = [n0, n1, ... n[Array.Length]]
**********************************************************/

int parseLine(struct TourStruct *tour, char line[1024])
{
	int x = 0;
	//int v[1000];
	
	// parse numbers from lines into array
	char *pt;
	pt = strtok(line," ");

	while (pt != NULL) {
		if(x==0)
			tour->city[tour->cityLength].id = atoi(pt);
		else if(x==1)
			tour->city[tour->cityLength].x = atoi(pt);
		else if(x==2)
			tour->city[tour->cityLength].y = atoi(pt);
		
		pt = strtok (NULL, " ");
		x++;
	}

	return(0);
}


/**********************************************************
Name: runRandom()
Description: Generates a random path between the cities.
	Calculates distance between cities and total 
	distance of tour.
**********************************************************/
int runRandom(struct TourStruct *tour)
{
	
	int randomArray[1000];
	
	//populate randomArray from 0->length for random shuffle
	for (int x = 0; x < tour->cityLength; x++)
	{
		randomArray[x] = x;
	}
	
	//random shuffle 
	for (int x = 0; x < tour->cityLength; x++)
	{	
		int temp = randomArray[x];
		int randnum = rand() % tour->cityLength;
		randomArray[x] = randomArray[randnum];
		randomArray[randnum] = temp;
	}
	
	//add paths between cities and calculates distance
	tour->pathLength = 0;
	for (int x = 0; x < tour->cityLength; x++)
	{
		tour->path[tour->pathLength].citya = tour->city[randomArray[x]].id;
		if(x+1 < tour->cityLength)
			tour->path[tour->pathLength].cityb = tour->city[randomArray[x+1]].id;
		else
			//back to start
			tour->path[tour->pathLength].cityb = tour->city[randomArray[0]].id;
			
		//sqrt(pow((x1 - x2),2) + pow((y1 - y2),2)
		tour->path[tour->pathLength].distance = 
			sqrt(
				pow(((float)tour->city[randomArray[x]].x /*x1*/ - (float)tour->city[randomArray[x+1]].x /*x2*/),2)
				+
				pow(((float)tour->city[randomArray[x]].y /*y1*/ - (float)tour->city[randomArray[x+1]].y /*y2*/),2)
			);
		
		//increment total distance
		tour->totalDistance += tour->path[tour->pathLength].distance;
		tour->pathLength++;
	}
	
	//test print
	printf("Random Algorithim Path Test\nTotal Distance = %d\n", tour->totalDistance);
	for (int x = 0; x < tour->pathLength; x++)
	{
		printf("tour->path[%d].citya=%d; ", x, tour->path[x].citya);
		printf("tour->path[%d].cityb=%d; ", x, tour->path[x].cityb);
		printf("tour->path[%d].distance=%d\n", x, tour->path[x].distance);
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
	struct TourStruct tour;
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
		tour.cityLength = 0;
		while ((read = getline(&line, &len, fp)) != -1) {
			parseLine(&tour, line);
			tour.cityLength++;
		}
		//print city array test
		printResults(&tour);
		runRandom(&tour);
			
		//close file
		fclose(fp);
	}
	
	//Exit
	printf("\nHave a nice day.\n");
	return 0;
}

