
int solution(int X[], int Y[], int N) 
{
    int t, l, r, b, count=0;
    for(t=0;t<N;t++)
    {
        if(X[t]==0||X[t]==N-1||Y[t]<2) continue;
        for(b=0;b<N;b++)
        {
            if(X[b]!=X[t]||(Y[t]-Y[b])<2) continue;
            for(l=0;l<N;l++)
            {
                if( X[l]>=X[t] || ((Y[t]-Y[l])!=(Y[l]-Y[b])))continue;
                for(r=0;r<N;r++)
                {
                    if(Y[r]!=Y[l] || (X[r]-X[t]!=X[t]-X[l])) continue;
                    count++;
                }
            }
        }
    }
    return count;
}