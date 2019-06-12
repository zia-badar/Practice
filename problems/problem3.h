// couting pairs in sorted array with sum = x
#ifndef PROBLEM_3_H
#define PROBLEM_3_H

int count(int* array, int size, int x)
{
    int l=0, r=size-1;
    int count = 0;
    while(l < r)
    {
        while(array[l] + array[r] >= x && r > l) r--;
        count += r-l;
        l++;
    }
    return count;
}

#endif