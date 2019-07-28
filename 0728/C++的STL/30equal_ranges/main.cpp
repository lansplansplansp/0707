//returns iterators to the first and last elements that
//match a certain key
#include <iostream>
#include <set>
    //#include <map>
    #include <map>
using namespace std;
void print (multiset<int, less<int> >& s)
{
    multiset<int, less<int> >::iterator It;
    for ( It = s.begin(); It != s.end(); It++ )
    cout << *It << " ";
    cout << endl;
}
//--------------------------------------------
int main ()
{
//     set<int> c;//…∂“‚Àº
//     c.insert(1);
//     c.insert(2);
//     c.insert(4);
//     c.insert(10);
//     c.insert(11);
//     cout << "lower_bound(3): "
//     << *c.lower_bound(3) << endl;
//     cout << "upper_bound(3): "
//     << *c.upper_bound(3) << endl;
//     cout << "equal_range(3): "
//     << *c.equal_range(3).first << " "
//     << *c.equal_range(3).second << endl;
//     cout << endl;

//     cout << "lower_bound(5): "
//     << *c.lower_bound(5) << endl;
//     cout << "upper_bound(5): "
//     << *c.upper_bound(5) << endl;
//     cout << "equal_range(5): "
//     << *c.equal_range(5).first << " "
//     << *c.equal_range(5).second << endl;
//     cin.get();
//     return 0;
      int ary[] = {1,2,3,2,3,4,8,2,5,6};
      multiset<int, less<int> > s;
      s.insert(ary,ary+10);
      print(s);
      // erase all '2'
      s.erase(2);
      print(s);
      multiset<int, less<int> >::iterator It;
      It = s.find(5);
      // erase '5'
      s.erase(It);
      print(s);
      It = s.find(4);
      // erase from It to the end of multiset
      s.erase(It,s.end());
      print(s);
      return 0;
}
