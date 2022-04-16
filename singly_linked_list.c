#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* link;      
} listNode;

typedef struct Head {       //��ó������ų ���
	struct Node* first;
}headNode;


headNode* initialize(headNode* h);      //�ʱ�ȭ
int freeList(headNode* h);

int insertFirst(headNode* h, int key);      /*ù��°�� key ����*/
int insertNode(headNode* h, int key);       /*key ����(���������ǵ���)*/
int insertLast(headNode* h, int key);       /*�������� key ����*/

int deleteFirst(headNode* h);               //ó��������
int deleteNode(headNode* h, int key);       //key������ ��� ����
int deleteLast(headNode* h);                //��������� ����
int invertList(headNode* h);                //��带 �Ųٷ�

void printList(headNode* h);            //����Ʈ���

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;
	printf("[----- [������] [2021041021] -----]\n");
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
		case 'z': case 'Z':     //z�� �ʱ�ȭ
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':     //p�� ����Ʈ���
			printList(headnode);
			break;
		case 'i': case 'I':     //i�� �Է¹����� ���������ǰ� �ֱ�
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':     //d�� key�ִ� ��� ����
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':     //n�� �Ǿտ� ����
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':     //e�� ������ ��� ����
			deleteLast(headnode);
			break;
		case 'f': case 'F':     //f�� �Ǿտ� key ����
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':     //t�� �Ǿ� ��� ����
			deleteFirst(headnode);
			break;
		case 'r': case 'R':     //r�� ����Ʈ �Ųٷ� �ϱ�
			invertList(headnode);
			break;
		case 'q': case 'Q':     //q�� �޸� ��ȯ�ϰ�
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');       //q�� ����

	return 1;
}

headNode* initialize(headNode* h) {

	if(h != NULL)       //��尡 ������� ������
		freeList(h);    //�޸� ��ȯ�ϰ�

	headNode* temp = (headNode*)malloc(sizeof(headNode));       //����� �޸��Ҵ�
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){

	listNode* p = h->first;     //p�� ù��° ��� �ְ�
	listNode* prev = NULL;     

	while(p != NULL) {          //��忡 ��������
		prev = p->link;         //������ prev�� �ְ�
        free(p);                //p�� ����Ű�� �޸� ��ȯ
		p = prev;                //p���� prev�� �ٽóֱ�
	}
	free(h);        //���޸𸮹�ȯ
	return 0;
}


int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)       //ù��°�����������
	{
		h->first = node;        //ù��°�� �ְ� ����
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = h->first;     //n�տ���

	while(n != NULL) {      //����Ʈ�������ݺ�
		if(n->key >= key) {     //�����ִ°��� key���� �Է¹��� key�� �۰ų�������
			if(n == h->first) {     //n�� ó���̸� ó���ſ� node�� �־�
				h->first = node;
				node->link = n;
			} else {                //ó���ƴϸ� n�տ��� ����
				node->link = n;
				trail->link = node;
			}
			return 0;       //���������� ����
		}

		trail = n;      //trail�� n�� �ְ�
		n = n->link;    //n�� ������ �ֱ�
	}

	trail->link = node;         //�Էµ� Ű�� �� ũ�� �ǵڿ� �ְ� ����
	return 0;
}

int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;        //Ű�ְ�
	node->link = NULL;

	if (h->first == NULL)       //ó����� ó���� �ְ� ����
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->link != NULL) {        //���������� ã�ư���
		n = n->link;
	}
	n->link = node;     //�����ϱ�
	return 0;
}

int insertFirst(headNode* h, int key) {
    
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;      //�����Ű� ����ó���̾����� ����Ű���ϰ�
	h->first = node;            //ù��°�� �Էµ�key���� ��带 ����Ű����

	return 0;
}

int deleteNode(headNode* h, int key) {

	if (h->first == NULL)       //����Ʈ ���������
	{
		printf("nothing to delete.\n");     //�����ҰԾ���
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	while(n != NULL) {
		if(n->key == key) {         //key���� ������ ã�Ƽ�
			if(n == h->first) {     //ó���Ÿ� �״����� ����Ű���ϰ�
				h->first = n->link;
			} else {
				trail->link = n->link;      //������ũ�� trail�� ����Ű�� ������
			}
			free(n);        //�޸𸮹�ȯ
			return 0;       //����
		}

		trail = n;      //���������� trail�� n �ְ�
		n = n->link;    //n�� ������ ����Ű��
	}
    //�ٵ��� ������ ���ٰ����
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

int deleteLast(headNode* h) {

	if (h->first == NULL)		//��������� �����ҰԾ���
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;	//ù��°��尡��Ű���ϰ�
	listNode* trail = NULL;

	if(n->link == NULL) {		//��� ������ ������(n�� �����������)
		h->first = NULL;		//first�� �ƹ��͵� �� ����Ű���ϰ�
		free(n);				//�޸𸮹�ȯ
		return 0;
	}

	while(n->link != NULL) {		//������ �ϰ͵� ���������� ��� ������ũ�� �̵�
		trail = n;
		n = n->link;
	}

	trail->link = NULL;		//�������
	free(n);				//�޸𸮹�ȯ

	return 0;
}

int deleteFirst(headNode* h) {

	if (h->first == NULL)		//����ž���
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;	

	h->first = n->link;//ù��°��ũ�� �״����� ����Ű���ϰ�
	free(n);			//�����ִ�ó���Ǹ޸𸮹�ȯ

	return 0;
}


int invertList(headNode* h) {


	if(h->first == NULL) {//��������� �������Ծ���
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;		
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle;		//trail�� middle��
		middle = n;			//middle�� n����
		n = n->link;		//n�� ������
		middle->link = trail;		//middle������ trail
	}

	h->first = middle;	//midle�� ù��°��

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

	while(p != NULL) {		//������ ���°������ key�� ���
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);		//��ִ������
}
