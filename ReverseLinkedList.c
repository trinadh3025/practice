#include<stdio.h>
#include<stdlib.h>

//Node structure
struct Node{
	int data;
	struct Node* next;
};

//Function to reverse the Linked list
void reverseList(struct Node** head){
	struct Node* prev = NULL;
	struct Node* current = *head;
	struct Node* next = NULL;

	while(current != NULL){
		next = current->next; // store the next node
		current->next = prev; //Reverse the link
		prev = current; //Move prev ahead
		current = next;
	}

	*head = prev; //Update head
}

void append(struct Node** head, int new_data){
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	new_node->data = new_data;
	new_node->next = NULL;

	if(*head == NULL){
		*head = new_node;
		return;
	}

	struct Node* temp = *head;
	while(temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
}

void printList(struct Node* head){
	while(head->next != NULL){
		printf("%d -> ", head->data);
		head = head->next;
	}

	printf("%d -> ", head->data);
	printf("NULL\n");
}

int detectCycle(struct Node* head){
	struct Node* slow = head;
	struct Node* fast = head;

	while(fast != NULL && fast->next != NULL){
		slow = slow->next;
		fast = fast->next->next;

		if (slow == fast){
			return 1;
		}

	}

	return 0;
}

void free_list(struct Node* head){
	struct Node* temp;
	while(head->next != NULL){
		temp = head;
		head = head->next;
		free(temp);	
	}
	free(head);
}
int main(){

	struct Node* head = NULL;

	append(&head, 1);
	append(&head, 2);
	append(&head, 3);
	append(&head, 4);
	append(&head, 5);
	append(&head, 6);
	append(&head, 7);

	printf("Original: ");
	printList(head);
	reverseList(&head);
	printf("After reversal: ");
	printList(head);

	free_list(head);
	return 0;
}
