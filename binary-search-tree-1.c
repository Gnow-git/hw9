/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}
// ���� Ž�� Ʈ�� �ʱ�ȭ
int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}


void inorderTraversal(Node* ptr)	// ���� Ʈ�� ���� ��ȸ �Լ�
{
	if(ptr){
		inorderTraversal(ptr->left);	// ���� ����� �������� �̵��Ѵ�.
		printf("[%d]", ptr->key);		// ���� ��带 ����Ѵ�.
		inorderTraversal(ptr->right);	// ���� ����� ���������� �̵��Ѵ�.
	}
}

void preorderTraversal(Node* ptr)	// ���� Ʈ�� ����  ��ȸ �Լ�
{
	if(ptr){
		printf("[%d]", ptr->key);		// ���� ��带 ����Ѵ�.
		preorderTraversal(ptr->left);	// ���� ����� �������� �̵��Ѵ�.
		preorderTraversal(ptr->right);	// ���� ����� ���������� �̵��Ѵ�.
	}
}

void postorderTraversal(Node* ptr)	// ���� Ʈ�� ���� ��ȸ �Լ�
{
	if(ptr){
		postorderTraversal(ptr->left);	// ���� ����� �������� �̵��Ѵ�.
		postorderTraversal(ptr->right);	// ���� ����� ���������� �̵��Ѵ�.
		printf("[%d]",ptr->key);		// ���� ��带 ����Ѵ�.
	}
}


int insert(Node* head, int key)			// �Է��� ��� ���� �����ϴ� �Լ�
{
	Node* tempNode;						// �Է��� ���� ���� ��带 �����Ѵ�.
	tempNode =(Node*)malloc(sizeof(Node));
	Node *temp;
	temp = head->left;		    		// ù ����� ���� ���긦 ���� temp ��� ����
	tempNode ->left = NULL;				// ������ ����� ������ NULL�� �ʱ�ȭ
	tempNode ->right = NULL;			// ������ ����� �������� NULL�� �ʱ�ȭ
	tempNode -> key = key;				// ������ ����� data ���� �Է��� key�� ����

	if(head->left == NULL){				// ������ Ʈ���� ���ٸ�
	head ->left = tempNode;				// ������ ��带 ù ���� �Է��Ѵ�.
	}

	else{
		

			// ���ʰ� ������ ���갡 NULL�̰ų� �Է°��� ��� ���� ���������� �ݺ�
			while((temp -> left != NULL||temp->right !=NULL) && temp->key != key){
				if(temp -> key > key){		// �Է� ���� temp ����� �� ���� ���� ���
					if(temp->left == NULL)	// temp �����  ���� ���갡 NULL�� ��� Ż��
						break;		
					temp = temp->left;		// temp ����� ���� ����� �̵�
				}
				else						// �Է� ���� temp ����� �� ���� Ŭ ���
				{
					if(temp->right == NULL)	// temp �����  ������ ���갡 NULL�� ��� Ż��
						break;
					temp = temp ->right;	// temp ����� ������ ����� �̵�
				}
			}


		if(temp->key == key){
			printf("���� ���� ���� �� �����ϴ�.");
			return 1;		
		}
		// while Ż��� ����� �Լ�
		if(temp->key > key){		// �Է� ����  temp ����� ������ �������
			temp ->left = tempNode;	// �Է��� ���� temp ��� ���ʿ� �����Ѵ�.
		}
		else{						// �Է� ����  temp ����� ������ Ŭ���
			temp->right = tempNode;	// �Է��� ���� temp ��� �����ʿ� �����Ѵ�.
		}
	}
	return 0;

}

int deleteLeafNode(Node* head, int key)			// head ������ Ž���Ͽ� �Է��� Ű�� ���� ��带 �����ϴ� �Լ�
{
	Node* parent, *p, *succ, *succ_parent;
	Node* child;
	parent = NULL;
	p = head->left;

	while((p != NULL)&&(p-> key != key )){		// ������ ����� ��ġ Ž��
		parent = p;
		if(key < p->key)
			p = p->left;
		else p = p -> right;
	}
	if(p == NULL ){								// ������ ��尡 ���� ���
		printf("ã�� Ű�� �����ϴ�");
		return 0;
	}

	if((p->left == NULL) && (p-> right == NULL)){	// ������ ��尡 leap ����� ���
		if(parent != NULL){
			if(parent -> left == p)
				parent->left = NULL;
			else parent -> right = NULL;
		}

		else head = NULL;
	}

	else if((p->left== NULL) || (p->right == NULL)){	// ������ ��尡 �ڽ� ��带 �� �� ������ �ִ� ���
		if(p->left != NULL)								// ������ ��尡 ���� �ڽ� ��带 ������ �ִٸ�
			child = p -> left;							// �����ֱ� ���� ���� �ڽ� ��忡 child�� ����
		else child = p -> right;						// �����ֱ� ���� ������ �ڽ� ��忡 child�� ����

		if (parent != NULL){
			if (parent -> left == p)
				parent -> left = child;					// ������ ����� �θ� ���� �ڽ� ��带 �����Ѵ�.
			else parent -> right = child;
		}
		else head = child;
	}

	else{												// ������ ��尡 �ڽ� ��带 �� �� ������ �ִ� ���
		succ_parent = p;
		succ = p -> left;
		while(succ->right != NULL){						// ���� ���� Ʈ������ ������ ��ũ�� �̵�
			succ_parent = succ;							// ���� ū ��带 ã�� succ�� �����Ѵ�.
			succ = succ -> right;
		}
		if(succ_parent -> left == succ)
			succ_parent -> left = succ -> left;			// succ�� ���� ��带 �θ� ���� ��忡 �����Ѵ�.
		else
		 succ_parent -> right = succ -> left;			// succ�� ���� ��带 �θ� ������ ��忡 �����Ѵ�.
		p->key = succ->key;								// succ�� ���� p ������ �Ű��ش�
		p = succ;
	}
	free(p);
}

Node* searchRecursive(Node* ptr, int key)
{
	
}

Node* searchIterative(Node* head, int key)
{
	
}


int freeBST(Node* head)
{
	
}







