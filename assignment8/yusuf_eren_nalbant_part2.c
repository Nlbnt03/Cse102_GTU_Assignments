#include <stdio.h>
#include <string.h>

#define MAX_COL_COUNT 100
#define MAX_ROW_COUNT 100
#define MAX_MATCHES 100

char data[MAX_ROW_COUNT][MAX_COL_COUNT];

char *ft_strstr(char *str, char *to_find)
{
    int i = 0;
    int j = 0;

    if (to_find[j] == '\0')
        return str;

    while (str[i] != '\0')
    {
        if (str[i] == to_find[j])
        {
            i++;
            j++;
        }
        else if (to_find[j] == '\0')
        {
            return (&str[i - j]);
        }
        else
        {
            i++;
            j = 0;
        }
    }
    return NULL;
}

void search_p1(char strs[][MAX_COL_COUNT], int num_rows, int matches[][2], int *num_matches) {
    int i, j, k, patternLength, rowLength, matchCount;
    char *pattern = "***++++***++++***";

    patternLength = strlen(pattern);

    *num_matches = 0; /* Eşleşme sayısını sıfırla */

    /* Her bir satır için döngü */
    for (i = 0; i < num_rows; i++) {
        rowLength = strlen(strs[i]);
        
        /* Satırdaki her bir karakter için döngü */
        for (j = 0; j <= rowLength - patternLength; j++) {
            /* Desenin eşleşip eşleşmediğini kontrol et */
            for (k = 0; k < patternLength; k++) {
                if (strs[i][j+k] != pattern[k])
                    break;
            }
            /* Eğer desen tamamen eşleşirse, eşleşmenin konumunu kaydet */
            if (k == patternLength) {
                matches[*num_matches][0] = i; /* Satır indeksi */
                matches[*num_matches][1] = j; /* Başlangıç sütun indeksi */
                (*num_matches)++; /* Eşleşme sayısını arttır */
            }
        }
    }
}

/* P2 deseni arayan fonksiyon */
void search_p2(char strs[][MAX_COL_COUNT], int num_rows, int matches[][2], int *num_matches) {
    int i, j, k, rowLength, matchCount;
    char *pattern = "+*+*+";

    *num_matches = 0; /* Eşleşme sayısını sıfırla */

    /* Her bir sütun için döngü */
    for (j = 0; j < MAX_COL_COUNT; j++) {
        /* Her bir satır için döngü */
        for (i = 0; i < num_rows - 2; i++) {
            rowLength = strlen(strs[i]);
            
            /* Desenin eşleşip eşleşmediğini kontrol et */
            if (strs[i][j] == '+' && strs[i+1][j] == '*' && strs[i+2][j] == '+') {
                matches[*num_matches][0] = i; /* Satır indeksi */
                matches[*num_matches][1] = j; /* Sütun indeksi */
                (*num_matches)++; /* Eşleşme sayısını arttır */
            }
        }
    }
}

void get_data()
{
    FILE *input;
    input = fopen("input2.txt", "r");
    if (input == NULL)
    {
        printf("Dosya acilamadi\n");
        return;
    }

    char line[MAX_COL_COUNT];
    int i = 0;

    /* Dosyadan satır satır oku ve veriyi 2 boyutlu diziye aktar */
    while (i < MAX_ROW_COUNT && fgets(line, MAX_COL_COUNT, input) != NULL)
    {
        /* Satır sonundaki yeni satır karakterini (\n) kaldır */
        if (line[strlen(line) - 1] == '\n')
        {
            line[strlen(line) - 1] = '\0';
        }
        strcpy(data[i], line);
        i++;
    }

    fclose(input);

    int j;
    for (j = 0; j < i; j++)
    {
        printf("%s\n", data[j]);
    }
}

int main()
{
    get_data();
    int matches[MAX_MATCHES][2];
    int num_matches = 0;

    /* P1 desenini ara */
    search_p1(data, 10, matches, &num_matches);

    printf("Desen P1 eşleşmeleri bulunduğu yerler:\n");
    int i;
    for (i = 0; i < num_matches; i++) {
        printf("P1 @ (%d,%d)\n", matches[i][0] + 1, matches[i][1] + 1);
    }
    /* P2 desenini ara */
    search_p2(data, 10, matches, &num_matches);

    printf("Desen P2 eşleşmeleri bulunduğu yerler:\n");
    for (i = 0; i < num_matches; i++) {
        printf("P2 @ (%d,%d)\n", matches[i][0] + 1, matches[i][1] + 1);
    }
    return 0;
}