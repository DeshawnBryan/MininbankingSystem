#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "students.dat"

struct Student{
    int id;
    char name[50];
    int age;
    float grades;
};

void addStudent(){
    struct Student s;
    printf("Enter Student id: ");
    scanf("%d", &s.id);

    int studentExists(int id);
    if(studentExists(s.id)){
        printf("Cannot add duplicate student!\n");
        return;
    }

    printf("Enter name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter age: ");
    scanf("%d", &s.age);

    printf("Enter Student grade: ");
    scanf("%f", &s.grades);
    printf("Student successfully added\n");
    FILE *fp = fopen(FILE_NAME, "ab");
    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}

void viewStudents(){
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "rb");
    if(!fp){
        printf("File error\n");
    }

    printf("\n=====STUDENTS=======");
    while(fread(&s, sizeof(s), 1, fp)){
        printf("\nStudent Id: %d\n", s.id);
        printf("Student name: %s\n", s.name);
        printf("Student grade: %.2f\n", s.grades);
        printf("Student age: %d\n", s.age);
    }
    fclose(fp);
}

int searchStudent(struct Student *result){
    struct Student s;
    int id;

    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp){
        printf("File not found!");
    }

    printf("Enter Id: ");
    scanf("%d", &id);
    while(fread(&s, sizeof(s), 1, fp)){
        if(s.id == id){
            *result = s;
            fclose(fp);
            return 1;

        }
    }
    printf("Student not found\n");
    fclose(fp);
    return 0;

}


int updateStudent(){
    struct Student s;
    int id;
    int found = 0;
    FILE *fp = fopen(FILE_NAME, "rb");
    //New temporary file: temp.dat
    FILE *temp = fopen("temp.dat", "wb");
      if (!fp){
            printf("File not found!");
            return 0;
        }
      if(!temp){
        printf("Temp file error!\n");
        fclose(fp);
        return 0;
      }

    printf("Enter Student id: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(s), 1, fp)){
        if(s.id == id){
            found = 1;

            printf("Enter new name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter new age: ");
            scanf("%d", &s.age);

            printf("Enter new grade: ");
            scanf("%f", &s.grades);
        }
        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if(found){
        printf("Student updated successfully!\n");
        return 1;
    }else{
        printf("Student not found\n");
        return 0;
    }

}


int deleteStudent(){
    struct Student s;
    int id;
    int found = 0;
    FILE *fp = fopen(FILE_NAME, "rb");
    //New temporary file: temp.dat
    FILE *temp = fopen("temp.dat", "wb");
      if (!fp){
            printf("File not found!");
            return 0;
        }
      if(!temp){
        printf("Temp file error!\n");
        fclose(fp);
        return 0;
      }

    printf("Enter Student id: ");
    scanf("%d", &id);

    while(fread(&s, sizeof(s), 1, fp)){
        if(s.id == id){
            found = 1;
            continue;
        }
        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if(found){
        printf("Student deleted successfully!\n");
        return 1;
    }else{
        printf("Student not found\n");
        return 0;
    }

}

int studentExists(int id){
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "rb");
    if(!fp){
        return 0;
    }

    while(fread(&s, sizeof(s), 1, fp)){
            if(s.id == id){
            fclose(fp);
            return 1;
          }
    }
    fclose(fp);
    return 0;
}


int main(){
    struct Student s;
    int choice;
    while(1){
        printf("\n\nSTUDENT SYSTEM\n");
        printf("1. Add Students\n");
        printf("2. View Students\n");
        printf("3. Search Students\n");
        printf("4. Update Students\n");
        printf("5. Delete Students\n");
        printf("6. Exit Students\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice){
        case 1:
            addStudent();
            break;
        case 2:
            viewStudents();
            break;
        case 3:
            if(searchStudent(&s)){
                printf("Student ID: %d\n", s.id);
                printf("Student Name: %s\n", s.name);
                printf("Student Grades: %.2f\n", s.grades);
            }
            break;
        case 4:
            updateStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 6:
            exit(0);
        }

    }
    return 0;
}
