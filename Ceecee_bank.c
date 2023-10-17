#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct User
{
    /* Declaring the different variable types to be used
    in creating and managing a bank account */

    float acctBalance;
    float amount;
    char  acctNumber[11];
    char firstName[30], lastName[30];
    char Password[20], Password1[20], phone[11];
};
int main(){
    struct User cstmr, cstmr1;
    FILE *fp1;
    int choice, opt;
    int source_account_number, target_account_number;
    char userFilename[30],phone[50],password[50],acctNumber[50], pword[20];
    double amount;
    char cont = 'y';

    // Home screen for user registration
    // Accepting user details

    printf("\n\nWELCOME TO CEECEE BANK\n");
    printf("\nWhat will you like to do?\n");
    printf("\n\n1.Create an account\n");
    printf("\n2.Login to account\n");

    printf("\n\nEnter your choice:");
    scanf("%d", &opt);


    if (opt == 1){
        system ("cls");
        printf("To create an account with us, enter the following details\n\n");
        printf("Enter your first name: \n");
        scanf("%s", cstmr.firstName);
        printf("Enter your last name: \n");
        scanf("%s", cstmr.lastName);
        printf("Enter your phone number: \n");
        scanf("%s", cstmr.phone);
        printf("Enter a preffered 10-digit account number: \n");
        scanf("%s", cstmr.acctNumber);
        printf("Enter an 8-digit password: \n");
        scanf("%s",cstmr.Password);
        printf("Confirm 8-digit password: \n");
        scanf("%s",cstmr.Password1);
        if (!strcmp(cstmr.Password1, cstmr.Password)){
            cstmr.acctBalance = 0;
            strcpy(userFilename,cstmr.acctNumber);// This copies the account number and saves it as file name
            fp1 = fopen(strcat(userFilename,".txt"), "w"); // Here I'm both creating a file, concatenating it with an extension(.txt),
            // and opening the file for the structure 'User' to be written into it
            fwrite(&cstmr, sizeof(struct User),1,fp1);
            system ("cls");
            printf("Congratulations!!! You have successfully created an account with us!\n");
        }
        else{
                printf("Error creating account. Password mismatch. Otherwise, try again.");
            }
        fclose(fp1);
    }
    if (opt == 2){
        system("cls");
        printf("\nAccount Number:");
        scanf("%s",acctNumber);
        printf("Password:");
        scanf("%s",pword);
        strcpy(userFilename,acctNumber);
        fp1 = fopen(strcat(userFilename,".txt"),"r");
        if(fp1 == NULL){
            printf("\nAccount number not registered or incorrect password. Try again");
        }
        else{
            fread(&cstmr,sizeof(struct User),1,fp1);
            fclose(fp1);
            if(!strcmp(pword,cstmr.Password)){
               printf("Welcome %s", cstmr.firstName);
               while(cont  == 'y'){
                    system("cls");
                    printf("\t\t\tWelcome %s\n",cstmr.firstName);
                    printf("\t\tPress 1 for balance inquiry\n");
                    printf("\t\tPress 2 to deposit cash\n");
                    printf("\t\tPress 3 to make withdrawal\n");
                    printf("\t\tPress 4 to make transfer\n");
                    printf("\t\nEnter Your Choice:");
                    scanf("%d",&choice);

                    switch(choice){
                        case 1:
                            printf("Your current balance is $%.2f\n\n",cstmr.acctBalance);
                            break;

                        case 2:
                            printf("Enter deposit amount: ");
                            scanf("%lf", &amount);
                            cstmr.acctBalance += amount;
                            fp1 = fopen(userFilename,"w");
                            fwrite(&cstmr,sizeof(struct User),1,fp1);
                            if(fwrite != NULL){
                                printf("\nSuccessfully deposited");
                            }
                            fclose(fp1);
                            break;
                        case 3: // for withdrawal
                            printf("Enter amount to withdraw: ");
                            scanf("%lf", &amount);
                            cstmr.acctBalance -= amount;
                            fp1 = fopen(userFilename,"w");
                            fwrite(&cstmr,sizeof(struct User),1,fp1);
                            if(fwrite != NULL){
                                printf("\nYou have successfully withdrawn %lf", amount);
                            }
                            fclose(fp1);
                            break;
                        case 4: // for transfer
                            printf("Enter the account number to transfer:");
                            scanf("%s", acctNumber);
                            printf("Enter the amount to transfer:");
                            scanf("%lf", &amount);
                            strcpy(userFilename,acctNumber);
                            fp1 = fopen(strcat(userFilename,".txt"),"r");
                            if(fp1 == NULL){
                                    printf("\nAccount number not registered");
                                    return 0;
                                }
                                fread(&cstmr1,sizeof(struct User),1,fp1);
                                fclose(fp1);
                                if(amount > cstmr.acctBalance) printf("\nInsufficient balance");
                                else{
                                    fp1 = fopen(userFilename,"w");
                                    cstmr1.acctBalance += amount;
                                    fwrite(&cstmr1,sizeof(struct User),1,fp1);
                                     if(fwrite != NULL){
                                        printf("You have successfully transferred $%lf to %s", amount, acctNumber);
                                        strcpy(userFilename,cstmr.acctNumber);
                                        fp1 = fopen(strcat(acctNumber,".txt"),"w");
                                        cstmr.acctBalance -= amount;
                                        fwrite(&cstmr,sizeof(struct User),1,fp1);
                                        fclose(fp1);
                                     }
                                }
                            break;
                        default:
                            printf("INVALID OPTION!");
                    }
                    printf("\t\nDo you want to continue transaction [y/n]:");
                    scanf("%s",&cont);
                    if (cont != 'y')
                    {
                        printf("Successfully logged out");
                    }

               }

            }
            else{
                printf("Password do not match. Try again.");
            }
        }
    }
    return 0;
}
