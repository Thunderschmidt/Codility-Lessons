#include<string.h>
int solution(int K, int C[], int N, int D[], int M) 

{
    int ccount=0, dcount=0, tmp;
    int csocks[51], dsocks[51], i;
    memset(csocks, 0x00, sizeof(int)*51);
    memset(dsocks, 0x00, sizeof(int)*51);
    for(i=0;i<N;i++)csocks[C[i]]++;
    for(i=0;i<M;i++)dsocks[D[i]]++;

    for(i=1;i<51;i++) //zähle saubere paare
    {
        if(csocks[i]>=2)
        {
            tmp=csocks[i]-csocks[i]%2;
            csocks[i]=-tmp;
            ccount+=tmp;
        }
    }
    if(K==0)return ccount/2;
    for(i=0;i<51;i++) //zähle saubere/schmutzige paare
    {
        if(csocks[i]&&dsocks[i])
        { 
            dsocks[i]--;
            ccount+=2;
            dcount++;
            if(dcount==K)return ccount/2;
            
        }
    }
    for(i=1;i<51;i++) //zähle schmutzige paare
    {
        if(dsocks[i]>=2)
        {
            tmp=dsocks[i]-dsocks[i]%2;
            if(dcount+tmp<=K)
            {
                ccount+=tmp;
                dcount+=tmp;
            }
            else return (ccount+K-dcount)/2;
        }
    }
    return ccount/2;
}

