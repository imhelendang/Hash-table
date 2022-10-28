/*
 * TEMPLATE FROM: CS 11, C Track, lab 7
 * http://users.cms.caltech.edu/~mvanier/CS11_C/labs/7/lab7.html
 *
 * PROGRAMMED BY : Jade Tran
 * CLASS : CS1D
 * SECTION : TTh 11:3 - 1:50
 * FILE: hash_table.h
 *     Definition of hash table data structures and
 *     declaration of functions that operate on them.
 * ASSIGNMENT : A3 - Hash Table part 2
 */

/*
 * The next two lines are called "include guards" and will be
 * explained in class.
 */
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

/* Number of slots in the hash table array. */
#define SLOTS 128

/*Define global variable - used to count number of collisions*/
extern int num_coll;

/*
 * Data structure definitions.
 */

/*
 * Declaration of the linked list `node' struct.
 */
typedef struct _node
{
    char *key;
    int value;
    struct _node *next; /* pointer to the next node in the list */
} node;


/*
 * Declaration of the hash table struct.
 * 'slot' is an array of node pointers, so it's a pointer to a pointer.
 */
typedef struct
{
    node **slot;
} hash_table;


/*
 * Function declarations.
 */

/*** Hash function. ***/
int hash(char *s);



/*** Linked list utilities. ***/

/* Create a single node whose 'next' field is NULL. */
node *create_node(char *key, int value);


/* Look up the passed value in the hash table. */
/* This program must run in O(1) time */
/* return a pointer to the found or node or NULL */
/* if not found */
node *lookup(hash_table *ht, char *value);      /*Parameter char *value here is char *key*/


/* Delete will attempt to find the value in */
/* the hash table; if found will display a "found" message and delete */
/* the node, along with the corresponding value that is in memory. */
/* Otherwise will display a not found message. */
/* This function must run in O(1) time */
void delete(hash_table *ht, char *value);        /*Parameter char *value here is char *key*/


/* Free all the nodes of a linked list. */
void free_list(node *list);




/*** Hash table utilities. ***/
/* Create a hash table with size of SLOTS. */
hash_table *create_hash_table(void);

/* Free all the linked lists or slots in hash table. */
void free_hash_table(hash_table *ht);


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key);


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */
void set_value(hash_table *ht, char *key, int value);


/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht);


/* This line is part of the "include guard": */
#endif  /* HASH_TABLE_H */
