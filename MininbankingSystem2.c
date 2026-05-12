#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "accounts.dat"

struct Account{
    int accNo;
    char name[50];
    char password[20];
    float balance;
};

void createAccount(){
    struct Account acc;
    int accNo;
    printf("\nEnter Numer: ");
    scanf("%d", &acc.accNo);
    int accountExists(int accNo);
    if(accountExists(acc.accNo)){
        printf("AccountNo already exists\n");
        return;
    }
    printf("Enter name: ");
    scanf(" %[^\n]", &acc.name);
    printf("Enter password: ");
    scanf("%s", &acc.password);

    acc.balance = 0;

    FILE *fp = fopen(FILE_NAME, "ab");
    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);
    printf("Account successfully created!");
}

int login(struct Account *loggedIn){
    struct Account acc;
    int accNo;
    char password[20];

    printf("Enter Account Number: ");
    scanf("%d", &accNo);
    printf("Enter password: ");
    scanf("%s", password);
    FILE *fp = fopen(FILE_NAME, "rb");
    if(!fp) return 0;

    while(fread(&acc, sizeof(acc), 1, fp)){
        if(acc.accNo == accNo && strcmp(acc.password, password)== 0){
            *loggedIn = acc;
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int accountExists(int accNo){
    struct Account acc;
    FILE *fp = fopen(FILE_NAME, "rb");
    if(!fp) return 0;

    while(fread(&acc, sizeof(acc), 1, fp)){
        if(acc.accNo == accNo){
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void Deposit(struct Account *acc){
    float amount;
    printf("Enter amount to Deposit: ");
    scanf("%f", &amount);
    acc->balance += amount;


    printf("Deposit successful!\n");

}



void withdrawal(struct Account *acc){
    float amount;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if(amount > acc->balance){
        printf("Insufficient balance\n");
        return;
    }
    acc->balance -= amount;


    printf("Withdrawal successful!\n");

}

void Dashboard(struct Account *acc){
    int choice;
    do{
        printf("\n\nDASHBOARD\n");
        printf("1. View Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Transfer\n");
        printf("5. Logout\n");
        printf("Choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("Student Number: %d\n", acc->accNo);
                printf("Student Name: %s\n", acc->name);
                printf("Balance: %.2f", acc->balance);
                break;
            case 2:
                Deposit(acc);
                break;
            case 3:
                withdrawal(acc);
                break;
            case 5:
                exit(0);

        }
    }while (choice != 5);

}


int main()
{

    int choice;
    struct Account acc;
    while(1){
        printf("\n\nBANK MENU\n");
        printf("1. Create Account\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        switch (choice){
            case 1:
                createAccount();
                break;
            case 2:
                if(login(&acc)){
                    printf("Login successful\n");
                    Dashboard(&acc);
                    break;
                }else{
                    printf("Login unsuccessful\n");
                }
                break;
            case 3:
                exit(0);
                break;


        }

    }
    return 0;
}
