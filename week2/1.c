#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    char *name;
    struct person* father;
    struct person* mother;
    struct person* spouse;
    struct person* next;
    struct children* children;
};
typedef struct person* PERSON;

struct children {
    struct person* people;
    struct children* next;
};
typedef struct children* CHILDREN;

PERSON newPerson(char* name1) {
    PERSON person = (PERSON)malloc(sizeof(struct person));
    person -> name = (char*)malloc(sizeof(name1));
    strcpy(person -> name, name1);
    person -> father = NULL;
    person -> mother = NULL;
    person -> spouse = NULL;
    person -> next = NULL;
    person -> children = NULL;
    return person;
}

void addParent(PERSON person, PERSON father, PERSON mother) {
    if (father != NULL)
        person -> father = father;
    if (mother != NULL)
        person -> mother = mother;
}

void marry(PERSON person, PERSON partner) {
    person -> spouse = partner;
    partner -> spouse = person;
}

void divorce(PERSON person, PERSON partner) {
    person -> spouse = NULL;
    partner -> spouse = NULL;
}

void addChildren(PERSON child, PERSON person) {
    if (person -> children == NULL) {
        CHILDREN children = malloc(sizeof(struct children));
        children -> people = child;
        children -> next = NULL;
        person -> children = children;
    }
    else {
        CHILDREN tempChild = person -> children;
        CHILDREN previous;
        while (tempChild != NULL) {
            previous = tempChild;
            tempChild = tempChild -> next;
        }
        CHILDREN newChild = malloc(sizeof(struct children));
        newChild -> people = child;
        newChild -> next = NULL;
        previous -> next = newChild;
    }
}

void spouse(PERSON person) {
    if (person -> spouse == NULL) {
        printf("%s's spouse = None\n", person -> name);
        return;
    }
    printf("%s's spouse is %s\n", person -> name, person -> spouse -> name);
}

void parent(PERSON person) {
    printf("%s's father is %s\n%s's mother is %s\n",
           person -> name, person -> father -> name,
           person -> name, person -> mother -> name);
}

void childrenOf(PERSON person) {
    CHILDREN child = person -> children;
    if (child == NULL) {
        printf("no child\n");
        return;
    }
    CHILDREN temp = child;
    while (temp != NULL) {
        printf("%s's child is %s\n", person -> name, temp -> people -> name);
        temp = temp -> next;
    }
}

PERSON findName(PERSON sentinel, char* name1) {
    PERSON temp = sentinel;
    while(temp != NULL) {
        if (strcmp(temp -> name, name1) == 0){
            return temp;
        }
        temp = temp -> next;
    }
}

int main(){
    char name[8][10] ={
            "William",
            "Jessica",
            "Samantha",
            "Ryan",
            "Sally",
            "Sam",
            "April",
            "Alan"
    };

    char *temp;
    PERSON firstPerson;
    PERSON lastPerson = NULL;
    PERSON tempPerson;
    for(int i = 0; i < 8; i++) {
        temp = name[i];
        if (lastPerson == NULL) {
            firstPerson = lastPerson = newPerson(temp);
        }
        else {
            tempPerson = newPerson(temp);
            lastPerson -> next = tempPerson;
            lastPerson = lastPerson -> next;
        }
    }

    char* name1 = name[0];
    PERSON william = findName(firstPerson, name1);
    name1 = name[1];
    PERSON jessica = findName(firstPerson, name1);
    marry(william, jessica);

    name1 = name[2];
    PERSON samantha = findName(firstPerson, name1);
    name1 = name[3];
    PERSON ryan = findName(firstPerson, name1);
    name1 = name[4];
    PERSON sally = findName(firstPerson, name1);

    addParent(samantha, william, jessica);
    addParent(ryan, william, jessica);
    addParent(sally, william, jessica);

    addChildren(samantha, william);
    addChildren(samantha, jessica);

    addChildren(sally, william);
    addChildren(sally, jessica);

    addChildren(ryan, william);
    addChildren(ryan, jessica);

    name1 = name[5];
    PERSON sam = findName(firstPerson, name1);
    marry(sam, sally);

    name1 = name[6];
    PERSON april = findName(firstPerson, name1);
    addParent(april, sam, sally);
    addChildren(april, sam);
    addChildren(april, sally);

    name1 = name[7];
    PERSON null = NULL;
    PERSON alan = findName(firstPerson, name1);
    addParent(alan, null, sally);
    addChildren(alan, sally);

    // test to see person's spouse, children, parents
    spouse(sam);
    spouse(william);
    parent(sally);
    divorce(sam, sally);
    spouse(sam);
    spouse(sally);
    childrenOf(sam);
    childrenOf(sally);
    childrenOf(william);

    // print the people's name in the LinkedList that connect one person to another
    lastPerson = firstPerson;
    printf("\nprint people names:\n");
    while (lastPerson != NULL) {
        printf("person = %s\n", lastPerson -> name);
        lastPerson = lastPerson -> next;
    }

    // free all allocated memory
    PERSON freeThis, nextPerson;
    nextPerson = firstPerson;
    while (nextPerson!= NULL) {
        freeThis = nextPerson;
        nextPerson = nextPerson -> next;

        // if they have children, free CHILDREN memory
        CHILDREN tempChild, freeChild;
        tempChild = freeThis -> children;
        while (tempChild != NULL) {
            freeChild = tempChild;
            tempChild = tempChild -> next;
            free(freeChild);
        }

        free(freeThis -> name);
        free(freeThis);
    }
    return 0;
}