#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum Status{
    Pending,
    Completed
};

struct Task{
    char name[50];
    char description[50];
    enum Status status;
    struct Task *next;
};


struct Task *head = NULL;

void addTask(){
    char name[50];
    int choice1;
    do{
        struct Task *temp = head;
        struct Task *newNode = malloc(sizeof(struct Task));
        if(newNode == NULL){
            printf("Memory not allocated.\n");
            return;
        }
        printf("\nEnter Task Name: ");
        scanf(" %[^\n]", newNode->name);
        printf("Enter description: ");
        scanf(" %[^\n]", newNode->description);
            newNode->next = NULL;

        if (head == NULL){
            head = newNode;
            newNode->status = Pending;
            printf("Task added successfully.\n");
            printf("Would you like to add another task?(1 is yes): ");
            scanf("%d", &choice1);
            continue;
        }

        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->status = Pending;
        printf("\nTask successfully added.\n");
        printf("Would you like to add another task?(1 is yes): ");
        scanf("%d", &choice1);
    }while(choice1 == 1);

}


void viewTasks(){

        char name[50];
        char description[50];
        //temp traverses the list, so you can use it to access the data in newNode
        //since newNode refers to that list
        //sole purpose of newNode is to add data at the end of the list
        struct Task *temp = head;
        if(temp == NULL){
            printf("No books.\n");
            return;
        }
        int i = 1;
        while(temp != NULL){
            printf("\n%d. %s\n",i, temp->name);
            printf("%s\n", temp->description);
            if(temp->status == Pending){
                printf("Status: Pending\n");
            }
            else{
                printf("Status: Completed\n");
            }
            temp = temp->next;
            i++;
        }

}

void searchTask(){
    char key[50];
    struct Task *temp = head;
    printf("Enter Task: ");
    scanf(" %[^\n]", key);
    int i = 1;
    while(temp != NULL){
            i++;

            //lettuce, le, 2
        //strncmp(string1, string2, numberOfCharactersToCompare)
        if(strncmp(temp->name, key, strlen(key)) == 0){
            printf("\n%d. %s\n",i, temp->name);
            printf("%s\n", temp->description);
            if(temp->status == Pending){
                printf("Status: Pending\n");
            }
            else{
                printf("Status: Completed\n");
            }

        }
        temp = temp->next;

    }
}

void ToggleTask(){
    //Enter name, change from pending to complete
    char name[50];
    struct Task *temp = head;
    printf("Enter Name Of Task to toggle: ");
    scanf(" %[^\n]", &name);
    while(temp != NULL){
        if(strcmp(name, temp->name)==0){
            if(temp->status == Pending){
                temp->status = Completed;
                printf("%s Completed!\n", name);
            }else{
                temp->status = Pending;
                printf("%s Pending...\n", name);

            }
        }else{
                printf("Task not found.\n");

        }
        temp = temp->next;
    }

}

void deleteTask(){
    struct Task *temp = head;
    struct Task *prev = NULL;
    char name[50];
    printf("Enter task you wanted to delete: ");
    scanf(" %[^\n]", &name);

    //delete head
    if(temp != NULL && strcmp(name, temp->name)==0){
        head = temp->next;
        free(temp);
        printf("Task deleted.\n");
        return;
    }

    //delete anything else
    while(temp != NULL && strcmp(name, temp->name) !=0){
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL){
        printf("Task not found.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);

    printf("Task deleted.\n");

}

void countTasks(){
    struct Task *temp = head;
    int i = 0;
    while(temp != NULL){
        temp = temp->next;
        i++;
    }
    if(i == 1){
       printf("\nThere is %d task\n", i);

    }else{
       printf("\nThere are %d tasks\n", i);

    }


}


int main(){
    int choice;
    while(1){
        printf("\nTO DO LIST\n");
        printf("1. addTask\n");
        printf("2. viewTasks\n");
        printf("3. searchTask\n");
        printf("4. ToggleTask\n");
        printf("5. deleteTask.\n");
        printf("6. countTasks.\n");
        printf("7. Exit program.\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch(choice){
        case 1:
            addTask();
            break;
        case 2:
            viewTasks();
            break;
        case 3:
            searchTask();
            break;
        case 4:
            ToggleTask();
            break;
        case 5:
            deleteTask();
            break;
        case 6:
            countTasks();
            break;
        case 7:
            exit(0);
            break;
        }
    }
    return 0;
}
