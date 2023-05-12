#include <stdio.h>

typedef int (*Operation)(int);

int square(int num){
    return num * num;
}

void map(int *nums, int size, Operation operation){
    for(int i = 0; i < size; i++){
        printf("%i\n", operation(nums[i]));
    }
}

int main(){

    int nums[5] = {1, 2, 3, 4, 5};
    map(nums, 5, square);

}