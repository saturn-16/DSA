class Solution {
public:
    int A,B,C,D,LB,LC,LD;
    vector<int> cost;
    int ct[10][4] = {{0,0,0,0},{0,0,0,0},{1,0,0,0},{0,1,0,0},{2,0,0,0},
                      {0,0,1,0},{1,1,0,0},{0,0,0,1},{3,0,0,0},{0,2,0,0}};
    inline int idx(int a,int b,int c,int d){ return ((a*LB+b)*LC+c)*LD+d; }

    string smallestNumber(string num, long long t) {
        A=B=C=D=0;
        while(t%2==0){t/=2;A++;}
        while(t%3==0){t/=3;B++;}
        while(t%5==0){t/=5;C++;}
        while(t%7==0){t/=7;D++;}
        if(t!=1) return "-1";

        LB=B+1; LC=C+1; LD=D+1;
        const int INF=1e6;
        cost.assign((A+1)*LB*LC*LD, INF);
        cost[idx(0,0,0,0)]=0;
        for(int a=0;a<=A;a++)for(int b=0;b<=B;b++)for(int c=0;c<=C;c++)for(int d=0;d<=D;d++){
            if(!a&&!b&&!c&&!d) continue;
            int best=INF;
            for(int g=2; g<=9; g++){
                int v=1+cost[idx(max(0,a-ct[g][0]),max(0,b-ct[g][1]),max(0,c-ct[g][2]),max(0,d-ct[g][3]))];
                best=min(best,v);
            }
            cost[idx(a,b,c,d)]=best;
        }

        int n=num.size();
        vector<array<int,4>> pre(n+1,{0,0,0,0});
        for(int i=0;i<n;i++){
            int g=num[i]-'0';
            pre[i+1]={min(A,pre[i][0]+ct[g][0]),min(B,pre[i][1]+ct[g][1]),
                      min(C,pre[i][2]+ct[g][2]),min(D,pre[i][3]+ct[g][3])};
        }

        bool zf = num.find('0')==string::npos;
        if(zf && pre[n][0]==A&&pre[n][1]==B&&pre[n][2]==C&&pre[n][3]==D) return num;

        auto fill=[&](int ra,int rb,int rc,int rd,int slots){
            string s;
            for(int k=0;k<slots;k++)
                for(int g=1;g<=9;g++){
                    int na=max(0,ra-ct[g][0]),nb=max(0,rb-ct[g][1]),nc=max(0,rc-ct[g][2]),nd=max(0,rd-ct[g][3]);
                    if(cost[idx(na,nb,nc,nd)]<=slots-k-1){ s+=char('0'+g); ra=na;rb=nb;rc=nc;rd=nd; break; }
                }
            return s;
        };

        size_t z=num.find('0');
        int maxI = (z==string::npos)? n-1 : (int)z;
        for(int i=maxI;i>=0;i--){
            int base=num[i]-'0';
            for(int v=base+1; v<=9; v++){
                int na=min(A,pre[i][0]+ct[v][0]),nb=min(B,pre[i][1]+ct[v][1]);
                int nc=min(C,pre[i][2]+ct[v][2]),nd=min(D,pre[i][3]+ct[v][3]);
                int ra=A-na,rb=B-nb,rc=C-nc,rd=D-nd, slots=n-1-i;
                if(cost[idx(ra,rb,rc,rd)]<=slots)
                    return num.substr(0,i)+char('0'+v)+fill(ra,rb,rc,rd,slots);
            }
        }

        int L=max(n+1, cost[idx(A,B,C,D)]);
        return fill(A,B,C,D,L);
    }
};