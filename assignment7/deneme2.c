#include <stdio.h>

int board_arr[14][12 * 4]; 
int stone_counts[14];
int pc_area[] = {7, 8, 9, 10, 11, 12};
int gamer_area[] = {0, 1, 2, 3, 4, 5};
int flag = 1;

void move(int index, int gamer, int *flag);
void gamePlay(int gamer);
int game_controller();
void initializeGame(int n);
void print_board();

int game_controller()
{
    int controller1 = 0;
    int controller2 = 0;
    int i, j;
    int counter1 = 0;
    int counter2 = 0;

    for (i = 0; i < 6; i++)
    {
        if (stone_counts[pc_area[i]] == 0)
        {
            counter1++;
        }
        if (counter1 == 6)
        {
            controller1 = 1;
            break;
        }
    }

    for (j = 0; j < 6; j++)
    {
        if (stone_counts[gamer_area[j]] == 0)
        {
            counter2++;
        }
        if (counter2 == 6)
        {
            controller2 = 1;
            break;
        }
    }

    if (controller1 == 1 || controller2 == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void calculate(int rows, int cols) 
{
    int i;
    for (i = 0; i < rows; i++) 
    {
        int count = 0;
        int j;
        for ( j = 0; j < cols; j++) 
        {
            if (board_arr[i][j] == 1) 
            {
                count++;
            }
        }
        stone_counts[i] = count;
    }
}

void initializeGame(int n) 
{
    int i;
    for (i = 0; i < 14; i++) 
    {
        int j;
        for (j = 0; j < n; j++)
         {
            if (i == 6 || i == 13) 
            {
                board_arr[i][j] = 0;
            } 
            else 
            {
                board_arr[i][j] = 1;
            }
        }
    }
    stone_counts[6] = 0;
    stone_counts[13] = 0;
    int x;
    for (x = 0; x < 14; x++) 
    {
        if (x != 6 && x != 13) 
        {
            stone_counts[x] = n;
        }
    }
}

void print_board()
{
    int i;
    for ( i = 1; i <= 5; i++)
    {
        if (i == 1 || i == 5)
        {
            printf("+----+---+---+---+---+---+---+----+\n");
        }
        else if(i == 2)
        {
            printf("|    | %d | %d | %d | %d | %d | %d |    |\n",stone_counts[12],stone_counts[11],stone_counts[10],stone_counts[9],stone_counts[8],stone_counts[7]);
        }
        else if(i == 3)
        {
            printf("| %d  |----+----+----+----+---| %d  |\n",stone_counts[13],stone_counts[6]);
        }
        else if(i == 4)
        {
            printf("|    | %d | %d | %d | %d | %d | %d |    |\n",stone_counts[0],stone_counts[1],stone_counts[2],stone_counts[3],stone_counts[4],stone_counts[5]);
        }
    }
}

int computer(int pc_area[], int stone_counts[]) {
    int max_index = pc_area[0]; 
    int max_stones = stone_counts[max_index]; 

    int i;
    /* Diğer indexleri kontrol ederek en fazla taş sayısına sahip olanı bulalım */
    for (i = 0; i < 6; i++) 
    {
        if (stone_counts[pc_area[i]] >= max_stones) 
        {
            max_index = pc_area[i];
            max_stones = stone_counts[max_index];
        }
    }
    return max_index;
}


void gamePlay(int gamer)
{
    int choice;
    int choice_area;
    if (gamer == 1)
    {
        printf("Oyuncu 1: Taş almak istediğiniz alani seçiniz {7, 8, 9, 10, 11, 12}:\n");
        choice_area = computer(pc_area,stone_counts);
        move(choice_area, gamer, &flag); /* choice değil, gamer kullanılmalı */
        print_board(); /* Tahtayı burada bastırın */  
    }
    else if(gamer == 2)
    {
        printf("Oyuncu 2: Taş almak istediğiniz alani seçiniz {0, 1, 2, 3, 4, 5}:\n");
        scanf("%d", &choice_area);
        move(choice_area, gamer, &flag); /*choice değil, gamer kullanılmalı*/ 
        print_board(); /*Tahtayı burada bastırın*/
    }
}

void move(int index, int gamer, int *flag)
{
    int result = 0;
    int queue = 0;
    if (gamer == 1) 
    {
    int i;
    int taken_stones = stone_counts[index]; /* Seçilen alandaki taş sayısını al*/
    stone_counts[index] = 0; /* Taşları aldığımız alanı boşalt*/

    for (i = 1; i <= taken_stones; i++) 
        {
            if (index + i == 20)
            {
                index += 1;
                stone_counts[(index + i) % 14]++;
            }
            else if (index + i > 13) 
            {
                stone_counts[(index + i) % 14]++;
            } 
            else 
            {
                stone_counts[index + i]++;
            }
        }
        if (stone_counts[(index + i - 1) % 14] == 1 || ((index + i - 1) % 14) == 13)
        {
            queue = 2;
        }
        else
        {
            queue = 1;
        }
    /*Taş dağıtımı tamamlandıktan sonra oyun tahtasını güncelle*/
    printf("Güncel oyun tahtası:\n");
    print_board();
    result = game_controller();
    if (result == 1)
    {
        if (stone_counts[13] > stone_counts[6])
        {
            printf("Kazanan oyuncu pc\n");
        }
        else if (stone_counts[6] > stone_counts[13])
        {
            printf("Kazanan oyuncu gamer\n");
        }
        else
        {
            printf("Berabere\n");
        }
        *flag = 0;
        return;
    }
    else
    {
         gamePlay(queue);
    }
  }   
    else if (gamer == 2)
    {
        int i;
        int taken_stones = stone_counts[gamer_area[index]]; /* Seçilen alandaki taş sayısını al*/
        stone_counts[gamer_area[index]] = 0; /*Taşları aldığımız alanı boşalt*/
        for (i = 1; i <= taken_stones; i++) 
        {
            if (index + i > 13) 
            {
                stone_counts[(index + i) % 14]++;
            } 
            else if (index + i == 13)
            {
                printf("amk\n");
                index += 1;
                printf("index + i = %d\n",index + i);
                stone_counts[(index + i) % 14]++;
            }
            else 
            {
                stone_counts[index + i]++;
            }
        }
        if (stone_counts[(index + i - 1) % 14] == 1 || ((index + i - 1) % 14) == 6)
        {
            queue = 1;
        }
        else
        {
            queue = 2;
        }
    /* Taş dağıtımı tamamlandıktan sonra oyun tahtasını güncelle*/
    printf("Guncel oyun tahtasi:\n");
    print_board();
    
    /*Oyuncunun hamlesini tamamladıktan sonra diğer oyuncunun hamlesine geç*/
    result = game_controller();
    if (result == 1)
    {
        if (stone_counts[13] > stone_counts[6])
        {
            printf("Kazanan oyuncu pc\n");
        }
        else if (stone_counts[6] > stone_counts[13])
        {
            printf("Kazanan oyuncu gamer\n");
        }
        else
        {
            printf("Berabere\n");
        }
        *flag = 0;
        return;
    }
    else
    {
         gamePlay(queue);
    }
}
}

int main() { 
    int n = 4;

    initializeGame(n);
    /* Oyun tahtasını ve taş sayılarını yazdıralım*/
    printf("Oyun tahtasi:\n");
    print_board(); /*Oyun tahtasının başlangıç halini yazdır*/
    int result;
    while (flag) 
    {
        gamePlay(2);
    }
    return 0;
}