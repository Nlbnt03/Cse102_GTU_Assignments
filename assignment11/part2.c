#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Hospital {
    char* name; 
    char citiesServed[4]; /*Her hastane için hizmet verilen şehirlerin karakter dizisi*/
};

int factorial(int n) 
{
    if (n == 0) return 1;
    return n * factorial(n - 1); /* Faktöriyel hesaplama fonksiyonu*/
}

int combination(int n, int r) 
{
    return factorial(n) / (factorial(r) * factorial(n - r)); /* Kombinasyon hesaplama fonksiyonu*/
}

/*Kombinasyonları bulmak için yardımcı bir işlev*/
void combinationUtil(struct Hospital hospitals[], struct Hospital data[], int start, int end, int index, int r, char cities[], int numCities, int* found, struct Hospital result[]) {
    if (*found == 1) {
        return; /*Çözüm bulunduysa devam etmeye gerek yoktur*/
    }

    /*Mevcut kombinasyonun kontrol edilmeye hazır olması durumunda*/
    if (index == r) {
        int covered[256] = {0}; /*Kapsanan şehirleri takip etmek için bir dizi*/
        int i,j;
        for ( i = 0; i < r; i++) 
        {
            for ( j = 0; j < 3; j++)
             {
                if (data[i].citiesServed[j] != '\0') 
                {
                    covered[(int)data[i].citiesServed[j]] = 1; /*Verilen hastanelerin hizmet verdiği şehirleri işaretle*/
                }
            }
        }

        int allCovered = 1; /*Tüm şehirlerin kapsandığını varsayalım*/
        for (i = 0; i < numCities; i++) 
        {     
            if (!covered[(int)cities[i]]) 
            {
                allCovered = 0; /*Eğer herhangi bir şehir kapsanmamışsa, işaretle*/
                break;
            }
        }

        if (allCovered) 
        {
            *found = 1; /*Tüm şehirler kapsanıyorsa, çözüm bulundu olarak işaretle*/
            for (i = 0; i < r; i++) 
            {
                result[i] = data[i]; /*Sonuç dizisine verileri kopyala*/
            }
        }
        return;
    }

    /* İndex'i tüm olası öğelerle değiştir*/
    int i;
    for ( i = start; i <= end && end - i + 1 >= r - index; i++) 
    {
        data[index] = hospitals[i];
        combinationUtil(hospitals, data, i + 1, end, index + 1, r, cities, numCities, found, result);
    }
}

/*Verilen hastaneler ve şehirler için tüm kombinasyonları bulan ana işlev*/
void findCombinations(struct Hospital hospitals[], int numHospitals, int r, char cities[], int numCities) {
    struct Hospital data[r]; /*Seçilen hastanelerin verilerini saklamak için bir dizi*/
    struct Hospital result[r]; /* Bulunan kombinasyonları saklamak için bir dizi*/
    int found = 0; /*Çözüm bulunup bulunmadığını belirlemek için bir bayrak*/ 

    /*Yardımcı işlevi çağırarak tüm kombinasyonları bul*/
    combinationUtil(hospitals, data, 0, numHospitals - 1, 0, r, cities, numCities, &found, result);

    /* Bulunan bir çözüm varsa ekrana yazdır, yoksa uygun bir mesaj ver*/
    if (found == 1) 
    {
        printf("Tüm şehirler %d hastane ile kapsanabilir.\n", r);
        int i,j;
        for ( i = 0; i < r; i++)
         {
            printf("%s, ", result[i].name); /*Hastane adını yazdır*/
            printf("Hizmet verilen şehirler: ");
            for ( j = 0; j < 3; j++) 
            {
                if (result[i].citiesServed[j] != '\0')
                 {
                    printf("%c ", result[i].citiesServed[j]); /*Hizmet verilen şehirleri yazdır*/ 
                }
            }
            printf("\n");
        }
    } 
    else 
    {
        printf("Tüm şehirler %d hastane ile kapsanamaz.\n", r);
    }
}

/*Ana programı test etmek için sürücü işlevi*/
int main() 
{
    struct Hospital hospitals[] = 
    {
        {"Hastane1", {'A', 'B', 'C','\0'}}, 
        {"Hastane2", {'A', 'C', 'D','\0'}}, 
        {"Hastane3", {'B', 'F', '\0','\0'}}, 
        {"Hastane4", {'D', 'E', 'F','\0'}} 
    };

    char cities[] = {'A', 'B', 'C', 'D', 'E', 'F'}; /*Kapsanacak şehirlerin dizisi*/
    int numHospitals = sizeof(hospitals) / sizeof(hospitals[0]); 
    int numCities = sizeof(cities) / sizeof(cities[0]); 

    int r;
    printf("Kurulabilecek maksimum hastane sayısını girin: ");
    scanf("%d", &r); 

    findCombinations(hospitals, numHospitals, r, cities, numCities);

    return 0;
}