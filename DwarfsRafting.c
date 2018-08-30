

#include<string.h>



int solution(int N, char *S, char *T) 
{
    
    char *C;
    int n=N/2;
    int vol=n*n;
    int space[2][2]={{vol, vol},{vol, vol}};
    int weight[2][2]={{0,0},{0,0}};
    int x, y, l, dwarfcount=0;
    C = strtok (S," ");
    while (C != NULL) //zähle Fässer;
    {
        l=strlen(C);
        x=C[l-1]-64;
        y=atoi(&C[0]);
        if(x<=n)
        {
            if(y<=n) space[0][0]--;
            else space [1][0]--;
        }
        else
        {
            if(y<=n) space[0][1]--;
            else space [1][1]--;
            
        }
//        printf ("x:%d y:%d\n",x,y);
        C = strtok (NULL, " ");
    }
    C = strtok (T," ");
    while (C != NULL) //zähle Zwerge
    {
//        dwarfcount++;
        l=strlen(C);
        x=C[l-1]-64;
        y=atoi(&C[0]);
        if(x<=n)
        {
            if(y<=n) {space[0][0]--; weight[0][0]++;}
            else {space [1][0]--; weight[1][0]++;}
        }
        else
        {
            if(y<=n) {space[0][1]--;weight[0][1]++;}
            else {space [1][1]--; weight[1][1]++;}
            
        }
        
//        printf ("x:%d y:%d\n",x,y);
        C = strtok (NULL, " ");
    }
    int diff=weight[0][0]-weight[1][1];
//    printf("%d", diff);
    if(diff)
    {
        if(diff>0)
        {
            if(space[1][1]-diff>=0)
            {
                dwarfcount+=diff;
                space[1][1]-=diff;
                weight[1][1]=weight[0][0];
            }
            else return -1;
        }
        else
        {
            if(space[0][0]+diff>=0)
            {
                dwarfcount-=diff;
                space[0][0]+=diff;
                weight[0][0]=weight[1][1];
            }
        else return -1;
            
        }
    }
    diff=weight[1][0]-weight[0][1];
    if(diff)
    {
        if(diff>0)
        {
            if(space[0][1]-diff>=0)
            {
                dwarfcount+=diff;
                space[0][1]-=diff;
                weight[0][1]=weight[1][0];
            }
            else return -1;
        }
        else
        {
            if(space[1][0]+diff>=0)
            {
                dwarfcount-=diff;
                space[1][0]+=diff;
                weight[1][0]=weight[0][1];
            }
        else return -1;
            
        }
    }
    dwarfcount+=(space[1][1]<space[0][0]?space[1][1]:space[0][0])*2;
    dwarfcount+=(space[0][1]<space[1][0]?space[0][1]:space[1][0])*2;
    return dwarfcount;

    
}

