#include<math.h>
int compare (const void * a, const void * b)
{
  return ( *(int*)b - *(int*)a );
}

inline int countit(int *A, int n)
{
    int i=1;
    while(A[i]==A[0]&&i<n){i++;}
    return i;
}

int solution(int A[], int N, int X) 
{
    int B[N];
    int i=0, tmp, n=0;
    qsort(A, N, sizeof(int), compare);
//    for (i=0;i<N;i++) printf("%d ", A[i]);
    i=0;
    while(i<N-1)
    {
        
        tmp=countit(&A[i], N-i);
//        printf("countit%d ", tmp);
        if(tmp>=4)
        {
            B[n]=A[i];
            B[n+1]=A[i];
            n+=2;
            i+=tmp;
            continue;
        }
        if(tmp>=2)
        {
            B[n]=A[i];
            n+=1;
            i+=tmp;
            continue;
        }
        i+=tmp;
        
    }
    B[n]=-1;B[n+1]=-1;
//    printf("\nn:%d\n", n);
//    for (i=0;i<n;i++) printf("t%d ", B[i]);
    int j,  count=0, max;
    float maxf;
    i=0;
    while(i<n)
    {
       maxf=X;maxf/=B[i]; max=ceil(maxf);if(B[i+1]<max)return count;
//       printf("max:%d\n", max);
        for(j=i+1;j<n;j++)
        {
            if(B[j]>=max)
            {
 //               printf("i:%d j:%d\n", i,j);
                count++;
                if(B[j]==B[j+1])j++;
            }
            else break;
        
        }
        if(count>1000000000) return-1;
        if(B[i+1]==B[i])i+=2;
        else i++;
    }
    return count;
}

