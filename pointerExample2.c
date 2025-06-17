#include <stdio.h>
#include <stdlib.h>

int main() {
    int **row=(int**)malloc(8*(sizeof(int*)));
    int *column[8];
    for(int i=0;i<8;i++) {
        column[i]=(int*)malloc(16*sizeof(int));
    }
    row=&column[0];
    for(int i=0;i<8;i++) {
        for(int j=0;j<16;j++) {
            int temp=*(*(row+i)+j)=j+16*i;
            if (j!=15)
                printf("%d, ",temp);
            else
                printf("%d",temp);
        }
        printf("\n");
    }

    return 0;
}