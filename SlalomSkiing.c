
#include<string.h>

typedef struct 
{
    int x;
    int y;
}gates;


int compare (const void * a, const void * b)
{
    gates *gateA = (gates *)a;
    gates *gateB = (gates *)b;
    return ( gateA->x - gateB->x );
}


int solution(int A[], int N) 
{
    int n=N*3;
    gates G[n];
    int i, max=0, tmp;
    for (i=0;i<N;i++)
    {
        tmp=A[i];
        max=tmp>max?tmp:max;
        G[i].y=i;
        G[i].x=A[i];
    }
    for (i=0;i<N;i++)
    {
        G[i+N].y=i;
        G[i+N].x=max+max-A[i]+1;
        G[i+N*2].y=i;
        G[i+N*2].x=max+max+A[i]+2;
    }
    qsort (G, n, sizeof(gates), compare);
//    for(i=0;i<n;i++) printf ("%d ", G[i].y);    
    int stack[N];
    memset(stack, 0xFF, N*sizeof(int));
    int maxstack=0;
    stack[0]=G[0].y;
    int s=0, j;
    for(i=1;i<n;i++)
    {
        s=0;
        if(G[i].y<stack[0])stack[0]=G[i].y;
        else
        while(1)
        {
            if     (G[i].y==stack[s])break;
            else if(G[i].y>stack[s] && G[i].y<stack[s+1]) {stack[s+1]=G[i].y;break;}
            else if(G[i].y>stack[s] && stack[s+1]==-1) {stack[s+1]=G[i].y;break;}
           else s++;
        }
//        for (j=0;j<10;j++)printf("%d ", stack[j]);
//        printf("\n");
    }
    for(s=0;s<N;s++) if(stack[s]==-1)return s;
}

