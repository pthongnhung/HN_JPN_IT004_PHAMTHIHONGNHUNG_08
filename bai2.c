#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int id;
    char name[100];
    int age;
} Student;

typedef struct Node {
    Student data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(Student s) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = s;
    node->left = node->right = NULL;
    return node;
}

Node* insert(Node* root, Student s) {
    if (root == NULL) return createNode(s);
    if (s.id < root->data.id)
        root->left = insert(root->left, s);
    else if (s.id > root->data.id)
        root->right = insert(root->right, s);
    else
        printf("Sinh vien co ID %d da ton tai\n", s.id);
    return root;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("ID: %d | Ten: %s | Tuoi: %d\n", root->data.id, root->data.name, root->data.age);
        inorder(root->right);
    }
}

void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    Node* root = NULL;
    int choice;

    do {
        printf("\n========= STUDENT MANAGER ==========\n");
        printf("1. THEM SINH VIEN\n");
        printf("2. HIEN THI DANH SACH SINH VIEN\n");
        printf("3. TIM KIEM SINH VIEN\n");
        printf("4. XOA SINH VIEN\n");
        printf("5. THOAT\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: {
                Student s;
                printf("Nhap ID: ");
                scanf("%d", &s.id);
                getchar();
                printf("Nhap ten: ");
                fgets(s.name, sizeof(s.name), stdin);
                s.name[strcspn(s.name, "\n")] = '\0';
                printf("Nhap tuoi: ");
                scanf("%d", &s.age);
                root = insert(root, s);
                break;
            }
            case 2:
                inorder(root);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                printf("Dang thoat chuong trinh\n");
                break;
            default:
                printf("Lua chon khong hop le\n");
        }

    } while (choice != 5);

    freeTree(root);
    return 0;
}
