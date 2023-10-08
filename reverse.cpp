#include<iostream>

using namespace std;

struct Node{
    int data;
    Node *next;
    Node(int data){
        this->data = data;
        this->next = nullptr;
    }
};

typedef struct Node* node;

node newNode(int a){
    node p = new Node(a);
    return p;
}

int size(node head){
    int cnt = 0;
    while(head != nullptr){
        cnt++;
        head = head->next;
    }
    return cnt;
}

void insertfirst(node &head, int data){
    node p = new Node(data);
    if(head == nullptr) head = p;
    else{
        p->next = head;
        head = p;
    }
}

void reverse(node &head){
    node reverse = nullptr;
    while(head != nullptr){
        insertfirst(reverse, head->data);
        head = head->next;
    }
    head = reverse;
}

void reversing(node &head){
    int s = size(head);
    node current = head;
    node tmp = head;
    node p = head->next;
    for(int i = 0; i < s - 1; i++){
        tmp->next = p->next;
        p->next = current;
        current = p;
        p = tmp->next;
    }
    head = current;
}

int main(){
    node head = nullptr;
    for(int i = 0; i < 5; i++){
        int data; cin>>data;
        insertfirst(head, data);
    }

   // cout<<size(head);

    reversing(head);

    while(head != nullptr){
        cout<<head->data<<" ";
        head = head->next;
    }
}