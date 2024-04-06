#include <stdio.h>

int main() {
    // Student number
    long student_number = 220104004049;

    // Variables for calculations
    int sum_of_numbers = 0;
    int toplamTekrar;
    int key;

    // Calculate key
    while (student_number != 0) {
        sum_of_numbers += student_number % 10;
        student_number /= 10;
    }

    while (sum_of_numbers >= 10) {
        toplamTekrar = 0;
        while (sum_of_numbers != 0) {
            toplamTekrar += sum_of_numbers % 10;
            sum_of_numbers /= 10;
        }
        sum_of_numbers = toplamTekrar;
    }

    key = sum_of_numbers; 

    // Alphabet definition
    char alphabet[61] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                         'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                         'w', 'x', 'y', 'z', '(', '<', '=', '+', ')', '[', '*', '/', ']',
                         '{', '>', '!', '-', '}', '?', '\\', '&', '|', '%', '_', ';', '"',
                         '#', '.', '\'', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    // Read and decrypt characters
    char karakter;
    int comment_count = 0;
    while (scanf("%c", &karakter) != EOF) {
        if (karakter == '@') { // Comment marker detected
            // Read encrypted comment information
            printf("/*");
            char onlar, birler;
            scanf("%c%c", &onlar, &birler);

            // Decrypt onlar basamağı
            int tmp_index = -1;
            for (int i = 0; i < 61; i++) {
                if (onlar == alphabet[i]) {
                    tmp_index = i;
                    break;
                }
            }
            printf("There is a ");
            // Decrypt and write character if found
            if (tmp_index != -1) {
                int new_index = (tmp_index - key + 61) % 61;
                printf("%c", alphabet[new_index]);
            } else {
                // Write non-alphabetical characters directly
                printf("%c", onlar);
            }

            // Decrypt birler basamağı
            int tmp_index2 = -1;
            for (int i = 0; i < 61; i++) {
                if (birler == alphabet[i]) {
                    tmp_index2 = i;
                    break;
                }
            }

            // Decrypt and write character if found
            if (tmp_index2 != -1) {
                int new_index = (tmp_index2 - key + 61) % 61;
                printf("%c", alphabet[new_index]);
            } else {
                // Write non-alphabetical characters directly
                printf("%c", birler);
            }
            printf(" characters as comment.");
            printf("*/");
        }
        else {
            int index = -1;

            // Convert uppercase to lowercase for case-insensitive decryption
            if (karakter >= 'A' && karakter <= 'Z') {
                karakter = karakter + 32;
            }

            // Find character index in the alphabet
            for (int i = 0; i < 61; i++) {
                if (karakter == alphabet[i]) {
                    index = i;
                    break;
                }
            }

            // Decrypt and write character if found
            if (index != -1) {
                int new_index = (index - key + 61) % 61;
                printf("%c", alphabet[new_index]);
            } else {
                // Write non-alphabetical characters directly
                printf("%c", karakter);
            }
        }
    }
    return 0;
}
