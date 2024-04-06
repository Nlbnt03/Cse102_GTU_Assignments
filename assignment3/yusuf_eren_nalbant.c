#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size 16

int ones[8] = {119, 120, 121, 135, 137, 151, 152, 153};
int firstwall[16] = {102, 103, 104, 105, 106, 118, 122, 134, 138, 150, 154, 166, 167, 168, 169, 170};
int twowall[32] = {68, 69, 70, 71, 72, 73, 74, 75, 76, 84, 92, 100, 108, 116, 124, 132, 140, 148, 156, 164, 
172, 180, 188, 196, 197, 198, 199, 200, 201, 202, 203, 204};
int twos[24] = {85, 86, 87, 88, 89, 90, 91, 107, 123, 139, 155, 171, 187, 186, 185, 184, 183, 182, 181, 
165, 149, 133, 117, 101};
int selectedOnes[4];
int selectedTwos[3];
int usedOnes[8] = {0};  
int usedTwos[24] = {0};
char board[size * size];
int ects = 0;
int movecount = 0;
int main_flag = 1;

void initialize_game()
{
    srand(time(NULL));

    int i = 0;
    while (i < 4)
    {
        int random_index;
        do
        {
            random_index = rand() % 8;
        } while (usedOnes[random_index]);
        selectedOnes[i] = ones[random_index];
        usedOnes[random_index] = 1;
        i++;
    }

    i = 0;
    while (i < 3)
    {
        int random_index;
        do
        {
            random_index = rand() % 24;
        } while (usedTwos[random_index]);
        selectedTwos[i] = twos[random_index];
        usedTwos[random_index] = 1;
        i++;
    }

    printf("Rastgele seçilen 4 ones eleman:\n");
    i = 0;
    while (i < 4)
    {
        printf("%d\n", selectedOnes[i]);
        i++;
    }

    printf("Rastgele seçilen 3 twos eleman:\n");
    i = 0;
    while (i < 3)
    {
        printf("%d\n", selectedTwos[i]);
        i++;
    }
}

void print_board()
{
    initialize_game();
    int k = 0;
    int tmp_j;
    int i = 1;
    while (i <= 16)
    {
        if (i <= 4 || i >= 14)
        {
            int j = 1;
            while (j <= 16)
            {
                board[k] = '.';
                k++;
                j++;
            }
        }
        else if (i == 5 || i == 13)
        {
            int j = 1;
            while (j <= 16)
            {
                if (j >= 5 && j <= 13)
                {
                    board[k] = '#';
                    k++;
                }
                else
                {
                    board[k] = '.';
                    k++;
                }
                j++;
            }
        }
        else if (i == 6 || i == 12)
        {
            int j = 1;
            while (j <= 16)
            {
                if (j == 5 || j == 13)
                {
                    board[k] = '#';
                    k++;
                }
                else
                {
                    board[k] = '.';
                    k++;
                }
                j++;
            }
        }
        else if (i == 7 || i == 11)
        {
            int j = 1;
            while (j <= 16)
            {
                if (j == 5 || j == 13 || (j >= 7 && j <= 11))
                {
                    board[k] = '#';
                    k++;
                }
                else
                {
                    board[k] = '.';
                    k++;
                }
                j++;
            }
        }
        else if (i >= 8 && i <= 10)
        {
            int j = 1;
            while (j <= 16)
            {
                if (j == 5 || j == 7 || j == 11 || j == 13)
                {
                    board[k] = '#';
                    k++;
                }
                else
                {
                    board[k] = '.';
                    k++;
                }
                j++;
            }
        }
        printf("\n");
        i++;
    }
    board[(size * size) - 1] = 'X';
    board[136] = 'P';
    int d, y;
    i = 0;
    while (i < 4)
    {
        d = selectedOnes[i];
        board[d] = '1';
        i++;
    }
    i = 0;
    while (i < 3)
    {
        y = selectedTwos[i];
        board[y] = '2';
        i++;
    }
    printf("Use W (Up), A (Left), S (Down), D (Right) to move.\n");
    int index = 0;
    while (index < 16 * 16)
    {
        printf("%c ", board[index]);
        if ((index + 1) % 16 == 0)
        {
            printf("\n");
        }
        index++;
    }
    printf("Total ECTS : %d\n", ects);
}

void print_board2() {
    printf("Use W (Up), A (Left), S (Down), D (Right) to move.\n");
    int i = 0;
    while (i < 16 * 16)
    {
        printf("%c ", board[i]);
        if ((i + 1) % 16 == 0)
        {
            printf("\n");
        }
        i++;
    }
    printf("Total ECTS : %d\n", ects);
}


void move_player(char direction)
{
    int current_index;
    int i = 0;
    while (i < size * size)
    {
        if (board[i] == 'P')
        {
            current_index = i;
            break;
        }
        i++;
    }
    int start_index = 136;
    int last_index;
    int final_index = (size * size) - 1;
    int flag = 0;

    switch (direction)
    {
    case 'a':
        movecount++;
        last_index = current_index;
        current_index -= 1;
        if (board[current_index] == '#')
        {
            if (board[current_index] == '#' && board[current_index - 1] == '#')
            {
            }
            else
            {
                int i = 0;
                while (i < 16 && flag == 0)
                {
                    if (current_index == firstwall[i])
                    {
                        flag = 1;
                    }
                    i++;
                }

                i = 0;
                while (i < 32 && flag == 0)
                {
                    if (current_index == twowall[i])
                    {
                        flag = 2;
                    }
                    i++;
                }

                if (flag == 1 && ects >= 32)
                {
                    current_index -= 1;
                    board[current_index] = 'P';
                    board[last_index] = '.';
                    print_board2();
                }
                else if (flag == 2 && ects == 56)
                {
                    current_index -= 1;
                    board[current_index] = 'P';
                    board[last_index] = '.';
                    print_board2();
                }
                else
                {
                    print_board2();
                    printf("Insufficient ects !!!\n");
                }
            }
        }
        else if (current_index == 255)
        {
            board[current_index] = 'P';
            board[last_index] = '.';
            print_board2();
            main_flag = 0;
            printf("Congratulations! You have completed the game with %d moves and %d ECTS.\n\n", movecount, ects);
        }
        else if (board[current_index] == '1')
        {
            ects += 8;
            board[current_index] = 'P';
            board[last_index] = '.';
            print_board2();
        }
        else if (board[current_index] == '2')
        {
            ects += 8;
            board[current_index] = 'P';
            board[last_index] = '.';
            print_board2();
        }
        else
        {
            board[current_index] = 'P';
            board[last_index] = '.';
            print_board2();
        }
        break;

    case 'd':
        movecount++;
        last_index = current_index;
        current_index += 1;
        if (board[current_index] == '#')
        {
            if (board[current_index] == '#' && board[current_index - 1] == '#')
            {
            }
            else
            {
                int i = 0;
                while (i < 16 && flag == 0)
                {
                    if (current_index == firstwall[i])
                    {
                        flag = 1;
                    }
                    i++;
                }

                i = 0;
                while (i < 32 && flag == 0)
                {
                    if (current_index == twowall[i])
                    {
                        flag = 2;
                    }
                    i++;
                }

                if (flag == 1 && ects >= 32)
                {
                    current_index += 1;
                    board[current_index] = 'P';
                    board[last_index] = '.';
                    print_board2();
                }
                else if (flag == 2 && ects >= 56)
                {
                    current_index += 1;
                    board[current_index] = 'P';
                    board[last_index] = '.';
                    print_board2();
                }
                else
                {
                    print_board2();
                    printf("Insufficient ects !!!\n");
                }
            }
        }
        else if (current_index == 255)
        {
            board[current_index] = 'P';
            board[last_index] = '.';
            print_board2();
            main_flag = 0;
            printf("Congratulations! You have completed the game with %d moves and %d ECTS.\n\n", movecount, ects);
        }
        else if (board[current_index] == '1')
        {
            ects += 8;
            board[current_index] = 'P';
            board[last_index] = '.';
            print_board2();
        }
        else if (board[current_index] == '2')
        {
            ects += 8;
            board[current_index] = 'P';
            board[last_index] = '.';
            print_board2();
        }
        else
        {
            board[current_index] = 'P';
            board[last_index] = '.';
            print_board2();
        }
        break;

    case 'w':
        movecount++;
        last_index = current_index;
        current_index -= 16;
        if (board[current_index] == '#')
        {
            if (board[current_index] == '#' && board[current_index - 16] == '#')
            {
            }
            else
            {
                int i = 0;
                while (i < 16 && flag == 0)
                {
                    if (current_index == firstwall[i])
                    {
                        flag = 1;
                    }
                    i++;
                }

                i = 0;
                while (i < 32 && flag == 0)
                {
                    if (current_index == twowall[i])
                    {
                        flag = 2;
                    }
                    i++;
                }

                if (flag == 1 && ects >= 32)
                {
                    current_index -= 16;
                    board[current_index] = 'P';
                    board[last_index] = '.';
                    print_board2();
                }
                else if (flag == 2 && ects >= 56)
                {
                    current_index -= 16;
                    board[current_index] = 'P';
                    board[last_index] = '.';
                    print_board2();
                }
                else
                {
                    print_board2();
                    printf("Insufficient ects !!!\n");
                }
            }
        }
        else if (current_index == 255)
        {
            board[current_index] = 'P';
            board[last_index] = '.';
            print_board2();
            main_flag = 0;
            printf("Congratulations! You have completed the game with %d moves and %d ECTS.\n\n", movecount, ects);
        }
        else if (board[current_index] == '1')
        {
            ects += 8;
            board[current_index] = 'P';
            board[last_index] = '.';
            print_board2();
        }
        else if (board[current_index] == '2')
        {
            ects += 8;
            board[current_index] = 'P';
            board[last_index] = '.';
            print_board2();
        }
        else
        {
            board[current_index] = 'P';
            board[last_index] = '.';
            print_board2();
        }
        break;

    case 's':
        movecount++;
        last_index = current_index;
        current_index += 16;
        if (board[current_index] == '#')
        {
            if (board[current_index] == '#' && board[current_index + 16] == '#')
            {
            }
            else
            {
                int i = 0;
                while (i < 16 && flag == 0)
                {
                    if (current_index == firstwall[i])
                    {
                        flag = 1;
                    }
                    i++;
                }

                i = 0;
                while (i < 32 && flag == 0)
                {
                    if (current_index == twowall[i])
                    {
                        flag = 2;
                    }
                    i++;
                }

                if (flag == 1 && ects >= 32)
                {
                    current_index += 16;
                    board[current_index] = 'P';
                    board[last_index] = '.';
                    print_board2();
                }
                else if (flag == 2 && ects == 56)
                {
                    current_index += 16;
                    board[current_index] = 'P';
                    board[last_index] = '.';
                    print_board2();
                }
                else
                {
                    print_board2();
                    printf("Insufficient ects !!!\n");
                }
            }
        }
        else if (current_index == 255)
        {
            board[current_index] = 'P';
            board[last_index] = '.';
            print_board2();
            main_flag = 0;
            printf("Congratulations! You have completed the game with %d moves and %d ECTS.\n\n", movecount, ects);
        }
        else if (board[current_index] == '1')
        {
            ects += 8;
            board[current_index] = 'P';
            board[last_index] = '.';
            print_board2();
        }
        else if (board[current_index] == '2')
        {
            ects += 8;
            board[current_index] = 'P';
            board[last_index] = '.';
            print_board2();
        }
        else
        {
            board[current_index] = 'P';
            board[last_index] = '.';
            print_board2();
        }
        break;

    default:
        break;
    }
}

int main()
{
    print_board();
    
    while (main_flag)
    {
        char move;
        printf("choice :");
        scanf("%c", &move);
        if (move == 'q')
        {
            main_flag = 0;
            break;
        }
        else
        {
            move_player(move);
        }
    }
}