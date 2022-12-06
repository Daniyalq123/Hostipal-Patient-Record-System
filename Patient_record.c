#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void menu(void);
void add(void);
void edit(void);
void display(void);
void delete (void);
void search(void);
struct record
{

	char id[10];
	char name[20];
	char cnic[15];
	char ph[15];
	char disease[20];
	char status[5];

} patients;

int main()
{

	FILE *fptr;

	fptr = fopen("patients_record.txt", "a");
	if (fptr == NULL)
	{
		printf("file not found\nCreating one.....\nCreated..\n\n");
		fptr = fopen("patients_record.txt", "w");
	}

	fflush(stdin);
	menu();
}

void menu(void)
{

	int a;
	printf("Enter Choice\n");
	printf("\n1.Add record\n");
	printf("2.Edit record\n");
	printf("3.Display record\n");
	printf("4. Delete\n");
	printf("5. Search\n");
	printf("0.Exit\n");
	scanf("%d", &a);

	switch (a)
	{

	case 1:
		add();
		break;

	case 2:
		edit();
		break;

	case 3:
		display();
		break;
	case 4:
		delete ();
		break;
	case 5:
		search();
		break;
	case 0:
		exit(1);
		break;
	default:
		menu();
	}
}
void add(void)
{

	char temp[20];
	FILE *check;
	do
	{
		printf("enter the patient id : ");
		fflush(stdin);
		gets(temp);
	} while (strlen(temp) < 1);
	check = fopen("patients_record.txt", "r");

	while (fread(&patients, sizeof(patients), 1, check))
	{
		if (strcmp(temp, patients.id) == 0)
		{
			printf("ID already exixts!");
			return;
		}
	}
	fclose(check);

	strcpy(patients.id, temp);

	do
	{
		printf("enter the patient name: ");
		gets(patients.name);
	} while (strlen(patients.name) < 1);

	do
	{
		printf("enter the patient cnic_number: ");
		gets(patients.cnic);
	} while (strlen(patients.cnic) < 1);

	do
	{
		printf("enter the patient phone number: ");
		gets(patients.ph);
	} while (strlen(patients.ph) < 1);

	do
	{
		printf("enter the patient disease: ");
		gets(patients.disease);
	} while (strlen(patients.disease) < 1);

	int x;
	do
	{
		printf("Was patient atmitted before or not(1 for 'yes' & 0 for 'no'): ");
		scanf("%d", &x);

	} while (x > 1 || x < 0);

	if (x == 1)
	{
		strcpy(patients.status, "yes");
	}
	else
	{
		strcpy(patients.status, "no");
	}

	FILE *fptr;
	fptr = fopen("patients_record.txt", "a");
	fwrite(&patients, sizeof(patients), 1, fptr);
	fclose(fptr);
	menu();
}
void delete ()
{
	FILE *ptr = fopen("patients_record.txt", "r+");
	int account = 0;
	struct record s = {"0", "0", "0", "0", "0", "0"};
	printf("Enter Record Number: ");
	scanf("%d", &account);
	fflush(stdin);
	fseek(ptr, (account - 1) * sizeof(struct record), SEEK_SET);
	fwrite(&s, sizeof(struct record), 1, ptr);
	fclose(ptr);
	printf("Record deleted successfully.\n");
	menu();
}
void search(void)
{

	char temp[20];
	FILE *check;

	do
	{
		fflush(stdin);
		printf("\nEnter the patient id to search: ");
		gets(temp);
	} while (strlen(temp) < 1);
	check = fopen("patients_record.txt", "r");

	int ret = 1;
	while (fread(&patients, sizeof(patients), 1, check))
	{
		if (strcmp(temp, patients.id) == 0)
		{
			printf("\n\nID exixts: \n");
			printf("\n\nID: %s\nName: %s\nCNIC: %s\nPhone Number: %s\nDisease: %s\nStatus:%s\n\n", patients.id, patients.name, patients.cnic, patients.ph, patients.disease, patients.status);
			ret = 0;
			break;
		}
	}

	fclose(check);

	if (ret == 1)
	{
		return;
	}
}
void edit(void)
{

	FILE *ptr = fopen("patients_record.txt", "r+");
	int account = 0;
	struct record s;
	printf("Enter Record Number: ");
	scanf("%d", &account);
	fflush(stdin);
	printf("enter the patient name: ");
	gets(s.name);

	printf("Enter id: ");
	gets(s.id);
	printf("enter the patient cnic_number: ");
	gets(s.cnic);

	printf("enter the patient phone number: ");
	gets(s.ph);

	printf("enter the patient disease: ");
	gets(s.disease);

	int x;

	printf("Was patient atmitted before or not(1 for 'yes' & 0 for 'no'): ");
	scanf("%d", &x);

	if (x == 1)
	{
		strcpy(s.status, "yes");
	}
	else
	{
		strcpy(s.status, "no");
	}
	fseek(ptr, (account - 1) * sizeof(struct record), SEEK_SET);
	fwrite(&s, sizeof(struct record), 1, ptr);
	fclose(ptr);
	printf("Record updated successfully.\n");
	menu();
}

void display(void)
{

	FILE *d;
	d = fopen("patients_record.txt", "r");
	while (fread(&patients, sizeof(patients), 1, d))
	{
		if (strcmp(patients.id, "0") != 0)
		{
			printf("\n\nID: %s\nName: %s\nCNIC: %s\nPhone Number: %s\nDisease: %s\nStatus:%s\n\n", patients.id, patients.name, patients.cnic, patients.ph, patients.disease, patients.status);
		}
	}

	menu();
}
