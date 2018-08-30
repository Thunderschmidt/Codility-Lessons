

#include <vector>
#include<math.h>
#include<limits.h>
#include<string>

class platf
{
    public:
    std::vector<int> p;
    std::vector<int> b;
};

class brid
{
    public:
    std::vector<int> nxtBridge[2];
    int count[2];
    int plat[2]; //welches ist die angrenzende platform?
    int rekursor(class platf &platform, int bridgenr);
};

int RekCount(class platf *platform, class brid *bridge, int actbridge, int lastbridge, int dir, int lastplat, int N)
{
    int i;
    bridge[actbridge].count[dir]=1;
    int p=bridge[actbridge].plat[0]==lastplat?bridge[actbridge].plat[1]:bridge[actbridge].plat[0];
    //p ist die platform, die nicht die letzte ist. Die, über die sich der Baum forsezen soll
    int n=platform[p].p.size();
//    cout <<"actbridge:"<<actbridge<<  " p:"<<p<<" lastplat: "<<lastplat<<" verzw.plat.:" <<n<<"\n";
    for(i=0;i<n;i++)
    {
        if(platform[p].p[i]!=lastplat)
        {
//            cout << "->"<<platform[p].p[i]<<" ";
            bridge[actbridge].count[dir]+=RekCount(platform, bridge, platform[p].b[i], actbridge, dir, p, N);
        }
       
    }
//    cout << "<-\n";
    bridge[actbridge].count[1-dir]=N-bridge[actbridge].count[dir];
    return(bridge[actbridge].count[dir]);
}


string solution(vector<int> &A, vector<int> &B)
{
    int i, dir;
    int N=A.size();
    if (N==1)return "2";
    if (N==2)return "3";
    class platf platform[N+1];
    class brid bridge[N];
    for(i=0;i<N;i++) //übertrage daten an Klasse platform
    {
        platform[A[i]].p.push_back(B[i]);
        platform[A[i]].b.push_back(i);
        platform[B[i]].p.push_back(A[i]);
        platform[B[i]].b.push_back(i);
        bridge[i].plat[0]=A[i];
        bridge[i].plat[1]=B[i];
    }
    RekCount(platform, bridge, 0, 0, 0, bridge[0].plat[1], N+1);
    RekCount(platform, bridge, 0, 0, 1, bridge[0].plat[0], N+1);
//    for(i=0;i<N;i++) cout << "bridge nr.:" <<i<<": " << bridge[i].count[1] <<"-"<< bridge[i].count[0] << "\n";
    float tmp, ideal, min;
    int br0, br1;
    long long int tm, max=N+1;
    ideal=N+1;ideal/=2;
    min=INT_MAX;
    for(i=0;i<N;i++) //Brücke für nur eine Teilung finden
    {
        tmp=bridge[i].count[0]; tmp-=ideal;tmp=abs(tmp);
        if(tmp<min)
        {
            min=tmp;
            br0=i;
        }
        tmp=bridge[i].count[1]; tmp-=ideal;tmp=abs(tmp);
        if(tmp<min)
        {
            min=tmp;
            br0=i;
        }
    }
//    cout <<"mitteldurchtrennende: "<<br0 <<"\n\n";
    tm=bridge[br0].count[0]*bridge[br0].count[1];
    if(tm>max) max=tm;    
    ideal=N+1;ideal/=3;
    min=INT_MAX;
    for(i=0;i<N;i++) //erste Brücke für zwei Teilungen finden
    {
        tmp=bridge[i].count[0]; tmp-=ideal;tmp=abs(tmp);
        if(tmp<min)
        {
            min=tmp;
            br0=i;
            dir=0;
        }
        tmp=bridge[i].count[1]; tmp-=ideal;tmp=abs(tmp);
        if(tmp<min)
        {
            min=tmp;
            br0=i;
            dir=1;
        }
    }
//    cout <<"erste drittelnde: "<<br0 <<"\n\n";
    int n=bridge[br0].count[1-dir]; //n=größe des neuen subtrees
//    cout <<"n: "<<n<<"\n";
//    cout <<" size zuerst "<<platform[bridge[br0].plat[1-dir]].p.size();
    for (i=0;i<platform[bridge[br0].plat[1-dir]].p.size();i++) //verbindung zur br. löschen
    {
        if(platform[bridge[br0].plat[1-dir]].b[i]==br0)
        {
            platform[bridge[br0].plat[1-dir]].p.erase(platform[bridge[br0].plat[1-dir]].p.begin()+i);
            platform[bridge[br0].plat[1-dir]].b.erase(platform[bridge[br0].plat[1-dir]].b.begin()+i);
            break;
        }
    }
//        cout <<" size danach "<<platform[bridge[br0].plat[1-dir]].p.size();
    int newstartbr=platform[bridge[br0].plat[1-dir]].b[0];
//    cout <<"\n"<<"br0: "<<br0<<" newstartbr:"<<newstartbr<<"\n";
    for(i=0;i<N;i++) //Brückenzähler zurücksetzen
    {
       bridge[i].count[0]=-1;
       bridge[i].count[1]=-1;
    }
    RekCount(platform, bridge, newstartbr, br0, 1, bridge[newstartbr].plat[1], n);
    RekCount(platform, bridge, newstartbr, br0, 0, bridge[newstartbr].plat[0], n);
//    for(i=0;i<N;i++) cout << "bridge nr.:" <<i<<": " << bridge[i].count[1] <<"-"<< bridge[i].count[0] << "\n";
    ideal=n;ideal/=2;
    min=INT_MAX;
    for(i=0;i<N;i++) //Brücke für die zweite Teilung finden 
    {
        tmp=bridge[i].count[0];
        if(tmp<0)continue;
        tmp-=ideal;tmp=abs(tmp);
        if(tmp<min)
        {
            min=tmp;
            br1=i;
        }
        tmp=bridge[i].count[1]; tmp-=ideal;tmp=abs(tmp);
        if(tmp<min)
        {
            min=tmp;
            br1=i;
        }
    }
//    cout <<"zweite drittelnde: "<<br1 <<"\n\n";
    tm=bridge[br1].count[1]*bridge[br1].count[0]*(N-n+1);
    if(tm>max) max=tm;    
//    cout <<"br0: "<<br0<<" br1: "<<br1<<"\n";
    std::string s = std::to_string(max);
    return(s);
}

