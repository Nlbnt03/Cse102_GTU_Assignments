#include <stdlib.h>
#include <stdio.h>
#include <string.h>

union Value 
{
    int intx;
    double doublex;
    char charx;
    float floatx;
};

typedef enum 
{
    INT,
    DOUBLE,
    CHAR,
    FLOAT,
    UNKNOWN
} ValueType;

typedef struct item 
{
    char *key;
    ValueType type;
    union Value value;
} item;

typedef struct customDict 
{
    item *items;
    int current_size;
    int total_size;
} customDict;

customDict *create_dict();
void add_item(customDict *dict, char *key, union Value value, ValueType type);
void deleteItem(customDict *dict, char *key);
void set_value(customDict *dict, char *key, union Value value);
union Value *search_item(customDict *dict, char *key);
void print_dict(customDict *dict);
void free_dict(customDict *dict);
void read_csv_to_dict(const char *filename, customDict *dict);