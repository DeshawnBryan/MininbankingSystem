#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book{
    int bookID;
    char title[50];
    char author[50];
    struct Book *next;
};


void addBook(){
    int bookID;
    char title[50];
    char author[50];
    
    struct Book *newNode = malloc(sizeof(struct Book));

    
    if (newNode == NULL){
        printf("Memory allocation failed.\n");
        return;
    }
    struct Book *temp = head;

    printf("Enter BookID: ");
    scanf("%d", &bookID);

    printf("Enter Title: ");
    scanf(" %[^\n]", newNode->title);

    printf("Enter author: ");
    scanf(" %[^\n]", newNode->author);

    newNode->bookID = bookID;
    
   
    if(head == NULL){
        head = newNode;
        return;
    }

    
    while(temp->next != NULL){
        temp = temp->next; //points to the next Node until NULL is reached
    }

    temp->next = newNode;
    printf("Book successfully accounted for!");

}


void viewBooks(){

    struct Book *temp = head;

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
    struct Book *prev = NULL;
    int bookID;

    printf("Enter BookID: ");
    scanf("%d", &bookID);

    if (temp != NULL && temp->bookID == bookID){

        head = temp->next;


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

    while (temp != NULL){

        if (temp->bookID == bookID){

            printf("Enter new Title: ");
            scanf(" %[^\n]", temp->title);

            printf("Enter New Author: ");
            scanf(" %[^\n]", temp->author);

            printf("Book updated.\n");
            return;
        }

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