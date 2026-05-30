#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Book{
    int bookID;
    char title[50];
    char author[50];
    struct Book *next;
};

struct Book *head = NULL;


void addBook(){
    int bookID;
    char title[50];
    char author[50];
    //creates a pointer variable, stores the address of a struct Book
    //right side, allocates enough memory to store one struct Book(information in Book struct)
    //malloc allocates the size
    //SSo this makes space for Book struct
    struct Book *newNode = malloc(sizeof(struct Book));

    // If memory was not allocated for struct Book (newNode == NULL), memory allocation failed, and return back
    if (newNode == NULL){
        printf("Memory allocation failed.\n");
        return;
    }

    //Creates a pointer called temp, and stores info in head in temp pointer
    ///Creates a pointer called temp and assigns it the address stored in head
    //Both head and temp, point to the same first Node
    struct Book *temp = head;
    printf("Enter book ID: ");
    scanf("%d", &bookID);

    printf("Enter title: ");
    scanf(" %[^\n]", newNode->title);

    printf("Enter author: ");
    scanf(" %[^\n]", newNode->author);


    newNode->bookID = bookID;


    newNode->next = NULL;

    if(head == NULL){
        head = newNode;
        return;
    }

    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = newNode;
    printf("Book successfully accounted for!");

}



void viewBooks(){

    // Creates a pointer called temp and sets it to point to the same node as head
    struct Book *temp = head;
    //head = first record/first collective information for book

    //temp != head... temp is NOT pointing to the first node
    //but just because it's not pointing towards the first node, doesn't mean it is pointing towards head
    //If temp is NULL, then the list is empty, so print “No books available” and stop the function.
    if (temp == NULL){
        printf("No books available.\n");
        return;
    }

    //if temp Node is NOT empty, then output the information
    while (temp != NULL){
        printf("\nBook ID: %d\n", temp->bookID);
        printf("Title: %s\n", temp->title);
        printf("Author: %s\n", temp->author);

        temp = temp->next;
    }

}

void searchBook(){

    struct Book *temp = head;
    int bookID;
    char title[50];
    char author[50];

    if (temp == NULL){
        printf("No books available on record.\n");
        return;
    }
    printf("Enter BookID: ");
    scanf("%d", &bookID);

    while (temp != NULL ){

        if(temp->bookID == bookID){
            printf("Title: %s\n", temp->title);
            printf("Author: %s\n", temp->author);
            return;
        }

        temp = temp->next;
    }

    printf("Book not found.\n");



}


void deleteBook(){
    struct Book *temp = head;


    //not pointing to anything
    struct Book *prev = NULL;
    int bookID;

    printf("Enter BookID: ");
    scanf("%d", &bookID);

    if (temp != NULL && temp->bookID == bookID){

        //deletes the first node (head node/first record) of a linked list

        ///move head to the node after temp.
        /*
        head
         ↓
        [Book1] -> [Book2] -> [Book3] -> NULL
        */



        ///STEP 2
        /*
        head
         ↓
        [Book2] -> [Book3] -> NULL

        temp
         ↓
        [Book1]

        head no longer points to Book1, but Book2... while temp points to Book1
        */
        head = temp->next;

        ///free(temp)
        //Return the memory used by Book1 back to the system.
        //If only this was used then, head would still point to memory that has been freed, which is dangerous.
        free(temp);

        printf("Book deleted.\n");
        return;
    }

    while (temp != NULL && temp->bookID != bookID){
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL){
        printf("Book not found.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);

    printf("Book deleted.\n");

}

void updateBook(){
    struct Book *temp = head;
    int bookID;
    printf("Enter Book ID: ");
    scanf("%d", &bookID);

    //First, verify that records aren't empty
    while (temp != NULL){

        if (temp->bookID == bookID){

            printf("Enter new Title: ");
            scanf(" %[^\n]", temp->title);

            printf("Enter New Author: ");
            scanf(" %[^\n]", temp->author);

            printf("Book updated.\n");
            return;
        }

        //moves temp to the next node in the linked list
        temp = temp->next;
    }

    printf("Book not found.\n");
}


int main(){
    int choice;

    while (1){
        printf("\nBOOK SYSTEM\n");
        printf("1. addBook\n");
        printf("2. viewBooks\n");
        printf("3. searchBook\n");
        printf("4. deleteBook\n");
        printf("5. updateBook\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice){
        case 1:
            addBook();
            break;
        case 2:
            viewBooks();
            break;
        case 3:
            searchBook();
            break;
        case 4:
            deleteBook();
            break;
        case 5:
            updateBook();
            break;
        case 6:
            exit(0);
            break;
        }
    }

}
