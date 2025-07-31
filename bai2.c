#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Student {
    int id;
    char name[100];
    int age;
}Student;
typedef struct Node {
    Student student;
    struct Node* left;
    struct Node* right;
}Node;
Node* createNode(Student data) {
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->student=data;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}
int generateID() {
    static int id=0;
    id++;
    return id;
}
Node* insertStudent(Node* root, Student student) {
    if (!root) {
        printf("Da them phan tu vao cay\n");
        return root;
    }
    while (root->left) {
        if (root->left==NULL) {
            root->left=createNode(student);
        }
        break;
    }
    while (root->right) {
        if (root->right==NULL) {
            root->right=createNode(root->student);
        }
        break;
    }

}
void printInorder(Node* root) {
    if (!root) {
        return;
    }
    printInorder(root->left);
    printf("%d ",root->student.id);
    printInorder(root->right);
    printf("\n");
}
void searchId(Node* root,int id) {
    if (!root) {
        return;
    }
    if (root->student.id==id) {
        printf("%d ",root->student.id);
        printf("%s\t",root->student.name);
        printf("%d\t",root->student.age);
        printf("\n");
    }
}
int main() {
    int choice;
    Node* root=createNode(3);
    Node* node2=createNode(4);
    Node* node3=createNode(5);
    Node* node4=createNode(6);
    root->left=node2;
    root->right=node3;
    node2->left=node4;

    do {
        printf("1.Them sinh vien\n");
        printf("2.Hiem thi danh sach sinh vien\n");
        printf("3.Tim kiem sinh vien\n");
        printf("4.Xoa sinh vien\n");
        printf("5.Thoat");
        printf("Nhap lua chon cua ban: ");
        scanf("%d",&choice);
        switch(choice) {
            case 1:
                Student student;
                student.id=generateID();
                printf("Nhap ten sinh vien: ");
                fgets(student.name,100,stdin);
                student.name[strlen(student.name)]='\0';

                printf("Nhap tuoi cua sinh vien: ");
                scanf("%d",&student.age);
                getchar();

                insertStudent(root,student);
                break;
            case 2:
                printInorder(root);
                break;
            case 3:
                int id;
                printf("Nhap id can tim kiem: ");
                scanf("%d",&id);
                searchId(root,id);
                break;
            case 4:
                break;
            case 5:
                printf("Cam on ban da dung chuong trinh\n");
                break;
                default:
                printf("Vui long nhap lua chon hop le\n");
        }
    }while (choice!=5);
    return 0;
}