#include "customDict.h"

customDict *create_dict()
 {
    customDict *dict = (customDict *)malloc(sizeof(customDict));
    if (dict == NULL) 
    {
        printf("Bellek ayrılamadı.\n");
        return NULL;
    }

    dict->items = NULL;
    dict->current_size = 0;
    dict->total_size = 0;

    printf("Bellek başarıyla ayrıldı.\n");
    return dict;
}

void add_item(customDict *dict, char *key, union Value value, ValueType type) 
{
    if (dict->current_size == dict->total_size)
    {
        int new_size;
        if (dict->total_size == 0)
        {
            new_size = 1;
        }
        else
        {
            new_size = dict->total_size * 2;
        }
        item *new_items = (item *)realloc(dict->items, new_size * sizeof(item));
        if (new_items == NULL)
        {
            printf("Bellek yeniden boyutlandırılamadı.\n");
            return;
        }
        dict->items = new_items;
        dict->total_size = new_size;
    }

    int currentIndex = dict->current_size;
    dict->items[currentIndex].key = (char *)malloc(strlen(key) + 1);
    if (dict->items[currentIndex].key == NULL) 
    {
        printf("Anahtar için bellek ayrılamadı.\n");
        return;
    }

    strcpy(dict->items[currentIndex].key, key);
    dict->items[currentIndex].type = type;
    dict->items[currentIndex].value = value;
    dict->current_size++;
}

void deleteItem(customDict *dict, char *key) 
{
    int index = -1;
    int i;
    for (i = 0; i < dict->current_size; i++) 
    {
        if (strcmp(dict->items[i].key, key) == 0) 
        {
            index = i;
            break;
        }
    }

    if (index == -1)
     {
        printf("Girilen key bulunamadi\n");
        return;
    }

    free(dict->items[index].key);

    for (i = index; i < dict->current_size - 1; i++) 
    {
        dict->items[i] = dict->items[i + 1];
    }

    dict->current_size--;
}

void set_value(customDict *dict, char *key, union Value value) 
{
    int index = -1;
    int i;
    for (i = 0; i < dict->current_size; i++) 
    {
        if (strcmp(dict->items[i].key, key) == 0) 
        {
            index = i;
            break;
        }
    }

    if (index == -1) 
    {
        printf("Girilen key bulunamadi\n");
        return;
    }

    dict->items[index].value = value;
}

union Value *search_item(customDict *dict, char *key) 
{
    int index = -1;
    int i;
    for ( i = 0; i < dict->current_size; i++) 
    {
        if (strcmp(dict->items[i].key, key) == 0) 
        {
            index = i;
            break;
        }
    }
    if (index == -1) 
    {
        printf("İtem bulunamadi.\n");
        return NULL;
    }
    return &dict->items[index].value;
}

void print_dict(customDict *dict) 
{
    int i;
    for (i = 0; i < dict->current_size; i++) 
    {
        printf("Key: %s\n", dict->items[i].key);
        printf("Value: ");
        switch (dict->items[i].type) 
        {
            case INT:
                printf("%d\n", dict->items[i].value.intx);
                break;
            case DOUBLE:
                printf("%lf\n", dict->items[i].value.doublex);
                break;
            case CHAR:
                printf("%c\n", dict->items[i].value.charx);
                break;
            case FLOAT:
                printf("%f\n", dict->items[i].value.floatx);
                break;
            default:
                printf("Bilinmeyen değer tipi.\n");
        }
        printf("-------------------------------------\n");
    }
}

void free_dict(customDict *dict) 
{
    int i;
    for (i = 0; i < dict->current_size; i++) 
    {
        free(dict->items[i].key);
    }
    free(dict->items);
    free(dict);
}

void read_csv_to_dict(const char *filename, customDict *dict) 
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) 
    {
        printf("Dosya acilamadi !: %s\n", filename);
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file))
    {
        char *type_str = strtok(line, ", ");
        char *key = strtok(NULL, ", ");

        union Value value;
        ValueType type;
        if (strcmp(type_str, "int") == 0) 
        {
            value.intx = atoi(key);
            type = INT;
        } 
        else if (strcmp(type_str, "double") == 0) 
        {
            value.doublex = atof(key);
            type = DOUBLE;
        } 
        else if (strcmp(type_str, "char") == 0) 
        {
            value.charx = key[0];
            type = CHAR;
        } 
        else if (strcmp(type_str, "float") == 0) 
        {
            value.floatx = atof(key);
            type = FLOAT;
        } else {
            printf("Bilinmeyen tip: %s\n", type_str);
            type = UNKNOWN;
            continue; 
        }

        char *value_str;
        while ((value_str = strtok(NULL, ", ")) != NULL) 
        {
            union Value new_value;
            if (strcmp(type_str, "int") == 0) 
            {
                new_value.intx = atoi(value_str);
            } 
            else if (strcmp(type_str, "double") == 0) 
            {
                new_value.doublex = atof(value_str);
            } 
            else if (strcmp(type_str, "char") == 0) 
            {
                new_value.charx = value_str[0];
            }
             else if (strcmp(type_str, "float") == 0) 
            {
                new_value.floatx = atof(value_str);
            }
            add_item(dict, key, new_value, type);
        }
    }

    fclose(file);
}

int main() {
    customDict *myDict = create_dict();
    if (myDict == NULL) 
    {
        return 1;
    }
    read_csv_to_dict("data.csv", myDict);

    printf("Sözlüğün içeriği:\n");
    print_dict(myDict);

    free_dict(myDict);

    return 0;
}