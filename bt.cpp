#include<iostream>
#include <assert.h>

using namespace std;


//BAI1
/*
int size(LLNode *head){
    int n = 0;
    while(head != nullptr) {n++; head = head->next;}
    return n;
}

void insertLast(LLNode *&head, LLNode *&tail, LLNode *n){
    if(head == nullptr){
        head = tail = n;
    }
    else{
        tail->next = n;
        tail = n;
    }
}

LLNode* addLinkedList(LLNode* l0, LLNode* l1) {
    int s1 = size(l0), s2 = size(l1); int n = 0, plus = 0;
    LLNode *l = nullptr; LLNode *ltail = l;
    s1 >= s2 ? n = s1 : n = s2;
    for(int i = 0; i < n; i++){
        if(l0 == nullptr) l0 = new LLNode(0, nullptr);
        if(l1 == nullptr) l1 = new LLNode(0, nullptr);
        LLNode *tmp = new LLNode((l0->val + l1->val + plus) % 10, nullptr);
        plus = (l0->val + l1->val + plus)/10;
        insertLast(l, ltail, tmp);
        l0 = l0->next; l1 = l1->next;
    }
    if(plus == 1){
        LLNode *k = new LLNode(1, nullptr); insertLast(l, ltail, k);
    }
    return l;
}*/



//BAI2
/*template <class T>
SLinkedList<T>::Iterator::Iterator(SLinkedList<T>* pList, bool begin)
{
    
    this -> pList = pList;
    if (pList == nullptr){}
    else if (begin == true){
        if (this -> pList != nullptr){
            this -> current = pList -> head;
            this -> index = 0;
        }
        else{
            this -> current = nullptr;
            this -> index = -1;
        }
    }
    else{
        this -> current = nullptr;
        if (this -> pList != nullptr){
            this -> index = pList -> size();
        } else this -> index = 0;
    }
}

template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator=(const Iterator& iterator)
{
    
    this -> current = iterator.current;
    this -> pList = iterator.pList;
    this -> index = iterator.index;
    return *this;
}

template <class T>
void SLinkedList<T>::Iterator::remove()
{
    
    if (current == nullptr) throw std::out_of_range("Segmentation fault!");
    int index = pList -> indexOf(current -> data);
    if (current == pList -> head){
        current = nullptr;
        index = -1;
    }
    else{
        Node* prev = nullptr;
        Node* temp = pList -> head;
        for (int i = 0; i < index; i++){
            prev = temp;
            temp = temp -> next;
        }
        prev -> next = temp -> next;
        delete temp;
        index--;
        current = prev;
    }
    pList->count--;
}

template <class T>
void SLinkedList<T>::Iterator::set(const T& e)
{
    
    if (current == nullptr) throw std::out_of_range("Segmentation fault!");
    current -> data = e;
}

template <class T>
T& SLinkedList<T>::Iterator::operator*()
{
    
    if (current == nullptr) throw std::out_of_range("Segmentation fault!");
    return current -> data;
}

template <class T>
bool SLinkedList<T>::Iterator::operator!=(const Iterator& iterator)
{
    
    if (this -> current != iterator.current && this -> index != iterator.index) return true;
    return false;
}
// Prefix ++ overload
template <class T>
typename SLinkedList<T>::Iterator& SLinkedList<T>::Iterator::operator++()
{
    
    if (current == nullptr) throw std::out_of_range("Segmentation fault!");
    if (index == -1){
        current = pList -> head;
        index = 0;
    }
    else {
        current = current -> next;
        index++;
    }
    return *this;
}
// Postfix ++ overload
template <class T>
typename SLinkedList<T>::Iterator SLinkedList<T>::Iterator::operator++(int)
{
    
    Iterator temp = *this;
    if (current == nullptr) throw std::out_of_range("Segmentation fault!");
    if (index == -1) current = pList -> head;
    else current = current -> next;
    return temp;
}
*/


//BAI3
/*
template <class T>
void SLinkedList<T>::add(const T& e) {
    
    Node* newNode = new Node(e, nullptr);
    if (count == 0) {
        head = tail = newNode;
    } 
    else {
        tail->next = newNode;
        tail = newNode;
    }
    count++;
    
}

template<class T>
void SLinkedList<T>::add(int index, const T& e) {
    
    Node *newNode = new Node(e, nullptr);
    if(index == 0){
        if(head == nullptr){
            head = tail = newNode;
        }
        else{
            newNode->next = head;
            head = newNode;
        }
    }
    else if(index == count){
        add(e); count--;
    }
    else if(index < 0 || index > count){count--;}
    else{
        Node *tmp = nullptr; Node *k = head;
        int cnt = 0;
        for(int i = 0; i < count; i++){
            if(cnt == index){
                tmp->next = newNode;
                newNode->next = k;
            }
            else{
                tmp = k;
                k = k->next; cnt++;
            }
        }
    }
    count++;
}

template<class T>
int SLinkedList<T>::size() {
    return count;
}*/



//BAI4
/*template <class T>
T SLinkedList<T>::removeAt(int index)
{
    
    T del = 0;
    if(index < 0 || index > count - 1) return -1;
    else if(index == 0){
        if(count > 0){
            del = head->data; head = head->next;
        }
    }
    else if(index == count - 1){
        if(count > 0){
            Node *tmp = head; del = tail->data;
            while(tmp->next != tail){
                tmp = tmp->next;
            }
            tmp->next = nullptr;
            tail = tmp;
        }
    }
    else{
        if(count > 0){
            Node *tmp = head; Node *p = head;
            for(int i = 1; i < count - 1; i++){
                p = p->next;
                if(i == index){
                    del = p->data;
                    tmp->next = p->next; break;
                }
                else{tmp = p;}
            }
        }
    }
    count--;
    return del;
}

template <class T>
bool SLinkedList<T>::removeItem(const T& item)
{
    
    Node *p = head; int index;
    for(int  i = 0; i < count; i++){
        if(p->data == item){
            index = i;
        }
        p = p->next;
    }
    if(index < 0 || index > count - 1) return false;
    else if(index == 0){
        if(count > 0){
            head = head->next;
        }
    }
    else if(index == count - 1){
        if(count > 0){
            Node *tmp = head;
            while(tmp->next != tail){
                tmp = tmp->next;
            }
            tmp->next = nullptr;
            tail = tmp;
        }
    }
    else{
        if(count > 0){
            Node *tmp = head; Node *q = head;
            for(int i = 1; i < count - 1; i++){
                q = q->next;
                if(i == index){
                    tmp->next = q->next; break;
                }
                else{tmp = q;}
            }
        }
    }
    count--;
    return true;
}

template<class T>
void SLinkedList<T>::clear(){
    Node* temp = head;
    while (head != NULL) {
        head = head->next;
        delete temp;
        temp = head;
    }
    tail = NULL;
    count = 0;
}*/




//BAI5
/*void swapTailtoHead(LLNode *&head){
    LLNode *tail = head;
    if(head != nullptr){
        while(tail->next != nullptr){
            tail = tail->next;
        }
        LLNode *before = head;
        while(before->next != tail){
            before = before->next;
        }
        tail->next = head;
        head = tail;
        before->next = nullptr;
    }
}

LLNode* rotateLinkedList(LLNode* head, int k){
    
    for(int i = 0; i < k; i++){
        swapTailtoHead(head);
    }
    return head;
}*/