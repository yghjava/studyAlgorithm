#include<stdio.h>
#define MAXSIZE 100
#include<stdlib.h>
#include<malloc.h>

//define linkear list
typedef int dataType;
typedef struct lNode{
    dataType data[MAXSIZE];
    int length;
}list,*pList;

//initalize a linkear list
pList init(){
    pList li;
    li = (pList)malloc(sizeof(list));
    if(li){
        li->length=0;
    }
    return (li);
}

//find element by index
int findKth(int index,pList li){
    return li->data[index];
}

//inde element by key
int findElement(dataType key,pList li){
    pList head = li;
    int i=0;
    while(li->data[i]!=key && i <= li->length){
        i++;
    }
    if(i>li->length){
        return -1;
    }else{
        return i;
    }
}

int insert(dataType key,pList li,int index){
    int i;
    if(li->length==MAXSIZE){
        printf("linker has filled,don't insert to it");
        return 0;
    }
    if(index>li->length){
        printf("the index greater than table length!");
    }
    for(i=li->length-1;i>=index;i--){
        li->data[i+1]=li->data[i];
    }
    li->data[index]=key;
    li->length++;
    return 1;
}

int insertAfter(dataType key,pList li){
    if(li->length==MAXSIZE){
        printf("linker has filled,don't insert to it");
        return 0;
    }
    //li->length++;
    li->data[li->length]=key;
    li->length++;
    return 1;
}

//delete the index element
int deleteElementByIndex(pList li,int index){
    int i;
    if(li->length==0){
        printf("The table has be empty,don't delete any element!");
        return 0;
    }
    for(i=index+1;i<=li->length;i++){
        li->data[i-1]=li->data[i];
    }
    li->length--;
}

void toString(pList li){
    int i;
    if(li->length==0){
        printf("The table has be empty");
        return;
    }
    printf("toString: ");
    for(i=0;i<li->length;i++){
        printf("%d ",li->data[i]);
    }
    printf("\n");
}

void main(){
    dataType Kth = 2;
    dataType keyEle = 13;
    pList pli = init();
    insertAfter(12,pli);
    insertAfter(13,pli);
    insert(14,pli,1);
    //deleteElementByIndex(pli,0);
    toString(pli);
    dataType key = findKth(1,pli);
    printf("the %d th is %d\n",Kth,key);
    dataType index = findElement(keyEle,pli);
    printf("the %d element's index is %d",keyEle,index);
}

