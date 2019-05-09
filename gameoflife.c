/*
 * The Game of Life
 *
 * a 2D array of ints is used with a random number generator.
 *
 *
 * if it has exactly three neighbors a cell is born, 
 * if it has less than two neighbors a cell dies of loneliness, 
 * if it has more than three neighbors a cell dies of overcrowding, 
 * if it does not die of loneliness a cell survives to the next generation
 * or overcrowding 
 * 
 * random number generator.  A 1 cell is on, a 0 cell is off.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define MAXROWS 200
#define MAXCOLS 200

void printTableOfInts(int table[MAXROWS][MAXCOLS], int nRows, int nCols)
{
int i, j;
for (i=0; i < nRows; i++)
    {   
            for (j=0; j < nCols; j++)
            {
                printf("%5d", table[i][j]);
            }       
        printf("\n");        
    }
}
void printGameOfLife(int table[MAXROWS][MAXCOLS], int nRows, int nCols)
{
int i, j;
for (i=0; i < nRows; i++)
    {   
            for (j=0; j < nCols; j++)
            {
                if (table[i][j]==1 ){
                    printf("*");
                }
                else printf(" ");
            }       
        printf("\n");        
    }
}

void countNeighbors(int sourceGrid[MAXROWS][MAXCOLS], int countGrid[MAXROWS][MAXCOLS], int nRows, int nCols)
{
int i, j, deltaRow, deltaCol;

for (i=0; i < nRows; i++)  { 
    for (j=0; j < nCols; j++)  { 
        countGrid[i][j] = 0;
        for ( deltaRow = -1; deltaRow <= 1; deltaRow++)  { 
            for ( deltaCol = -1; deltaCol <= 1; deltaCol++)  {
                
                
                    if ( i+deltaRow >=0 && j+deltaCol >= 0 && i+deltaRow < nRows && j+deltaCol < nCols )  {
                    if (  ( deltaRow != 0 ) || ( deltaCol != 0 )  ) {
                    countGrid[i][j] = countGrid[i][j] + sourceGrid[i+deltaRow][j+deltaCol];
                    }
                }
            }               
        }
    }
}          

}               

void updateGameOfLife(int golGrid[MAXROWS][MAXCOLS], int nRows, int nCols) 
{
    int countGrid[MAXROWS][MAXCOLS];
    countNeighbors(golGrid, countGrid, nRows, nCols);
    for (int i=0; i<nRows; i++) {
        for (int j=0; j<nCols; j++) {
            if ( golGrid[i][j]==1 )  { 
                if ( countGrid[i][j] < 2 || countGrid[i][j] >= 4)  {
                    golGrid[i][j] = 0;
                }
        } else {// cell is currently empty
            if ( countGrid[i][j] == 3 )  {
                golGrid[i][j] = 1;
            }
          }
        }
    }

}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    
    int useRows = 20, useCols = 20; 
    int rowIndex, colIndex;
    
    //2Darray of doubles
    int golGrid[MAXROWS][MAXCOLS];   
    
    int golNeighborCounts[MAXROWS][MAXCOLS];
    
    for (rowIndex=0; rowIndex < useRows; rowIndex++)
    {           for (colIndex=0; colIndex < useCols; colIndex++)
         {
           golGrid[rowIndex][colIndex] = rand() % 2;
         
         }       
        
    } 

          
    printTableOfInts( golGrid, useRows, useCols );
    printGameOfLife( golGrid, useRows, useCols );
    
    countNeighbors( golGrid, golNeighborCounts, useRows, useCols );
    
    printTableOfInts( golNeighborCounts, useRows, useCols );
    
    while(1)  {
        printf("----------------------------\n");
        printGameOfLife( golGrid, useRows, useCols );
        updateGameOfLife( golGrid, useRows, useCols );
        usleep(1000000);
        system("clear");            
    }   
    
    
}


