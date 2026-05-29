#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Contact{
    char name[50];
    char phone[15];
    struct Contact *next;
};

struct Contact *head = NULL;

/* implement an insertContact() function that dynamically allocates memory for a new node
   using malloc, takes user input for the contact's name and phone number, sets the next pointer
   to NULL, and inserts the node at the end of the list by traversing from head to the last node
   and linking it appropriately; */
void insertContact() {

    /*implement an insertContact() function that dynamically allocates memory for a new node using malloc*/
    struct Contact *newNode = malloc(sizeof(struct Contact));

    /*ensure safe memory allocation*/
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }

    struct Contact *temp = head;

    /* takes user input for the contact's name and phone number */
    printf("Enter name: ");
    scanf("%s", newNode->name);

    printf("Enter phone: ");
    scanf("%s", newNode->phone);

    /* sets the next pointer to NULL */
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        return;
    }

    /* inserts the node at the end of the list by traversing from head to the last node */
    while (temp->next != NULL) {
        temp = temp->next;
    }

    /* and linking it appropriately */
    temp->next = newNode;
}

void viewContacts(){
    struct Contact *temp = head;

    if (temp == NULL){
        printf("List empty\n");
        return;
    }

    while(temp != NULL){
        printf("Name: %s | Phone: %s\n", temp->name, temp->phone);
        temp = temp->next;
    }
}

/* create a searchContact() function that asks the user for a name, then traverses the list
   comparing each node's name using string comparison, printing the matching contact if found
   or a "not found" message if no match exists; */
void searchContact(){
    struct Contact *temp = head;
    char name[50];
    printf("Enter name: ");
    scanf(" %[^\n]", &name);

    if (temp == NULL){
        printf("List empty\n");
        return;
    }

    while (temp != NULL){
        if(strcmp(temp->name, name)==0) {
            printf("Found: %s | %s\n", temp->name, temp->phone);
            return;
        }
        temp = temp->next;
    }
    printf("Not found\n");
}

void deleteContact(){
    struct Contact *temp = head;
    struct Contact *prev = NULL;
    char name[50];

    printf("Enter name: ");
    scanf(" %[^\n]", &name);


    if(temp != NULL && strcmp(name, temp->name)==0){
            head = temp->next;
            free(temp);
            printf("Deleted\n");
            return;
        }


    while (temp != NULL && strcmp(temp->name, name) != 0){
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL){
        printf("Not found\n");
        return;
    }

    prev->next = temp->next;
    free(temp);

    printf("Deleted\n");


}

int main(){
    int choice;
    while(1){
        printf("\nCONTACT SYSTEM\n");
        printf("1. Insert Contact\n");
        printf("2. View Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice){
        case 1:
            insertContact();
            break;
        case 2:
            viewContacts();
            break;
        case 3:
            searchContact();
            break;
        case 4:
            deleteContact();
            break;
        case 5:
            exit(0);
            break;
        }



    }
    return 0;
}
