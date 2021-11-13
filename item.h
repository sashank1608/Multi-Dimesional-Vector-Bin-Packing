#ifndef ITEM_H
#define ITEM_H

using namespace std;

struct item {
    double d1,d2,d3,d4;
    int id;
};


bool comp(item i1, item i2) {
    return i1.d1 > i2.d1 && i1.d2 > i2.d2 && i1.d3 > i2.d3 && i1.d4 > i2.d4 ;
}
bool less_than(item a,item b)
{
 return (a.d1<b.d1 && a.d2<b.d2 && a.d3<b.d3 && a.d4<b.d4)
}
item sub(item a,item b)
{
     return {a.d1-b.d1 , a.d2-b.d2 , a.d3-b.d3 , a.d4-b.d4,0};
}
item add(item a,item b)
{
     return {a.d1+b.d1 , a.d2+b.d2 , a.d3+b.d3 , a.d4+b.d4};
}

#endif // ITEM_H