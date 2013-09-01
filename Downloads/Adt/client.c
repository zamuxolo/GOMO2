/**************************************
*  This Project Made By Carmit & Alon *
*				Class 103             *
**************************************/
#include <iostream>
#include <stdio.h>
#include "item.h"
#include "list.h"

int main()
{
	List *ptrList;
	int i,status;	
	Item Arr[] = {"Alon",35981612,
				  "Carmit", 40230260,
				  "Chendler",32156864,
				  "Monika", 24832115,
				  "Richel", 32684596};
	Item tmp = {"Fibi",12486468};	
	int arrLen = sizeof(Arr) / sizeof(Item);
	
	ptrList = createList();
	
	if (ptrList== NULL)
	{
		printf("Problem to allocate List (list manager)\n");
		exit(1);
	}
	
	/* all of the next lines check the functions */

	for (i = 0; i < arrLen; i++)
	{
		status = insertToHeadList(ptrList,&Arr[i]);
		if (status == SUCCESS)
		{
			printList(ptrList);
			puts("Press Enter To Continue");
			getchar();
		}
		else
		{
			printf("failed to insert to the list!!\n");
			exit(1);
		}
	}
	
	status=insertToTailList(ptrList,&tmp);
	if(status==SUCCESS)
	{
		printList(ptrList);
		puts("Press Enter To Continue");
		getchar();
	}

	tmp=removeFirst(ptrList);
	PRINT_ITEM(tmp);
	puts("Press Enter To Continue");
	getchar();

	tmp=GetFirstItem(ptrList);
	PRINT_ITEM(tmp);
	puts("Press Enter To Continue");
	getchar();

	tmp=removeLast(ptrList);
	PRINT_ITEM(tmp);
	puts("Press Enter To Continue");
	getchar();

	tmp=GetLastItem(ptrList);
	PRINT_ITEM(tmp);
	puts("Press Enter To Continue");
	getchar();

	tmp.id=40230260;
	tmp=getItemByKey(ptrList,&tmp);
	PRINT_ITEM(tmp);
	puts("Press Enter To Continue");
	getchar();

	tmp.id=35981612;
	tmp=delRecByKey(ptrList,&tmp);
	PRINT_ITEM(tmp);
	puts("Press Enter To Continue");
	getchar();
	printList(ptrList);
	puts("Press Enter To Continue");
	getchar();

	tmp.id=40230260;
	status = RemoveRecByKey(ptrList,&tmp);
	if(status==SUCCESS)
	{
		printList(ptrList);
		puts("Press Enter To Continue");
		getchar();
	}

	/* free all the list and manger */
	destroyList(ptrList);
	shutDown(ptrList);
	ptrList=NULL;
}

