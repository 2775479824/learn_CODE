#define _CRT_SECURE_NO_WARNINGS 1
#include<vector>
class Solution {
public:
    using ll = long long;
    int numberOfArrays(vector<int>& differences, int lower, int upper) {
        ll sum = 0, max_s = 0, min_s = 0;
        for (auto x : differences)
        {
            sum += x;
            min_s = min_s < sum ? min_s : sum;
            max_s = max_s > sum ? max_s : sum;
            if (max_s - min_s > upper - lower)return 0;
        }
        return (upper - lower) - (max_s - min_s) + 1;
    }
};