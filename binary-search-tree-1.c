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
// 이진 탐색 트리 초기화
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


void inorderTraversal(Node* ptr)	// 이진 트리 중위 순회 함수
{
	if(ptr){
		inorderTraversal(ptr->left);	// 현재 노드의 왼쪽으로 이동한다.
		printf("[%d]", ptr->key);		// 현재 노드를 출력한다.
		inorderTraversal(ptr->right);	// 현재 노드의 오른쪽으로 이동한다.
	}
}

void preorderTraversal(Node* ptr)	// 이진 트리 전위  순회 함수
{
	if(ptr){
		printf("[%d]", ptr->key);		// 현재 노드를 출력한다.
		preorderTraversal(ptr->left);	// 현재 노드의 왼쪽으로 이동한다.
		preorderTraversal(ptr->right);	// 현재 노드의 오른쪽으로 이동한다.
	}
}

void postorderTraversal(Node* ptr)	// 이진 트리 후위 순회 함수
{
	if(ptr){
		postorderTraversal(ptr->left);	// 현재 노드의 왼쪽으로 이동한다.
		postorderTraversal(ptr->right);	// 현재 노드의 오른쪽으로 이동한다.
		printf("[%d]",ptr->key);		// 현재 노드를 출력한다.
	}
}


int insert(Node* head, int key)			// 입력한 노드 값을 삽입하는 함수
{
	Node* tempNode;						// 입력한 값을 받을 노드를 생성한다.
	tempNode =(Node*)malloc(sizeof(Node));
	Node *temp;
	temp = head->left;		    		// 첫 노드의 다음 서브를 위한 temp 노드 생성
	tempNode ->left = NULL;				// 생성한 노드의 왼쪽을 NULL로 초기화
	tempNode ->right = NULL;			// 생성한 노드의 오른쪽을 NULL로 초기화
	tempNode -> key = key;				// 생성한 노드의 data 값을 입력한 key로 설정

	if(head->left == NULL){				// 생성된 트리가 없다면
	head ->left = tempNode;				// 생성한 노드를 첫 노드로 입력한다.
	}

	else{
		

			// 왼쪽과 오른쪽 서브가 NULL이거나 입력값과 노드 값이 같을때까지 반복
			while((temp -> left != NULL||temp->right !=NULL) && temp->key != key){
				if(temp -> key > key){		// 입력 값이 temp 노드의 값 보다 작을 경우
					if(temp->left == NULL)	// temp 노드의  왼쪽 서브가 NULL일 경우 탈출
						break;		
					temp = temp->left;		// temp 노드의 왼쪽 서브로 이동
				}
				else						// 입력 값이 temp 노드의 값 보다 클 경우
				{
					if(temp->right == NULL)	// temp 노드의  오른쪽 서브가 NULL일 경우 탈출
						break;
					temp = temp ->right;	// temp 노드의 오른쪽 서브로 이동
				}
			}


		if(temp->key == key){
			printf("동일 값을 넣을 수 없습니다.");
			return 1;		
		}
		// while 탈출시 실행될 함수
		if(temp->key > key){		// 입력 값이  temp 노드의 값보다 작을경우
			temp ->left = tempNode;	// 입력한 값을 temp 노드 왼쪽에 삽입한다.
		}
		else{						// 입력 값이  temp 노드의 값보다 클경우
			temp->right = tempNode;	// 입력한 값을 temp 노드 오른쪽에 삽입한다.
		}
	}
	return 0;

}


int deleteLeafNode(Node* head, int key)
{

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





