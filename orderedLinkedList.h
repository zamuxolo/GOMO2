#ifndef H_orderedLinkedListType
#define H_orderedLinkedListType

#include <iostream>
#include <cassert>

#include "linkedList.h"

using namespace std;

template<class Type>
class orderedLinkedListType: public linkedListType<Type>
{
public:
   bool search(const Type& searchItem);
     //Function to determine whether searchItem is in the list.
     //Postcondition: Returns true if searchItem is found in
     //               the list; otherwise, it returns false

   void insertNode(const Type& newItem);
     //Function to insert newItem in the list.
     //Postcondition: first points to the new list and newItem is 
     //               inserted at the proper place in the list.

   void deleteNode(const Type& deleteItem);
     //Function to delete deleteItem from the list.
     //Postcondition: If found, the node containing deleteItem
     //               is deleted from the list; first points 
     //               to the first node of the new list.
     //               If deleteItem is not in the list, an 
     //               appropriate message is printed.
};



template<class Type>
bool orderedLinkedListType<Type>::search(const Type& searchItem)
{
    bool found;
    nodeType<Type> *current; //pointer to traverse the list
	
    found = false;    //initialize found to false
    current = first;  //start the search at the first node

    while(current != NULL && !found)
       if(current->info >= searchItem)
          found = true;
       else
          current = current->link;

      if(found)       
         found = (current->info == searchItem); //test for equality

    return found;
}//end search


template<class Type>
void orderedLinkedListType<Type>::insertNode(const Type& newItem)
{
	nodeType<Type> *current; //pointer to traverse the list
	nodeType<Type> *trailCurrent; //pointer just before current
	nodeType<Type> *newNode;  //pointer to create a node

	bool  found;

	newNode = new nodeType<Type>; //create the node
 	assert(newNode != NULL);

	newNode->info = newItem;   //store newitem in the node
	newNode->link = NULL;      //set the link field of the node 
	                           //to NULL

	if(first == NULL)  //Case 1	
	{	
	   first = newNode;
	   count++;
 	}
	else
	{
	   current = first;
	   found = false;

	   while(current != NULL && !found) //search the list
			if(current->info >= newItem)
				found = true;
     		else
			{
				trailCurrent = current;
				current = current->link;
			}
		  
	   if(current == first)  	//Case 2
	   {
			newNode->link = first;
			first = newNode;
 			count++;
	   }
	   else				//Case 3
	   {
			trailCurrent->link = newNode;
			newNode->link = current;
 			count++;
	   }
	}//end else
}//end insertNode

template<class Type>
void orderedLinkedListType<Type>::deleteNode
                                    (const Type& deleteItem)
{
	nodeType<Type> *current; //pointer to traverse the list
	nodeType<Type> *trailCurrent; //pointer just before current
	bool found;

	if(first == NULL) //Case 1
		cerr<<"Cannot delete from an empty list."<<endl;
	else
	{
		current = first;
		found = false;

		while(current != NULL && !found)  //search the list
			if(current->info >= deleteItem)
				found = true;
			else
			{
				trailCurrent = current;
				current = current->link;
			}
		
		if(current == NULL)   //Case 4
			cout<<"The item to be deleted is not in the list."
			    <<endl;
		else
 			if(current->info == deleteItem) //item to be deleted  
											//is in the list
			{
  				if(first == current) 		//Case 2
				{
					first = first->link;

					delete current;
				}
				else     				//Case 3
				{
					trailCurrent->link = current->link;
					delete current;
				}
 				count--;
			}
			else  					//Case 4
				cout<<"The item to be deleted is not in the list."
				    <<endl;
	}
} //end deleteNode

#endif