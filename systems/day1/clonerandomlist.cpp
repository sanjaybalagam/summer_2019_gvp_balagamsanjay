#include<stdio.h>
#include<iostream>
#include<functional>
#include<stdlib.h>

struct randomll{
	int data;
	struct randomll *next, *rand;
};

typedef randomll randomlist;

randomlist * create1(int i)
{
	randomlist *newlist;
	newlist = (randomlist *)malloc(sizeof(randomlist));
	newlist->data = i;
	newlist->next = NULL;
	newlist->rand = NULL;
	return newlist;
}

randomlist * createrandomlist()
{
	randomlist *temp[6];
	temp[0] = create1(1);
	temp[1] = create1(2);
	temp[2] = create1(3);
	temp[3] = create1(4);
	temp[4] = create1(5);
	temp[5] = create1(6);
	
	
	temp[0]->next = temp[1];
	temp[1]->next = temp[2];
	temp[2]->next = temp[3];
	temp[3]->next = temp[4];
	temp[4]->next = temp[5];
	temp[5]->next = NULL;

	temp[0]->rand = temp[2];
	temp[1]->rand = temp[4];
	temp[2]->rand = temp[5];
	temp[3]->rand = temp[4];
	temp[4]->rand = temp[4];
	temp[5]->rand = temp[4];
	return temp[0];
}	


/*
randomlist* clonehash(randomlist *list)
{


}*/


void printrandomlist(randomlist* list)
{
	while (list != NULL)
	{
		printf("%d  ", list->data);
		list = list->next;
	}
}

randomlist* clonenohash(randomlist* list)
{
	if (list == NULL)
		return NULL;
	
	randomlist *temp=list, *newlisthead, *temp2;
	
	temp2 = create1(temp->data);
	newlisthead =temp2;
	temp2->next = temp->next;
	temp->next = temp2;
	temp = temp2->next;
	while (temp != NULL)//inserting nodes in between
	{
		temp2 = create1(temp->data);
		temp2->next = temp->next;
		temp->next = temp2;
		temp = temp2->next;
	}
	temp = list;
	while (temp != NULL)
	{
		if (temp->rand == NULL)
			temp->next->rand = NULL;
		else
			temp->next->rand = temp->rand->next;
		temp = temp->next->next;
	}	
	temp = list;//starting
	temp2 = temp->next;
	while (temp!=NULL)
	{
		temp->next = temp2->next;
		temp = temp->next;
		if (temp!=NULL)
			temp2->next = temp->next;
		temp2 = temp2->next;
	}
	return newlisthead;
}


int main()
{
	
	randomlist *list = createrandomlist();
	


	printrandomlist(list);
	printf("\n\n\n");
	randomlist* cloned=clonenohash(list);
	printrandomlist(cloned);
	return 0;
}