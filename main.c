/*
 * TEMPLATE FROM: CS 11, C Track, lab 7
 * http://users.cms.caltech.edu/~mvanier/CS11_C/labs/7/lab7.html
 *
 * PROGRAMMED BY : Jade Tran
 * CLASS : CS1D
 * SECTION : TTh 11:3 - 1:50
 * FILE: main.c
 *     Main file for the hash table program.
 * ASSIGNMENT : A3 - Hash Table part 2
 * PURPOSE : Get familiar with hashing, hash table, hash function
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hash_table.h"

#define MAX_WORD_LENGTH 15

int num_coll = 0;           /*Set number of collision (global variable) = 0*/ 

/*Function add new element to hash_table
*Precondition: hash_table and its slots are already created 
*              already recieve "key" from the user (here is phone number) to add
*Postcondition: check whether after hashking "key" is valid or invalid (0)
*               then call "set_value" function to add the element at index "v" 
*               in hash_table
*/
void add_to_hash_table(hash_table *ht, char *key)
{
    int v = get_value(ht, key);
    set_value(ht, key, v + 1);
}

/*Function to print execution time in hh:mm:ss format*/ 
void print_exe_time(int time_taken)
{
    /*Variables used for output time execution in hh:mm:ss*/
    int hh, mm, ss;
    
    /*Formatting time in hh:mm:ss*/
    hh = time_taken / 3600;
    ss = time_taken %  3600;
    mm = ss / 60;
    ss = ss % 60;

    if(hh >= 0 && hh < 10)
        printf("---Time program took 0%d:", hh);
    else 
        printf("---Time program took %d:", hh);

    if(mm >= 0 && mm < 10)
        printf("0%d:", mm);
    else
        printf("%d:", mm);
    
    if(ss >= 0 && ss < 10)
        printf("0%d to execute!\n\n", ss);
    else   
        printf("%d to execute!\n\n", ss);
}



int main(int argc, char **argv)
{
    FILE *input_file;
    int nphone = 0;
    char  word[MAX_WORD_LENGTH];
    char  line[MAX_WORD_LENGTH];
    char *new_word;
    char *search_phone;             /*Pointer variable used to find a phone number*/
    double time_taken;
    clock_t t; 
    hash_table *ht;                 /*Create pointer ht hash_table type*/
    node *found_phone = NULL;
            
    system("clear");

    if (argc != 2)
    {
        exit(1);
    }

     /* Make the hash table. */
    ht = create_hash_table();

    /*
     * Open the input file.  For simplicity, we specify that the
     * input file has to contain exactly one word per line.
     */
    input_file = fopen(argv[1], "r");

    if (input_file == NULL)  /* Open failed. */
        {
            fprintf(stderr, "Input file \"%s\" does not exist! "
                            "Terminating program.\n", argv[1]);
            return 1;
        }

    /* Add the words to the hash table until there are none left. */

    while (fgets(line, MAX_WORD_LENGTH, input_file) != NULL)
        {
            /* Clear the contents of 'word'. */
            word[0] = '\0';

            /* Convert the line to a word. */
            nphone = sscanf(line, "%s", word);

            if (nphone != 1)  /* Conversion failed, e.g. due to a blank line. */
            {
                continue;
            }
            else
            {
                /* Copy the word.  Add 1 for the zero byte at the end. */
                new_word = (char *)calloc(strlen(word) + 1, sizeof(char));  /******/

                if (new_word == NULL)
                {
                    fprintf(stderr, "Error: memory allocation failed! "
                                    "Terminating program.\n");
                    return 1;
                }

                new_word = word;

                /* Add it to the hash table. */
                add_to_hash_table(ht, new_word);
            }
            
        }
    
    /*Close the file*/
    fclose(input_file);
    
    /* Print out the hash table key/value pairs. */
    printf("---The number of collisions was: %d\n", num_coll);

    /*Start the clock*/
    t = clock();

    /*lookup function*/
    printf("---Look up function!\n");
    printf("---Please enter a phone that you wish to look up:");
    scanf("%s", word);
    search_phone = word;

    /*Call look up function*/
    found_phone = lookup(ht, search_phone);

    if(found_phone == NULL)
        printf("---Error! Can't find %s\n\n", search_phone);
    else
        printf("---Found %s!\n\n", search_phone);


    /*delete function*/
    printf("---Delete function!\n");
    printf("---Please enter a phone that you wish to look up:");
    scanf("%s", word);
    search_phone = word;

    /*Call delete function*/
    delete(ht, search_phone);

    /*End counting clock 2*/
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC; 
    print_exe_time((int)(time_taken*1000));


    /* Clean up. */
    free_hash_table(ht);
    new_word = NULL;
    
    return 0;
}
