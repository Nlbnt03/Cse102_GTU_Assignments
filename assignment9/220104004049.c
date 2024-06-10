#include <stdio.h>
#include <string.h>

char taken_data[100];
char map[10][10];
int agac_sayisi;
int flag = 1;

typedef struct forest
{
    int width;
    int height;
    int flow_x;
    int flow_y;
    char map[10][10];
} forest;

typedef struct botanist
{
    int cord_x;
    int cord_y;
    int bottle_size;
} botanist;

typedef struct nokta
{
    int x;
    int y;
} nokta;

void creater()
{
    FILE *file;
    file = fopen("init.txt", "r");
    if (file == NULL)
    {
        printf("File Error!\n");
        return;
    }

    char karakter;
    int x = 0, y = 0;
    
    /*Ağaç sayısını sıfırla*/
    agac_sayisi = 0;

    while ((karakter = fgetc(file)) != EOF && y < 10)
    {
        if (karakter == '\n')
        {
            y++;
            x = 0;
            continue;
        }

        if (karakter == 'T')
        {
            agac_sayisi++;
        }

        if (karakter != ',')
        {
            map[y][x] = karakter;
            x++;
        }
    }

    fclose(file);
}

void initGame(forest *forest, botanist *botanist, nokta *agaclar)
{
    creater();
    int i, j;
    int k = 0;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (map[i][j] == 'B')
            {
                botanist->cord_x = i;
                botanist->cord_y = j;
            }
            else if (map[i][j] == 'X')
            {
                forest->flow_x = i;
                forest->flow_y = j;
            }
            else if (map[i][j] == 'T')
            {
                nokta agac;
                agac.x = i;
                agac.y = j;
                agaclar[k] = agac;
                k++;
            }
        }
    }
}

void endOfGame(char lastMap[10][10])
{
    FILE *file;

    file = fopen("output.txt","w");
   
   int i, j;
   for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if (j != 9) {
                fprintf(file, "%c, ", map[i][j]);
            } else {
                fprintf(file, "%c ", map[i][j]);
            }
        }
        fputc('\n', file); 
    }

    fclose(file);

    printf("Dosya basimi tamamlandi.\n");
    
}

void moveBotanist(char choice, forest *forest, botanist *botanist, nokta *agaclar, int agac_sayisi, int *flag)
{

    if (choice == 'q')
    {
        printf("exiting from the game\n");
        *flag = 0;
        return;   
    }
    

    if((botanist->cord_x == forest->flow_x && botanist->cord_y == forest->flow_y))
    {
        printf("I founded it\n");
        *flag = 0;
        return;
    }

    /*Bir sonraki adım için recursive çağrı yapalım*/
    if (map[botanist->cord_x][botanist->cord_y] == 'X') 
    {
            printf("Botanist reached the destination!\n");
            *flag = 0;
            return;
    }

    else
    {
        printf("Enter a choice (w-a-s-d) for exit enter a 'q' :");
        scanf(" %c", &choice);

        /* Geçici değişkenlerde botanistin mevcut konumunu saklayalım*/
        int current_x = botanist->cord_x;
        int current_y = botanist->cord_y;
        int last_x = current_x;
        int last_y = current_y;

        /*Yeni konumu hesaplayalım*/
        if (choice == 'w') current_x -= 1;
        else if (choice == 'd') current_y += 1;
        else if (choice == 's') current_x += 1;
        else if (choice == 'a') current_y -= 1;

        /*Yeni konumun ağaçlarla çakışıp çakışmadığını kontrol edelim*/
        int i;
        for (i = 0; i < agac_sayisi; i++)
        {
            if (agaclar[i].x == current_x && agaclar[i].y == current_y)
            {
                printf("Cannot move: there is a tree at the destination!\n");
                return;
            }
        }

        /*Yeni konumu haritada güncelleyelim*/
        map[current_x][current_y] = 'B';
        map[last_x][last_y] = ' ';

        /*Eğer çakışma yoksa, botanistin mevcut konumunu güncelleyelim*/
        botanist->cord_x = current_x;
        botanist->cord_y = current_y;

        /*Haritayı ve mevcut konumu yazdıralım*/
        int y, z = 0;
        printf("%d,%d\n", 10, 10);
        printf("%d,%d\n", botanist->cord_x, botanist->cord_y);
        printf("%d,%d\n", forest->flow_x, forest->flow_y);
        for (y = 0; y < 10; y++)
        {
            for (z = 0; z < 10; z++)
            {
                printf("%c ", map[y][z]);
            }
            printf("\n");
        }
    }

    moveBotanist(choice, forest, botanist, agaclar, agac_sayisi, flag);
   
}

int main()
{
    botanist botanist;
    forest forest;
    nokta agaclar[100];  /*maksimum ağaç sayısı*/

    initGame(&forest, &botanist, agaclar);

    int y, z = 0;
    char choice;

    printf("%d,%d\n", 10, 10);
    printf("%d,%d\n", botanist.cord_x, botanist.cord_y);
    printf("%d,%d\n", forest.flow_x, forest.flow_y);
    for (y = 0; y < 10; y++)
    {
        for (z = 0; z < 10; z++)
        {
            printf("%c ", map[y][z]);
        }
        printf("\n");
    }

    while (flag)
    {
        moveBotanist(choice, &forest, &botanist, agaclar, agac_sayisi, &flag);
    }
    
    endOfGame(map);
}