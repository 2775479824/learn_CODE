#include<iostream>

using namespace std;

typedef struct ListNode {
    int val;
    struct ListNode* next;
}ListNode;



class PalindromeList {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == NULL)return head;
        ListNode* p1, * p2, * p3;
        p1 = NULL;
        p2 = head;
        p3 = head->next;
        while (p2)
        {
            p2->next = p1;
            p1 = p2;
            p2 = p3;
            if (p3)p3 = p3->next;
        }
        return p1;
    }

    ListNode* FindMiddle(ListNode* head)
    {
        ListNode* slow, * fast;
        slow = fast = head;
        while (fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }

    bool chkPalindrome(ListNode* A) {
        ListNode* mid = FindMiddle(A);
        ListNode* rmid = reverseList(mid);
        while (rmid && A)
        {
            if (A->val != rmid->val)
            {
                return false;
            }
            rmid = rmid->next;
            A = A->next;
        }
        return true;
    }
};
