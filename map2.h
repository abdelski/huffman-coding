// implementation of map library
// kind of map<char,string> that is
// built in c++
// this data structure is needed to
// count the letters and corresponding codes
// which are in string(char array) format


#ifndef map2_h
#define map2_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define szz 1000 //sizeof my map
#define MAX_STRING 80 // maximum size of one data code

// structure of single map
typedef struct map_inn
{
    char key;             //key of the map
    char *value;          //value of map
    struct map_inn *next; //linked list shows to the next map
} map_inn;

//structure of the list of maps
typedef struct mapp
{
    map_inn **init; //points to every signle map
} mapp;

//puts key value into single node of map
map_inn *map_pair2(char key, char *value)
{
    map_inn *in = malloc(sizeof(map_inn) * 1);
    in->value = malloc(strlen(value) + 1);

    // copy the key and value
    in->key = key;
    strcpy(in->value, value);

    // next is null 
    in->next = NULL;

    return in;
}

//creates a list of maps
mapp *create_map2()
{
    mapp *maps = malloc(sizeof(mapp) * 1);
    maps->init = malloc(sizeof(map_inn *) * szz);

    for (int i = 0; i < szz; i++)
    {
        maps->init[i] = NULL; //initially all values in NULL in order to know the end of the future list
    }

    return maps;
}

//setting single map into list of maps
void map_set2(mapp *mp, char key, char *value)
{

    int id = key;

    map_inn *in = mp->init[id];
    map_inn *prev;

    if (in == NULL)
    {
        mp->init[id] = map_pair2(key, value);
        return;
    }

    while (in != NULL)
    {
        if (in->key == key)
        {
            free(in->value);
            in->value = malloc(strlen(value) + 1);
            strcpy(in->value, value);
            return;
        }

        prev = in;
        in = prev->next;
    }
    prev->next = map_pair2(key, value);
}

//shows the list of maps
void map_show2(mapp *mp)
{
    for (int i = 0; i < szz; ++i)
    {
        map_inn *in = mp->init[i];

        if (in == NULL)
        {
            continue;
        }

      
        for (;;)
        {
            printf("%c= %s ", in->key, in->value);

            if (in->next == NULL)
            {
                break;
            }

            in = in->next;
        }

        printf("\n");
    }
}

//function that returns size of the map
int map_size2(mapp *mp)
{
    int kol = 0;
    for (int i = 0; i < szz; ++i)
    {
        map_inn *in = mp->init[i];

        if (in == NULL)
        {
            continue;
        }

        for (;;)
        {
            ++kol;
            if (in->next == NULL)
            {
                break;
            }

            in = in->next;
        }

        // printf("%d ", kol);
    }
    return kol;
}

//function that return values of the map as array of strings
char **map_value2(mapp *mp)
{
    int j = 0;
    char **arr = malloc(sizeof(char *) * map_size2(mp));
    if (!arr)
        return NULL;
    for (int i = 0; i < map_size2(mp); i++)
    {
        arr[i] = malloc(MAX_STRING + 1);
        if (!arr[i])
        {
            free(arr);
            return NULL;
        }
    }
    for (int i = 0; i < szz; ++i)
    {
        map_inn *in = mp->init[i];

        if (in == NULL)
        {
            continue;
        }

        for (;;)
        {
            
            strcpy(arr[j], in->value);
            j++;
            if (in->next == NULL)
            {
                break;
            }

            in = in->next;
        }

    }
    return arr;
}


//function that returns keys of the map 
char *map_key2(mapp *mp)
{

    int j = 0;
    char *arr = malloc(sizeof(char) * map_size2(mp));
    for (int i = 0; i < szz; ++i)
    {
        map_inn *in = mp->init[i];

        if (in == NULL)
        {
            continue;
        }

        for (;;)
        {
            arr[j] = in->key;
            j++;
            if (in->next == NULL)
            {
                break;
            }

            in = in->next;
        }
    }
    return arr;
}

#endif