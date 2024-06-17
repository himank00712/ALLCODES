/*#include<stdio.h>
void main()
{
	int a=1,b,c,d=1;
	scanf("%d",&b);

	for(c=0;c<b;c++)
	{
	  printf("%d ",d);
	  d=d+a;
	  a++;
	}
}*/
/*#include <stdio.h>
#include <stdlib.h>
#define maxsize 1000
int queue[maxsize];
int front = -1,rear = -1;
int isfull()
{
	return rear == maxsize-1;
}
int isempty()
{
	return front == -1;
}
void Enqueue(value)
{
	if(isfull())printf("\nQueue Overflow\n");
	else
	{
		queue[++rear] = value;
		if(front==-1)
		front=rear;
		printf("\n%d is added in queue !!!!\n",value);
	}
}
int Dequeue()
{
	if(isempty()||front>rear)printf("\nQueue underflow\n");
	else
	{
		int value = queue[front++];
		if(front>rear)
		front=rear=-1;
		return value;
	}
}
void peek()
{
	if(isempty()||front>rear)
	printf("\nQueue is Empty!!!!\n");
	else {
	int value1;
	value1 = queue[front];
	if(value1>0)
	printf("\nValue in the queue is :- %d\n",value1);
	}
}
void display(){
	int i;
	if(isempty())
	printf("\nQueue is Empty !!!!\n");
	else {
		for(i=front;i<=rear;i++)
		printf("%d\t",queue[i]);
	}
	printf("\n");
}
void main()
{
	Enqueue(10);
	Enqueue(20);
	Enqueue(30);
	Enqueue(40);
	Enqueue(50);
	display();
	printf("\nDequeued item: %d\n",Dequeue());
	printf("\nDequeued item: %d\n",Dequeue());
	display();
	Enqueue(60);
	Enqueue(70);
	display();

}*/
/*
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char operators[128], operands[128];
int top1 = -1, top2 = -1;

int precedence(char c)
{
	 if (c == '*' || c == '/') return 3;
	 if (c == '+' || c == '-') return 1;
	 return -1;
}

char *InfixToPostfix(char *exp)
{
	 int len = strlen(exp);
	 char *res = (char *)malloc(len + 1);
	 int ri = 0;

	 for (int i = 0; i < len; i++) {
			 char c = exp[i];
			 if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
					 res[ri++] = c;

			 } else if (c == '(') {
					 operators[++top1] = c;
			 } else if (c == ')') {
					 while (top1 != -1 && operators[top1] != '(') {
							 res[ri++] = operators[top1--];
					 }
					 top1--;
			 } else {
					 while (top1 != -1 && (precedence(c) <= precedence(operators[top1]))) {
							 res[ri++] = operators[top1--];
					 }
					 operators[++top1] = c;
			 }
	 }
	 while (top1 != -1) { res[ri++] = operators[top1--]; }
	 res[ri] = '\0';
	 return res;
}

char *PostFixToInfix(char *exp)
{
	 int len = strlen(exp);
	 char *res = (char *)malloc(len + 1);
	 char tmp[128][128] = { 0 };
	 int ti = -1;

	 for (int i = 0; i < len; i++) {
			 char c = exp[i];
			 if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
					 ti++;
					 tmp[ti][0] = c;
					 tmp[ti][1] = '\0';
			 } else {
					 char op2[128];
					 strcpy(op2, tmp[ti--]);
					 char op1[128];
					 strcpy(op1, tmp[ti--]);
					 sprintf(tmp[++ti], "(%s%c%s)", op1, c, op2);
			 }
	 }
	 strcpy(res, tmp[0]);
	 return res;
}

char *InfixToPrefix(char *exp)
{
	 int len = strlen(exp);
	 char *res = (char *)malloc(len + 1);
	 int ri = 0;
	 for (int i = 0; i < len / 2; i++) {
			 char tmp = exp[i];
			 exp[i] = exp[len - i - 1];
			 exp[len - i - 1] = tmp;
	 }
	 for (int i = 0; i < len; i++) {
			 if (exp[i] == '(')
					 exp[i] = ')';
			 else if (exp[i] == ')')
					 exp[i] = '(';
	 }

	 char *postfix = InfixToPostfix(exp);
	 for (int i = 0; i < len / 2; i++) {
			 char tmp = postfix[i];
			 postfix[i] = postfix[len - i - 1];
			 postfix[len - i - 1] = tmp;
	 }
	 for (int i = 0; i < len; i++) {
			 if (postfix[i] == '(')
					 postfix[i] = ')';
			 else if (postfix[i] == ')')
					 postfix[i] = '(';
	 }
	 strcpy(res, postfix);
	 free(postfix);
	 return res;
}

char *PrefixToInfix(char *exp)
{
	 int len = strlen(exp);
	 char *res = (char *)malloc(len + 1);
	 char tmp[128][128] = { 0 };
	 int ti = -1;

	 for (int i = len - 1; i >= 0; i--) {
			 char c = exp[i];
			 if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
					 ti++;
					 tmp[ti][0] = c;
					 tmp[ti][1] = '\0';
			 } else {
					 char op1[128];
					 strcpy(op1, tmp[ti--]);
					 char op2[128];
					 strcpy(op2, tmp[ti--]);
					 sprintf(tmp[++ti], "(%s%c%s)", op1, c, op2);
			 }
	 }

	 strcpy(res, tmp[0]);
	 return res;
}

int main()
{
	 char buffer[101];

	 printf("Enter Infix expression: ");
	 scanf("\n%[^\n]100s", buffer);

	 char *res = InfixToPostfix(buffer);
	 printf("Postfix: %s\n", res);
	 free(res);

	 res = InfixToPrefix(buffer);
	 printf("Prefix: %s\n", res);
	 free(res);

	 printf("Enter Postfix Expression: ");
	 scanf("\n%[^\n]100s", buffer);

	 res = PostFixToInfix(buffer);
	 printf("Infix: %s\n", res);
	 free(res);

	 printf("Enter Prefix Expression: ");
	 scanf("\n%[^\n]100s", buffer);

	 res = PrefixToInfix(buffer);
	 printf("Infix: %s\n", res);
	 free(res);
	 return 0;
}
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
 int te,d=0;
 scanf("%d",&te);
 char a[1000],b[1000],c;
for( int i=0;i<te;i++)
{
 fgets(c,sizeof(c),stdin);
 a[d++]=c;
 printf("%s",a[d--]);
}

 return 0;
}
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main()
{

	int c, d, e = 0, g, h, l = 0,j;
	scanf("%d", &d);
	getchar();
	for (l = 0; l < d; l++)
	{
		char a[1000], b[100], k;
		fgets(a, sizeof(a), stdin);
		c = strlen(a);

		for ( j = 0; j < c; j++)
		{
			if (j % 2 == 1)
			{
				printf("%c", a[j]);
			}
		}
		printf(" ");
		for (int f = 0; f < c; f++)
		{
			if (f % 2 == 0)
			{
				printf("%c", a[f]);
			}
		}
		printf("\n");
	}
	return 0;
}
/*#include <stdio.h>
#include <string.h>

int main()
{
	int num_cases;
	scanf("%d", &num_cases);

	for (int i = 0; i < num_cases; i++)
	{
		char string[10001]; // Maximum length of string
		scanf("%s", string);

		int len = strlen(string);

		// Print even-indexed characters
		for (int j = 0; j < len; j += 2)
		{
			printf("%c", string[j]);
		}
		printf(" ");

		// Print odd-indexed characters
		for (int j = 1; j < len; j += 2)
		{
			printf("%c", string[j]);
		}
		printf("\n");
	}

	return 0;
}
#include<stdio.h>
void main()
{
	printf("%d",printf("tima"));
	printf("\n%f",9/5);

}
#include <stdio.h>
#include <stdlib.h>
struct Node
{
	int data;
	struct Node *next;
};
struct Node *head = NULL;
struct Node *createnode()
{
	struct Node *node = (struct Node *)malloc(sizeof(struct Node));
	printf("Enter data : ");
	scanf("%d", &node->data);
	node->next = NULL;
	return node;
}
void insertNodeInBeg()
{
	struct Node *newnode = createnode();
	if (head == NULL)
		head = newnode;
	else
	{
		newnode->next = head;
		head = newnode;
	}
}
void insertNodeInEnd()
{
	struct Node *newnode = createnode();
	if (head == NULL)
		head = newnode;
	else
	{
		struct Node *temp = head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newnode;
	}
}
void insertNodeAtPosition()
{
	if (head == NULL)
	{
		printf("Invalid Postion !!!!\n");
	}
	else
	{
		int pos, cnt = 1;
		printf("Enter Postion : ");
		scanf("%d", &pos);
		if (pos == 1)
		{
			struct Node *newnode = createnode();
			newnode->next = head;
			head = newnode;
		}
		else
		{
			struct Node *temp = head;
			while (temp->next != NULL)
			{
				if (cnt == pos - 1)
				{
					break;
				}
				cnt++;
				temp = temp->next;
			}
			if (temp->next == NULL)
			{
				printf("Invalid Postion !!!!\n");
			}
			else
			{
				struct Node *newnode = createnode();
				newnode->next = temp->next;
				temp->next = newnode;
			}
		}
	}
}
void deleteNodeAtPosition()
{
	if (head == NULL)
	{
		printf("\nInvalid Postion\n");
		return;
	}
	else
	{
		int pos, cnt = 1;
		printf("Enter Postion : ");
		scanf("%d", &pos);
		if (pos == 1)
		{
			head = head->next;
		}
		else
		{
			struct Node *temp = head;
			while (temp->next != NULL)
			{
				if (cnt == pos - 1)
				{
					break;
				}
				cnt++;
				temp = temp->next;
			}

			if (temp->next == NULL)
			{
				printf("\nInvalid Postion !!!!\n");
			}
			else
			{
				temp->next = temp->next->next;
			}
		}
	}
}
void createlist()
{
	int n, i;
	printf("Enter number of nodes :- ");
	scanf("%d", &n);
	struct Node *temp = NULL;
	for (i = 0; i < n; i++)
	{
		struct Node *newNode = createnode();
		if (head == NULL)
			head = newNode;
		else
			temp->next = newNode;
		temp = newNode;
	}
}

int searchNode(int value)
{
	struct Node *current = head;
	while (current != NULL)
	{
		if (current->data == value)
		{
			return 1;
		}
		current = current->next;
	}
	return 0;
}
void displaylist()
{
	system("clear");
	if (head == NULL)
		printf("\nList is Empty\n");
	else
	{
		struct Node *temp = head;
		printf("\nList elements :- ");
		while (temp != NULL)
		{
			printf("%d ", temp->data);
			temp = temp->next;
		}
	}
	printf("\n");
}
int main()
{
	system("clear");
	createlist();
	while (1)
	{
		printf("\n");
		printf("\n1. Insert Node In Begining\n");
		printf("\n2. Insert Node In End\n");
		printf("\n3. Insert Node At Any Position\n");
		printf("\n4. Delete Node From Given Position\n");
		printf("\n5. Search Node In List\n");
		printf("\n6. Display List\n");
		printf("\n7. Exit\n");
		int choice;
		printf("\nEnter your choice : \n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			insertNodeInBeg();
			break;
		case 2:
			insertNodeInEnd();
			break;
		case 3:
			insertNodeAtPosition();
			break;
		case 4:
			deleteNodeAtPosition();
			break;
		case 5:
			int val;
			printf("Enter the value : ");
			scanf("%d", &val);
			if (searchNode(val))
				printf("\nFOUNDED\n");
			else
				printf("\nNOT FOUNDED\n");
			break;
		case 6:
			displaylist();
			break;
		case 7:
			exit(0);
			break;
		}
	}
	printf("\n");
	return 0;
}*/
/*#include<stdio.h>
void main()
{
	int a[1000],b,c,d,e,f,g;
	printf("enter the size of array:");
	scanf("%d",&b);
	for(c=0;c<b;c++)
	{
		scanf("%d",&a[c]);
	}

	for(c=1;c<=b;c++)
	{
		for(d=0;d<b;d++)
		{
			if(a[d]>a[d+1])
			{
				g=a[d];
				a[d]=a[d+1];
				a[d+1]=g;

			}
		}
	}
	printf("sorted elements are:");
	for(c=0;c<b;c++)
	{
		printf("%d\n",a[c]);
	}

}*/
// WAP to check if a given expression is correctly parenthesized using stacks
// 3rd manual program
/*#include <stdio.h>
#include <string.h>
#define max 15
char stack[max];
int top = -1, i;
void push(char);
char pop();
void display();
int main()
{
	char expression[max], temp;
	display();
	int count = 1;
	printf("\n Enter an expression..\n");
	scanf("%s", &expression);
	for (i = 0; i < strlen(expression); i++)
	{
		if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[')
		{
			push(expression[i]);
		}
		if (expression[i] == ')' || expression[i] == '}' || expression[i] == ']')
		{
			if (top == -1)
			{
				count = 0;
			}
			else
			{
				temp = pop();
				if (expression[i] == ')' && (temp == '{' || temp == '['))
				{
					count = 0;
				}
				if (expression[i] == '}' && (temp == '(' || temp == '['))
				{
					count = 0;
				}
				if (expression[i] == ']' && (temp == '(' || temp == '{'))
				{
					count = 0;
				}
			}
		}
	}
	if ((count == 1)&&(top==-1))
	{
		printf("\n valid Expression..");
	}
	else
	{
		printf("\n not valid expression..\n");
	}
}

void push(char c)
{

	if (top == max - 1)
	{
		printf("\n overflow...");
	}
	else
	{
		top = top + 1;
		stack[top] = c;
	}
	printf("\n");
}

char pop()
{
	if (top == -1)
	{
		printf("\n underflow...");
	}
	else
	{
		return (stack[top--]);
	}
}

void display()
{
	if (top == -1)
	{
		printf("No elements in stack..");
	}
	else
	{
		for (i = 0; i < max; i++)
		{
			printf("%s", stack[i]);
		}
	}
}*/
// Write a program to evaluate  prefix  expressions using stacks
/*#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
int stack[1000];
int top = -1;
char push(int a)
{
	top++;
	stack[top] = a;
}
char pop()
{
	char z;
	z = stack[top--];
	return z;
}
int main()
{
	char a[1000];
	int i, ans, b;
	printf("Enter prefix expression\n");
	fgets(a, sizeof(a), stdin);
	for (i = strlen(a) - 1; i >= 0; i--)
	{
		if (isdigit(a[i]))
		{
			b = a[i] - 48;//to convert char into number using'0' or 48
			push(b);
		}
		else
		{
			int x, y;
			x = pop();
			y = pop();
			switch (a[i])
			{
			case '+':
				ans = x + y;
				break;
			case '-':
				ans = x - y;
				break;
			case '*':
				ans = x * y;
				break;
			case '/':
				ans= x / y;
				break;
			case '^':
				ans= pow(y, x);
				break;
			}

			push(ans);
		}
	}
	printf("result is :%d", pop());
	return 0;
}*/
// Write a program to evaluate  postfix  expressions using stacks:
/*#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#include<ctype.h>
char stack[1000];
int top = -1;
char push(char a)
{
	top++;
	stack[top] = a;
}
char pop()
{
	char z;
	z = stack[top];
	top--;
	return z;
}
int main()
{
	char a[1000];
	int i,b,w;
	printf("Enter postfix expression\n");
	fgets(a,sizeof(a),stdin);
	for (i =0 ; i <strlen(a); i++)
	{
		if (isdigit(a[i]))
		{
			b=a[i]-'0';
			push(b);
		}
		else
		{
			int  x, y;
			x = pop();
			y = pop();
			switch (a[i])
			{
				case '+':
				w=y+x;
				break;
				case '-':
				w=y-x;
				break;
				case'*':
				w=x*y;
				break;
				case'/':
				w=y/x;
				break;
				case'^':
				w=pow(y,x);
				break;
			}
			
			push(w);
		}
	}
	printf("result is :%d",pop());
}*/
// Write a program to evaluate  infix  expressions using stacks:
/*#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#include<ctype.h>
char stack[1000];
int top = -1;
char push(char a)
{
	top++;
	stack[top] = a;
}
char pop()
{
	char z;
	z = stack[top];
	top--;
	return z;
}
int main()
{
	char a[1000];
	int i,b,w;
	printf("Enter postfix expression\n");
	fgets(a,sizeof(a),stdin);
	for (i =0 ; i <,strlen(a); i++)
	{


	}
}*/
// WAP TO CONVERT THE INFIX TO POSTFIX EXPRESION:
/*#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

char stack[MAX_SIZE];
int top = -1;

int isEmpty() {
	return top == -1;
}

int isFull() {
	return top == MAX_SIZE - 1;
}

char peek() {
	if (isEmpty()) {
		printf("Stack Underflow\n");
		exit(1);
	}
	return stack[top];
}

void push(char item) {
	if (isFull()) {
		printf("Stack Overflow\n");
		exit(1);
	}
	stack[++top] = item;
}

char pop() {
	if (isEmpty()) {
		printf("Stack Underflow\n");
		exit(1);
	}
	return stack[top--];
}

int precedence(char ch) {
	switch (ch) {
		case '^':
			return 3;
		case '*':
		case '/':
			return 2;
		case '+':
		case '-':
			return 1;
		default:
			return 0;
	}
}

void infixToPostfix(char *exp) {
	char *postfix = (char *)malloc(sizeof(char) * MAX_SIZE);
	int i, j;
	char item, x;

	postfix[0] = '\0';
	i = j = 0;

	while (exp[i] != '\0') {
		item = exp[i];

		if (isalnum(item)) {
			postfix[j++] = item;
		} else if (item == '(') {
			push(item);
		} else if (item == ')') {
			while ((x = pop()) != '(') {
				postfix[j++] = x;
			}
		} else {
			while (!isEmpty() && precedence(peek()) >= precedence(item)) {
				x = pop();
				postfix[j++] = x;
			}
			push(item);
		}
		i++;
	}

	while (!isEmpty()) {
		postfix[j++] = pop();
	}

	postfix[j] = '\0';
	printf("Postfix Expression: %s\n", postfix);
	free(postfix);
}

int main() {
	char exp[MAX_SIZE];

	printf("Enter an infix expression: ");
	fgets(exp, MAX_SIZE, stdin);

	infixToPostfix(exp);

	return 0;
}*/
// WAP TP CONVERT INFIX TO PREFIX EXPRESSION:
/*#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 1000

// Stack for operators
char stack[MAX];
int top = -1;

void push(char c) {
	if (top == MAX - 1) {
		printf("Stack overflow\n");
		exit(1);
	}
	stack[++top] = c;
}

char pop() {
	if (top == -1) {
		printf("Stack underflow\n");
		exit(1);
	}
	return stack[top--];
}

char peek() {
	if (top == -1) {
		return '\0';
	}
	return stack[top];
}

int precedence(char op) {
	switch (op) {
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		case '^':
			return 3;
		default:
			return 0;
	}
}

int isOperator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

void infixToPostfix(char infix[], char postfix[]) {
	int i, j = 0;
	for (i = 0; infix[i] != '\0'; i++) {
		char c = infix[i];
		if (isdigit(c) || isalpha(c)) {
			postfix[j++] = c;
		} else if (c == '(') {
			push(c);
		} else if (c == ')') {
			while (top != -1 && peek() != '(') {
				postfix[j++] = pop();
			}
			pop(); // remove '(' from stack
		} else if (isOperator(c)) {
			while (top != -1 && precedence(peek()) >= precedence(c)) {
				postfix[j++] = pop();
			}
			push(c);
		}
	}
	while (top != -1) {
		postfix[j++] = pop();
	}
	postfix[j] = '\0'; // Null-terminate the postfix expression
}

int main() {
	char infix[MAX], postfix[MAX];

	printf("Enter an infix expression: ");
	fgets(infix, sizeof(infix), stdin);
	infix[strcspn(infix, "\n")] = '\0'; // Remove the newline character

	infixToPostfix(infix, postfix);
	printf("Postfix expression: %s\n", postfix);

	return 0;
}*/
// SIMPLE CODE OF QUEUE:
/*#include <stdio.h>
int front = -1, rear = -1, queue[1000];
void insert(int num)
{
	if (rear == 999)
	{
		printf("queue is full.");
		return;
	}

	if (front == -1)
	{
		rear = front = 0;
		queue[front] = num;
		return;
	}
	rear++;
	queue[rear] = num;
}
int delete()
{
	if (front == -1 && rear == -1)
	{
		printf("queue underflow...");
		return;
	}
	if (front != -1 && front == rear)
	{
		int i = queue[front];
		front = rear = -1;
		return i;
	}
	return queue[front++];
}
void display()
{
	if(front==-1&&rear==-1)
	{
		printf("queue is empty");
		return;
	}
	printf("elements are");
	for(int i=front;i<=rear;i++)
	{
		printf("%d \n",queue[i]);
	}
}
int main()
{
 int n,choice;
 while(1)
 {
printf(" \nENTER :");
printf(" \n1.ENQUEUE :");
printf(" \n2. DEQUEUE:");
printf(" \n3.DISPLAY:");
printf(" \n4.EXIT:");
scanf("%d",&choice);
 }
}*/
// LINKED LIST :
/*#include <stdio.h>
#include <stdlib.h>
struct node
{
	int data;
	struct node *next;
};
struct node *head = NULL; // VARIABLE(ADDRESS OF FIRST NODE)
struct node *temp = NULL; // VARIABLE (address of last node)
struct node *createnode() // to create the new node which consist of data and next
{
	struct node *node = (struct * node) malloc(sizeof(struct node)); // create the space
	printf("Enter data");
	scanf("%d", &node->data); //-> to access pointer of structure
	node->next = NULL;		  // to create  next null (by default)
	return node;
}
void createlist()
{
	int i, n;
	printf("Enter the  of number of elements");
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		struct node *newnode = createnode();
		if (head == NULL)
		{
			head = newnode;
		}
		else
		{
			temp->next = newnode; // temp is considered as tail until user want to enter the new node
		}
		temp = newnode;
	}
}
void display()
{

	if (head == NULL)
	{
		printf("List is empty");
	}
	else
	{
		struct node *i;
		i = head;
		while (i != NULL)
		{
			printf("%d ", i->data);
			i = i->next; // increment or i++
		}
	}
}
void insertatbeg()
{
	struct node *newnode = createnode();
	newnode->next = head;
	head = newnode;
}
void insertatend()
{
	struct node *newnode = createnode();
	if (head == NULL)
	{
		printf("List is empty");
	}
	else
	{
		temp->next = newnode;
		temp = newnode;
	}
}
void insertatany()
{
	struct node *newnode = createnode();
	struct node *te = head, *tp;
	int n, i, f = -1;
	printf("Enter position where data to be entered");
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		if (n == 1)
		{
			newnode->next = head;
			head = newnode;
			f = 1;
			break;
		}
		else if (i == n - 1)
		{
			tp = te->next;
			te->next = newnode;
			te->next->next = tp;
			f = 2;
			break;
		}
		if (i == n)
		{
			te = newnode;
			te->next = NULL;
		}

		else
			te = te->next;
	}
	if (f == -1)
	{
		printf("Invalid position");
	}
}
void delete()
{
	struct node *delnode;
	struct node *te = head;
	int n, i, f = -1;
	printf("Enter position where data to be deleted");
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		if (n == 1)
		{
			if (head->next != NULL)
			{
				head = head->next;
				f = 2;
				break;
			}
			else
			{
				head = NULL;
				break;
			}

			f = 2;
		}
		else if (i == n - 1)
		{
			if (te->next != NULL && te->next->next != NULL)
			{
				te->next = te->next->next;
			}
			else
			{
				te->next = NULL;
			}
			f = 2;
			break;
		}
		else if (i == n)
		{
			te = NULL;
			f = 2;
			break;
		}
		else
			te = te->next;
	}
	if (f == -1)
	{
		printf("Invalid position");
	}
}
void search()
{
	int ser, f = -1;
	struct node *temp = head; // from firstb value
	printf("Enter data to search");
	scanf("%d", &ser);
	while (temp != NULL)
	{
		if (ser == (temp->data))
		{
			printf("value found at %d", temp);
			f = 2;
			break;
		}
		else
		{
			temp = temp->next;
		}
	}
	if (f == -1)
	{
		printf("Value not found");
	}
	else
	{
		printf("Value found");
	}
}
int main()
{
	createlist();
	while (1)
	{
		system("cls");
		printf("Enter your choice\n");
		printf("1.Insert node in begining\n2.Insert node in end\n3.Insert node at any position\n4.");
		printf("Delete node from given position\n5.Search node in list\n6.Display\n7.Exit");
		int ch;
		scanf("%d", &ch);
		switch (ch)
		{
		case 1: // insert node in begining
			insertatbeg();
			break;
		case 2: // insert node in end
			insertatend();
			break;
		case 3: // insert node at any position
			insertatany();
			break;
		case 4: // delete the node from given position
			delete ();
			break;
		case 5: // search node in th e list
			search();
			break;
		case 6: // display
			display();
			break;
		case 7: // exit the loop
			exit(0);
		default:
			printf("Invalid input");
		}
		system("pause");
	}
	return 0;
}*/
/*
# include <stdio.h>
# include <stdlib.h>
struct node{
    int data;
    struct node*next;
};
struct node *head=NULL,*temp=NULL,*newnode,*insert=NULL;
struct node*createnode(){
    newnode=(struct node*)malloc(sizeof(struct node));
    scanf("%d",&newnode->data);
    newnode->next=NULL;
}
void createlist(){
    int n,i;
    printf("Enter number of elements");
    scanf("%d",&n);
    for(i=0;i<=n-1;i++){
        struct node *newnode=createnode();
        if(head==NULL){
            head=newnode;
            temp=head;

        }
        else{
            temp->next =newnode;
            temp=newnode;
        }
        temp=head;
        while(temp!=NULL){
            printf("%d",temp->data);
            temp=temp->next;
        }


    }
}
void insertatbeg()
{
    insert=(struct node*)malloc(sizeof(struct node));
    printf("Enter the element to insert at beg");
    scanf("%d",&insert->data);
    insert->next=head;
    head=insert;
    temp=head;
    while(temp!=NULL){
        printf("%d",temp->data);
        temp=temp->next;
}
}
int main()
{
    createlist();
    insertatbeg();
    return 0;
}*/
#include<stdio.h>
void main()
{
	printf("hello");
}