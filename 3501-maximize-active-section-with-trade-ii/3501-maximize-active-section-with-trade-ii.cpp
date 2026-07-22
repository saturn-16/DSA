#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Item { int val, pos; };
struct Top3 { Item it[3]; int cnt; };

static inline Top3 emptyTop3(){ Top3 t; t.cnt=0; return t; }

// Fast merge: inputs are already sorted (desired order), each size <= 3.
// Manual pointer-merge, no std::sort, no lambda overhead.
static inline Top3 mergeTop(const Top3&a, const Top3&b, bool wantMax){
    Top3 res; res.cnt=0;
    int ia=0, ib=0;
    while(res.cnt<3 && (ia<a.cnt || ib<b.cnt)){
        bool takeA;
        if(ia>=a.cnt) takeA=false;
        else if(ib>=b.cnt) takeA=true;
        else if(wantMax) takeA = a.it[ia].val >= b.it[ib].val;
        else             takeA = a.it[ia].val <= b.it[ib].val;
        Item cand = takeA ? a.it[ia++] : b.it[ib++];
        bool dup=false;
        for(int i=0;i<res.cnt;i++) if(res.it[i].pos==cand.pos){ dup=true; break; }
        if(!dup) res.it[res.cnt++]=cand;
    }
    return res;
}

class Solution {
public:
    int n, K, LOG;
    vector<int> btype,bstart,bend,blen,blockOf,logt;
    vector<ll> pre;
    vector<int> gArr;
    vector<vector<int>> stG;
    vector<vector<Top3>> stZero, stOne;

    int queryG(int l,int r){
        if(l>r) return INT_MIN;
        int k=logt[r-l+1];
        return max(stG[k][l], stG[k][r-(1<<k)+1]);
    }
    Top3 queryZero(int l,int r){
        if(l>r) return emptyTop3();
        int k=logt[r-l+1];
        return mergeTop(stZero[k][l], stZero[k][r-(1<<k)+1], true);
    }
    Top3 queryOne(int l,int r){
        if(l>r) return emptyTop3();
        int k=logt[r-l+1];
        return mergeTop(stOne[k][l], stOne[k][r-(1<<k)+1], false);
    }

    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        n=s.size();
        blockOf.assign(n,0);
        int i=0;
        while(i<n){
            int j=i;
            while(j<n && s[j]==s[i]) j++;
            btype.push_back(s[i]-'0');
            bstart.push_back(i);
            bend.push_back(j-1);
            blen.push_back(j-i);
            for(int t=i;t<j;t++) blockOf[t]=(int)btype.size()-1;
            i=j;
        }
        K=(int)btype.size();
        pre.assign(n+1,0);
        for(int t=0;t<n;t++) pre[t+1]=pre[t]+(s[t]-'0');
        ll totalOnes = pre[n];

        gArr.assign(K, INT_MIN);
        for(int idx=1; idx<K-1; idx++)
            if(btype[idx]==1) gArr[idx]=blen[idx-1]+blen[idx+1];

        int maxN=max(K,2);
        logt.assign(maxN+1,0);
        for(int t=2;t<=maxN;t++) logt[t]=logt[t/2]+1;
        LOG = (K>0? logt[K]+1 : 1);

        stG.assign(LOG, vector<int>(max(K,1), INT_MIN));
        stZero.assign(LOG, vector<Top3>(max(K,1), emptyTop3()));
        stOne.assign(LOG, vector<Top3>(max(K,1), emptyTop3()));

        for(int t=0;t<K;t++){
            stG[0][t]=gArr[t];
            Top3 z; z.cnt=0;
            if(btype[t]==0){ z.it[0]={blen[t], t}; z.cnt=1; }
            stZero[0][t]=z;
            Top3 o; o.cnt=0;
            if(btype[t]==1){ o.it[0]={blen[t], t}; o.cnt=1; }
            stOne[0][t]=o;
        }
        for(int k=1;k<LOG;k++){
            int half=1<<(k-1);
            for(int t=0; t+(1<<k)<=K; t++){
                stG[k][t]=max(stG[k-1][t], stG[k-1][t+half]);
                stZero[k][t]=mergeTop(stZero[k-1][t], stZero[k-1][t+half], true);
                stOne[k][t]=mergeTop(stOne[k-1][t], stOne[k-1][t+half], false);
            }
        }

        vector<int> ans;
        ans.reserve(queries.size());
        for(auto& q: queries){
            int l=q[0], r=q[1];
            int p=blockOf[l], qq=blockOf[r];
            if(p==qq){ ans.push_back((int)totalOnes); continue; }

            ll caseA = LLONG_MIN;
            int diff=qq-p;
            if(diff==2){
                int mid=p+1;
                if(btype[mid]==1){
                    ll clipL=bend[p]-l+1;
                    ll clipR=r-bstart[qq]+1;
                    caseA=clipL+clipR;
                }
            } else if(diff>=3){
                if(btype[p+1]==1){
                    ll clipL=bend[p]-l+1;
                    ll rightLen=blen[p+2];
                    caseA=max(caseA, clipL+rightLen);
                }
                if(btype[qq-1]==1){
                    ll leftLen=blen[qq-2];
                    ll clipR=r-bstart[qq]+1;
                    caseA=max(caseA, leftLen+clipR);
                }
                if(diff>=4){
                    int rmq=queryG(p+2, qq-2);
                    if(rmq!=INT_MIN) caseA=max(caseA,(ll)rmq);
                }
            }

            int rangeL=p+1, rangeR=qq-1;
            Top3 zeros = queryZero(rangeL, rangeR);
            Top3 ones  = queryOne(rangeL, rangeR);

            Item zcand[5]; int zc=0;
            for(int t=0;t<zeros.cnt;t++) zcand[zc++]=zeros.it[t];
            if(btype[p]==0)  zcand[zc++]={ (int)(bend[p]-l+1), p };
            if(btype[qq]==0) zcand[zc++]={ (int)(r-bstart[qq]+1), qq };

            ll caseB = LLONG_MIN;
            for(int a=0;a<zc;a++)
                for(int b=0;b<ones.cnt;b++)
                    if(abs(zcand[a].pos - ones.it[b].pos)!=1)
                        caseB = max(caseB, (ll)zcand[a].val - ones.it[b].val);

            ll gain = max((ll)0, max(caseA, caseB));
            ans.push_back((int)(totalOnes+gain));
        }
        return ans;
    }
};