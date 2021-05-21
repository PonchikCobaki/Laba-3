#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <iostream>
#include <fstream>

#pragma pack(4)

void view(char* file);
void view_2(char* file);
void viewww(char* file);
void create(void);

typedef struct
{
	int number;
	char name[20];
	int birthday;
	char education[5];
	char gender[5];
	int date;
} Staff;

int main()
{
	char file[50];
	puts("Name of file:");
	gets(file);
	char menu;
	do
	{
		system("cls");
		puts("1. View");
		puts("2. View older man");
		puts("3. View staff under 28 years old with higher education");
		puts("4. Create");
		puts("5. Exit");
		menu = _getch();
		switch (menu)
		{
		case '1': view(file); break;
		case '2': view_2(file); break;
		case '3': viewww(file); break;
		case '4': create();
		}
		system("pause");

	} while (menu != '5');
	return 0;
}

void view(char* file)
{
	int i;
	FILE* fp = fopen(file, "rb");
	fseek(fp, 0, SEEK_END);
	int lenght = sizeof(Staff);
	int size = ftell(fp) / lenght;
	Staff* laboratory = (Staff*)malloc(lenght * size);
	rewind(fp);
	for (i = 0; i < size; i++)
	{
		fread(&laboratory[i], sizeof(Staff), 1, fp);
	}
	for (i = 0; i < size; i++)
	{
		printf("Staff #%d <%s>, birthday %d, name <%s>, education <%s>, gender <%s>, date = %d\n", i + 1, laboratory[i].birthday, laboratory[i].name, laboratory[i].education, laboratory[i].gender, laboratory[i].date);
	}
	fclose(fp);

}

void view_2(char* file)
{
	FILE* fp = fopen(file, "rb+");
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp) / sizeof(Staff);
	rewind(fp);
	Staff* laboratory = (Staff *)malloc(sizeof(Staff) * size);
	int i, max, flag = 0;
	fread(laboratory, sizeof(Staff), size, fp);
	max = laboratory[0].birthday;
	for (i = 0; i < size; i++)
	{
		if (laboratory[i].birthday <= max)
		{
			max = laboratory[i].birthday;
		}
		else flag++;
	}
	if (flag == size) max = laboratory[size - 1].birthday;
	for (i = 0; i < size; i++)
	{
		if (laboratory[i].birthday == max && strlen(laboratory[i].gender) < 4)
			printf("Staff #%d <%s>, birthday %d, name <%s>, education <%s>, gender <%s>, date = %d\n", i + 1, laboratory[i].birthday, laboratory[i].name, laboratory[i].education, laboratory[i].gender, laboratory[i].date);
	}
	fclose(fp);
}


void viewww(char* file)
{
	FILE* fp = fopen(file, "rb");
	fseek(fp, 0, SEEK_END);
	int lenght = sizeof(Staff);
	int size = ftell(fp) / lenght;
	rewind(fp);
	Staff* laboratory = (Staff*)malloc(lenght * size);
	int i;
	for (i = 0; i < size; i++)
	{
		fread(&laboratory[i], sizeof(Staff), 1, fp);
	}
	for (i = 0; i < size; i++)
	{
		if (strlen(laboratory[i].education) > 3 && laboratory[i].birthday > 1993)
			printf("Staff #%d <%s>, birthday %d, name <%s>, education <%s>, gender <%s>, date = %d\n", i + 1, laboratory[i].birthday, laboratory[i].name, laboratory[i].education, laboratory[i].gender, laboratory[i].date);
	}
	fclose(fp);

}

void create(void)
{
	int i, n;
	char filename[100] = {};
	puts("Enter file name:");
	gets(filename);
	puts("Enter count of elements:");
	scanf("%d", &n);
	Staff laboratory;
	FILE* fp = fopen(filename, "wb");
	if (!feof(fp)) {}
	fflush(stdin);
	for (i = 0; i < n; i++)
	{
		printf("Describe Staff #%d\nName Staff > ", i + 1);
		gets(laboratory.name);
		printf("education > ");
		gets(laboratory.education);
		printf("gender > ");
		gets(laboratory.gender);
		printf("birthday > ");
		scanf("%d", &laboratory.birthday);
		fflush(stdin);
		printf("date > ");
		scanf("%d", &laboratory.date);
		fflush(stdin);
		//printf("Staff #%d <%s>, birthday %d, name <%s>, education <%s>, gender <%s>, date = %d\n", i+1, laboratory.name, laboratory.education, laboratory.gender, laboratory.birthday, laboratory.date);
		fwrite(&laboratory, sizeof(Staff), 1, fp);
	}
	fclose(fp);
}