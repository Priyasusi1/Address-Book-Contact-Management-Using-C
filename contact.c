#include "contact.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* Function call */
/* dispaly the name ,phone number, email */
void start(AddressBook *addressBook)
{
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("                          Name                           Number                           Email\n");
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
}
void end(AddressBook *addressBook)
{
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
}

/* Initializing the contacts details */
void initialize(AddressBook *addressBook)
{
	char *token,str[200];
	FILE *ptr;
	/* Opening the file.csv file*/
	ptr=fopen("file.csv","r");
	if(ptr==NULL)
	{
		printf("Unable to open the file");
	}
	/* read the first line from the file.cdv*/
	fscanf(ptr,"%[^\n]",str);
	token=strtok(str,"#");
	addressBook->contactCount=atoi(token);
	addressBook->contacts=malloc((addressBook->contactCount)*sizeof(Contact));
	for(int i=0;i<addressBook->contactCount;i++)
	{
		fscanf(ptr," %[^\n]",str);
		token=strtok(str,",");
		strcpy(addressBook->contacts[i].name,token);
		token =strtok(NULL,",");
		strcpy(addressBook->contacts[i].phone,token);
		token=strtok(NULL,",");
		strcpy(addressBook->contacts[i].email,token);
	}
}

/* list the contacts details */
void listContacts(AddressBook *addressBook)
{
	start(addressBook);
	/*list the all contact details*/
	for(int i=0;i<addressBook->contactCount;i++)
	{
		printf("%32s%32s%32s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	}
	end(addressBook);
}

/* create a new contacts details */
void createContact(AddressBook *addressBook)
{
	/* user enter the string value */
	listContacts(addressBook);
	char name[50],phone[20],email[30],ch;
	do
	{
		printf("Enter the name: ");
		scanf(" %[^\n]",name);
		int len=0,i=0,count=0;
		do
		{
			/*checking the phone number present or not */
			len=0,i=0;
			printf("Enter the phone number: ");
			scanf(" %s",phone);
			while(phone[i]!='\0')
			{
				if(isdigit(phone[len]))
				{
					len++;
				}i++;
			}
			if(len!=10)
			{
				printf("Number is invalid\nEnter the number again \n");
			}
			for(int j=0;j<addressBook->contactCount;j++)
			{
				if((strcmp(addressBook->contacts[j].phone,phone))==0)
				{
					printf("Number is already present\n");
					len=0;
					break;
				}
			}
		}while(len!=10);
		do
		{
			/* checking for email id present or not */
			count=0;
			printf("Enter the email Id: ");
			scanf(" %s",email);
			if(email[0]!='@')
			{
				if((strstr(email,"@"))&&(strstr(email,".com")))
				{
					count++;
				}
				if(count==0)
				{
					printf("Invalid\n");
				}
				for(int j=0;j<addressBook->contactCount;j++)
				{
					if((strcmp(addressBook->contacts[j].email,email))==0)
					{
						printf("Email is already present\n");
						count=0;
						break;
					}
				}
			}
		}while(count==0);
		/*increase the size from realloc*/
		addressBook->contacts=realloc((addressBook->contacts),(addressBook->contactCount+1)*sizeof(Contact));
		strcpy(addressBook->contacts[addressBook->contactCount].name,name);
		strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
		strcpy(addressBook->contacts[addressBook->contactCount].email,email);
		addressBook->contactCount++;
		printf("Do you want to continue:y/n\n");
		scanf(" %c",&ch);
	}while(ch!='n');
	end(addressBook);
}

/* search the contact */
void searchContact(AddressBook *addressBook)
{
	listContacts(addressBook);
	/*user enter the string value*/
	char name[50],phone[50],email[50],ch;
	do
	{
		/* enter the options*/
		int n,len=0,i=0,flag=0;
		printf("Enter options:\n");
		printf("1.search by name:\n");
		printf("2.search by contact:\n");
		printf("3.search by email:\n");
		printf("Enter you choice: ");
		scanf("%d",&n);
		switch(n)
		{
			case 1:printf("Enter the name: ");
				   getchar();
				   scanf("%[^\n]",name);
				   int count=0;
				   /*enter the search name it is present print the statment
					 else print not available*/
				   for(int i=0;i<addressBook->contactCount;i++)
				   {
					   if((strcmp(addressBook->contacts[i].name,name))==0)
					   {
						   start(addressBook);
						   printf("%32s%32s%32s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
						   end(addressBook);
						   flag=1;
						   break;
					   }
				   }
				   if(flag==0)
				   {
					   printf("Not available\n");
				   }
				   break;
			case 2:do
				   {
					   len=0,i=0;
					   printf("Enter the phone number: ");
					   scanf(" %s",phone);
					   while(phone[i]!='\0'){
						   if(isdigit(phone[len]))
						   {
							   len++;
						   }i++;}
					   if(len!=10)
						   printf("Number is invalid\n");
				   }while(len!=10);
				   /*condition check for the phone number is present print the statement
					 else print not available*/
				   for(int i=0;i<addressBook->contactCount;i++)
				   {
					   if((strcmp(addressBook->contacts[i].phone,phone))==0)
					   {
						   start(addressBook);
						   printf("%32s%32s%32s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
						   end(addressBook);
						   flag=1;
						   break;
					   }
				   }
				   if(flag==0)
				   {
					   printf("Not available\n");
				   }
				   break;
			case 3:do
				   {
					   count=0;
					   printf("Enter the email Id: ");
					   scanf(" %s",email);
					   if(email[0]!='@')
					   {
						   if((strstr(email,"@"))&&(strstr(email,".com")))
						   {
							   count++;
						   }
						   if(count==0)
						   {
							   printf("Invalid\n");
						   }
					   }
				   }while(count==0);
				   /*condition check for email is present or not it is present print the statment
					 else not avilable*/
				   for(int i=0;i<addressBook->contactCount;i++)
				   {
					   if((strcmp(addressBook->contacts[i].email,email))==0)
					   {
						   start(addressBook);
						   printf("%32s%32s%32s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
						   end(addressBook);
						   flag=1;
						   break;
					   }
				   }
				   if(flag==0)
				   {
					   printf("Not available\n");
				   }
				   break;
			default:printf("Invalid Input\n");
		}
		printf("Do you want to continue:y/n");
		scanf(" %c",&ch);
	}while(ch!='n');
}
void editContact(AddressBook *addressBook)
{
	listContacts(addressBook);
	/* user enter the strings value */
	char name[50],phone[50],email[50],email1[50],phone1[50],ch;
	do
	{
		/* select the options */
		int n,flag=0,count=0;
		printf("Enter options\n");
		printf("1.edit by name:\n");
		printf("2.edit by contact:\n");
		printf("3.edit by email:\n");
		printf("Enter your choice:");
		scanf("%d",&n);
		switch(n)
		{
			case 1:printf("Enter the name: ");
				   getchar();
				   scanf("%[^\n]",name);
				   count=0;
				   /* condition check for the name is present print the statemnt
					  else print not avilable */
				   for(int i=0;i<addressBook->contactCount;i++)
				   {
					   if((strcmp(addressBook->contacts[i].name,name))==0)
					   {
						   start(addressBook);
						   printf("%32s%32s%32s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
						   end(addressBook);
						   edit1(addressBook,&addressBook->contacts[i]);
						   flag=1;
						   break;
					   }
				   }
				   if(flag==1)
				   {
					   printf("Contact edited successfully\n");
				   }
				   else
				   {
					   printf("Not Availabe\n");
				   }
				   break;
			case 2:printf("Enter the number: ");
				   getchar();
				   scanf("%[^\n]",phone);
				   /* condition check for the phone number is present print the details
					  false means not avilable */
				   for(int i=0;i<addressBook->contactCount;i++)
				   {
					   if((strcmp(addressBook->contacts[i].phone,phone))==0)
					   {
						   start(addressBook);
						   printf("%32s%32s%32s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
						   end(addressBook);
						   edit1(addressBook,&addressBook->contacts[i]);
						   flag=1;
						   break;
					   }
				   }
				   if(flag==1)
				   {
					   printf("Not available\n");
					   printf("phone number edited successfully\n");
				   }
				   else
				   {
					   printf("Not available\n");
				   }
				   break;
			case 3:printf("Enter the email: ");
				   getchar();
				   scanf("%[^\n]",email);
				   /* condition check for the email id is present print the details
					  false means print not avilable */
				   for(int i=0;i<addressBook->contactCount;i++)
				   {
					   if((strcmp(addressBook->contacts[i].email,email))==0)
					   {
						   start(addressBook);
						   printf("%32s%32s%32s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
						   end(addressBook);
						   edit1(addressBook,&addressBook->contacts[i]);
						   flag=1;
						   break;
					   }
				   }
				   if(flag==1)
				   {
					   printf("email edited successfully\n");
				   }
				   else
				   {
					   printf("Not available\n");
				   }
				   break;

			default:printf("Invalid Input\n");
		}
		printf("Do you want to continue:y/n\n");
		scanf(" %c",&ch);
	}while(ch != 'n');

}

/* Deleting the contact details */
void deleteContact(AddressBook *addressBook)
{
	listContacts(addressBook);
	/* user enter the strings value */
	char name[50],phone[50],email[50],ch;
	do
	{
		int flag=0;
		int n;
		/* enter the options */
		printf("Enter options:\n");
		printf("1.search by name:\n");
		printf("2.search by contact:\n");
		printf("3.search by email:\n");
		printf("Enter your choice:");
		scanf("%d",&n);
		switch(n)
		{
			case 1:printf("Enter the name: ");
				   getchar();
				   scanf("%[^\n]",name);
				   int count=0;
				   /* searching the name
					  condition is true name is present print the details and delete the name
					  condition is false return not availablw */
				   for(int i=0;i<addressBook->contactCount;i++)
				   {
					   if((strcmp(addressBook->contacts[i].name,name))==0)
					   {
						   flag=1;
						   for(int j=i;j<addressBook->contactCount;j++)
						   {
							   addressBook->contacts[j]=addressBook->contacts[j+1];
						   }
					   }
				   }
				   if(flag==1)
				   {
					   (addressBook->contactCount)--;
					   addressBook->contacts=realloc((addressBook->contacts),(addressBook->contactCount)*sizeof(Contact));
					   printf("name successfully deleted\n");
				   }
				   else
				   {
					   printf("Not available\n");
				   }
				   break;
			case 2:printf("Enter the phone Number: ");
				   getchar();
				   scanf("%[^\n]",phone);
				   /* condition check for number is present or not
					  condition is true print detail and delete the name
					  false means not avilable */
				   for(int i=0;i<addressBook->contactCount;i++)
				   {
					   if((strcmp(addressBook->contacts[i].phone,phone))==0)
					   {
						   flag=1;
						   for(int j=i;j<addressBook->contactCount;j++)
						   {
							   addressBook->contacts[j]=addressBook->contacts[j+1];
						   }
					   }
				   }
				   if(flag==1)
				   {
					   (addressBook->contactCount)--;
					   addressBook->contacts=realloc((addressBook->contacts),(addressBook->contactCount)*sizeof(Contact));
					   printf("phone number successfully deleted\n");
				   }
				   else
				   {
					   printf("Not available\n");
				   }
				   break;
			case 3:printf("Enter the email: ");
				   getchar();
				   scanf("%[^\n]",email);
				   /* condition check for email or present or not
					  condition is true print the detail and delete the email
					  false means print not avilable */
				   for(int i=0;i<addressBook->contactCount;i++)
				   {
					   if((strcmp(addressBook->contacts[i].email,email))==0)
					   {
						   flag=1;
						   for(int j=i;j<addressBook->contactCount;j++)
						   {
							   addressBook->contacts[j]=addressBook->contacts[j+1];
						   }
					   }
				   }
				   if(flag==1)
				   {
					   (addressBook->contactCount)--;
					   addressBook->contacts=realloc((addressBook->contacts),(addressBook->contactCount)*sizeof(Contact));
					   printf("email successfully deleted\n");
				   }
				   else
				   {
					   printf("Not available\n");
				   }
				   break;
			default:printf("Invalid Input\n");
		}
		printf("Do you want to continue:y/n\n");
		scanf(" %c",&ch);
	}while(ch != 'n');
}
/* open the csv file in one file pointer */
void save(AddressBook *addressBook)
{
	FILE *ptr;
	/* open the file in write mod */
	ptr=fopen("file.csv","w");
	if(ptr==NULL)
	{
		printf("Unable to open the file");
	}
	fprintf(ptr,"#%d#\n",(addressBook->contactCount));
	for(int i=0;i<addressBook->contactCount;i++)
	{
		fprintf(ptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	}
}

void edit1(AddressBook *addressBook,Contact *contact)
{
	/* editing the contact by the options */
	char name[50],phone[50],email[50],email1[50],phone1[50];
	int num,count=0;
	/*enter the options*/
	printf("Enter options\n");
	printf("1.edit name:\n");
	printf("2.edit number:\n");
	printf("3.edit email:\n");
	printf("Enter your choice :");
	scanf("%d",&num);
	switch(num)
	{
		case 1:printf("Enter the new name: ");
			   scanf(" %[^\n]",contact->name);
			   break;
		case 2:int len=0,j=0;
			   do
			   {
				   len=0,j=0;
				   printf("Enter the contact number: ");
				   scanf("%s",phone1);
				   while(phone1[j]!='\0')
				   {
					   if(isdigit(phone1[len]))
					   {
						   len++;
					   }j++;
				   }
				   if(len!=10)
				   {
					   printf("number is invalid\nEnter the number again \n");
				   }
				   for(int j=0;j<addressBook->contactCount;j++)
				   {
					   if((strcmp(addressBook->contacts[j].phone,phone1))==0)
					   {
						   printf("number is already present\n");
						   len=0;
						   break;
					   }
				   }
			   }while(len!=10);
			   strcpy(contact->phone,phone1);
			   break;
		case 3:do
			   {
				   printf("Enter the email: ");
				   scanf(" %s",email1);
				   if(email1[0]!='@')
				   {
					   if((strstr(email1,"@"))&&(strstr(email1,".com")))
					   {
						   count++;
					   }
					   if(count==0)
						   printf("Invalid\n");
				   }
				   for(int j=0;j<addressBook->contactCount;j++)
				   {
					   if((strcmp(addressBook->contacts[j].email,email1))==0)
					   {
						   printf("email is already present\n");
						   count=0;
						   break;
					   }
				   }
			   }while(count==0);
			   strcpy(contact->email,email1);
			   break;
		default:printf("Invalid\n");
	}
}
