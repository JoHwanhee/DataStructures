#include <stdio.h>
#include <stdlib.h>
#define HASH_NUMBER 100

struct Node
{
    char* key;
    char* value;

    struct Node* next;
};

struct HashTable
{
    struct Node** values;
};

struct HashTable* createHashTable()
{
    struct HashTable* table = (struct HashTable*)malloc(sizeof(struct HashTable));
    table->values = (struct Node**)malloc(sizeof(struct Node*) * HASH_NUMBER);

    for(int i = 0; i < HASH_NUMBER; i++)
    {
        table->values[i] = NULL;
    }

    return table;
}

struct Node* createNode(char* key, char* value)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->value = value;
    node->next = NULL;

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

struct Node* moveToTail(struct Node* node)
{
    struct Node* current = node;

    while (current)
    {
        current = current->next;
    }

    return current;
}

struct Node* find(struct Node* node, char* key)
{
    struct Node* current = node;

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
    return code % HASH_NUMBER;
}

char* get(struct HashTable* table, char* key)
{
    unsigned int code = getHashcode(key);
    unsigned int index = hash(code);

    if (table->values[index] == NULL)
    {
        return NULL;
    }

    struct Node* found = find(table->values[index], key);
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
    struct Node* node = createNode(key, value);

    printf("%s hash : [%d] index : %d \n", key, code, index);

    if(table->values[index] == NULL)
    {
        table->values[index] = node;
    }
    else
    {
        struct Node* current = table->values[index];

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
