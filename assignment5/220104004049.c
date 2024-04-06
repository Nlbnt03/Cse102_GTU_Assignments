#include <stdio.h>

int new1 = 0;
int new2 = 0;
int new3 = 0;
int new4 = 0;
int ids[4];
int rakamlar[10];
int readedId[4];

void get_readed_id()
{
    FILE *dosya = fopen("readed_news_id.txt","r");
    int id;
    if (dosya == NULL)
    {
        printf("Error!\n");
    }
    else
    {
        int i = 0, j = 0, k = 0;
        while (fscanf(dosya,"%d",&id) != EOF)
        {
            while (readedId[j] != '\0')
            {
                if (readedId[j] == id)
                {
                    break;
                }
                j++;
            }
            readedId[i] = id;
            i++;
        }
    }
}

void find_magic_number(FILE *file)
{
    char karakter;
    int rakam_indeksi = 0;

    if (file == NULL) 
    {
        printf("Dosya açilamadi!");
    }
    while ((karakter = fgetc(file)) != EOF) 
    {
        if (karakter == '#') {
            karakter = fgetc(file);
            if (karakter >= '0' && karakter <= '9') 
            {
                rakamlar[rakam_indeksi] = karakter - '0';
                rakam_indeksi++;
                if (rakam_indeksi >= 10) 
                {
                    break;
                }
            }
        }
    }
}

double formula(int size, int *numbers)
{
    int j = 0;
    double result = 0;
    int i;
    for (i = 0; i < size; i++) 
    {
        int num = numbers[i];
        result = result + ((num*num*num-num*num+2)*(num*num*num-num*num+2));
    }
    return result;
}

void read_titles(char *title, FILE *news) 
{
    fgets(title, 500, news);
}

void read_news(FILE *news)
{
    char new;
    printf("-------------------------------------------\n");
    while ((new = fgetc(news)) != EOF)
    { 
        printf("%c", new);
    }
    printf("-------------------------------------------\n");
    fclose(news);
}

void menu() 
{
    FILE *news1, *news2, *news3, *news4;
    char title1[500];
    char title2[500];
    char title3[500];
    char title4[500];
    char choice;

    news1 = fopen("1.txt", "r");
    news2 = fopen("2.txt", "r");
    news3 = fopen("3.txt", "r");
    news4 = fopen("4.txt", "r");

    if (news1 == NULL || news2 == NULL || news3 == NULL || news4 == NULL) 
    {
        printf("Dosya açilamadi!");
        return;
    }

    read_titles(title1, news1);
    read_titles(title2, news2);
    read_titles(title3, news3);
    read_titles(title4, news4);

    fclose(news1);
    fclose(news2);
    fclose(news3);
    fclose(news4);

    printf("**************Daily Press**************\n");
    printf("Today's news are listed for you :\n");

    printf("Title of 1. news: %s", title1);
    printf("Title of 2. news: %s", title2);
    printf("Title of 3. news: %s", title3);
    printf("Title of 4. news: %s\n", title4);
    printf("What do you want to do?\n");
    printf("a.Read a new\nb.List the readed news\nc.Get decrypted information from the news\n");
    scanf(" %c", &choice);
    
    switch (choice)
    {
    case 'a':
        get_readed_id();
        int flag = 1;
        while (flag)
        {
            int choice2;
            printf("Which news do you want to read?:");
            FILE *readed;
            readed = fopen("readed_news_id.txt","a");
            scanf("%d",&choice2);
            if (choice2 == 1)
            {
                FILE *news = fopen("1.txt","r");
                read_news(news);
                int flag1 = 0;
                int x = 0;
                while (readedId[x] != '\0')
                {
                    if (readedId[x] == 1)
                    {
                        flag1 = 1;
                        break;
                    }
                    x++;
                }
                if (flag1 == 1)
                {
                    
                }
                else
                {
                    fprintf(readed,"1\n");
                    new1 = 1;
                }
                fclose(readed);
            }
            else if (choice2 == 2)
            {
                FILE *news = fopen("2.txt","r");
                read_news(news);
                int flag2 = 0;
                int x = 0;
                while (readedId[x] != '\0')
                {
                    if (readedId[x] == 2)
                    {
                        flag2 = 1;
                        break;
                    }
                    x++;
                }
                 if (flag2 == 1)
                {
                    
                }
                else
                {
                    fprintf(readed,"2\n");
                    new2 = 1;
                }
                fclose(readed);
            }
            else if (choice2 == 3)
            {
                FILE *news = fopen("3.txt","r");
                read_news(news);
                int flag3 = 0;
                int x = 0;
                while (readedId[x] != '\0')
                {
                    if (readedId[x] == 3)
                    {
                        flag3 = 1;
                        break;
                    }
                    x++;
                }
                if (flag3 == 1)
                {
                    
                }
                else
                {
                    fprintf(readed,"3\n");
                    new3 = 1;
                }
                fclose(readed);
            }
            else if (choice2 == 4)
            {
                FILE *news = fopen("4.txt","r");
                read_news(news);
                int flag4 = 0;
                int x = 0;
                while (readedId[x] != '\0')
                {
                    if (readedId[x] == 4)
                    {
                        flag4 = 1;
                        break;
                    }
                    x++;
                }
                 if (flag4 == 1)
                {
                    
                }
                else
                {
                    fprintf(readed,"4\n");
                    new4 = 1;
                }
                fclose(readed);
            }
            else
            {
                printf("invalid choice!\n");
            }
            printf("This new is readed. Do you want to read again? Yes(1) / No(0):");
            int choice3;
            scanf("%d", &choice3);
            if (choice3 == 1)
            {
            
            }
            else
            {
                flag = 0;
                menu();
                break;
            }
        }
        break;
    case 'b':
        get_readed_id();
        int x = 0;
        while (readedId[x] != '\0')
        {
            printf("%d. new is readed\n", readedId[x]);
            x++;
        }
        char choice4;
        printf("Do you want to continue? Yes(y) / No(n): ");
        scanf(" %c", &choice4);
        if (choice4 == 'y')
        {
            menu();
            break;
        }
        else if (choice4 == 'n')
        {
            printf("exiting...\n");
            break;
        }
        break;
    case 'c':
        int choice_c;
        printf("Which news would you like to decrypt? :");
        scanf("%d", &choice_c);
        if (choice_c == 1)
        {
            FILE *file = fopen("1.txt","r");
            find_magic_number(file);
            double result;
            result = formula(sizeof(rakamlar), rakamlar);
            printf("First Experiment Key = %lf\n",result);
            fclose(file);
        }
        else if (choice_c == 2)
        {
            FILE *file = fopen("2.txt","r");
            find_magic_number(file);
            double result;
            result = formula(sizeof(rakamlar), rakamlar);
            printf("Second Experiment Key = %lf\n",result);
            fclose(file);
        }
        else if (choice_c == 3)
        {
            FILE *file = fopen("3.txt","r");
            find_magic_number(file);
            double result;
            result = formula(sizeof(rakamlar), rakamlar);
            printf("Third Experiment Key = %lf\n",result);
            fclose(file);
        }
        else if (choice_c == 4)
        {
            FILE *file = fopen("4.txt","r");
            find_magic_number(file);
            double result;
            result = formula(sizeof(rakamlar), rakamlar);
            printf("Fourth Experiment Key = %lf\n",result);
            fclose(file);
        }
        break;    
    default:
        break;
    }
}

int main() 
{
    get_readed_id();
    menu();
    return 0;
}