//Program to test various operations on an ordered linked list

#include <iostream> 
#include "orderedLinkedList.h"

using namespace std;

int main()
{
     orderedLinkedListType<int> list1, list2;	//Line 1
     int num;									//Line 2

     cout<<"Line 3: Enter integers ending with -999"
         <<endl;								//Line 3
     cin>>num;									//Line 4

     while(num != -999)							//Line 5
     {
		list1.insertNode(num);					//Line 6
		cin>>num;								//Line 7
     }

     cout<<endl;								//Line 8

     cout<<"Line 9: List 1: "<<list1<<endl;		//Line 9

     list2 = list1; //test the assignment operator; Line 10

     cout<<"Line 11: List 2: "<<list2<<endl;	//Line 11

     cout<<"Line 12: Enter the number to be "
         <<"deleted: ";							//Line 12
     cin>>num;									//Line 13
     cout<<endl;	                            //Line 14

     list2.deleteNode(num);						//Line 15

     cout<<"Line 16: After deleting the node, "
         <<"List 2: "<<endl<<list2
         <<endl;								//Line 16

     return 0;					
}





