#include<bits/stdc++.h>
using namespace std;
struct item
{
    int d1,d2,d3,d4;
};
int n,m;
int best_cost=INT_MAX;
void dfs(int idx,vector<item> list_of_items,vector<item> rem_bincapacity,int cost)
{
    if(cost >= best_cost) return;
    if(idx >= list_of_items.size())
    {
        best_cost=min(best_cost,cost);
        return;
    }
    auto check=[](item a,item b){
        return (a.d1>=b.d1 && a.d2>=b.d2 && a.d3>=b.d3 &&a.d4>=b.d4 );
    };
    auto sub=[](item &a,item b)
    {
        a.d1-=b.d1;
        a.d2-=b.d2;
        a.d3-=b.d3;
        a.d4-=b.d4;

    };
    auto add=[](item &a,item b)
    {
        a.d1+=b.d1;
        a.d2+=b.d2;
        a.d3+=b.d3;
        a.d4+=b.d4;

    };
    item cur = list_of_items[idx];
    for(int i=0;i<rem_bincapacity.size();i++)
    {
       
        if(check(rem_bincapacity[i],cur)) 
        {
             sub(rem_bincapacity[i],cur);
             dfs(idx+1,list_of_items,rem_bincapacity,cost);
              add(rem_bincapacity[i],cur);
        }
    }

    rem_bincapacity.push_back({m,m,m,m});
    int sz = rem_bincapacity.size()-1;
    
    if(check(rem_bincapacity[sz],cur)) 
    {
        sub(rem_bincapacity[sz],cur);
        dfs(idx+1,list_of_items,rem_bincapacity,cost+1);
    }
    
    return;
    
}
int main()
{
    vector<item> list_of_items;
    cin>>n>>m;
    for(int i=0;i<n;i++)
    {
        int p,q,r,s;
        cin>>p>>q>>r>>s;
        list_of_items.push_back({p,q,r,s});
    }
    vector<item> rem_bincapacity;
    dfs(0,list_of_items,rem_bincapacity,0);
    
    cout<<"Minimum no of bins is : "<<best_cost;
}