#define _CRT_SECURE_NO_WARNINGS 1


int missingNumber(int* nums, int numsSize) {
    int x = 0;
    int n = numsSize;
    for (int j = 0;j < numsSize;++j)
    {
        x ^= nums[j];
    }

    for (int i = 0;i <= n;++i)
    {
        x ^= i;
    }
    return x;
}

void Reverse(int* a, int left, int right)
{
    while (left < right)
    {
        int tmp = a[left];
        a[left] = a[right];
        a[right] = tmp;
        ++left;
        --right;
    }
}

void rotate(int* nums, int numsSize, int k) {
    k %= numsSize;
    //[0,numsSize-k-1]
    Reverse(nums, 0, numsSize - k - 1);
    //[numsSize-k,numsSize-1]
    Reverse(nums, numsSize - k, numsSize - 1);

    Reverse(nums, 0, numsSize - 1);
}