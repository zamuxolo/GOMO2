# include <stdio.h>
# include "/usr/i686-w64-mingw32/include/conio.h"
# include <stdlib.h>
# include <string.h>

# define EMP_FILE "empdata.txt"
# define TMP_FILE "tmpdata.txt"

# define EPF_RATE 0.18
# define ETF_RATE 0.03
# define GEN_TIME (8 * 20)
# define PWD "hacker\0"

int main(int, char**);
void welcome_message(void);
void get_password(void);
void main_menu(void);
void manage_employee(void);
void add_employee(void);
void delete_employee(void);
void edit_employee(void);
void search_employee(void);
void print_report(void);
void print_slip(void);
void emp_menu(void);
void exit_message(void);

int main(int argc, char *argv[])
{
	char menuOpt;
	int isExit = 0;
	welcome_message();
	if(argc > 1)
	{
		clrscr();
		printf("%s : Start Up Error >>> ", argv[0]);
		fflush(stdin);
		getch();
		return (EXIT_FAILURE);
	}
	get_password();
	do
	{
		main_menu();
		fflush(stdin);
		menuOpt = (char)getch();
		switch(menuOpt)
		{
			case '1':
			{
				manage_employee();
				break;
			}
			case '2':
			{
				print_report();
				break;
			}
			case '3':
			{
				print_slip();
				break;
			}
			case '4':
			{
				isExit = 1;
				break;
			}
			default:
			{
				clrscr();
				printf("Invalid Option!");
				fflush(stdin);
				getch();
				break;
			}
		}
	}while(isExit == 0);
	exit_message();
	fflush(stdin);
	getch();
    return (EXIT_SUCCESS);
}

void welcome_message(void)
{
	clrscr();
	printf("WELCOME!");
	fflush(stdin);
	getch();
}

void main_menu(void)
{
	clrscr();
	printf("                MENU\n");
	printf("                ----\n");
	printf("     [1] : Manage Employees\n");
	printf("     [2] : Print Report\n");
	printf("     [3] : Print Slip\n");
	printf("     [4] : Exit\n\n");
	printf(" >>> ");
}

void manage_employee(void)
{
	char menuOpt;
	int isExit = 0;
	do
	{
		emp_menu();
		fflush(stdin);
		menuOpt = (char)getch();
		switch(menuOpt)
		{
			case '1':
			{
				add_employee();
				break;
			}
			case '2':
			{
				delete_employee();
				break;
			}
			case '3':
			{
				edit_employee();
				break;
			}
			case '4':
			{
				search_employee();
				break;
			}
			case '5':
			{
				isExit = 1;
				fflush(stdin);
				break;
			}
			default:
			{
				clrscr();
				printf("Invalid Option!");
				getch();
			}
		}
	}while(isExit == 0);
}

void add_employee(void)
{
	char name[50];
	char address[100];
	char phone[11];
	char id[5];
	float salary;
	float hours;
	FILE *fp;
	fp = fopen(EMP_FILE, "a+");
	do
	{
		fscanf(fp, "%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%f %f%*c", name, address, phone, id, &salary, &hours);
		if(feof(fp))
		{
			break;
		}
	}while(!(feof(fp)));
	clrscr();
	printf("Name         : ");
	fflush(stdin);
	gets(name);
	printf("Address      : ");
	fflush(stdin);
	gets(address);
	printf("Phone        : ");
	fflush(stdin);
	gets(phone);
	printf("ID           : ");
	fflush(stdin);
	gets(id);
	printf("Salary       : ");
	fflush(stdin);
	scanf("%f", &salary);
	printf("Hours        : ");
	fflush(stdin);
	scanf("%f", &hours);
	fprintf(fp, "%s/%s/%s/%s/%.2f %.2f\n", name, address, phone, id, salary, hours);
	fflush(fp);
	fclose(fp);
	clrscr();
	printf("Done Entering New Record >>> ");
	getch();
}

void delete_employee(void)
{
	char name[50];
	char address[100];
	char phone[11];
	char id[5];
	char idDel[5];
	float salary;
	float hours;
	FILE *fp1;
	FILE *fp2;
	fp1 = fopen(EMP_FILE, "r");
	fp2 = fopen(TMP_FILE, "w");
	clrscr();
	printf("Enter Employee ID to Delete : ");
	fflush(stdin);
	gets(idDel);
	do
	{
		fscanf(fp1, "%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%f %f%*c", name, address, phone, id, &salary, &hours);
		if(feof(fp1))
		{
			break;
		}
		if((strcmp(id, idDel)) != 0)
		{
			fprintf(fp2, "%s/%s/%s/%s/%.2f %.2f\n", name, address, phone, id, salary, hours);
		}
	}while(!(feof(fp1)));
	fflush(fp2);
	fclose(fp1);
	fclose(fp2);
	remove(EMP_FILE);
	rename(TMP_FILE, EMP_FILE);
	clrscr();
	printf("Done Deleting >>> ");
	fflush(stdin);
	getch();
}

void edit_employee(void)
{
	char name[50];
	char address[100];
	char phone[11];
	char id[5];
	char idEdit[5];
	float salary;
	float hours;
	FILE *fp1;
	FILE *fp2;
	fp1 = fopen(EMP_FILE, "r");
	fp2 = fopen(TMP_FILE, "w");
	clrscr();
	printf("Enter Employee ID to Edit : ");
	fflush(stdin);
	gets(idEdit);
	do
	{
		fscanf(fp1, "%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%f %f%*c", name, address, phone, id, &salary, &hours);
		if(feof(fp1))
		{
			break;
		}
		if((strcmp(id, idEdit)) == 0)
		{
			clrscr();
			printf("Enter new basic salary : ");
			fflush(stdin);
			scanf("%f", &salary);
			printf("Enter the new number of hours worked : ");
			fflush(stdin);
			scanf("%f", &hours);
		}
		fprintf(fp2, "%s/%s/%s/%s/%.2f %.2f\n", name, address, phone, id, salary, hours);
	}while(!(feof(fp1)));
	fflush(fp2);
	fclose(fp1);
	fclose(fp2);
	remove(EMP_FILE);
	rename(TMP_FILE, EMP_FILE);
	clrscr();
	printf("Done Editing >>> ");
	fflush(stdin);
	getch();
}

void search_employee(void)
{
	char name[50];
	char address[100];
	char phone[11];
	char id[5];
	char idSearch[5];
	float salary;
	float hours;
	FILE *fp;
	fp = fopen(EMP_FILE, "r");
	clrscr();
	printf("Enter the Employee ID to Search : ");
	fflush(stdin);
	gets(idSearch);
	do
	{
		fscanf(fp, "%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%f %f%*c", name, address, phone, id, &salary, &hours);
		if(feof(fp))
		{
			break;
		}
		if((strcmp(id, idSearch)) == 0)
		{
			clrscr();
			printf("Name         : %s\n", name);
			printf("Address      : %s\n", address);
			printf("Phone        : %s\n", phone);
			printf("ID           : %s\n", id);
			printf("Salary       : %.2f\n", salary);
			printf("Hours        : %.2f\n\n", hours);
			printf("Press ENTER to continue >>> ");
			fflush(stdin);
			getch();
		}
	}while(!(feof(fp)));
	fclose(fp);
}

void print_report(void)
{
	char name[50];
	char address[100];
	char phone[11];
	char id[5];
	float salary;
	float hours;
	float epf;
	float etf;
	float netSal;
	float ot, otRate, otHrs;
	FILE *fp;
	fp = fopen(EMP_FILE, "r");
	clrscr();
	do
	{
		fscanf(fp, "%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%f %f%*c", name, address, phone, id, &salary, &hours);
		if(feof(fp))
		{
			break;
		}
		epf = salary * EPF_RATE;
		etf = salary * ETF_RATE;
		otHrs = hours - GEN_TIME;
		otRate = salary / GEN_TIME;
		if(otHrs > 0)
		{
			ot = otHrs * otRate;
		}
		else
		{	
			ot = 0;
			otHrs = 0;
		}
		netSal = salary - (epf + etf) + ot;
		printf("%5s %5.2f %3.2f %3.2f %3.2f %5.2f %5.2f %5.2f %5.2f\n", id, salary, hours, otHrs, ot, epf, etf, netSal);
		getch();
	}while(!(feof(fp)));
	fclose(fp);
}

void print_slip(void)
{
	char name[50];
	char address[100];
	char phone[11];
	char id[5];
	char empId[5];
	float salary;
	float hours;
	float epf;
	float etf;
	float netSal;
	float ot, otRate, otHrs;
	FILE *fp;
	fp = fopen(EMP_FILE, "r");
	clrscr();
	printf("Enter Employee ID to print : ");
	fflush(stdin);
	gets(empId);
	do
	{
		fscanf(fp, "%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%f %f%*c", name, address, phone, id, &salary, &hours);
		if(feof(fp))
		{
			break;
		}
		if((strcmp(id, empId)) == 0)
		{
			epf = salary * EPF_RATE;
			etf = salary * ETF_RATE;
			otHrs = hours - GEN_TIME;
			otRate = salary / GEN_TIME;
			if(otHrs > 0)
			{
				ot = otHrs * otRate;
			}
			else
			{	
				ot = 0;
				otHrs = 0;
			}
			netSal = salary - (epf + etf) + ot;
			clrscr();
			printf("Name              : %s\n", name);
			printf("Address           : %s\n", address);
			printf("Phone             : %s\n", phone);
			printf("id                : %s\n", id);
			printf("Basic Salary      : %.2f\n", salary);
			printf("Total Hours       : %.2f\n", hours);
			printf("OT Hours          : %.2f\n", otHrs);
			printf("OT Rate           : %.2f\n", otRate);
			printf("OT Amount         : %.2f\n", ot);
			printf("EPF               : %.2f\n", epf);
			printf("ETF               : %.2f\n", etf);
			printf("Net Salary        : %.2f\n", netSal);
		}
	}while(!(feof(fp)));
	fclose(fp);
	printf("Done >>> ");
	fflush(stdin);
	getch();
}

void get_password(void)
{
	char password[7];
	do
	{
		clrscr();
		printf("Enter Password >>> ");
		fflush(stdin);
		gets(password);
	}while((strcmp(password, PWD)) != 0);
}

void emp_menu(void)
{
	clrscr();
	printf("               MENU\n");
	printf("               ----\n");
	printf("    [1] : Add Employee\n");
	printf("    [2] : Delete Employee\n");
	printf("    [3] : Edit Employee\n");
	printf("    [4] : Search Employee\n");
	printf("    [5] : Go Back\n\n");
	printf(" >>> ");
}

void exit_message(void)
{
	clrscr();
	printf("THANK YOU!\n");
	printf(">>> ");
}
