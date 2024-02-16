#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
	node* currentNode = head;
	int length = 0;

	//Otherwise, for each node add one to length
	while(currentNode != NULL)
	{
		length++;
		currentNode = currentNode->next;
	}

	//Return length
	return length;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{
	node* currentNode = head;
	int len = length(head);
	char* string = (char*)malloc((len+1) * sizeof(char));

	int i;
	for (i = 0; i < len; i++)
	{
		string[i] = currentNode->letter;
		currentNode = currentNode->next;
	}

	string[len] = '\0'; //Insert \0 at the end

	//Return string
	return string;
}

// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	node* newNode = (node*)malloc(sizeof(node));
	newNode->letter = c;
	newNode->next = NULL;
	node* currentNode = *pHead;

	//If the head is null, simply insert the new node there
	if(currentNode == NULL)
	{
		*pHead = newNode;
		return;
	}
	
	//Otherwise, find the last node
	while(currentNode->next != NULL)
	{
		//printf("in loop\n");
		currentNode = currentNode->next;
	}

	//Make the last node's next be the new node
	currentNode->next = newNode;
	return;
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
    if(*pHead == NULL)
    {
        return;
    }
    struct node* temp;
    //struct node* cur = pHead;

    while(*pHead != NULL)
    {
        temp = (*pHead)->next; //Save the next node's reference
		free(*pHead); //Free the node
		*pHead = NULL; //Set it to null because aparently free != NULL
		pHead = &temp; //Make pHead point to temp
    }

	return;
	
	/*
	node* toDestroy;
	node* currentNode = *pHead;

	//If the head is null, we're done!
	if(currentNode == NULL)
	{
		return;
	}
	
	//For every node in the list, destroy it and advance current node;
	while(currentNode != NULL)
	{
		toDestroy = currentNode;
		currentNode = currentNode->next;
		free(toDestroy);
	}

	*pHead = NULL; //Sets pHead to null

	return;
	*/
}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head == NULL)
		{
			printf("Based\n");
		}

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}