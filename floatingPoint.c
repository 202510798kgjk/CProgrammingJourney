#include <stdio.h>
#include <stdlib.h>

#define BYTE unsigned char

BYTE* decimaltoBinaryText(BYTE byte);

int main() {
    char ch;
    int i,j;
    BYTE buf[8][4];
    float a[8]={0.0f,1.0f,1.35f,2.25f,3.0f,3.5f,3.75f,3.875f};
    /*
    for(i=0;i<8;i++) {
        a[i]=i;
        printf("%lf",a[i]);
        if (i!=7)
            printf(", ");
        else
            printf("\n\n");
    }
    */
    BYTE* p=(BYTE*)&a;
    for(i=0;i<8;i++) {
        for(j=0;j<4;j++) {
            buf[i][j]=(BYTE)*(p+j+4*i);
            printf("%X ",buf[i][j]);
        }
        printf("\n\n");
    }
    int k;
    for (i=0;i<8;i++) {
        for(j=0;j<4;j++) {
            char* result=decimaltoBinaryText(buf[i][j]);
            for(k=0;k<8;k++) {
                printf("%c",*(result+k));
            }
            printf(" ");
            free(result);
        }
        printf("\n\n");
    }
    while(1) {if (scanf("%c",&ch) && ch =='\n') break;}
    return 0;
}

BYTE* decimaltoBinaryText(BYTE byte) {
    int i; BYTE* buf=(BYTE*)calloc(8,sizeof(BYTE));
    for(i=0;i<8;i++) {
        *(buf+i)=((byte>>i)&0x1)+0x30;  
    }
    
    return buf;
}
