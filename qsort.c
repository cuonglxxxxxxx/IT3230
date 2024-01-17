#include<stdio.h>
void swap(int *a,int *b){
    int tmp=*a;
    *a=*b;
    *b=tmp;
}
int hoarepartition(int a[],int l,int r){
    int i=l-1;
    int j=r+1;
    int pivot=a[l];
    while(1){
        do{
            i++;
        }while(a[i]<pivot);
        do{
            j--;
        }while(a[j]>pivot);
        if(i<j){
            swap(&a[i],&a[j]);
        }else return j;
    }
}
void myqsort(int a[],int l,int r){
    int p=hoarepartition(a,l,r);
    if(l>r){
        return;
    }
    myqsort(a,l,p);
    myqsort(a,p+1,r);
}
int main(){

}