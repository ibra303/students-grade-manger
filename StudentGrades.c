#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
//student struct
struct Student
{
	char* SName;
	long ID;
	float MatamGrade;
	char HW[5];
}typedef Student;
//university struct
struct University
{
	Student* SArr;
	int NumOfStudents;
}typedef University;
//functions 
void FreeTheArrI(Student* STD, int SizeOf);
int ScanTheStudentsInfo(FILE* F1, Student** S1);
void PrintTheStudentsInfo(FILE* F2, University* U1);
void PrintTheFinalGrades(FILE* F2, University* U1);
void StudentsGrades(FILE* F2, University* U1);
void BlackList(FILE* F2, University* U1);
//main
int main()
{
	University University1;
	char Input ="0";
	FILE* in = fopen("input.txt","r");
	if (!in)
	{
		printf("Error File not opening");
		exit(1);
	}
	University1.NumOfStudents = ScanTheStudentsInfo(in,&University1.SArr);
	FILE* out = fopen("output.txt","w");
	if (!out)
	{
		printf("Error File not opening");
		FreeTheArrI(&University1.SArr, University1.NumOfStudents);
		exit(1);
	}
	//while the user dont want to end the program
	while (Input != 'f' && Input!='F')
	{
		printf("Enter You Option (B/C/D/E) /(F to end):");
		if (Input == 'b' || Input == 'B')
		{
			fprintf(out, "%s\n\n", "Option B:");
			PrintTheStudentsInfo(out, &University1);
		}
		if (Input == 'c' || Input == 'C')
		{
			fprintf(out, "%s\n\n", "Option C:");
			fprintf(out,"Before :\n");
			PrintTheStudentsInfo(out, &University1);
			fprintf(out, "After :\n");
			PrintTheFinalGrades(out, &University1);
		}
		if (Input == 'd' || Input == 'D')
		{
			fprintf(out, "%s\n\n", "Option D:");
			StudentsGrades(out, &University1);
		}
		if (Input == 'e' || Input == 'E')
		{
			fprintf(out, "%s\n\n", "Option E:");
			BlackList(out, &University1);
		}
		scanf(" %c", &Input);
	}
	fprintf(out, "%s\n\n", "Option F:");
	fprintf(out, "End Of Program");
	return 0;
}
//this function takes info of students from file and put them in struct using malloc function
//to make structs for all students in the file 
int ScanTheStudentsInfo(FILE* F1, Student** S1)
{
	Student* arr;
	char Sname[100];
	int counter = 1;
	arr = (Student*)malloc(sizeof(Student));
	if (!arr)
	{
		printf("Not Enough Memory");
		FreeTheArrI(arr, counter - 1);
		exit(1);
	}
	while (fscanf(F1, "%s %li %f %c %c %c %c %c", &Sname, &arr[counter - 1].ID, &arr[counter - 1].MatamGrade, &arr[counter - 1].HW[0], &arr[counter - 1].HW[1], &arr[counter - 1].HW[2], &arr[counter - 1].HW[3], &arr[counter - 1].HW[4]) != EOF)
	{
		arr[counter-1].SName = (char*)malloc((strlen(Sname) + 1) * sizeof(char));
		if (arr[counter - 1].SName == NULL)
		{
			printf("Not Enough Memory");
			FreeTheArrI(arr, counter -1);
			exit(1);
		}
		strcpy(arr[counter - 1].SName, Sname);
		Student* oldarr = arr;
		counter++;
		arr = (Student*)realloc(arr, counter * sizeof(Student));
		if (!arr)
		{
			printf("Not Enough Memory");
			FreeTheArrI(arr, counter - 1);
			exit(1);
		}
		if (arr == NULL)
		{
			free(oldarr);
			printf("Encountered an error in memory allocation");
		}
	}
	fclose(F1);
	*S1 = arr;
	return counter - 1;
}
//this function print the info of structs to other file using for loop 
void PrintTheStudentsInfo(FILE* F2,University* U1)
{
	int i = 0;
	for ( i = 0; i <U1->NumOfStudents ; i++)
	{
		int flag = 0;
		int count = 0;
		Student Now = U1->SArr[i];
		for (int j = 0; j < 5; j++)
		{
			if (Now.HW[j] == '1')
				count++;
		}
		if (count>=3)
		{
			flag = 1;
		}
		fprintf(F2, "Stduent %d : %s %li %.2f %d\n",i+1, Now.SName,Now.ID,Now.MatamGrade,flag);
	}
	fprintf(F2, "\n");
}
//this function print the info of structs to other file using for loop and also prints the final grade
//for all structs students 
void PrintTheFinalGrades(FILE* F2, University* U1)
{
	int i = 0;
	
	for (i = 0; i < U1->NumOfStudents; i++)
	{
		int flag = 0;
		int count = 0;
		float Part2 = 0;
		float Final = 0;
		Student Now = U1->SArr[i];
		for (int j = 0; j < 5; j++)
		{
			if (Now.HW[j] == '1')
				count++;
		}
		if (count >= 3)
		{
			flag = 1;
		}
		if (flag==1 && Now.MatamGrade >=55)
		{
			Part2 = Now.MatamGrade * 0.85;
			Final = Part2 + 15;
		}
		else
		{
			Final = Now.MatamGrade;
		}
		fprintf(F2, "Stduent %d : %s %li %.2f %d  Final : %.2f\n", i + 1, Now.SName, Now.ID, Now.MatamGrade, flag,Final);
	}
	fprintf(F2,"\n");
}
//this function helps us to sum the final grade for students using for loop to get
//there info and make a final grade 
void StudentsGrades(FILE* F2, University* U1)
{
	int i = 0;
	float AVG = 0, SD = 0, Max = 0, Min = Max;
	Student Now1 = U1->SArr[i];
	for ( i = 0; i < U1->NumOfStudents; i++)
	{
		Now1 = U1->SArr[i];
		AVG =AVG + Now1.MatamGrade;
		if (Now1.MatamGrade > Max)
			Max = Now1.MatamGrade;
		Min = Max;
		if (Now1.MatamGrade < Min)
			Min = Now1.MatamGrade;
	}
	AVG = AVG / U1->NumOfStudents;
	for ( i = 0; i < U1->NumOfStudents; i++)
	{
		Now1 = U1->SArr[i];
	    SD += pow((Now1.MatamGrade -AVG),2);
	}
	SD =sqrt(SD / U1->NumOfStudents);
	fprintf(F2, "Students Grades Average : %.2f\n",AVG);
	fprintf(F2, "Standard Deviation : %.2f\n", SD);
	fprintf(F2,"Amount Of Students : %d\n", U1->NumOfStudents);
	fprintf(F2, "Grades Range : %.2f - %.2f\n",Max,Min);
	fprintf(F2, "\n");
}
//this function makes a black list .. a list that include all students info that they didnt make at least 3 homeworks
void BlackList(FILE* F2, University* U1)
{
	int i = 0, count = 0, flag = 0;
	Student Now2 = U1->SArr[i];
	for ( i = 0; i < U1->NumOfStudents; i++)
	{
		count = 0;
		flag = 0;
		Now2 = U1->SArr[i];
		for (int j = 0; j < 5; j++)
		{
			if (Now2.HW[j] == '1')
				count++;
		}
		if (count >= 3)
		{
			flag = 1;
		}
		if (flag == 0)
		{
			fprintf(F2, " %s %li ", Now2.SName, Now2.ID);
		}
	}
	fprintf(F2, "\n\n");
}
// if there was error in name memmory
void FreeTheArrI(Student* STD, int SizeOf)
{
	for (int j = 0; j < SizeOf; j++)
	{
		free(STD[j].SName);
	}
	free(STD);
}