
#include "list.h"
#include "item.h"

typedef struct Node_s
{
	Item data;			/*Struct For Node (item & next item)*/
	struct Node_s *next;
}Node;

struct Manger_s /*THE MANGER*/
{
	Node * start;
	Node * end;
	int num;
};


/*Creates a new 'list manager'
, initializes it, and returns its address */
List * createList(void)
{
	List *ptrNewList;

	ptrNewList = (List *)malloc(sizeof(List));
	if (ptrNewList)
	{
		ptrNewList->start = NULL;
		ptrNewList->end = NULL;
		ptrNewList->num = 0;
	}
	return ptrNewList;
}

/* Check if List Got No Elements */
int ListIsEmpty(List * ptrList)
{
	if (ptrList->start)
		return FAILURE;

	return SUCCESS;
}


/* inserts one record at the head of the list */
int insertToHeadList(List *ptrList, Item *item)
{
	Node *ptrNewNode;
	
	if(!ptrList)
	{
		NO_LIST;
		return FAILURE;
	}

	ptrNewNode = (Node *)malloc(sizeof(Node));
	if (ptrNewNode)
	{
		ptrNewNode->data = *item;
		ptrNewNode->next = ptrList->start;
		ptrList->start = ptrNewNode;
		ptrList->num++;
		if(!ptrList->start->next)
			ptrList->end=ptrNewNode;
		return SUCCESS;
	}	
	return FAILURE;
}


/* inserts one record at the tail of the list */
int insertToTailList(List *ptrList, Item *item)
{
	Node *ptrNewNode;
	
	if(!ptrList)
	{
		NO_LIST;
		return FAILURE;
	}
	
	ptrNewNode = (Node *)malloc(sizeof(Node));

	if (ptrNewNode)
	{
		ptrNewNode->data = *item;
		ptrNewNode->next = NULL;
		ptrList->end->next = ptrNewNode;
		ptrList->end=ptrNewNode;
		ptrList->num++;
		return SUCCESS;
	}
	return FAILURE;
}

/* removes the first node from the list and returns its data */
Item removeFirst(List *ptrList)
{
	Node * ptrDel;
	Item tmp={"No Item"};
	
	if(!ptrList)
	{
		NO_LIST;
		return tmp;
	}

	if(ListIsEmpty(ptrList))
	{
		LIST_IS_EMPTY;
		return tmp;
	}
	
	if(ptrList->start == ptrList->end)
		ptrList->end=NULL;
	
	ptrDel = ptrList->start;
	ptrList->start = ptrDel->next;
	ptrList->num--;
	tmp = ptrDel->data;
	free(ptrDel);
	return tmp;
}



/* get first item from list */
Item GetFirstItem(List *ptrList)
{
	if(!ptrList)
	{
		Item tmp={"No Item"};
		NO_LIST;
		return tmp;
	}

	if(ListIsEmpty(ptrList))
	{
		Item tmp={"No Item"};
		LIST_IS_EMPTY;
		return tmp;
	}
	
	return ptrList->start->data;
}


/* Remove Last Item From The List */
Item removeLast(List *ptrList)
{
	Node *tmpNode;
	Item tmp={"No Item"};
	
	if(!ptrList)
	{
		NO_LIST;
		return tmp;
	}

	if(ListIsEmpty(ptrList))
	{
		Item tmp={"No Item"};
		LIST_IS_EMPTY;
		return tmp;
	}
	
	tmpNode=ptrList->start;

	if(!tmpNode->next)
	{
		tmp=removeFirst(ptrList);
		return tmp;
	}

	while(tmpNode->next->next)
		tmpNode=tmpNode->next;
	
	ptrList->end = tmpNode;
	tmp=tmpNode->next->data;
	free(tmpNode->next);
	tmpNode->next=NULL;
	ptrList->num--;
	
	return tmp;
}



/* get last item from list */
Item GetLastItem(List *ptrList)
{
	if(!ptrList)
	{
		Item tmp={"No Item"};
		NO_LIST;
		return tmp;
	}

	if(ListIsEmpty(ptrList))
	{
		Item tmp={"No Item"};
		LIST_IS_EMPTY;
		return tmp;
	}

	return ptrList->end->data;
}



/* gets the data of the recNum-th node by key */
Item getItemByKey(List *ptrList,Item *item)
{
	Node *ptrNode;
	Item tmp={"No Item"};

	if(!ptrList)
	{
		NO_LIST;
		return tmp;
	}

	if(ListIsEmpty(ptrList))
	{
		LIST_IS_EMPTY;
		return tmp;
	}

	ptrNode = ptrList->start;

	while (ptrNode)
	{
		if(COMPARE(ptrNode->data,*item))  /*this macro return TRUE if equal*/
			return ptrNode->data;

		ptrNode = ptrNode->next;
	}
	return tmp;
}


/* free "list manager" */
void shutDown(List *pList)
{
	if (pList != NULL)
		free(pList);
}



/*This Func Del an Existing User By Key*/
Item delRecByKey(List *ptrList,Item *ptritem)
{
	Node *tmpitem,*deleteNode;
	Item tmp={"No Item"};

	if(!ptrList)
	{
		NO_LIST;
		return tmp;
	}

	if(ListIsEmpty(ptrList))
	{
		Item tmp={"No Item"};
		LIST_IS_EMPTY;
		return tmp;
	}

	tmpitem=ptrList->start;

	if(COMPARE(*ptritem,tmpitem->data))
	{/*in case that the 1st is to delete*/
		tmp=removeFirst(ptrList);
		return tmp;
	}

	while(tmpitem->next)
	{
		if(COMPARE(tmpitem->next->data,*ptritem))
		{
			if (tmpitem->next == ptrList->end)
				ptrList->end = tmpitem;
			tmp=tmpitem->next->data;
			deleteNode=tmpitem->next;
			tmpitem->next=tmpitem->next->next;
			free(deleteNode);
			ptrList->num--;
			return tmp;
		}
		tmpitem=tmpitem->next;
	}
	
	return tmp;
}


/*This Func Remove an Existing User By Key*/
int RemoveRecByKey(List *ptrList,Item *ptritem)
{
	Node *tmpitem,*deleteNode;
	Item tmp;
	
	if(!ptrList)
	{
		NO_LIST;
		return FAILURE;
	}

	if(ListIsEmpty(ptrList))
	{
		LIST_IS_EMPTY;
		return FAILURE;
	}
	
	tmpitem=ptrList->start;

	if(COMPARE(*ptritem,tmpitem->data))
	{/*in case that the 1st is to delete*/
		tmp=removeFirst(ptrList);
		return SUCCESS;
	}

	while(tmpitem->next)
	{
		if(COMPARE(tmpitem->next->data,*ptritem))
		{
			if (tmpitem->next == ptrList->end)
				ptrList->end = tmpitem;
			tmp=tmpitem->next->data;
			deleteNode=tmpitem->next;
			tmpitem->next=tmpitem->next->next;
			free(deleteNode);
			ptrList->num--;
			return SUCCESS;
		}
		tmpitem=tmpitem->next;
	}
	
	return FAILURE;
}


//free all nodes (dynamic allocatin)
void destroyList(List *ptrList)
{
	Node *ptrDel;

	if (ptrList != NULL)
	{
		ptrDel = ptrList->start;
		while (ptrDel)
		{
			ptrList->start = ptrDel->next;
			free(ptrDel);
			ptrDel = ptrList->start;
		}
	}
}


/* This Func Prints All Of The List */
void printList(List *ptrList)
{
	Node *tmpList;

	if(!ptrList)
	{
		NO_LIST;
		return;
	}

	tmpList=ptrList->start;

	if(ListIsEmpty(ptrList))
		LIST_IS_EMPTY;

	while(tmpList)
	{
		PRINT_ITEM(tmpList->data);
		tmpList=tmpList->next;
	}
}
