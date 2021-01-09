#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"            // this local library for counting frequency of elements of the file
#include "huffman_encode.h" //local library for encoding
#include "map2.h"           //for saving letters and their corresponding binary codes
#include "huffman_decode.h" //for decoding 

#define max_length 1000*1000*1000

void read_file();
void write_file();
void write_code_file();
void read_code_file();
int size_file();
// user_input function interact with user
void user_input()
{
    map *mp;
    int *val;
    char *keyy;
    char *keyy2;
    char **val2;
    int mp_size;
    // int fsize=size_file("file.txt");
    int f2size;

    mapp *mp2;
    char arr2[100];
    int cnt = 0;
    int arr[100];
    int top = 0;

    char *text= malloc(sizeof(char) * 10000);
    char *ftext=malloc(sizeof(char) * 10000);
            
    node *root;

    char *decodedString;
    char *encodedString= malloc(sizeof(char) * max_length);

    while (1) //loop while user do not want to leave program
    {
        int option = -1;
        printf("Press any key except(1,2,3) to exit\nPress 1 to enter name of the file\nPress 2 to encode file\nPress 3 to decode file\n"); //menu
        scanf("%d", &option);                                                                                                               // choosing option that is suggested above
        
        //switching option of what user wants
        switch (option)
        {
        case 1:
            //name of file
           
            mp = create_map();
            mp2 = create_map2();
        
            read_file(mp, text);
            break;
        case 2:
            //encode_function

            keyy = map_key(mp);
            val = map_value(mp);
            mp_size = map_size(mp);
            root = build_huffman_tree(keyy, val, mp_size);
            print_codes(root, arr, top);

            
            encoded_string(root, mp2, arr2, cnt);
            val2 = map_value2(mp2);

            encoded_code(encodedString,text, keyy, val2, mp2);
            printf("%s\n", encodedString);
            
            write_code_file(encodedString);
            break;
        case 3:
            //decode_function
            
            
           
            read_code_file(ftext);
            printf("\n%s\n", ftext);
          
            

            decodedString = decode_file(root, ftext);
            // printf("%s\n", decodedString);
            write_file(decodedString);
            free(ftext);

            break;
        default:
            printf("\nYou've left the programm!\n");
            exit(0); //for breaking program
            break;
        }
    }
}


// FILE HANDLING
//finction to read from file
void read_file(map *mp, char *str)
{
    char file_name[10];
    char c;
    printf("\nPlease enter name of the file!\n");
    // fgets(file_name, sizeof(file_name), stdin);

    scanf("%s", file_name);
    strcat(file_name, ".txt");

    FILE *myFile = fopen(file_name, "r");
    if (myFile == NULL)
    {
        printf("\nFile is not found!\n");
        exit(0);
    }
    int cnt = 0;
    while (fscanf(myFile, "%c", &c) == 1) //empty map value to be considered as space ' '
    {
        strncat(str, &c, 1);
        // if (c != '\n')
            map_set(mp, c);
    }

    map_show(mp);

    fclose(myFile);
}
int  size_file(char*file_name)
{
    char c;
    int cnt=0;
    
    FILE *myFile = fopen(file_name, "r");
    if (myFile == NULL)
    {
        printf("\nFile is not found!\n");
        exit(0);
    }
    while (fscanf(myFile, "%c", &c) == 1) //empty map value to be considered as space ' '
    {
        cnt++;
        // if (c != '\n')
    
    }


    fclose(myFile);
    return cnt;
}


void read_code_file(char *str)
{
    char *ch="huff_code_list.txt";
    char c;
    
    
    FILE *myFile = fopen(ch, "r");
    if (myFile == NULL)
    {
        printf("\nFile is not found!\n");
        exit(0);
    }
    int cnt = 0;
    while (fscanf(myFile, "%c", &c) == 1) //empty map value to be considered as space ' '
    {
        strncat(str, &c, 1);
        // printf("%c",c);
        // if (c != '\n')
           
    }

    fclose(myFile);
}


//WRITING DECODED TEXT OT THE NEW FILE CALLED HUFFOUT.TXT
void write_file(char *text)
{
    char *name = "huffOut.txt";
    FILE *myFile = fopen(name, "w");
    if (myFile == NULL)
    {
        printf("\nFile is not found!\n");
        exit(0);
    }
    for (int i = 0; i < strlen(text); i++)
    {
        fprintf(myFile, "%c", text[i]);
    }
    printf("\nNew File successfully created as hufOut.txt!\n\n");

    fclose(myFile);
}

//writes code and a symbols with their codes
void write_code_file(char* code){
    char *name = "huff_code_list.txt";

    FILE *myFile = fopen(name, "w");
    if (myFile == NULL)
    {
        printf("\nFile is not found!\n");
        exit(0);
    }
    for (int i = 0; i < strlen(code); i++)
    {
        fprintf(myFile, "%c", code[i]);
    }

     printf("\nNew File successfully created as huf_code_list.txt!\n\n");

    fclose(myFile);


}

int main()
{
    user_input();
    return 0;
}
