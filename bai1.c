#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
typedef struct Operation {
    char url[100];
    char timestamp[100];
}Operation;
typedef struct Stack {
    Operation *data;
    int top;
    int capacity;
}Stack;
Stack* createStack(int capacity) {
    Stack* stack=(Stack*)malloc(sizeof(Stack));
    stack->data=(Operation*)malloc(sizeof(Operation)*capacity);
    stack->top=-1;
    stack->capacity=capacity;
    return stack;
}
typedef struct doubleNode {
    Operation data;
    struct doubleNode* next;
    struct doubleNode* prev;
}doubleNode;
doubleNode* createDoubleNode(Operation data) {
    doubleNode* newNode=(doubleNode*)malloc(sizeof(doubleNode));
    newNode->data=data;
    newNode->next=NULL;
    newNode->prev=NULL;
    return newNode;
}
doubleNode* insert(doubleNode* history,Operation op) {
    doubleNode* newNode=createDoubleNode(op);
    doubleNode* temp=history;
    while(temp->next!=NULL) {
        temp=temp->next;
    }
    temp->next=newNode;
    newNode->prev=temp;
    return newNode;
}
int isEmpty(Stack* stack) {
    if (stack->top==-1) {
        return 1;
    }
    return 0;
}
int isFull(Stack* stack) {
    if (stack->top==stack->capacity-1) {
        return 1;
    }
    return 0;
}
void push(Stack* stack,Operation op) {
    if (isFull(stack)) {
        printf("Ngan xep da day\n");
        return;
    }
    stack->top++;
    stack->data[stack->top]=op;
}
Operation pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Ngan xep rong\n");
        return stack->data[0];
    }
    return stack->data[stack->top--];
}

void back(Stack* back, Stack* forward) {
    if (isEmpty(back)) {
        printf("Ngan xep rong\n");
        return;
    }
    Operation temp=pop(back);
    push(forward,temp);
}
void forward(Stack* forward, Stack* back) {
    if (isEmpty(forward)) {
        printf("Ngan xep rong\n");
        return;
    }
    Operation temp=pop(forward);
    push(back,temp);
}
void printList(doubleNode* history) {
    doubleNode* temp=history;
    if (temp->next==NULL) {
        printf("Lich su rong");
    }
    while(temp!=NULL) {
        printf("%s ",temp->data.url);
        printf("%s ",temp->data.timestamp);
        temp=temp->next;
    }
}
doubleNode* deleteNode(doubleNode* history) {
    doubleNode* temp=history;
    temp->next=NULL;
    temp->prev=NULL;
    free(temp);
    return history;
}
int main() {
    int choice;
    Stack* Back=createStack(100);
    Stack* Forward=createStack(100);
    doubleNode* history;
    do{
        printf("\nWEB HISTORY\n");
        printf("1.VISIT url\n");
        printf("2.BACKWARD\n");
        printf("3.FORWARD\n");
        printf("4.CURRENT\n");
        printf("5.HISTORY\n");
        printf("6.CLEAR HISTORY\n");
        printf("7.THOAT\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                Operation operation;
                printf("Nhap url: ");
                fflush(stdin);
                fgets(operation.url,sizeof(operation.url),stdin);
                operation.url[strlen(operation.url)]='\0';
                printf("Nhap timestamp: ");
                fgets(operation.timestamp,sizeof(operation.timestamp),stdin);
                operation.timestamp[strlen(operation.timestamp)]='\0';
                push(back,operation);
                insert(history,operation);
                while(!isEmpty(Forward)) {
                    pop(Forward);
                }
                break;
            case 2:
                back(Forward,Back);
                break;
            case 3:
                forward(Forward,Back);
                break;
            case 4:
                break;
            case 5:
                printList(history);
                break;
            case 6:
                deleteNode(history);
                break;
            case 7:
                printf("Cam on ban da su dung chuong trinh\n");
                break;
            default:
                printf("Vui long lua chon hop le\n");
        }
    }while(choice!=7);
    return 0;
}