#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Operation {
    char url[100];
    char timestamp[100];
} Operation;

typedef struct Stack {
    Operation* data;
    int top;
    int capacity;
} Stack;

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (Operation*)malloc(sizeof(Operation) * capacity);
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, Operation op) {
    if (stack->top < stack->capacity - 1) {
        stack->data[++stack->top] = op;
    }
}

Operation pop(Stack* stack) {
    Operation empty ={"",""};
    if (isEmpty(stack)) {
        return empty;
    }
    return stack->data[stack->top--];
}

typedef struct doubleNode {
    Operation data;
    struct doubleNode* next;
    struct doubleNode* prev;
} doubleNode;

doubleNode* historyHead = NULL;

void addToHistory(Operation op) {
    doubleNode* node = (doubleNode*)malloc(sizeof(doubleNode));
    node->data = op;
    node->next = NULL;
    node->prev = NULL;

    if (historyHead == NULL) {
        historyHead = node;
    } else {
        doubleNode* temp = historyHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
        node->prev = temp;
    }
}

void printHistory() {
    if (!historyHead) {
        printf("Khong co lich su nao\n");
        return;
    }
    doubleNode* temp = historyHead;
    while (temp) {
        printf("%s (%s)\n", temp->data.url, temp->data.timestamp);
        temp = temp->next;
    }
}

void clearHistory() {
    doubleNode* temp = historyHead;
    while (temp) {
        doubleNode* next = temp->next;
        free(temp);
        temp = next;
    }
    historyHead = NULL;
}

int main() {
    Stack* back = createStack(100);
    Stack* forward = createStack(100);
    Operation current;
    int choice;
    do {
        printf("\n==========WEB HISTORY==========\n");
        printf("1. VISIT url\n");
        printf("2. BACKWARD\n");
        printf("3. FORWARD\n");
        printf("4. CURRENT\n");
        printf("5. HISTORY\n");
        printf("6. CLEAR HISTORY\n");
        printf("7. THOAT\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: {
                Operation op;
                printf("Nhap dia chi URL: ");
                fgets(op.url, sizeof(op.url), stdin);
                op.url[strcspn(op.url, "\n")] = '\0';
                printf("Nhap thoi diem truy cap: ");
                fgets(op.timestamp, sizeof(op.timestamp), stdin);
                op.timestamp[strcspn(op.timestamp, "\n")] = '\0';
                if (strlen(current.url) > 0) {
                    push(back, current);
                }
                current = op;
                addToHistory(op);
                forward->top = -1;
                printf("Da truy cap: %s\n", current.url);
                break;
            }
            case 2:
                if (isEmpty(back)) {
                    printf("Khong co trang truoc de quay lai.\n");
                } else {
                    push(forward, current);
                    current = pop(back);
                    printf("Da quay lai: %s\n", current.url);
                }
                break;
            case 3:
                if (isEmpty(forward)) {
                    printf("Khong co trang sau de tien toi.\n");
                } else {
                    push(back, current);
                    current = pop(forward);
                    printf("Da tien toi: %s\n", current.url);
                }
                break;
            case 4:
                if (strlen(current.url) == 0) {
                    printf("Chua co trang nao dang hien tai.\n");
                } else {
                    printf("Trang hien tai: %s (%s)\n", current.url, current.timestamp);
                }
                break;
            case 5:
                printHistory();
                break;
            case 6:
                clearHistory();
                printf("Da xoa lich su\n");
                break;
            case 7:
                printf("Dang thoat chuong trinh\n");
                break;
            default:
                printf("Lua chon khong hop le\n");
        }

    } while (choice != 7);

    free(back->data);
    free(forward->data);
    free(back);
    free(forward);
    clearHistory();

    return 0;
}
