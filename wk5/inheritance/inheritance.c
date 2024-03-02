// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    /*Here, p is declared as a pointer to a person structure.
    The purpose is to store the "root" of the family tree that will be created by create_family(GENERATIONS).
    Essentially, p will point to the youngest member of the family tree.*/
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    // Here, p is serving as the starting point for the memory deallocation process.
    free_family(p);
}

// Create a new new_person with `generations` (with the specified number of generations)
person *create_family(int generations)
{
    // Allocate memory for new person
    /*new_person is a pointer to a newly allocated person structure.
    It serves a similar role to p in the context of this function.
    The new_person eventually gets returned and, in the main function, its address is stored in p.*/
    person *new_person = malloc(sizeof(person));

    // check for successful memory allocation
    if (new_person == NULL)
    {
        printf("memory allocation for new person failed\n");
        return NULL;
    }

    // Recursive case: if more than one generation needs to be created. (If there are still generations left to create, recursively create previous generations)
    if (generations > 1)
    {
        // Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // Set parent pointers for current person (assign the newly created parents to the current person))
        new_person->parents[0] = parent0;
        new_person->parents[1] = parent1;

        // inherit alleles from parents: randomly select one allele from each parent
        int r = rand() % 2;
        new_person->alleles[0] = (r == 0) ? parent0->alleles[0] : parent0->alleles[1];
        r = rand() % 2;
        new_person->alleles[1] = (r == 0) ? parent1->alleles[0] : parent1->alleles[1];
    }

    // Base case: If there are no generations left to create
    else
    {
        // Set parent pointers to NULL
        new_person->parents[0] = NULL;
        new_person->parents[1] = NULL;

        // Randomly assign alleles
        new_person->alleles[0] = random_allele();
        new_person->alleles[1] = random_allele();
    }

    // Return pointer to newly created person
    return new_person;
}

// Free `p` and all ancestors of `p`.
// here, p is a local pointer to the current person node being processed for deallocation.
void free_family(person *p)
{
    // Base Case: If the person pointer is NULL, nothing needs to be freed
    if (p == NULL)
    {
        return; // return as there's nothing to free
    }

    // Free parents recursively (call free_family on each parent, which will call on each grandparent, etc)
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Free current person (root) node
    free(p);
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
