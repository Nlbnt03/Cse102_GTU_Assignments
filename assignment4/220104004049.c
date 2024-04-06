#include <stdio.h>

char first_initial(FILE *id_fp, int id) {
    char firstInitial;
    int currentId = 0;

    id_fp = fopen("second 1.txt", "r");
    if (id_fp == NULL) {
        printf("Error!");
        return -1;
    }

    while (fscanf(id_fp, "%d;", &currentId) != EOF) {
        if (currentId == id) {
            fscanf(id_fp, " %c", &firstInitial);
            fclose(id_fp);
            return firstInitial;
        } else {
            while (fgetc(id_fp) != '\n' && !feof(id_fp));
        }
    }

    fclose(id_fp);
    return '\0';  
}

char last_initial(FILE *id_fp, int id) {
    char lastInitial, tempChar;
    int currentId = 0;

    id_fp = fopen("second 1.txt", "r");
    if (id_fp == NULL) {
        printf("Error!");
        return -1;
    }

    while (fscanf(id_fp, "%d;", &currentId) != EOF) 
    {
        if (currentId == id) 
        {
            while (fscanf(id_fp, "%c", &tempChar) == 1 && tempChar != ';');
            fscanf(id_fp, " %c", &lastInitial);
            fclose(id_fp);
            return lastInitial;
        } 
        else 
        {
            while (fgetc(id_fp) != '\n' && !feof(id_fp));
        }
    }

    fclose(id_fp);
    return '\0';
}

int get_id_fi(FILE *id_fp, char first_initial) 
{
    char currentFirstInitial, tempChar;
    int idFind = 0;

    id_fp = fopen("second 1.txt", "r");
    if (id_fp == NULL) {
        printf("Error!");
        return -1;
    }

    while (fscanf(id_fp, "%d;", &idFind) != EOF) 
    {
        fscanf(id_fp, " %c", &currentFirstInitial); 

        while (fscanf(id_fp, "%c", &tempChar) == 1 && tempChar != '\n');

        if (currentFirstInitial == first_initial) 
        {
            printf("%d\n", idFind); 
        }
    }

    if (fclose(id_fp) == EOF) 
    {
        printf("Error!");
        return -1;
    }

    return 0; 
}

int get_id_li(FILE *id_fp, char last_initial) {
    char currentFirstInitial, currentLastInitial, tempChar;
    int idFind = 0;

    id_fp = fopen("second 1.txt", "r");
    if (id_fp == NULL) {
        printf("Error!");
        return -1;
    }

    while (fscanf(id_fp, "%d;", &idFind) != EOF) {
        fscanf(id_fp, " %c", &currentFirstInitial); 

        while (fscanf(id_fp, "%c", &tempChar) == 1 && tempChar != ';');

        fscanf(id_fp, " %c", &currentLastInitial);

        while (fscanf(id_fp, "%c", &tempChar) == 1 && tempChar != '\n');

        if (currentLastInitial == last_initial) {
            printf("%d\n", idFind); 
        }
    }

    if (fclose(id_fp) == EOF) 
    {
        printf("Error!");
        return -1;
    }

    return 0;
}

int average_grade(FILE *info_fp, int id) {
    int idFind = 0, midterm,midterm1, midterm2, final;

    info_fp = fopen("first 1.txt", "r");
    if (info_fp == NULL) 
    {
        printf("Error!");
        return -1;
    }

    while (idFind != id) 
    {
        fscanf(info_fp, "%d;", &idFind);
    }

    fscanf(info_fp, "%d;", &midterm1);
    fscanf(info_fp, "%d;", &midterm2);
    fscanf(info_fp, "%d;", &final);

    if (final > 100) 
    {
        midterm = midterm1;
        final = midterm2;
    } 
    else 
    {
        midterm = (midterm1 + midterm2) / 2;
    }
    return (midterm + final) / 2;
}

int main() {
    printf("-------------------- utility functions demo\n");
    char firstInitial = first_initial(NULL, 220015014);
    char lastInitial = last_initial(NULL, 220015014);
    printf("First initial of given example id (220015014): %c\n", firstInitial);
    printf("Last initial of given example id (220015014): %c\n", lastInitial);
    printf("ID's of people whose name starts with given example letter ('m'):\n");
    get_id_fi(NULL, 'm');
    printf("\n");
    printf("ID's of people whose surname starts with given example letter ('m'):\n");
    get_id_li(NULL, 'm');
    printf("\n");
    printf("Average grade of given example id (220015014): %d\n", average_grade(NULL, 210015012));
    printf("-------------------- end of utility functions demo\n\n");
    char selection ='0';
    while (selection != 'e') {
        char functionchar = '0';
        int functionint = 0;
        printf("p: Print all the users pass or fail.\n");
        printf("n: Print only the user with a specific first initial.\n");
        printf("g: Calculate the GPA of a given student.\n");
        printf("c: Print whether each user passed or failed the same class.\n");
        printf("t: Print the number of classes for the instructor.\n");
        printf("d: Print the department of all persons according to the role.\n");
        printf("l: Print the course_id of a given student.\n");
        printf("e: Quit the program.\n");
        printf("Please select: ");
        scanf("%c", &selection);
        while (getchar() != '\n');
        switch(selection) {
            case 'p':
                break;
            case 'n':
                printf("Please enter the first initial: ");
                break;
            case 'g':
                printf("Please enter the ID: ");
                break;
            case 'c':
                printf("Please enter the course ID: ");
                break;
            case 't':
                printf("Please enter the ID: ");
                break;
            case 'd':
                printf("Please enter the role initial: ");
                break;
            case 'l':
                printf("Please enter the ID: ");
                break;
            case 'e':
                printf("Exiting program...\n\n");
                break;
            default:
                printf("Invalid selection!\n");
        }
    }

    return 0;
}