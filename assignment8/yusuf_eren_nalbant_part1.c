#include <stdio.h>
#include <string.h>

#define MAX_SATIR_UZUNLUGU 1000
#define MAX_KAYIT_SAYISI 1000

int kayit_sayisi = 0;

void menu()
{
    printf("****** MENU ******\n");
    printf("1. Sort and display all individuals by age\n");
    printf("2. Sort and display individuals in the branch by age\n");
    printf("3. Show individuals with the branch 'SCIENCE'\n");
    printf("4. Show computer scientist who are not mathematicians\n");
    printf("5. Exit\n");
}

void bosluklariKaldir(char *satir) 
{
    int i, j = 0;
    for (i = 0; satir[i] != '\0'; i++) {
        /* Eğer karakter bir boşluk değilse,
           yeni dizideki indeks j'ye kopyala ve j'yi bir arttır */
        if (satir[i] != ' ' && satir[i] != '\t' && satir[i] != '\n' && satir[i] != '\r') {
            satir[j++] = satir[i];
        }
    }
    /* Yeni dizideki son karakterden sonraki bölgeyi işaretle */
    satir[j] = '\0';
}

void data()
{
    FILE *read_file;
    read_file = fopen("input1.txt", "r");
    if (read_file == NULL) {
        printf("Dosya açilamadi.\n");
        return;
    }

    FILE *output_file;
    output_file = fopen("output.txt", "w");
    if (output_file == NULL) 
    {
        printf("Çikti dosyasi oluşturulamadi.\n");
        fclose(read_file);
        return;
    }

    char satir[MAX_SATIR_UZUNLUGU];
    while (fgets(satir, sizeof(satir), read_file) != NULL) 
    {
        bosluklariKaldir(satir);
        fprintf(output_file, "%s\n", satir);
    }

    fclose(read_file);
    fclose(output_file);

    read_file = fopen("output.txt","r");
    output_file = fopen("lastOutput.txt","w");
    int karakter;
    int onceki_karakter = EOF; /* Önceki karakteri saklamak için bir değişken */
    while ((karakter = fgetc(read_file)) != EOF)
    {
        if (karakter == ',' && onceki_karakter == ',')
        {
            fputs("nan,", output_file);
        }
        else
        {
            fputc(karakter, output_file);
        }
        onceki_karakter = karakter; /* Şu anki karakteri önceki karakter olarak sakla */
    }
    fclose(output_file);
    fclose(read_file);
}

struct scientist
{
    char name[100];
    char surname[100];
    int age;
    char alan[100];
};

struct scientist bilim_adamlari[MAX_KAYIT_SAYISI];
struct scientist filter[MAX_KAYIT_SAYISI];

void create_objects()
{
    char satir[MAX_SATIR_UZUNLUGU]; /* Satırları okumak için geçici bir bellek alanı */

    /* Dosyayı aç */
    FILE *dosya = fopen("lastOutput.txt", "r");
    if (dosya == NULL) 
    {
        printf("Dosya acilamadi.\n");
        return;
    }

    kayit_sayisi = 0;
    /* Satır satır oku ve bilim adamı verilerini oku */
    while (fgets(satir, sizeof(satir), dosya) != NULL && kayit_sayisi < MAX_KAYIT_SAYISI) 
    {
        sscanf(satir, "%[^,],%[^,],%d,%[^\n]", bilim_adamlari[kayit_sayisi].name,
                                                bilim_adamlari[kayit_sayisi].surname, 
                                                &bilim_adamlari[kayit_sayisi].age,
                                                bilim_adamlari[kayit_sayisi].alan);
        kayit_sayisi++;
    }
    /* Dosyayı kapat */
    fclose(dosya);
}

void sort_by_age(struct scientist bilim_adamlari[], int kayit_sayisi) 
{
    int i, j;
    struct scientist temp;

    for (i = 0; i < kayit_sayisi - 1; i++) 
    {
        for (j = 0; j < kayit_sayisi - i - 1; j++) 
        {
            if (bilim_adamlari[j].age > bilim_adamlari[j + 1].age) 
            {
                /* Swap işlemi */
                temp = bilim_adamlari[j];
                bilim_adamlari[j] = bilim_adamlari[j + 1];
                bilim_adamlari[j + 1] = temp;
            }
        }
    }
    /* Sıralanmış bilim adamlarını ekrana yazdır */
    int k;
    for (k = 0; k < kayit_sayisi; k++)
    {
        printf("%s \t %s \t %d \t %s\n", bilim_adamlari[k].name,
                                         bilim_adamlari[k].surname,
                                         bilim_adamlari[k].age,
                                         bilim_adamlari[k].alan);
    }
}

/* İlk branşa göre sıralama işlevi */
void sort_by_branch() {
    int i, j;
    struct scientist temp;

    /* İlk branşa göre sırala */
    for (i = 0; i < kayit_sayisi - 1; i++) {
        for (j = 0; j < kayit_sayisi - i - 1; j++) {
            /* İlk branşlara göre alfabetik sıralama */
            if (strcmp(bilim_adamlari[j].alan, bilim_adamlari[j + 1].alan) > 0) {
                temp = bilim_adamlari[j];
                bilim_adamlari[j] = bilim_adamlari[j + 1];
                bilim_adamlari[j + 1] = temp;
            }
            /* Eğer branşlar aynı ise yaşa göre sıralama */
            else if (strcmp(bilim_adamlari[j].alan, bilim_adamlari[j + 1].alan) == 0) {
                if (bilim_adamlari[j].age > bilim_adamlari[j + 1].age) {
                    temp = bilim_adamlari[j];
                    bilim_adamlari[j] = bilim_adamlari[j + 1];
                    bilim_adamlari[j + 1] = temp;
                }
            }
        }
    }

    int k;
    for (k = 0; k < kayit_sayisi; k++)
    {
        printf("%s \t %s \t %d \t %s\n", bilim_adamlari[k].name,bilim_adamlari[k].surname,bilim_adamlari[k].age,bilim_adamlari[k].alan);
    }
}


void filter_people_by_branch()
{
    char filtre[] = "SCIENCE";
    int i = 0;
    while (i < kayit_sayisi)
    {
        if (strstr(bilim_adamlari[i].alan,filtre) != NULL)
        {
             printf("%s \t %s \t %d \t %s\n", bilim_adamlari[i].name,bilim_adamlari[i].surname,bilim_adamlari[i].age,bilim_adamlari[i].alan);
        }
        i++;
    }
}


void filter_people_by_profession()
{
    int i;
    char filter[] = "COMPUTERSCIENCE";
    char filter2[] = "MATHEMATICS";
    for (i = 0; i < kayit_sayisi; i++)
    {
        if ((strstr(bilim_adamlari[i].alan, filter) != NULL) && (strstr(bilim_adamlari[i].alan, filter2) == NULL))
        {
         printf("%s \t %s \t %d \t %s\n", bilim_adamlari[i].name,bilim_adamlari[i].surname,bilim_adamlari[i].age,bilim_adamlari[i].alan);   
        }
    }
}

int main() 
{
    data();
    create_objects();
    int choice;
    int flag = 1;
    while (flag)
    {
        menu();
        printf("Choice :");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            sort_by_age(bilim_adamlari,kayit_sayisi);
            break;
        case 2:
            sort_by_branch();
            break;
        case 3:
            filter_people_by_branch();
            break;
        case 4:
            filter_people_by_profession();
            break;
        case 5:
            flag = 0;
            break;               
        default:
            printf("invalid choice!");
            break;
        }
    }
    
    return 0;
}