#include "contact.h"
#include<string.h>
#include<stdlib.h>

int main()
{
    int n;
    /* Iniatializing a variable for the structure  */
    AddressBook addressBook;
    initialize(&addressBook);
    /* Displaying the options for the user to do choose*/
    do
    {
        printf("Address Book Menu:\n");
		printf("1.Create Contact\n");
		printf("2.Search Contact\n");
		printf("3.Edit Contact\n");
		printf("4.Delete Contact\n");
		printf("5.List all contacts\n");
		printf("6.Save and Exit\n");
		printf("7.Exit\n");
		printf("Enter your choice:");
        scanf("%d",&n);
        switch(n)
        {
            /* function call from switch case */
            case 1:createContact(&addressBook);
                   break;
            case 2:searchContact(&addressBook);
                   break;
            case 3:editContact(&addressBook);
                   break;
            case 4:deleteContact(&addressBook);
                   break;
            case 5:listContacts(&addressBook);
                   break;
            case 6:printf("do you want to save:y/n\n");
                   char ch;
                   scanf(" %c",&ch);
                   if(ch=='y'||ch=='Y')
                   {
                       save(&addressBook);
                       n=7;
                       printf("Exit\n");
                   }
                   else
                   {
                       n=7;
                       printf("Exit\n");
                   }
                   break;
            case 7:printf("Exit\n");
                   break;
            default:printf("Invalid\n");
        }
        /* loop terminates when the user gives 7 as input */
    }while(n!=7);
}
