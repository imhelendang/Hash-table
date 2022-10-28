/*
 * TEMPLATE FROM: CS 11, C Track, lab 7
 * http://users.cms.caltech.edu/~mvanier/CS11_C/labs/7/lab7.html
 *
 * PROGRAMMED BY : Jade Tran
 * CLASS : CS1D
 * SECTION : TTh 11:3 - 1:50
 * FILE: hash_table.c
 *     Include the declaration of the hash table data structures
 *      and the function prototypes.
 * ASSIGNMENT : A3 - Hash Table part 2
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hash_table.h"


/*** Hash function. ***/
/*Function used to hashing key which is used as index in hash_table
*Algorithm: "key" mod number of slots in hash_table
*Precondition: value being passed is valid (here is phone number) 
*Postcondition: return "key"
*/
int hash(char *s)
{
    int i = 0;            /*Variable control loop*/

    while(*s != '\0')
        {
            i = i + *s;
            s++;
        }
    return (i % SLOTS);   /*Return the result of i mod SLOTS*/
}



/*** Linked list utilities. ***/

/* Create a single node. */
/*Function used to create a new node
*Algorithm: create and dynamically allocate new node
*Precondition: value being passed are valid
*Postcondition: assign new_node->key = pointer variable type char being passed
*                      new_node->value = variable type int being passed
*                      new_node tail points to NULL
*               return new node
*/
node *create_node(char *key, int value)
{
    node *temp = (node *)malloc(sizeof(node));         /*Create pointer temp type and Dynamically allocate*/
    temp->key = key;
    temp->value = value;
    temp->next = NULL;                                 /*Point to NULL after creating a new node*/

    return temp;
}


/* Look up the passed value in the hash table. */
/* This program must run in O(1) time */
/* return a pointer to the found or node or NULL */
/* if not found */
node *lookup(hash_table *ht, char *value)
{
    node *head;
    int i = 0;


    /*Call hash function to find the slot*/
    i = hash(value);
    head = ht->slot[i];
      
    if(head != NULL)  
        {
            if(strcmp(head->key, value) == 0)
                return head;
                                
            while(head->next != NULL)
                {
                    if(strcmp(head->key, value) == 0)
                        return head;
                    head = head->next;
                }                
        }

    return NULL;
}


/* Delete will attempt to find the value in */
/* the hash table; if found will display a "found" message and delete */
/* the node, along with the corresponding value that is in memory. */
/* Otherwise will display a not found message. */
/* This function must run in O(1) time */
void delete(hash_table *ht, char *value)
{
    node *found, *head, *temp;
    int x = hash(value);

    head = ht->slot[x];

    /*Call lookup funtion*/
    found = (node *)malloc(sizeof(node));
    found = lookup(ht, value);

    if(found == NULL)
        {
            printf("\n---Error! Can't find %s---\n", value);
            printf("---Can't delete phone number---\n");
        }
    else
        {
            printf("---Found %s!---\n", value);
            printf("---Error!---\n");
            if(head->key == found->key)
                {
                    printf("---Error1!---\n");
                    if(head->next != NULL)
                        head = found->next;
                }
            else
                {
                    printf("---Error2!---\n");
                    while(head->key !=  found->key)
                        {
                            temp = found;
                            found = found->next;
                        }
                    
                    temp->next = found->next;

                }
            
            free(found);
            printf("---Successfully delete %s!---\n\n", value);
        }
    return;
}


/* Free all the nodes of a linked list. */
/*Function used to prevent memory leak from dynamically allocating variables
*Algorithm: using free()
*Precondition: node is not NULL; otherwise, get errors
*Postcondition: free() nodes in a linked list
*/
void free_list(node *list)
{
    if (list == NULL) {
        return;
    }
 
    if (list->next) {
        free_list(list->next);
    }
 
    free(list);
 
    list = NULL;
    return;
}


/*** Hash table utilities. ***/

/* Create a new hash table. */
/*Function used to create hash table with size of SLOTS
*Algorithm: create and dynamically allocate hash table and number of slots (linked lists)
*Precondition: none
*Postcondition: create and initialize all nodes to be NULL then return hash table
*/
hash_table *create_hash_table()
{
    int i;                                                          /*Variable control loop*/
    hash_table *temp = (hash_table *)malloc(sizeof(hash_table));    /*Create pointer temp type hash_table*/
    temp->slot = (node **)malloc(sizeof(node) * SLOTS);             /*Dynamically allocate node temp->slot*/

    for(i = 0; i < SLOTS; i++)
            temp->slot[i] = NULL;
            
    return temp;
}


/* Free a hash table. */
/*Function used to prevent memory leak from dynamically allocating variables
*Algorithm: using free()
*Precondition: hash_table is not NULL; otherwise, get errors
*Postcondition: free() linked lists and hash_table
*/
void free_hash_table(hash_table *ht)
{
    int i = 0;                /*Variable control loop*/
    
    /*Loop through the linkedlist to free() memory*/
    for(i = 0; i < SLOTS; i++)
        {
            free_list(ht->slot[i]);
        }
    free(ht);   
    return;
}




/* Get value */
/*Function used to determine whether the key after hash function is valid or invalid
*Algorithm: Look for a key in the hash table.  Return 0 if not found.
*           If it is found return the associated value.
*Precondition: hash_table is not NULL
*Postcondition: return 0 or return int
*/
int get_value(hash_table *ht, char *key)
{
    /*Create a variable to store int returned from hash function*/
    int value = hash(key);  

    if(ht->slot[value] == NULL)
        return 0;
    else
        return value;
}



/* Set value */
/*Function used to add new node to hash table and set its value
*Algorithm: Set the value stored at a key.  If the key is not in the table,
*           create a new node and set the value to 'value'.  Note that this
*           function alters the hash table that was passed to it.
*Precondition: hash_table is already created
*/
void set_value(hash_table *ht, char *key, int value)
{
    node *temp = NULL;                  /*Create pointer temp type node and initialize to NULL*/
    node *head;                         /*Create pointer head type node*/
    int x = 0;                          /*Variable x type int and initialize to 0*/

    x = hash(key);                      /*Call hash function and store to variable x*/
    temp = create_node(key, x);         /*Call create node function and store node in variable temp*/


    /*If the key is not in the table, create a new node consider 2 cases*/
    if(value == 1)                      /*Case 1: no key in a linked list*/
            ht->slot[x] = temp;
    else                                /*Case 2: there is/are key(s) in a linked list*/
        {
            head = ht->slot[x];         /*traverse the list*/
            while(head->next != NULL)
                {
                    head = head->next;
                } 
            head->next = temp;          
            num_coll = num_coll + 1;                 /*Count number of collisions*/
        }

    return;
}


/* Print out the contents of the hash table as key/value pairs. */
/*
*Precondition: hash_table and its slots are created 
*Postcondition: if slot (linked list) is NULL, print in empty format
*               else, print all the nodes with its "key"
*/
void print_hash_table(hash_table *ht)
{
    int i = 0;             /*Variable control loop*/
    int x;                 /*Use to print nodes in linked list*/
    node *head;            /*Create pointer head type node*/

    printf("\tValue\tKey\n\n");
    for(i = 0; i < SLOTS; i++)
        {
            if(ht->slot[i] != NULL)
                {
                    head = ht->slot[i];
                    do
                        {
                            if(x == 1)
                                {
                                    printf("\t\t%s\n", ht->slot[i]->key);
                                }
                            else
                                {
                                    printf("\t%i\t%s\n", i, ht->slot[i]->key);
                                    x = 1;
                                }

                            head = head->next;
                        }while(head!=NULL);
                }
            else            /*Empty format - nothing in the linked list*/
                printf("\t%i\t----\n",i);
        }

    return;
}

