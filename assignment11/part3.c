#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct card 
{
    const char *face;
    const char *suit;
} card;

card deste[52];
const char *suits[] = {"kupa", "karo", "sinek", "maca"};
const char *faces[] = {"As", "ikili", "üç", "dört", "beş", "alti", "yedi", "sekiz", "dokuz", "on", "vale", "kiz", "papaz"};

void createDeste() 
{
    int i = 0;
    int j, z;
    for (j = 0; j < 4; j++) 
    {     
        for (z = 0; z < 13; z++) 
        { 
            deste[i].face = faces[z];
            deste[i].suit = suits[j];
            i++;
        }
    }
}

void shuffleDeste() 
{
    int i;
    for (i = 51; i > 0; i--) 
    {
        int j = rand() % (i + 1);
        card temp = deste[i];
        deste[i] = deste[j];
        deste[j] = temp;
    }
}

void printDeste() 
{
    int i;
    for (i = 0; i < 52; i++) 
    {
        printf("%s %s\n", deste[i].face, deste[i].suit);
    }
}

int main() 
{
    srand(time(NULL)); 
    createDeste();
    shuffleDeste();
    printDeste();
    return 0;
}
