#include <stdio.h>
#include <stdlib.h>

void update(int *BIT, int size, int index, int value){
    while(index <= size){
        BIT[index] += value;
        index += index & -index;
    }
}

int query(int *BIT, int index){
    int sum = 0;
    while (index > 0) {
        sum += BIT[index];
        index -= index & -index;
    }
    return sum;
}

int compare(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}

int* countSmaller(int* nums, int numsSize, int* returnSize){
    *returnSize = numsSize;
    int* result = (int*)malloc(numsSize * sizeof(int));
    if(!result) return NULL;

    int* sortedNums = (int*)malloc(numsSize * sizeof(int));
    for(int i = 0; i < numsSize; i++) sortedNums[i] = nums[i];

    qsort(sortedNums, numsSize, sizeof(int), compare);

    int* rank = (int*)malloc(numsSize * sizeof(int));
    for(int i = 0; i < numsSize; i++){
        int* pos = (int*)bsearch(&nums[i], sortedNums, numsSize, sizeof(int), compare);
        rank[i] = (pos - sortedNums) + 1; 
    }

    int* BIT = (int*)calloc(numsSize + 1, sizeof(int));
    for(int i = numsSize - 1; i >= 0; i--){
        result[i] = query(BIT, rank[i] - 1); 
        update(BIT, numsSize, rank[i], 1);   
    }

    free(sortedNums);
    free(rank);
    free(BIT);
    return result;
}

int main(){
    int nums[] = {5, 2, 6, 1};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;
    int* result = countSmaller(nums, numsSize, &returnSize);
    printf("Output: [");
    for (int i = 0; i < returnSize; i++) {
        printf("%d%s", result[i], (i == returnSize - 1) ? "]\n" : ", ");
    }
    free(result);
    return 0;
}
