#ifndef huffman_decode_h
#define huffman_decode_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman_encode.h"
#include "map2.h"


//deocdes the huffman code
char *decode_file(node *root, char *s)
{
    char ans[10000] = "";
    node *curr = root;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        // reached leaf node
        if (curr->left == NULL && curr->right == NULL)
        {
            // printf("%c", curr->letter);
            strncat(ans, &curr->letter, 1);
            curr = root;
        }
    }

    return strncat(ans, "\0", 1);
}

//sets symbols and their codes to the mapp
void encoded_string(node *root, mapp *mp, char arr[], int cnt)
{

    if (root->left)
    {
        arr[cnt] = '0';
        encoded_string(root->left, mp, arr, cnt + 1);
    }
    if (root->right)
    {
        arr[cnt] = '1';
        encoded_string(root->right, mp, arr, cnt + 1);
    }
    if (is_leaf(root))
    {
        // printf("root->letter:%c\n", root->letter);
        char ch[40] = "";
        for (int i = 0; i < cnt; i++)
        {
            strncat(ch, &arr[i], 1);
            // printf(" %c ", arr[i]);
        }
        // printf("\n%s ", ch);
        map_set2(mp, root->letter, ch);
    }
}

//makes a single string of codes by the corresponding symbol in original file 
void encoded_code(char* encodedString,char *text, char *keyy, char** val2, mapp *mp2)
{

    for (int j = 0; j < strlen(text); j++)
    {
        // printf("-%c", text[j]);
        for (int i = 0; i < map_size2(mp2); i++)
        {

            if (text[j] == keyy[i])
            {

                strcat(encodedString, val2[i]);
            }
        }
    }
  
}

#endif