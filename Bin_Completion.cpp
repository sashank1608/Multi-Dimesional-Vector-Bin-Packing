#include<bits/stdc++.h>
using namespace std;
struct item
{
    int d1,d2,d3,d4;
     bool operator<(const item& b) const
    {
        return (d1<b.d1&& d2<b.d2 && d3<b.d3 && d4<b.d4);

    }
    bool operator=(const item& b) const
    {
         return (d1==b.d1&& d2==b.d2 && d3==b.d3 && d4==b.d4);
    }
     item operator-(const item& b) const
     {
         item res;
         res.d1= d1-b.d1;
         res.d2= d2-b.d2;
         res.d3= d3-b.d3;
         res.d4= d4-b.d4;
         return res;

     }
     item operator+(const item& b) const
     {
         item res;
         res.d1= d1+b.d1;
         res.d2= d2+b.d2;
         res.d3= d3+b.d3;
         res.d4= d4+b.d4;
         return res;

     }
};
int n,m;
int best_cost=INT_MAX;

bool test(vector<item> I,vector<item> E,item common)
{
    
    item residual = {m-common.d1,m-common.d2,m-common.d3,m-common.d4};
    item total_sum={0,0,0,0};
    for(int i=0;i<I.size();i++)
    {
        total_sum=total_sum+I[i];
    }
    int sz= I.size();
    //iterate all subset sums
    for(int i=0;i<(1<<sz);i++)
    {
        item subset_sum={0,0,0,0};
        for(int j=0;j<sz;j++)
        {
            if((i>>j) & 1) subset_sum+=I[j];
        }
        // iterate all excluded nos
        for(int k=0;k<E.size();k++)
        {
           // assert((E[k]-subset_sum)>(residual-total_sum) && (residual-total_sum)< (E[k]-subset_sum));
            if((E[k]-subset_sum)<(residual-total_sum) && (residual-total_sum)> (E[k]-subset_sum))
            {
                //replce the dominated value
                I[i]=E[k];
            }
        }
    }
}
void Feasible(vector<item> I,vector<item> E,set<item> R,item l,item u,vector<vector<item>> &usets,item common){
    if(R.size() == 0 || u==0)
    {
        if(test(I,E,common)) usets.push_back(I);
    }
    else
    {
        item x = R[0];
        if(x > u) {
            R.erase(x);
            Feasible(I,E,R,l,u)
        }
        else if(x == u)
        {
            I.push_back(x);
            R.erase(x);
            Feasible(I,E,R,l-x,u-x)
        }
        else if(x < u) {
        R.erase(x);
        I.push_back(x);
        Feasible(I ,E,R,l-x,u-x);
        E.push_back(x);
        I.pop_back();
        x.d1+=1;
        x.d2+=1;
        x.d3+=1;
        x.d4+=1;
        //find max based on max dimensional value
        auto max_on_dim(item a,item b)(){
            int m1=max(a.d1,max(a.d2,max(a.d3,a.d4)));
            int m2=max(b.d1,max(b.d2,max(b.d3,b.d4)));
            if(m1>m2) return a;
            else return b;

        };
        // if l = (4,6) then (4,0) would be accepted, as it is sufficient to meet the lower bound in one dimension
        Feasible(I ,E ,R,max_on_dim(l,x+1),u)

        }
    }

}
void add_newgood_sets(vector<vector<int>> &nogood,vector<vector<int>> temp,vector<int> items)
{
    item item_sum={0,0,0,0};
    for(int i=0;i<items.size();i++)
    {
        item_sum+=list_of_items[items[i]];
    }
    for(int i=0;i<temp.size();i++)
    {
        item temp_sum={0,0,0,0};
        for(int j=0;j<temp[i].size();i++)
        {
            temp_sum+=list_of_items[temp[i][j]];
        }
        if(temp_sum > item_sum) nogood.push_back(temp[i]);
    }
    

}
bool nogood_pruning(vector<vector<int>> nogood,set<int>  items)
{
    
    for(int i=0;i<nogood.size();i++)
    {
        int flag=1;
        for(int j=0;j<nogood[i].size();j++)
        {
            if(items.find(nogood[i][j])==items.end()) flag=0; 
        }
        if(flag) return 1;
    }
    return 0;
}
void bin_completion(int idx,vector<item> list_of_items,int cost,vector<vector<int>> nogood,int mask)
{
    if(idx==n) best_cost=min(cost,best_cost);
    if(mask & (1<<idx)==1 && idx<n)
    {
        bin_completion(idx+!,list_of_items,cost,nogood,mask);
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
    /*********** generate undominated sets ***********/
    vector<vector<item>> usets;
    vector<item> included,excluded,remaining;
    for(int i=0;i<(1<<mask);i++)
    {
        if(mask & (1<<i))
        remaining.push_back(list_of_items[i]);
    }
    
    Feasible(included,excluded,remaining,{0,0,0,0},{m-cur.d1,m-cur.d2,m-cur.d3,m-cur.d4},usets,cur);
    /********************************************/
   vector<vector<int>> temporary_list;
    for(int i=0;i<usets.size();i++)
    {
        item item_sum={0,0,0,0};
        vector<vector<int>> new_good=good;
        //add subsets from temporary_list whose vector sum  > usets[i] in all dimensions 
        add_newgood_sets(new_good,temporary_list,usets[i]);
        int new_mask=mask;
         for(int j=0;j<usets[i].size();j++)
         {
             new_mask|=(1<<usets[i][j]);
             item_sum+=list_of_items[usets[i][j]];
             
         }
         // prune  if there exists a set in new_good whic is subset of our packing usets[i]
         if(!nogood_pruning(new_good,usets[i]))
         bin_completion(idx+1,list_of_items,cost+1,new_good,mask)
         temporary_list.push_back(usets[i]);
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
    vector<item> nogood;
    
    bin_completion(0,list_of_items,rem_bincapacity,0,nogood,0);
    
    cout<<"Minimum no of bins is : "<<best_cost;
}