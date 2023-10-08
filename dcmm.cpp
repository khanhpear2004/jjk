#include<iostream>
#include<string>
#include<vector>
#include<set>

using namespace std;


struct ListNode {
     int val;
     ListNode *next;
     ListNode *prev;

     ListNode(int val, ListNode *next, ListNode *prev){
        this->val = val;
        this->next = next; this->prev = prev;
     }
 };

 void add(ListNode *&l, int n){
    ListNode *tmp = new ListNode(n, nullptr, nullptr);
    if(l == nullptr){
        l = tmp; l->next = l; l->prev = l;
    }
    else{
        l->next->prev = tmp; tmp->next = l->next;
        l->next = tmp; tmp->prev = l;
        l = tmp;
    }
 }

 void swap(ListNode *&a, ListNode *&b){
    if(a->next = b){
        a->next = b->next; b->next->prev = a;
        b->prev = a->prev; a->prev->next = b;
        b->next = a; a->prev = b;
    }
    else if(b->next = a){
        b->next = a->next; a->next->prev = b;
        a->prev = b->prev; b->prev->next = a;
        a->next = b; b->prev = a;
    }
    else{
        ListNode *aNext = a->next; ListNode *aPrev = a->prev;
        ListNode *bNext = b->next; ListNode *bPrev = b->prev;
        a->next = bNext; a->prev = bPrev;
        bPrev->next = a; bNext->prev = a;
        b->next = aNext; b->prev = aPrev;
        aPrev->next = b; aNext->prev = b;
    }
 }



class Solution {
public:
    vector<vector<int>> v; vector<int> tmp;
    bool used[8];

    void permute(vector<int>& nums){
        int n = nums.size(); set<int> same;
        for(int i = 0; i < n; i++){
            if(!used[i] && same.find(nums[i]) == same.end()){
                tmp.push_back(nums[i]);
                if(tmp.size() == n){
                    v.push_back(tmp); tmp.pop_back();
                }
                else{
                    used[i] = 1; same.insert(nums[i]);
                    permute(nums);
                    used[i] = 0; tmp.pop_back();
                }
            }
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        for(int i = 0; i < 8; i++){
            used[i] = 0;
        }
        permute(nums);
        return v;
    }
};

int main(){
    // Solution s;
    // vector<int> nums;
    // for(int i = 0; i < 3; i++){
    //     int val; cin>>val;
    //     nums.push_back(val);
    // }
    // vector<vector<int>> v = s.permuteUnique(nums);

    ListNode *l = nullptr;
    for(int i = 0; i < 5; i++){
        int n; cin>>n;
        add(l,n);
    }
    ListNode *a = l; ListNode *b = l;
    for(int i = 0; i < 2; i++) a = a->next;
    for(int i = 0; i < 3; i++) b = b->next;
    swap(a,b);
    ListNode *tmp = l->next;
    for(int i = 0; i < 5; i++){
        cout<<tmp->val<<" ";
        tmp = tmp->next;
    }

}