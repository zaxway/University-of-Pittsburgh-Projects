//
//  genMazeExample.c
//  MazeProject
//
//  Created by Mohit Jain on 10/19/17.
//  Copyright © 2017 Mohit Jain. All rights reserved.
//

#include <stdio.h>
#include "genMaze.h"

int genMaxeExample(int argc, char **argv)
{
    int numRows, numColumns, row, column;
    
    srand(time(0));
    
    numRows = 8;
    numColumns = 8;
    
    printf("Enter a number of rows: ");
    scanf("%i", &numRows);
    printf("Enter a number of columns: ");
    scanf("%i", &numColumns);
    
    cell *cells = (cell *) malloc(sizeof(cell) * numRows * numColumns);
    
    gen_maze(numRows, numColumns, cells);
    
    print_maze(numRows, numColumns, cells);
    
    int num_walls = get_num_walls(numRows, numColumns, cells);
    
    printf("The number of walls is %i.\n", num_walls);
    
    // Cast the one-dimensional array of cells into two-dimensional
    // array of cells
    
    cell (*cells2D)[numColumns] = (cell (*)[numColumns]) cells;
    
    // Show the north variables of each cell
    
    printf("The north component of each cell are as follows:\n");
    
    for(row = 0; row < numRows; row++)
    {
        for(column = 0; column < numColumns; column++)
        {
            printf("%i ", cells2D[row][column].north);
        }
        
        printf("\n");
    }
    
    return 0;
}
