#include<iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head){
        ListNode *check = new ListNode();
        ListNode *tmp = nullptr;
        for(ListNode *t = head; t != nullptr; t = t->next){
            if(tmp == nullptr && t->val == 0) tmp = t;
            if(t->val != check->val){
                check->val = t->val; tmp = t;
            }
            else{
                ListNode *n = t;
                tmp->next = n->next;
            }
        }
        delete check;
        return head;
    }

    int count(ListNode* head){
        int cnt = 0;
        while(head != nullptr){
            cnt++; head = head->next;
        }
        return cnt;
    }

    bool isSymmetric(TreeNode* root) {
        return (root==NULL)|| isSym(root->left,root->right);
    }

    bool isSym(TreeNode* l,TreeNode* r)
    {
        if(l==NULL or r==NULL)
        {
            return l==r;
        }
        if(l->val!=r->val) return false;
        
        return isSym(l->left,r->right) && isSym(l->right,r->left);
    }
};

int main(){
    Solution s;
    /*ListNode *head = nullptr;
    int n; cin>>n;
    for(int i = 0; i < n; i++){
        int x; cin>>x;
        ListNode *node = new ListNode(x);
        if(head == nullptr) head = node;
        else{
            ListNode *t = head;
            while(t->next != nullptr) t = t->next;
            t->next = node;
        }
    }

    ListNode *sol = s.deleteDuplicates(head);

    for(int i = 0; i < s.count(head); i++){
        cout<<sol->val<<"\t";
        sol = sol->next;
    }*/

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);

    cout<<s.isSymmetric(root);
    
}