// huffman encoding algoritm

#ifndef huffman_encode_h
#define huffman_encode_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define null NULL

//node for one data and its frequency
typedef struct node
{
    char letter;
    int frequency;

    struct node *left, *right;

} node;

//vector of single nodes with current size
typedef struct nodes
{
    int size;
    int volume;
    struct node **vector;
} nodes;

//creates one single node
node *create_node(char ch, int f)
{
    node *newNode = malloc(sizeof(node) * 1);

    newNode->letter = ch;
    newNode->frequency = f;
    newNode->left = null;
    newNode->right = null;

    return newNode;
}

//creates array from the signle nodes
nodes *create_nodes(int volume)
{
    nodes *arr = malloc(sizeof(nodes) * 1);

    arr->size = 0;

    arr->vector = malloc(sizeof(node) * volume);

    return arr;
}

//function to swap nodes
void swap(node **a, node **b)
{
    node *temp = *a;
    *a = *b;
    *b = temp;
}

//function to build binary tree(minimum heap)
void heapify(nodes *arr, int id)
{
    int smallest = id;
    int left = 2 * id + 1;
    int right = 2 * id + 2;

    if (left < arr->size && arr->vector[left]->frequency < arr->vector[smallest]->frequency)
    {
        smallest = left;
    }
    if (right < arr->size && arr->vector[right]->frequency < arr->vector[smallest]->frequency)
        smallest = right;

    if (smallest != id)
    {
        swap(&arr->vector[smallest], &arr->vector[id]);
        heapify(arr, smallest);
    }
}

//function to check if tree SIZE is 1
int nodes_size_one(nodes *arr)
{
    return (arr->size == 1);
}

//is to get minimum value node in tree
node *min_element(nodes *arr)
{
    node *mn = arr->vector[0];
    arr->vector[0] = arr->vector[arr->size - 1];
    --arr->size;
    heapify(arr, 0);
    return mn;
}

//function to insert new node to the tree
void insert_node(nodes *arr, node *element)
{
    ++arr->size;
    int i = arr->size - 1;

    while (i && element->frequency < arr->vector[(i - 1) / 2]->frequency)
    {

        arr->vector[i] = arr->vector[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    arr->vector[i] = element;
}

void build_tree(nodes *arr)

{

    int n = arr->size - 1;

    for (int i = (n - 1) / 2; i >= 0; --i)
        heapify(arr, i);
}

//function to print an array of size n
void print_arr(int arr[], int n)
{

    for (int i = 0; i < n; ++i)
        printf("%d", arr[i]);

    printf("\n");
}

//function to check if this node is leaf
int is_leaf(node *root)

{

    return !(root->left) && !(root->right);
}

// Creates a tree of capacity
// equal to size and inserts all character of
// data[] in tree. Initially size of
// min heap is equal to size
nodes *create_tree(char data[], int f[], int size)

{

    nodes *arr = create_nodes(size);

    for (int i = 0; i < size; ++i)
        arr->vector[i] = create_node(data[i], f[i]);

    arr->size = size;
    build_tree(arr);

    return arr;
}

// function that builds huffman tree
node *build_huffman_tree(char data[], int freq[], int size)

{
    node *left, *right, *top;

    nodes *arr = create_tree(data, freq, size);

    // Iterate while size of tree doesn't become 1 
    while (!nodes_size_one(arr))
    {

        left = min_element(arr);
        right = min_element(arr);

        top = create_node('$', left->frequency + right->frequency);

        top->left = left;
        top->right = right;

        insert_node(arr, top);
    }

    return min_element(arr);
}

void print_codes(node *root, int arr[], int top)
{

    if (root->left)
    {

        arr[top] = 0;
        print_codes(root->left, arr, top + 1);
    }

    if (root->right)
    {

        arr[top] = 1;
        print_codes(root->right, arr, top + 1);
    }

    if (is_leaf(root))
    {

        // printf("%c: ", root->letter);
        // print_arr(arr, top);
    }
}

#endif