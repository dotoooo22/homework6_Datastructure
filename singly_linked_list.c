#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* link;      
} listNode;

typedef struct Head {       //젤처음가리킬 헤드
	struct Node* first;
}headNode;


headNode* initialize(headNode* h);      //초기화
int freeList(headNode* h);

int insertFirst(headNode* h, int key);      /*첫번째에 key 삽입*/
int insertNode(headNode* h, int key);       /*key 삽입(오름차순되도록)*/
int insertLast(headNode* h, int key);       /*마지막에 key 삽입*/

int deleteFirst(headNode* h);               //처음노드삭제
int deleteNode(headNode* h, int key);       //key저장한 노드 삭제
int deleteLast(headNode* h);                //마지막노드 삭제
int invertList(headNode* h);                //노드를 거꾸로

void printList(headNode* h);            //리스트출력

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	printf("[----- [곽민정] [2021041021] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':     //z는 초기화
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':     //p는 리스트출력
			printList(headnode);
			break;
		case 'i': case 'I':     //i는 입력받은거 오름차순되게 넣기
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':     //d는 key있는 노드 삭제
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':     //n은 맨앞에 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':     //e는 마지막 노드 삭제
			deleteLast(headnode);
			break;
		case 'f': case 'F':     //f는 맨앞에 key 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':     //t는 맨앞 노드 삭제
			deleteFirst(headnode);
			break;
		case 'r': case 'R':     //r은 리스트 거꾸로 하기
			invertList(headnode);
			break;
		case 'q': case 'Q':     //q는 메모리 반환하고
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');       //q면 종료

	return 1;
}

headNode* initialize(headNode* h) {

	if(h != NULL)       //헤드가 비어있지 않으면
		freeList(h);    //메모리 반환하고

	headNode* temp = (headNode*)malloc(sizeof(headNode));       //헤드노드 메모리할당
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){

	listNode* p = h->first;     //p에 첫번째 노드 넣고
	listNode* prev = NULL;     

	while(p != NULL) {          //노드에 뭐있으면
		prev = p->link;         //다음걸 prev에 넣고
        free(p);                //p가 가리키는 메모리 반환
		p = prev;                //p에는 prev를 다시넣기
	}
	free(h);        //헤드메모리반환
	return 0;
}


int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)       //첫번째노드비어있으면
	{
		h->first = node;        //첫번째에 넣고 리턴
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = h->first;     //n앞에거

	while(n != NULL) {      //리스트끝까지반복
		if(n->key >= key) {     //지금있는곳의 key보다 입력받은 key가 작거나같으면
			if(n == h->first) {     //n이 처음이면 처음거에 node를 넣어
				h->first = node;
				node->link = n;
			} else {                //처음아니면 n앞에다 삽입
				node->link = n;
				trail->link = node;
			}
			return 0;       //삽입했으면 리턴
		}

		trail = n;      //trail에 n을 넣고
		n = n->link;    //n은 다음걸 넣기
	}

	trail->link = node;         //입력된 키가 젤 크면 맨뒤에 넣고 리턴
	return 0;
}

int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;        //키넣고
	node->link = NULL;

	if (h->first == NULL)       //처음비면 처음에 넣고 리턴
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->link != NULL) {        //마지막까지 찾아가서
		n = n->link;
	}
	n->link = node;     //연결하기
	return 0;
}

int insertFirst(headNode* h, int key) {
    
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;      //다음거가 원래처음이었던걸 가리키게하고
	h->first = node;            //첫번째가 입력된key가진 노드를 가리키게함

	return 0;
}

int deleteNode(headNode* h, int key) {

	if (h->first == NULL)       //리스트 비어잇으면
	{
		printf("nothing to delete.\n");     //삭제할게없음
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	while(n != NULL) {
		if(n->key == key) {         //key값과 같은걸 찾아서
			if(n == h->first) {     //처음거면 그다음걸 가리키게하고
				h->first = n->link;
			} else {
				trail->link = n->link;      //다음링크를 trail이 가리키게 연결함
			}
			free(n);        //메모리반환
			return 0;       //리턴
		}

		trail = n;      //같지않으면 trail에 n 넣고
		n = n->link;    //n은 다음걸 가리키게
	}
    //다돌고 없으면 없다고출력
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

int deleteLast(headNode* h) {

	if (h->first == NULL)		//비어있으면 삭제할게없음
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;	//첫번째노드가리키게하고
	listNode* trail = NULL;

	if(n->link == NULL) {		//노드 다음거 없으면(n이 마지막노드임)
		h->first = NULL;		//first가 아무것도 안 가리키게하고
		free(n);				//메모리반환
		return 0;
	}

	while(n->link != NULL) {		//다음에 암것도 없을때까지 계속 다음링크로 이동
		trail = n;
		n = n->link;
	}

	trail->link = NULL;		//연결끊고
	free(n);				//메모리반환

	return 0;
}

int deleteFirst(headNode* h) {

	if (h->first == NULL)		//지울거없음
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;	

	h->first = n->link;//첫번째링크에 그다음걸 가리키게하고
	free(n);			//원래있던처음건메모리반환

	return 0;
}


int invertList(headNode* h) {


	if(h->first == NULL) {//비어잇으면 뒤집을게없음
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;		
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle;		//trail을 middle로
		middle = n;			//middle을 n으로
		n = n->link;		//n은 다음거
		middle->link = trail;		//middle다음에 trail
	}

	h->first = middle;	//midle을 첫번째로

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {		//끝까지 몇번째인지랑 key값 출력
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);		//몇개있는지출력
}
