#include <stdio.h>
#include <stdlib.h>
#define BUSKET_NUMBER 100

struct Entry
{
    char* key;
    char* value;
    struct Entry* next;
};

struct HashTable
{
    struct Entry** buskets;
};

struct HashTable* createHashTable()
{
    struct HashTable* table = (struct HashTable*)malloc(sizeof(struct HashTable));
    table->buskets = (struct Entry**)malloc(sizeof(struct Entry*) * BUSKET_NUMBER);

    for(int i = 0; i < BUSKET_NUMBER; i++)
    {
        table->buskets[i] = NULL;
    }

    return table;
}

struct Entry* createEntry(char* key, char* value)
{
    struct Entry* node = (struct Entry*)malloc(sizeof(struct Entry));
    node->key = key;
    node->value = value;
    node->next = NULL;
    node->valueHashCode= 0;

    return node;
}

unsigned int getHashcode(char* str)
{
    char* runner = str;

    unsigned int hashCode = 0;
    while(*runner++)
    {
        hashCode += *runner;
    }

    return hashCode;
}

unsigned int equals(char* str1, char* str2)
{
    int i = 0;
    
    for(; str1[i] != '\0'; i++)
    {
        if(str2[i] == '\0')
        {
            return 0;
        }

        if(str1[i] != str2[i])
        {
            return 0;
        }
    }
    
    return 1;
}

struct Entry* moveToTail(struct Entry* node)
{
    struct Entry* current = node;

    while (current)
    {
        current = current->next;
    }

    return current;
}

struct Entry* find(struct Entry* node, char* key)
{
    struct Entry* current = node;

    while (current)
    {
        if(equals(current->key, key))
        {
            return current;
        }

        current = current->next;
    }

    return NULL;
}


int hash(int code)
{
    return code % BUSKET_NUMBER;
}

char* get(struct HashTable* table, char* key)
{
    unsigned int code = getHashcode(key);
    
    unsigned int index = hash(code);

    if (table->buskets[index] == NULL)
    {
        return NULL;
    }

    struct Entry* found = find(table->buskets[index], key);
    if (found == NULL)
    {
        return NULL;
    }

    return found->value;
}

void put(struct HashTable* table, char* key, char* value)
{
    unsigned int code = getHashcode(key);
    unsigned int index = hash(code);
    struct Entry* node = createEntry(key, value);

    printf("%s hash : [%d] index : %d \n", key, code, index);

    if(table->buskets[index] == NULL)
    {
        table->buskets[index] = node;
    }
    else
    {
        struct Entry* current = table->buskets[index];

        if(current == NULL)
        {
            current = node;
            return;
        }

        if (equals(current->key, key))
        {
            current->value = value;
            return;
        }

        while (current->next)
        {
            if(equals(current->key, key))
            {
                current->value = value;
                return;
            }

            current = current->next;
        }
        
        current->next = node;
    }
}

int main(void)
{
    struct HashTable* table = createHashTable();
    put(table, "Samsung", "Samsung is the most famous company in korea.");
    put(table, "Apple", "Apple is the compay making useful phone.");
    put(table, "Hwanhee", "Hwanhee is a person.");
    put(table, "Hwanhef", "Hwanhef is a wrong word.");

    printf("%s \n", get(table, "Samsung"));
    printf("%s \n", get(table, "Apple"));
    printf("%s \n", get(table, "Hwanhee"));
    printf("%s \n", get(table, "Hwanhee2"));
    
    put(table, "Hwanhee", "Hwanhee is a good person.");

    printf("%s \n", get(table, "Hwanhee"));
    printf("%s \n", get(table, "Hwanhef"));

    getchar();
    return 0;
}
