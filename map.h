// implementation of map library
// kind of map<char,int> that is
// built in c++
// this data structure is needed to
// count frequency of appearing of the
// elements of the function

#ifndef map_h
#define map_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define sz 1000 //sizeof my map

// structure of single map
typedef struct map_in
{
    char key;            //key of the map
    int value;           //value of map
    struct map_in *next; //linked list shows to the next map
} map_in;

//structure of the list of maps
typedef struct
{
    map_in **init; //points to every signle map
} map;

//puts key's value into map
map_in *map_pair(char key)
{

    map_in *in = malloc(sizeof(map_in) * 1);

    in->key = key;
    in->value = 1; //value is 1 because I need just to count nubmer of unique characters in my sting

    in->next = NULL;

    return in;
}

//creates a list of maps
map *create_map()
{
    map *maps = malloc(sizeof(map) * 1);
    maps->init = malloc(sizeof(map_in *) * sz);

    for (int i = 0; i < sz; i++)
    {
        maps->init[i] = NULL; //initially all values in NULL in order to know the end of the future list
    }

    return maps;
}

//setting single map into list of maps
void map_set(map *mp, char key)
{

    int id = key;

    map_in *in = mp->init[id];
    map_in *prev;

    if (in == NULL)
    {
        mp->init[id] = map_pair(key);
        return;
    }

    while (in != NULL)
    {
        if (in->key == key)
        {
            ++in->value;
            return;
        }

        prev = in;
        in = prev->next;
    }
    prev->next = map_pair(key);
}

//shows the list of maps
void map_show(map *mp)
{
    for (int i = 0; i < sz; ++i)
    {
        map_in *in = mp->init[i];

        if (in == NULL)
        {
            continue;
        }

        // printf("slot[%4d]: ", i);

        for (;;)
        {
            printf("%c=%d ", in->key, in->value);

            if (in->next == NULL)
            {
                break;
            }

            in = in->next;
        }

        printf("\n");
    }
}

//returns the size of the map
int map_size(map *mp)
{
    int kol = 0;
    for (int i = 0; i < sz; ++i)
    {
        map_in *in = mp->init[i];

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

//return values of the map as int array
int *map_value(map *mp)
{
    int j = 0;
    int *arr = malloc(sizeof(int) * map_size(mp));
    for (int i = 0; i < sz; ++i)
    {
        map_in *in = mp->init[i];

        if (in == NULL)
        {
            continue;
        }

        for (;;)
        {
            arr[j] = in->value;
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


// returns the keys of the map as char array
char *map_key(map *mp)
{

    int j = 0;
    char *arr = malloc(sizeof(char) * map_size(mp));
    for (int i = 0; i < sz; ++i)
    {
        map_in *in = mp->init[i];

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
