/***********************MOBILINK CUSTOMER DATABASE PROJECT*******************/
/***********************BY MUHAMMAD AWAIS RAZA ******************************/


/*HEADER FILES ARE INCLUDED*/

#include "/usr/i686-w64-mingw32/include/dos.h"
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include<graphics.h>

/*MACROS ARE DEFINED*/

#define NUM 5
#define PH 12
#define MIN 30
#define MAX 61

/*FUNCTION DECLARATION*/

void add();		// Ask user for input.
void view();            // Diplay all the record.
void search();          // Search for a record.
void c_name();          // Changes the name in a record.
void c_add();           // Changes the address in a record.
void c_ct();            // Changes the connection type in a record.
void c_ph();            // Changes the phone in a record.
void del();             // Deletes a record.
int date(void);         // This fucntion is for displaying System Date.


/*VALIDATION FUNCTIONS*/

void check_id(char *,int);	//Checks for the length and validity of SIM ID
void check_name(char *,int);    //Checks for the length and validity of NAME
void check_add(char *,int);     //Checks for the length and validity of ADDRESS
void check_phone(char *,int);   //Checks for the length and validity of PHONE NUMBER
void check_ct(int *);           //Checks for the CONNECTION TYPE
int duplicate(char idno[]);	//Checks for the Duplication of the SIM ID

/*MISC FUNCTION*/

void empty();

/*STRUCTURE DECLARATION*/

struct customer
{
	char id[NUM];		/* ID of Length 5*/
	char name[MIN];		/* Name of Length 30*/
	char address[MAX]; 	/* Address of Length 61*/
	char phone[PH]; 	/* Phone Number of Length 12*/
	int  connection;	/* Connection Type of length 2*/
	int  day;               /* It is used to display the day of length 2*/
	int  month;             /* It is used to display the month of length 2*/
	int  year;              /* it is used to display the year*/
}rec;

/***************************MAIN FUNCTION STARTS*****************************/
main()
{
	int c;

do{
	int i;
	window(1,1,80,25);
	textbackground(LIGHTRED);
	textcolor(LIGHTGRAY);

	clrscr();

	gotoxy(24,2);
	printf("<< MOBILINK CUSTOMER DATABASE >>");
	gotoxy(24,3);
	cprintf("<< BY-MUHAMMAD AWAIS RAZA     >>");


	for(i=10;i<=70;i++) 	//This 'FOR' loop will print a combination of
	{                       //asteriks '*' and dash '-' horizontally till
		gotoxy(i,4);    //the 70th column is reached.
		printf("Ü");
		gotoxy(71,4);    //the 70th column is reached.
		printf("Ü");
		gotoxy(i,7);
		printf("-");
		gotoxy(i,9);
		printf("-");
		gotoxy(i,11);
		printf("-");
		gotoxy(i,13);
		printf("-");
		gotoxy(69,16);
		printf("ß");
		gotoxy(71,16);
		printf("ß");
		gotoxy(i,16);
		printf("ß");
	}

	for(i=5;i<=15;i++)      //This 'FOR' loop will print asteriks '*'
	{                       //vertically till the 15th row is reached.
		gotoxy(10,i);
		printf("ÝÞ");
		gotoxy(70,i);
		printf("ÝÞ");
	}

	for(i=6;i<=12;i++)      //This 'FOR' loop will print '|' sign
	{                       //vertically till the 12th row is reached.
		gotoxy(40,i);
		printf("|");
	}

	gotoxy(15,6);
	printf("[1] ENTER A RECORD");
	gotoxy(15,8);
	printf("[2] VIEW RECORDS");
	gotoxy(15,10);
	printf("[3] SEARCH RECORD");
	gotoxy(15,12);
	printf("[4] DELETE RECORD");
	gotoxy(43,6);
	printf("[5] CHANGE NAME");
	gotoxy(43,8);
	printf("[6] CHANGE ADDRESS");
	gotoxy(43,10);
	printf("[7] CHANGE CONNECTION TYPE");
	gotoxy(43,12);
	printf("[8] CHANGE PHONE NUMBER");
	gotoxy(37,14);
	printf("[9] EXIT");
	gotoxy(10,20);
	textcolor(LIGHTGRAY);
	cprintf("PLEASE SELECT A CHOICE: ");

	c = (getche());

		switch (c)      //This 'SWITCH' structure will ask the user for input from [1] to [9] and will display error on Invalid Entry.
			{
				case '1': add();    break;   //It will call the add() funtion to allow user to add and save record.
				case '2': view();   break;   //It will call the view() funtion to allow user to view the saved record.
				case '3': search(); break;   //It will call the search() funtion to allow user to search records.
				case '4': del();    break;   //It will call the delete() funtion to allow user to delete a saved record.
				case '5': c_name(); break;   //It will call the c_name() funtion to allow user to modify name of a saved record.
				case '6': c_add();  break;   //It will call the c_add() funtion to allow user to modify address of a saved record.
				case '7': c_ct();   break;   //It will call the c_ct() funtion to allow user to modify  connection type & date of a saved record.
				case '8': c_ph();   break;   //It will call the c_ph() funtion to allow user to modify phone number of a saved record.
				case '9': gotoxy(30,24);printf("<<<<--THANK YOU-->>>>");getch();exit(0);  //It will terminate the program.
				default:
				sound(500);delay(200);nosound(); 	//sound turns the PC speaker on at the specified frequency, nosound turns the PC speaker off.
				gotoxy(26,24);
				puts("<<--ENTER FROM 1-9 PLEASE-->>");	//This message will only print on INVALID ENTRY and Will ask again for input.
				getch();
			}

}while(c != '9'); 	//This 'WHILE' loop will continue till the Exit option [9] is entered.

	return 0;
}
/**************************END OF MAIN FUNCTION******************************/
void add()
{
	FILE *fp;
	char ch;
	char temp[NUM];



	if(fp!=NULL)
	{
		 do{
			 fp=fopen("customer.rec","ab");

			 clrscr();

			 gotoxy(25,2);
			 printf("<<==--ADDING RECORD--==>>");
			 do{
				   gotoxy(1,4);
				   printf("Enter [UNIQUE] SIM ID: ");
				   check_id(temp, NUM);

			 }while(duplicate(temp));  		//This Condition Will keep on executng till a non duplicate ID is entered.

			 strcpy(rec.id, temp);     		//After verifying, ID in 'temp' will copy to 'rec.id'

			 gotoxy(1,6);
			 printf("Enter NAME: ");
			 check_name(rec.name,MIN);      	//It will verify that no neumerical input is given & the name input should not exceed the length limit
			 gotoxy(1,8);
			 printf("Enter ADDRESS: ");
			 check_add(rec.address,MAX);    	//It will verify that only alpha neumeric input is entered & should not exceed the length limit
			 gotoxy(1,10);
			 printf("Enter PHONE Number: ");
			 check_phone(rec.phone, PH);    	//It will verify phone number of a particular length
			 gotoxy(1,12);
			 printf("Enter CONNECTION TYPE: ");
			 check_ct(&rec.connection);     	//It will allow user to select between 'STAR' & 'JAZZ' only

			 {
				   struct date d;

				   getdate(&d);
				   gotoxy(1,12);
				   printf("DATE OF PURCHASE: %d %d %d ",d.da_day,d.da_mon,d.da_year);
				   rec.day   = d.da_day;
				   rec.month = d.da_mon;
				   rec.year  = d.da_year;
			 }

			 window(1,1,80,25);
			 gotoxy(1,12);

			 fwrite(&rec, sizeof(rec), 1, fp);	//Record will be written to file.

			 fclose(fp);
			  textbackground(LIGHTRED);
			 gotoxy(20,24);

			 printf("DO YOU WISH TO CONTINUE..[Y]/[N]: ");
			 ch=toupper(getche());

		}while(ch =='Y');	//Repeat loop while user inputs 'Y'
	}
	else
	{
		gotoxy(20,24);
		printf("Unable To Open File...");
	}
}

/**************************************************************************
| Function: view()	                                                  |
|                                                                         |
| Purpose : To Display all the records in the file in a                   |
|           formatted output.                                             |
|                                                                         |
| Local Variables:                                                        |
|									  |
| >FILE *fp: Decalres file pointer.                                       |
***************************************************************************/

void view()
{
	FILE *fp;


	fp=fopen("customer.rec","rb");

	if(fp!=NULL)
	{
		clrscr();

		while( fread(&rec, sizeof(rec), 1, fp))
			if(strcmp(rec.id," ")!=0)
			{

					clrscr();
					gotoxy(28,2);
					printf("<<==--VIEWING RECORDS--==>>");
					gotoxy(3,5);
					printf(" SIM ID: %s",rec.id);
					gotoxy(3,7);
					printf(" NAME: %s",rec.name);
					gotoxy(3,9);
					printf(" ADDRESS: %s",rec.address);
					gotoxy(3,11);
					printf(" PHONE Number: %s",rec.phone);
					gotoxy(3,13);
					printf(" CONNECTION TYPE: %s",rec.connection);
					if(rec.connection==1)
					{
						gotoxy(21,13);
						printf("STAR");
					}
					else
					if(rec.connection==2)
					{
						gotoxy(21,13);
						printf("JAZZ");
					}
					gotoxy(3,15);
					printf(" DATE Of PURCHASE: %d-%d-%d",rec.day,rec.month,rec.year);

					getch();
			}

			if(strcmp(rec.id," ")==NULL)
			{
				clrscr();
				gotoxy(20,13);
				sound(500);delay(200);nosound();
				printf("<<==--THERE ARE NO RECORDS TO VIEW--==>>");
				getch();
			}
		fclose(fp);
	}
	else
	{
		gotoxy(20,24);
		printf("Unable To Open File...");
	}
}
/*************************END OF VIEW FUNCTION*******************************/


void search()
{
	int ch;
	FILE *fp;
	char sno[NUM];
	clrscr();

	fp=fopen("customer.rec","rb");

	gotoxy(20,13);
	printf("PLEASE ENTER SIM ID ==->>>> ");
	check_id(sno,NUM);

		while ( fread(&rec, sizeof(rec), 1, fp) && strcmp(sno,rec.id) );


			ch=strcmp(sno,rec.id);
				if(ch!=0)
				{
					clrscr();
					sound(500);delay(200);nosound();
					gotoxy(28,13);
					printf("<<--RECORD NOT FOUND-->>");
					getch();
				}
				else

				{
					clrscr();
					gotoxy(28,2);
					printf("<<==SEARCH SUCCESSFUL==>>");
					gotoxy(3,5);
					printf(" SIM ID: %s",rec.id);

					gotoxy(3,7);
					printf(" NAME: %s",rec.name);

					gotoxy(3,9);
					printf(" ADDRESS: %s",rec.address);

					gotoxy(3,11);
					printf(" PHONE Number: %s",rec.phone);

					gotoxy(3,13);
					printf(" CONNECTION TYPE: %s",rec.connection);
					if(rec.connection==1)
					{
						gotoxy(21,13);
						printf("STAR");
					}
					else
					if(rec.connection==2)
					{
						gotoxy(21,13);
						printf("JAZZ");
					}
					gotoxy(3,15);
					printf(" DATE Of PURCHASE: %d-%d-%d",rec.day,rec.month,rec.year);

					getch();
				}
		fclose(fp);
}

/*************************END OF SEARCH FUNCTION*****************************/



void c_name()
{
	int ch;
	FILE *fp;
	char sno[NUM];
	clrscr();

	fp=fopen("customer.rec","rb+");

	gotoxy(20,13);
	printf("PLEASE ENTER SIM ID ==->>>> ");
	check_id(sno,NUM);

		while ( fread(&rec, sizeof(rec), 1, fp) && strcmp(sno,rec.id) );

			ch=strcmp(sno,rec.id);
				if(ch!=0)
				{
					clrscr();
					sound(500);delay(200);nosound();
					gotoxy(28,13);
					printf("<<--RECORD NOT FOUND-->>");
					getch();
				}
				else
				{
					clrscr();
					gotoxy(28,4);
					printf("<<<--==RECORD FOUND==-->>>");

					gotoxy(3,8);
					printf("OLD NAME: %s",rec.name);   // This will print the old name already stored.
					gotoxy(3,12);
					printf("ENTER NAME: ");            // This will allow the user to change the old name and input a new name.
					check_name(rec.name,MIN);          // The check will validate each character entered turn by turn.

					fseek(fp, ftell(fp) - sizeof(rec),0);
					  fwrite(&rec, sizeof(rec), 1, fp);  //The new name will be added to the record.

					gotoxy(34,24);
					printf("RECORD SAVED !!!");

					getch();
				}
		fclose(fp);
}

/*************************END OF CHANGE NAME FUNCTION************************/


void c_add()
{
	int ch;
	FILE *fp;
	char sno[NUM];
	clrscr();

	fp=fopen("customer.rec","rb+");

	gotoxy(20,13);
	printf("PLEASE ENTER SIM ID ==->>>> ");
	check_id(sno,NUM);

		while ( fread(&rec, sizeof(rec), 1, fp) && strcmp(sno,rec.id) );

			ch=strcmp(sno,rec.id);  // Here the result after comparing the values of the two strings by using the 'strcmp' function is assigned to 'ch'.
				if(ch!=0)       // This loop will execute if the SIM ID's dont compare.
				{
					clrscr();
					sound(500);delay(200);nosound();
					gotoxy(28,13);
					printf("<<--RECORD NOT FOUND-->>");
					getch();
				}
				else            // If the ID's match, then this block will be executed.
				{
					clrscr();
					gotoxy(28,4);
					printf("<<<--==RECORD FOUND==-->>>");

					gotoxy(3,8);
					printf("OLD ADDRESS: %s",rec.address);
					gotoxy(3,12);
					printf("ENTER NEW ADDRESS: ");
					check_add(rec.address,MAX);

					fseek(fp, ftell(fp) - sizeof(rec),0);	//fseek sets the file pointer associated with a stream to a new position.
					  fwrite(&rec, sizeof(rec), 1, fp);	//fwrite appends a specified number of equal-sized data items to an output file.

					gotoxy(34,24);
					printf("RECORD SAVED !!!");

					getch();
				}
		fclose(fp);
}

/*************************END OF CHANGE ADDRESS FUNCTION*********************/



void c_ct()
{
	int ch;
	FILE *fp;
	char sno[NUM];
	clrscr();

	fp=fopen("customer.rec","rb+");

	gotoxy(20,13);
	printf("PLEASE ENTER SIM ID ==->>>> ");
	check_id(sno,NUM);

		while ( fread(&rec, sizeof(rec), 1, fp) && strcmp(sno,rec.id) );

			ch=strcmp(sno,rec.id);
				if(ch!=0)
				{
					clrscr();
					sound(500);delay(200);nosound();
					gotoxy(28,13);
					printf("<<--RECORD NOT FOUND-->>");
					getch();
				}
				else
				{
					clrscr();
					gotoxy(28,2);
					printf("<<<--==RECORD FOUND==-->>>");

					gotoxy(3,6);
					printf("OLD DATE OF PURCHASE: %d %d %d",rec.day,rec.month,rec.year);	//Old Date Of purchase is displayed.
					{
						struct date d;

						getdate(&d);
						gotoxy(3,8);
						printf("NEW DATE OF PURCHASE: %d %d %d ",d.da_day,d.da_mon,d.da_year);	//New Date Of Purchase is stored.
						rec.day = d.da_day;
						rec.month = d.da_mon;
						rec.year= d.da_year;
					}

					gotoxy(3,10);
					printf("OLD CONNECTION TYPE: %s",rec.connection);	//Old Connection type is displayed
					if(rec.connection==1)
					{
						gotoxy(24,10);
						printf("STAR");  //If option stored in record is '1' Then "STAR" will be displayed on screen.
					}
					else
					if(rec.connection==2)
					{
						gotoxy(24,10);
						printf("JAZZ");  //If option stored in record is '2' Then "JAZZ" will be displayed on screen.
					}
					gotoxy(3,12);
					printf("NEW CONNECTION TYPE: "); //New Connection Type is asked for Input.
					check_ct(&rec.connection);       //This check provides choices to the user to select b/w "STAR" or "JAZZ".

					fseek(fp, ftell(fp) - sizeof(rec),0);
					  fwrite(&rec, sizeof(rec), 1, fp);

					window(1,1,80,25);
					gotoxy(1,12);
					gotoxy(35,24);
					printf("RECORD SAVED !!!");

					getch();
				}
		fclose(fp);
}

/*******************END OF CHANGE CONNECTION TYPE FUNCTION*******************/



void c_ph()
{
	int ch;
	FILE *fp;
	char sno[NUM];
	clrscr();

	fp=fopen("customer.rec","rb+");

	gotoxy(20,13);
	printf("PLEASE ENTER SIM ID ==->>>> ");
	check_id(sno,NUM);

		while ( fread(&rec, sizeof(rec), 1, fp) && strcmp(sno,rec.id) );

			ch=strcmp(sno,rec.id);
				if(ch!=0)
				{
					clrscr();
					sound(500);delay(200);nosound();
					gotoxy(28,13);
					printf("<<--RECORD NOT FOUND-->>");
					getch();
				}
				else
				{
					clrscr();
					gotoxy(28,4);
					printf("<<<--==RECORD FOUND==-->>>");

					gotoxy(3,8);
					printf("OLD PHONE NUMBER: %s",rec.phone); //Old phone number is displayed.
					gotoxy(3,12);
					printf("ENTER NEW PHONE NUMBER: ");       //New phone number is asked by the user.
					check_phone(rec.phone,PH);

					fseek(fp, ftell(fp) - sizeof(rec),0);
					  fwrite(&rec, sizeof(rec), 1, fp);

					gotoxy(34,24);
					printf("RECORD SAVED !!!");

					getch();
				}
		fclose(fp);
}

/*********************END OF CHANGE PHONE NUMBER FUNCTION********************/


void del()
{
	int ch;
	FILE *fp;
	char sno[NUM];
	clrscr();

	fp=fopen("customer.rec","rb+");

	gotoxy(20,13);
	printf("PLEASE ENTER SIM ID ==->>>> ");
	check_id(sno,NUM);

		while ( fread(&rec, sizeof(rec), 1, fp) && strcmp(sno,rec.id) );

			ch=strcmp(sno,rec.id);
				if(ch!=0)
				{
					clrscr();
					sound(500);delay(200);nosound();
					gotoxy(28,13);
					printf("<<--RECORD NOT FOUND-->>");
					getch();
				}
				else     //Here the saved record is displayed.
				{
					clrscr();
					gotoxy(28,2);
					printf("<<==SEARCH SUCCESSFUL==>>");
					gotoxy(3,5);
					printf(" SIM ID: %s",rec.id);

					gotoxy(3,7);
					printf(" NAME: %s",rec.name);

					gotoxy(3,9);
					printf(" ADDRESS: %s",rec.address);

					gotoxy(3,11);
					printf(" PHONE Number: %s",rec.phone);

					gotoxy(3,13);
					printf(" CONNECTION TYPE: %s",rec.connection);
					if(rec.connection==1)
					{
						gotoxy(21,13);
						printf("STAR");
					}
					else
					if(rec.connection==2)
					{
						gotoxy(21,13);
						printf("JAZZ");
					}
					gotoxy(3,15);
					printf(" DATE Of PURCHASE: %d-%d-%d",rec.day,rec.month,rec.year);

					gotoxy(26,24);
					printf("PRESS ANY KEY TO DELETE RECORD.....");
					getch();
					empty(); //this is a Function which will erase the record in memory & NOT physically.

					fseek(fp, ftell(fp) - sizeof(rec), 0);
					  fwrite(&rec, sizeof(rec), 1, fp);

					clrscr();
					sound(500);delay(200);nosound();
					gotoxy(33,13);
					printf("RECORD DELETED !!!");
					getch();
				}

		fclose(fp);
}

/***************************END OF DELETE FUNCTION***************************/


void check_id(char *p, int size)
{
	int i=0;
	char ch;

	do
	{
		ch=getch();

		if( (ch>='0' && ch<='9') && (i<size-1) )
		{
			 *p=ch;      	  //The value is assigned to the pointer.
			 p++;        	  //Pointer is incremented.
			 i++;        	  //Length counter is incremented.
			 printf("%c",ch); //Validated character is printed.
		}
		else      //This block of commands controls backspace.
		if(ch==8 && i>0)
		{
			printf("%c%c%c",8,32,8);
			i--;              //Length counter is decremented.
			p--;              //Pointer is decremented.
		}

	}while(ch!=13 || i<size-1);       //this loop will continue till the total given length is reached or 'ENTER' is pressed.

	*p='\0';

}


void check_phone(char *ph, int size)
{
	int p=0;
	char s[20],ch;

	do
	{
		ch=getch();

		if( ((ch>='0' && ch<='9')||(ch=='-')) && (p<size-1) )
		{
			*ph=ch;
			 ph++;
			 p++;
			 printf("%c",ch);
		}

		else

		if( (ch==8)&&(p>0) )
		{
			printf("%c%c%c",8,32,8);
			p--;
			ph--;
		}

	}while(ch!=13 || p<size-1);

	s[p]='\0';
	*ph='\0';

}

void check_name(char *p, int size)
{
	int j=0;
	char x[40],cj;

	do
	{

		cj=toupper(getch());

		if(((cj>='a' && cj<='z')||(cj>='A' && cj<='Z')||(cj==' ')) && (j<size-1))
		{
			*p++=cj;
			j++;
			printf("%c",cj);
		}

		else

		if(cj==8 && j>0)
		{
			printf("%c%c%c",8,32,8);
			j--; p--;
		}

	}while(cj!=13);

	x[j]='\0';
	*p='\0';
}

void check_add(char *p, int size)
{
	int l=0;
	char a[50],ad;

	do
	{

		ad=toupper(getch());

		if(((ad>='a' && ad<='z')||(ad>='A' && ad<='Z')||(ad==' ')||(ad==',')||(ad=='.')||(ad>='0' && ad<='9')) && (l<size-1))
		{
			*p++=ad;
			l++;
			printf("%c",ad);
		}

		else

		if( (ad==8)&&(l>0) )
		{
			printf("%c%c%c",8,32,8);
			l--; p--;
		}

	}while(ad!=13);

	a[l]='\0';   *p='\0';
}
void check_ct(int *p)
{
	int ab=1;
	char ch;
	int aa;

	window(24,18,51,24);
	textbackground(BLACK);
	clrscr();

	window(25,19,50,23);
	textbackground(WHITE);
	textcolor(BLACK);
	clrscr();

	gotoxy(11,2);
	printf("STAR");
	gotoxy(11,4);
	printf("JAZZ");

	     do{
			ch = getch();

			if(ch==0)
			{
				ch = getch();

				if(ch==72)
				{
					ab=ab-1;
				}
			else
				if(ch==80)
				{
					ab=ab+1;
				}
			}

			if(ab<1)
			{
				ab=1;

			}
			else

			if(ab==1)
			{
				window(1,1,80,25);
				window(35,22,40,22);
				textbackground(WHITE);
				textcolor(BLACK);
				clrscr();
				printf("JAZZ");
				window(1,1,80,25);
				window(35,20,41,20);
				textcolor(RED);
				clrscr();
				printf("STAR");
				aa=1;
				window(1,1,80,25);
			}

			else

			if(ab==2)
			{
				window(1,1,80,25);
				window(35,20,41,20);
				textbackground(WHITE);
				textcolor(BLACK);
				clrscr();
				printf("STAR");
				window(1,1,80,25);
				window(35,22,40,22);
				textcolor(RED);
				clrscr();
				aa=2;
				printf("JAZZ");
				window(1,1,80,25);
			}

			if(ab>2)
			{
				ab=2;
			}
	     }while(ch != 13);

	if (aa==1)
	{
		gotoxy(24,12);
		printf("STAR");
		*p=1;
	}
	else

	if (aa==2)
	{
		gotoxy(24,12);
		printf("JAZZ");
		*p=2;
	}


	getch();
	window(24,18,51,24);
	textbackground(LIGHTRED);
	textcolor(LIGHTGRAY);
	clrscr();

}

void empty()
{
     strcpy(rec.id," ");
     strcpy(rec.name," ");
     strcpy(rec.address," ");
     strcpy(rec.phone," ");
     rec.connection=0;
     rec.day=0;
     rec.month=0;
     rec.year=0;
}


int duplicate(char idno[])
{
    FILE *fp;

    fp=fopen("customer.rec","rb");

    while(fread(&rec, sizeof(rec), 1, fp) && strcmp(rec.id, idno));
    fclose(fp);

    if(strcmp(rec.id, idno)==0)
       return 1;
    else
       return 0;
}


/*²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²
²****************************|  	      |*****************************²
²****************************| END OF PROJECT |*****************************²
²****************************|  	      |*****************************²
²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²*/

			    /* MUHAMMAD AWAIS RAZA */
