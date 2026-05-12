#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "inventory.dat"
//NB: ID HERE IS FOR A SPECIFIC ITEM, NOT PERSON
//so it's used for search
struct Item{
    int id;
    char name[50];
    int quantity;
    float price;
};


void addItem(){
    struct Item it;

    printf("Enter item Id: ");
    scanf("%d", &it.id);

    printf("Enter name: ");
    scanf(" %[^\n]", &it.name);

    printf("Enter quantity: ");
    scanf("%d", &it.quantity);

    printf("Enter price: ");
    scanf("%f", &it.price);

    FILE *fp = fopen(FILE_NAME, "ab");
    fwrite(&it, sizeof(it), 1, fp);
    fclose(fp);

    printf("Item added successfully\n");
}


int viewItems(){
    struct Item it;

    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp){
        printf("File not found.\n");
        return 0;
    }


    while(fread(&it, sizeof(it), 1, fp)==1){
            printf("\n\nId number: %d\n", it.id);
            printf("Name: %s\n", it.name);
            printf("Quantity: %d\n", it.quantity);
            printf("Price: %.2f\n", it.price);

    }
    fclose(fp);
    return 1;
}

int searchItem(){
    struct Item it;
    int id;
    int found = 0;
    printf("Enter ID for item: ");
    scanf("%d", &id);
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp){
        printf("File not found\n");
        return 0;
    }
    while(fread(&it, sizeof(it), 1, fp)==1){
        if(it.id == id){
            printf("\n\nId number: %d\n", it.id);
            printf("Name: %s\n", it.name);
            printf("Quantity: %d\n", it.quantity);
            printf("Price: %.2f\n", it.price);

            found = 1;
            break;
        }
    }
    fclose(fp);

    if(!found){
        printf("\nItem not found\n");
    }
    return found;

}

void updateItem(){
    struct Item i;
    struct Item updated;//in deleteItem it's i
    int id;
    int found = 0;

    printf("Enter id of item: ");
    scanf("%d", &id);

    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if(!fp || !temp){
        printf("File error.\n");
        return;
    }


    //unlike deleteItem, you have to write data, as you are updating an item
    while(fread(&i, sizeof(i), 1, fp) == 1){
        if(i.id == id){
            found = 1;

            updated = i;  // keep old data

            printf("Enter new name: ");
            scanf(" %[^\n]", updated.name);

            printf("Enter new quantity: ");
            scanf("%d", &updated.quantity);

            printf("Enter new price: ");
            scanf("%f", &updated.price);

            fwrite(&updated, sizeof(updated), 1, temp);
        } else {
            fwrite(&i, sizeof(i), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if(found)
        printf("Item updated successfully\n");
    else
        printf("Item not found\n");
}

//same as updateItem with exceptions
void deleteItem(){
    struct Item i;
    //in update struct Item updated; is here
    int id;
    int found = 0;

    printf("Enter id of item: ");
    scanf("%d", &id);

    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");


    if(!fp || !temp){
        printf("File error.\n");
        return;
    }

    //while loop is shorted, as you aren't writing anythign but deleting(difference between updateItem and this method)
    while(fread(&i, sizeof(i), 1, fp)==1){
        if(i.id == id){
            found = 1;
        }else{
            fwrite(&i, sizeof(i), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if(found)
        printf("Item successfully deleted\n");
    else
        printf("Item not found\n");
}

int main(){
    int choice;
    struct Item item;

        while(1){
        printf("\n\nMANAGEMENT SYSTEM\n");
        printf("1. Add Item\n");
        printf("2. View Items\n");
        printf("3. Search Item\n");
        printf("4. Update Item\n");
        printf("5. Delete Item\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice){
            case 1:
                addItem();
                break;
            case 2:
                viewItems();
                break;
            case 3:
                searchItem();
                break;
             case 4:
                updateItem();
                break;
             case 5:
                deleteItem();
                break;

            case 6:
                exit(0);

            }
        }

    return 0;
}
