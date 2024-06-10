#include <stdio.h>

#define ROWS 5
#define COLS 5

char map[ROWS][COLS];

typedef struct nokta {
    int x;
    int y;
}nokta;

void createMap(struct nokta begin) 
{
    int i, j;
    for (i = 0; i < ROWS; i++) 
    {
        for (j = 0; j < COLS; j++) 
        {
            if (i == begin.x && j == begin.y) 
            
            {
                map[i][j] = 'S';
            } 
            else 
            {
                map[i][j] = '.';
            }
        }
    }
}

void printMap(char map[ROWS][COLS]) 
{
    int i, j;
    for (i = 0; i < ROWS; i++) 
    {
        for (j = 0; j < COLS; j++) 
        {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

int findPaths(int x, int y, int targetX, int targetY) 
{
    if (x < 0 || y < 0 || x >= ROWS || y >= COLS) 
    {
        return 0;
    }

    if (x == targetX && y == targetY) 
    {
        return 1;
    }
    
    int paths = 0;
    paths += findPaths(x + 1, y, targetX, targetY); 
    paths += findPaths(x, y - 1, targetX, targetY);

    return paths;
}

int main() {
    struct nokta target = {4, 0}; 
    nokta start;
    int x,y;
    
    printf("Enter a start x :");
    scanf("%d", &x);
    printf("Enter a start y :");
    scanf("%d", &y);

    start.x = x;
    start.y = y;

    createMap(start);
    printMap(map);
    
    int pathCount = findPaths(start.x, start.y, target.x, target.y);
    printf("Number of paths from (%d, %d) to (%d, %d): %d\n", start.x, start.y, target.x, target.y, pathCount);
    
    return 0;
}