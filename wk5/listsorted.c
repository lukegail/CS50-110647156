#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(int argc, char *argv[])
{
    node *list = NULL; // Create a pointer (called 'list') to a node and set it to NULL
                       // This will be the start of our linked list

    // iterate thru arguments
    for (int i = 1; i < argc; i++)
    {
        int input = atoi(argv[i]); // Convert the current argument from a string to an integer and store it in 'input'

        node *new_ptr = malloc(sizeof(node)); // Declare a pointer 'new_ptr' to a node and allocate memory for the node
        if (new_ptr == NULL)
        {
            return 1;
        }

        new_ptr->number = input; // Set the 'number' value of the new node to the current 'input'

        // If list is empty
        if (list == NULL)
        {
            list = new_ptr;
        }

        // Insert new node in sorted order
        // If input begins at beginning of list, prepend new node to list
        else if (new_ptr->number < list->number) // If the number value of the new node 'new_ptr' is less than the number value of the first node in the list
        {
            new_ptr->next = list; // Point the 'next' pointer of the new node to the first node in the current list
                              // or, if only one node exists, then list = NULL so new_ptr->next = NULL, indicating it is the end of the list)
            list = new_ptr; // Set the new node as the first node in the list
        }

        // If input belongs later in list, append or insert new node to list
        else
        {
            // Iterate over nodes in list
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                // If at end of list, append new node to list
                if (ptr->next == NULL)
                {
                    // Append node
                    ptr->next = new_ptr; // make the current last node's next pointer (ptr->next) point to the new node (new_ptr).
                    break;
                }

                // If in middle of list, insert new node into list
                if (new_ptr->number < ptr->next->number) // If the number value of the new node is less than the number value of the next node in the list
                {
                    new_ptr->next = ptr->next; // Point the 'next' pointer of the new node to the next node in the current list
                    ptr->next = new_ptr; // Set the next pointer of the current node to the new node
                    break;
                }
            }
        }
    }

    // iterate over the linked list and print the value of each node
    node *ptr = list; // Declare a new pointer 'ptr' and set it to point to the first node in the list // // for (node *ptr = list; ptr != NULL; ptr = ptr->next) // alternative to while loop below
    while (ptr != NULL) // Keep going until we've gone through every node in the list (until ptr is NULL)
    {
        printf("%i\n", ptr->number); // Print the 'number' value of the current node
        ptr = ptr->next; // Move to the next node in the list
    }

    ptr = list; // Set 'ptr' to point to the first node in the list
    while (ptr != NULL)
    {
        node *next = ptr->next; // Store the address of the next node
        free(ptr); // Deallocate memory assigned to the current node
        ptr = next; // Move to the next node in the list
        /*If you tried to free(ptr) before saving the address of the next node,
        you would lose the ability to access the next node,
        and therefore the ability to continue iterating through the rest of the list*/
    }
}