#include <vector>
#include "include/LinkedList.h"
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    vector<int> res;
    void backtracking(ListNode* head){
        if(!head){
            return;
        }
        backtracking(head->next);
        res.emplace_back(head->val);
    }
   public:
    vector<int> reversePrint(ListNode* head) {
        backtracking(head);
        return res;
    }
};