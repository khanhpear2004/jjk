#include<iostream>
#include<string>
#include<vector>

using namespace std;

 
struct ListNode{
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    int place[100];

    int robbing(vector<int> &nums, int i){
        if(i < 0){ return 0;}
        if(place[i] == 0){
            place[i] = max(robbing(nums, i - 2) + nums[i], robbing(nums, i - 1));
        }
        return place[i];
    }

    int rob(vector<int>& nums){
        int n = nums.size();
        for(int i = 0; i < n; i++) place[i] = 0;
        return robbing(nums, nums.size() - 1);
    }
};

int main(){
    Solution s;
    vector<int> v = {2,7,9,3,1};
    cout<<s.rob(v);
}