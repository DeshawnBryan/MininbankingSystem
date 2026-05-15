#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
    char name[50];
    int marks;

};

int main(){

    int n;
    struct Student students[100];
    printf("Enter how many students will be entered: ");
    scanf("%d", &n);

    for (int i = 0; i < n;  i++){
        printf("\nEnter student name: ");
        scanf(" %[^\n]", &students[i].name);
        printf("Enter student mark: ");
        scanf("%d", &students[i].marks);
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < 1-i; j++){
            if(students[j].marks < students[j + 1].marks){
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }

        }
    }

    printf("\n--- Student Rankings ---\n");
    for(int i = 0; i < n; i++) {
        printf("%d. %s - %d marks\n", i + 1, students[i].name, students[i].marks);
    }

        // Top 3
    printf("\n--- Top 3 Students ---\n");
    int limit = n < 3 ? n : 3;

    for(int i = 0; i < limit; i++) {
    printf("%d. %s - %d marks\n", i + 1, students[i].name, students[i].marks);
    }


    return 0;
}
