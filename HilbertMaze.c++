class maze
{
    private:
    int **grid;
    int SIZE;
    int raw[5][5]=   {{0,0,0,0,0}, //[y][x]
                      {0,5,3,5,0},
                      {0,5,3,5,0},
                      {0,5,5,5,0},
                      {0,0,0,0,0}};
                     
    int rotdata[4][6]={{0,1,2,3,4,5},
                       {0,2,1,4,3,5},
                       {0,3,4,1,2,5},
                       {0,4,1,2,3,5}};
   
    public:
    void create(int M);
    void copy(int xs, int ys, int xd, int yd, int size, int rot);
    void print();
    void init();
    void set(int x, int y, int val){grid[y][x]=val;};
    int drawpathtorim(int x, int y);
};

void maze::init()
{
    int x, y, tmp;
    tmp=SIZE-5;
    for(y=0;y<5;y++)
    {
        for(x=0;x<5;x++)
        {
            grid[y+tmp][x+tmp]=raw[y][x];
        }
    }
}

void maze::print()
{
    int x,y;
    for(y=SIZE-1;y>=0;y--)
    {
        for(x=0;x<SIZE;x++)
        {
            switch(grid[y][x])
            {
                case 0: printf("- ");break;
                case 1: printf("^ ");break;
                case 2: printf("> ");break;
                case 3: printf("v ");break;
                case 4: printf("< ");break;
                case 5: printf("# ");break;
                default: printf("S ");break;
            }
        }
        printf("\n");
    }
}

void maze::copy(int xs, int ys, int xd, int yd, int size, int rot)
{
    int x, y;
    int *rows, *rowd;

    switch (rot)
    {
        case 0:
        for(y=0;y<size;y++)
        {
            rows=&grid[ys+y][xs];
            rowd=&grid[yd+y][xd];
            for(x=0;x<size;x++)
            {
                rowd[x]=rows[x];
            }
        }
        return;
        case 1:
        for(y=0;y<size;y++)
        {
            rows=&grid[ys][xs];
            rowd=&grid[yd+size-y][xd];
            for(x=0;x<size;x++)
            {
                grid[yd+y][xd+x]=rotdata[1][grid[ys+x][xs+y]];
            }
        }
        return;
        case 3:
        for(y=0;y<size;y++)
        {
            rows=&grid[ys][xs];
            rowd=&grid[yd+size-y][xd];
            for(x=0;x<size;x++)
            {
                grid[yd+y][xd+(size-1-x)]=rotdata[3][grid[ys+x][xs+y]];
            }
        }
    }
    return;
}

void maze::create (int M)
{
    int i;
    SIZE=M;
    grid=(int **)calloc(M,sizeof(int*));
    for(i = 0; i < M; i++)
    grid[i] = (int*)calloc(M,sizeof(int));
}

int gx, gy;

int maze::drawpathtorim(int x, int y)
{
    int X=x;
    int Y=y;
    int count=10;
    while(1)
    {
        switch(grid[Y][X])
        {
            case 5: //rand erreicht
            grid[Y][X]=count;
            return (-count+10);
            Y--;
            break;
            case 0:
            gx=X;gy=Y;
            grid[Y][X]=count;
            return 0-(count-10);
            case 1:
            grid[Y][X]=count;
            Y++;
            break;
            case 2:
            grid[Y][X]=count;
            X++;
            break;
            case 3:
            grid[Y][X]=count;
            Y--;
            break;  
            case 4:
            grid[Y][X]=count;
            X--;
            break;
             default:
            return (grid[Y][X]+count-20)+1;
        }
        count++;
    }
}

int solution(int N, int A, int B, int C, int D)
{
    class maze MAZE;
    int SIZE=(2<<N)+1;
    int i, j, tmp, ext;
    MAZE.create(SIZE);
    MAZE.init();
    for(i=1;i<N;i++)
    {
        tmp=2<<i;
        ext=(SIZE-1)-2*tmp;
        MAZE.copy(ext+tmp, ext+tmp, ext+0, ext+tmp, tmp+1, 0 ); //vervielfältige Muster
        MAZE.copy(ext+tmp, ext+tmp, ext+0,ext+ 0, tmp+1, 1 ); 
        MAZE.copy(ext+tmp, ext+tmp, ext+tmp, ext+0, tmp+1, 3 );
        MAZE.set(ext+tmp,ext+tmp+1, 5); // setze Extra-Blöcke
        MAZE.set(ext+1,ext+tmp, 5);
        MAZE.set(ext+2*tmp-1,ext+tmp, 5);
        for(j=0;j<tmp-2;j++) //Male Extra-Weg ein
        {
            MAZE.set(ext+tmp, ext+tmp+2+j,1); 
            MAZE.set(ext+tmp+1+j, ext+tmp,4);
            MAZE.set(ext+2+j, ext+tmp,2);
            MAZE.set(ext+tmp, ext+1+j,3);
            MAZE.set(ext+tmp, ext+tmp-j,3);
        }
    }
    int x1,x2,y1,y2;
    int tmp1=MAZE.drawpathtorim(A, B);
    x1=gx;y1=gy;
    int tmp2=MAZE.drawpathtorim(C, D);
    x2=gx;y2=gy;
//    MAZE.print();    
    if(tmp2>0)return tmp2-1;
//    printf("\n%d %d %d %d %d %d", x1, y1, x2, y2, tmp1, tmp2);
    if(abs(x1-x2)==SIZE-1)
    {
        if(y1+y2<=(SIZE-1))return(abs(tmp1)+abs(tmp2)+y1+y2+SIZE-1);
        if(y1+y2>(SIZE-1))return(abs(tmp1)+abs(tmp2)+(SIZE-1-y1) + (SIZE-1-y2)+SIZE-1);
    }
    if(abs(y1-y2)==SIZE-1)
    {
        if(x1+x2<=(SIZE-1))return(abs(tmp1)+abs(tmp2)+x1+x2+SIZE-1);
        if(x1+x2>(SIZE-1))return(abs(tmp1)+abs(tmp2)+(SIZE-1-x1)+(SIZE-1-x2)+SIZE-1);
    }
    return(abs(x1-x2)+abs(y1-y2)+abs(tmp1)+abs(tmp2));
    return(0);
}
