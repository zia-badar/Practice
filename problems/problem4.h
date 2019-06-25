// couting pairs in two sorted array with sum = x
#ifndef PROBLEM_4_H
#define PROBLEM_4_H


int count(int* array1, int size1, int* array2, int size2, int x)
{
    int p1 = 0, p2 = size2-1;
    int count = 0;
    while(p1 < size1 && p2 >= 0)          // avoiding computing duplicate pairs
    {
        if(array1[p1] + array2[p2] < x) p1++;
        else
        {
            while(array1[p1] + array2[p2] > x) p2--;
            if(array1[p1] + array2[p2] == x)
                count++, p2--;         // arrays contains distinct value so only one
        }                                                       // consective pair is possible
    }
    return count;
}

#endif
