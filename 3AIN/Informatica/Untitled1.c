#include<stdio.h>
#include<locale.h>

void print_array(int vec[], size_t n){
    printf("vec[] = { ");
    for(size_t i=0; i<n; ++i)
        printf("%i, ", vec[i]);
    printf("}\n");
}
void swap_half(int vec[], size_t n){
    for(size_t i=0; i<n; ++i){
        int temp=vec[i];
        vec[i]=vec[n/2+i];
        vec[n/2+i]=temp;
    }
}


int main(){

    int v1[]={87, 79, 87, 70, 74, 83, 73, 79, 75, 71};
    size_t n1=10;

    swap_half(v1, n1);
    print_array(v1, n1);

    return 0;
}
