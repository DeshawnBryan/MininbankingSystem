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

/*
DELETEBOOKS EXPLANATION:
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

    //where deletion starts
    prev->next = temp->next;
    free(temp);

    printf("Book deleted.\n");

}




First initialize pointer temp to head so it has the same address/starting position as head.

Do the same thing with the pointer "prev" however have it as NULL instead

Prompt the user to enter an ID and store it into bookID... so you can later compare bookID with temp->bookID


IF STATEMENT
If temp has not reached the end of the list, and the book is found, then head takes the next position node.

Space is then allocated for "temp" (first record)
"head" data is moved to the next node.
free(temp) deletes the first record, Book1 is removed from memory.

If the condition is met, head is moved to point to the next node in the list. The original first node is then removed from the linked list(using free(temp)) by freeing the memory, which releases that node’s allocated memory back to the system.


HOW DELETION WORKS
Anything before head can not be accessed, so it might as well be non-existent. However it still exists in memory. But from this point it's treated as "deleted" since nothing before head can be accessed.

That's what free(temp) is for. It frees that memory floating around, actively deleting the non-accessible memory.

//REWRITTEN
Once a node is no longer reachable from head, it is no longer part of the linked list and cannot be accessed through it. From the perspective of the program, it is effectively treated as removed from the list, even though the actual data may still remain in memory.

However, the node still occupies memory until it is explicitly released. This is why free(temp) is used. It deallocates that memory, returning it to the system so it can be reused, fully removing the node’s allocated space from the program.

We use free(temp) so it does not consume memory or resources.

DELETION PROCESS FOR SOLELY BOOK1:
book1 -> book2 -> book3 -> book4 -> NULL
head = head->next;
(floating_lost_memory) -> book2 -> book3 -> book4 -> NULL

The floating lost memory is a waste of space, although not accessibly and is effectively "deleted" or removed from the list.

free(temp)
book2 -> book3 -> book4 -> NULL


    if(temp != NULL && temp->bookID == bookID){
        head = temp->next;
        free(temp);
        printf("Book deleted.\n");
        return;
    }
    
        free(temp);
        
        returns the memory used by Book1 back to the system from malloc
        NB: If temp points to Book1, when this is used, you're
        telling the system "I'm finished using this block of memory. 
        You may use it later.
        The memory becomes available again
        
         Free memory:
         [X] [ ] [ ] [ ] [ ] [ ]
         ^
         Book1
         
         Free memory:
         [ ] [ ] [ ] [ ] [ ] [ ]
        
        malloc()
           ↓
        Memory reserved for Book1
           ↓
        Program uses Book1
           ↓
        free()
           ↓
        Memory marked available again
           ↓
        Future malloc() may reuse it
                

WHILE LOOP TO TRAVERSE LIST IN SEARCH OF BOOK

    while(temp != NULL && temp->bookID != bookID){
    prev = temp;
    temp = temp->next;

    if(temp == NULL){
        printf("Book not found.\n");
        return;
    }
    prev->next = temp->next;
    free(temp);
        }


   while(temp != NULL && temp->bookID != bookID){
    prev = temp;
    temp = temp->next;
   }

//Until you reach NULL, or until temp reaches NULL(the end of the list)
//and until you find the book 

REPHRASED:
(Traverse the list with temp, indicated by it not being NULL... as long as it's not NULL there are more records to search... ALSO KEEP searching if the IDs do not match... ESSENTIALLY SAYING: as long as it's not the end of the list, and the ID is not found... keep traversing and do the following below)

Step 1 (start)
prev = NULL
temp = Book1

Step 2
prev = Book1
temp = Book2

Step 3
prev = Book2
temp = Book3

Here you're traversing through the array
They are building a relationship between nodes while moving forward.

Because before you can delete anything, you must:
find the node you want to delete

You don’t know where it is in the list.
So you must walk through it:

VALIDATION
    while(temp != NULL && temp->bookID != bookID){
    prev = temp;
    temp = temp->next;

    if(temp == NULL){
        printf("Book not found.\n");
        return;
    }
    prev->next = temp->next;
    free(temp);
        }


    if(temp == NULL){
        printf("Book not found.\n");
        return;
    }

If it reaches the end of the list, that means the book is not found. If the book was found it would've stopped and this message would not occur


//the previous node becomes the next node
//skip over the node I'm deleting

    prev->next = temp->next;
    free(temp);

//allocates space for temp

DELETION PROCESS IF THE BOOK BEING DELETED IS NOT BOOK1
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



Continue traversing the list as long as a record exists (temp != NULL) and the current record's ID does not match the ID being searched for (temp->bookID != bookID).

Store the current record in prev before moving to the next record. This ensures that if the book is found, the record immediately before it is known and can be reconnected to the next record when deletion occurs.

Example:
BEFORE
Book1 → Book2 → Book3 → Book4
         ^
        temp

AFTER
prev = temp;
Book1 → Book2 → Book3 → Book4
         ^
        prev


Initially, temp is set to the same address as head, so both pointers start at the first node in the list, while prev is set to NULL.

struct Book temp* = head
struct Book prev* = NULL

temp = book1
head = book1
prev = NULL

 while (temp != NULL && temp->bookID != bookID){
        prev = temp;
        temp = temp->next;
    }

At this point, all traversal begins from the start of the linked list.

During traversal, the line prev = temp; stores the current node that temp is pointing to. Immediately after, temp = temp->next; moves temp forward to the next node in the list.

BEFORE RUNNING ANYTHING:
head = book1
prev = NULL
temp = book1

prev = temp;
temp = temp->next
head = book1
prev = book1
temp = book2

prev = temp;
temp = temp->next
(temp moves to the next position, so if it was previously book1, it is now book2)
head = book1
prev = book2
temp = book3

prev = temp;
temp = temp->next
head = book1
prev = book3
temp = book4



REASON WHY PREV LEADS BEHIND TEMP, although temp already traverses through the list
It's so that when a book/record is deleted, it can be linked to the rest of the list.

Like the middle of a bridge being deleted. The closer the previous section is to the fixed section, the easier it would be to fix. 







This means that prev does not automatically follow temp — it simply holds the previous position that temp was on before it moved.

As the loop continues, temp keeps advancing through the list one node at a time, while prev always remains one step behind it.

So at different points:
At the start, both head and temp point to the first node, and prev is NULL.
After the first step, prev and head point to the first node, while temp moves to the second node.
As traversal continues, temp moves forward through the list, and prev follows behind, always pointing to the node just before temp.

This relationship is important because when the target node is found, prev is used to reconnect the list by linking its next pointer to temp->next, allowing the current node (temp) to be safely removed using free(temp).
    */
