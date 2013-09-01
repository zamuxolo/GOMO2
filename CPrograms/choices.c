#include<stdlib.h>
#include<stdio.h>

char* menu[] = {
"a - Add new record",
"d - Delete record",
"q - quit",
NULL
};

int getChoice(char* greet, char *choices[]) {

int chosen = 0;
int selected;
char **option;

do {
printf("Choice: %s\n", greet);
option = choices;

while(*option) {
printf("%s\n", *option);
option++;
}
selected = getchar();
option = choices;
while(*option) {
if(selected == *option[0]) {
chosen = 1;
break;
}
option++;
}
if(!chosen) {
printf("Incorrect choice, select again\n");
}
} while(!chosen);
return selected;
}
int main()
{
int choice = 0;
do
{
choice = getChoice("Please select an action", menu);
printf("You have chosen: %c\n", choice);
} while(choice != 'q');
exit(0);
}
 


