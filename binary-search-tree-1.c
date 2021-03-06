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
		printf("\t[-----[이 명 국]  [2017038100]-----]\n");
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

int deleteLeafNode(Node* head, int key)			// head 노드부터 탐색하여 입력한 키와 같은 노드를 삭제하는 함수
{
	Node* parent, *p, *succ, *succ_parent;
	Node* child;
	parent = NULL;
	p = head->left;

	while((p != NULL)&&(p-> key != key )){		// 삭제할 노드의 위치 탐색
		parent = p;
		if(key < p->key)
			p = p->left;
		else p = p -> right;
	}
	if(p == NULL ){								// 삭제할 노드가 없을 경우
		printf("찾는 키가 없습니다");
		return 0;
	}

	if((p->left == NULL) && (p-> right == NULL)){	// 삭제한 노드가 leap 노드인 경우
		if(parent != NULL){
			if(parent -> left == p)
				parent->left = NULL;
			else parent -> right = NULL;
		}

		else head = NULL;
	}

	else if((p->left== NULL) || (p->right == NULL)){	// 삭제할 노드가 자식 노드를 한 개 가지고 있는 경우
		if(p->left != NULL)								// 삭제할 노드가 왼쪽 자식 노드를 가지고 있다면
			child = p -> left;							// 물려주기 위해 왼쪽 자식 노드에 child로 설정
		else child = p -> right;						// 물려주기 위해 오른쪽 자식 노드에 child로 설정

		if (parent != NULL){
			if (parent -> left == p)
				parent -> left = child;					// 삭제할 노드의 부모 노드와 자식 노드를 연결한다.
			else parent -> right = child;
		}
		else head = child;
	}

	else{												// 삭제할 노드가 자식 노드를 두 개 가지고 있는 경우
		succ_parent = p;
		succ = p -> left;
		while(succ->right != NULL){						// 왼쪽 서브 트리에서 오른쪽 링크로 이동
			succ_parent = succ;							// 가장 큰 노드를 찾아 succ로 지정한다.
			succ = succ -> right;
		}
		if(succ_parent -> left == succ)
			succ_parent -> left = succ -> left;			// succ의 왼쪽 노드를 부모 왼쪽 노드에 연결한다.
		else
		 succ_parent -> right = succ -> left;			// succ의 왼쪽 노드를 부모 오른쪽 노드에 연결한다.
		p->key = succ->key;								// succ의 값을 p 값으로 옮겨준다
		p = succ;
	}
	free(p);
}

Node* searchRecursive(Node* ptr, int key)			// 순환을 통한 입력한 키와 같은 노드의 주소 호출 함수
{
	if(ptr == NULL) return NULL;					// 찾고자하는 노드가 없을경우( ptr이 NULL 경우 NULL 출력)

	if(key == ptr->key) return ptr;					// 입력한 값을 찾았을 경우 ptr를 리턴한다

	if(key < ptr->key){								// 입력한 값이 ptr의 값보다 작을 경우 왼쪽 노드로 이동
		return searchRecursive(ptr->left,key);
	}	
	else{											// 입력한 값이 ptr의 값보다 작을 경우 오른쪽 노드로 이동
		return searchRecursive(ptr->right,key);
	}							
}

Node* searchIterative(Node* head, int key)			// 반복을 통한 입력한 키와 같은 노드의 주소 호출 함수
{
	Node* h;
	h = head->left;									// root 노드를 h로 지정
	while(h != NULL){
		if(key < h->key) h = h -> left;				// 입력한 키의 값이 h의 값보다 작을 경우 왼쪽 노드로 이동
		else if (key == h->key) return h;			// 키의 값이 같을 경우 h 리턴
		else h = h->right;							// 입력한 키의 값이 h의 값보다 클 경우 오른쪽 노드로 이동
	}
	return h;										// h 리턴
}


int freeBST(Node* head)
{
	Node* h;
	h = head -> left;
	free(h);				// 할당된 헤드노드 메모리 해제
}







