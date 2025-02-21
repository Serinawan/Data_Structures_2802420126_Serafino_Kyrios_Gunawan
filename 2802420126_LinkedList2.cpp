#include <stdio.h>
#include <stdlib.h>

struct tnode
{
	int x; // Value
	/*
	char name[10]; // Value strcpy(node->name, "hh")
	*/
	tnode *next; // Link Next
	tnode *prev; // Link Previous
}*head, *tail, *curr;

void push_front(int value)
{
	struct tnode *node = (tnode*) malloc(sizeof(tnode));
	node->x = value;
	
	if(head==NULL)
	{
		node->next = NULL;
		node->prev = NULL;
		head = tail = node;
	}
	else
	{
		node->next = head;
		head->prev = node;
		head = node;
		head->prev = NULL;
	}
}

void push_back(int value)
{
	struct tnode *node = (tnode*) malloc(sizeof(tnode));
	node->x = value;
	
	if(head==NULL)
	{
		node->next = NULL;
		node->prev = NULL;
		head = tail = node;
	}
	else
	{
		tail->next = node;
		node->prev = tail;
		tail = node;
		tail->next = NULL;
	}
}

void push_mid(int value, int search_key)
{
	struct tnode *node = (tnode*) malloc(sizeof(tnode));
	node->x = value;
	
	if(head==NULL)
	{
		node->next = NULL;
		node->prev = NULL;
		head = tail = node;
		return;
	}
	else
	{
		struct tnode *curr = head;
		while(curr!=NULL)
		{
			if(curr->x == search_key)
			{
				if(curr == tail)
				{
					push_back(value);
				}
				else
				{
					node->next = curr->next;
					node->prev = curr;
					curr->next->prev = node;
					curr->next = node;
				}
				break;
			}
			curr = curr->next;
		}
		if(curr==NULL)
		{
			printf("Data %d not found inh the Linked List.\n", search_key);
		}
	}
}

void delete_front()
{
	if(head==NULL)
	{
		printf("Data not found.\n");
	}
	else
	{
		if(head==tail)
		{
			free(head);
			head = tail = NULL;
		}
		else
		{
			struct tnode *del = head;
			head = head->next;
			head->prev = NULL;
			free(del);
		}
	}
}

void delete_back()
{
	if(tail==NULL)
	{
		printf("Data not found.\n");
	}
	else
	{
		if(head==tail)
		{
			free(head);
			head = tail = NULL;
		}
		else
		{
			struct tnode *del = tail;
			tail = tail->prev;
			if(tail)
				tail->next = NULL;
			free(del);
		}
	}
}

void delete_mid(int value, int search_key)
{
	struct tnode *node = (tnode*) malloc(sizeof(tnode));
	node->x = value;
	
	if(head==NULL)
	{
		printf("Data not found.\n");
		return;
	}
    struct tnode *curr = head;

    while (curr != NULL) 
    {
        if (curr->x == search_key) 
        {
            if (head == tail) 
            {
                free(curr);
                head = tail = NULL;
            }
            else if (curr == head) 
            {
                head = head->next;
                head->prev = NULL;
                free(curr);
            }
            else if (curr == tail) 
            {
                tail = tail->prev;
                tail->next = NULL;
                free(curr);
            }
            else 
            {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                free(curr);
            }
            return;
        }
        curr = curr->next;
    }
    printf("Data %d not found in the Linked List.\n", search_key);
}

void print_list()
{
/*
	if(head==NULL)
	{
		printf("List not found.\n");
		return;
	}
	
	struct tnode *curr = head;
	
	while(curr!=NULL)
	{
		printf("%d ", curr->x);
		curr = curr->next;
	}
*/
	curr = head;
	while(curr!=NULL)
	{
		printf("%d ", curr->x);	
		curr = curr->next;
	}
}

void print_reverse()
{
	curr = tail;
	while(curr!=NULL)
	{
		printf("%d ", curr->x);
		curr = curr->prev;
	}
}

/*
struct tnode *head
{
	
}
*/      
int main()
{
	printf("Doubly Linked List Ahh\n");
	push_front(34);
	push_front(47);
	push_front(3);
	push_front(4);
	push_front(7);
	print_list();
	printf("\n");
	print_reverse();
	getchar();
	return 0;
}
