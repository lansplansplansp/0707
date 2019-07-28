//returns an iterator to the first element greater
//than a certain value
#include <iostream>
#include <set>
#include <iomanip>
#include <string>
    #include <map>
    #include <ctime>
#include <fstream>

using namespace std;
template <class T>
class Member
{
public:
     Member(T l) : last(l), first("") {} // for upper_bound
     // and lower_bound
     Member(T l, T f) : last(l), first(f) {}
     void print() const // const !!!
     {
          cout.setf(ios::left);
          cout << setw(15) << first.c_str()
          << last << endl;
     }
private:
      T first, last;
      // const !!!
      friend bool operator < (const Member& m1, const Member& m2)
      {
        return (m1.last < m2.last) ? true : false;
      }
      friend bool operator == (const Member& m1, const Member& m2)
      {
        return (m1.last == m2.last) ? true : false;
      }
 };
 //===============================================
unsigned long int gener_rand()
{
     unsigned long int random =
     (unsigned long int)
     (10000.0 * rand() /
     (RAND_MAX + 1.0 )) % 10;
     return random;
}
//-----------------------------------

 int main ()
 {
      typedef Member<string> M;
      typedef set<M, less<M> > S;
      S s;
      s.insert(M("Smith","John"));
      s.insert(M("Shevchenko","Taras"));
      s.insert(M("Amstrong","Bill"));
      s.insert(M("Bain","Linda"));
      s.insert(M("Pushkin","Alexander"));
      s.insert(M("Pasternak","Biris"));
      S::iterator It = s.begin();
      while ( It != s.end() )
        (It++)->print();
      cout << endl;
      M m1("P");
      M m2("Pzz");

      S::iterator low = s.lower_bound(m1);
      S::iterator upp = s.upper_bound(m2);
      It = low;
      while ( It != upp )
        (It++)->print();
      return 0;
//      unsigned long int ary[100];
//      typedef map<int, unsigned long int> M;
//      M m;
//      // initialize all values to 0
//      for ( int i=0; i<10; i++ )
//         m[i] = 0;
//      srand(time(0));
//      // initialize ary[] with random values
//      for ( int i=0; i<100; i++ )
//         ary[i] = gener_rand();
//      for ( int i=0; i<100; i++ )
//      {
//          if ( i % 10 == 0 && i != 0 )
//          cout << endl;
//          cout << ary[i] << " ";
//          // generate freaquances
//          m[ary[i]] += 1;
//      }
//      cout << endl << endl;
//      M::iterator It = m.begin();
//      while ( It != m.end() )
//      {
//          cout << "number " << (*It).first << " occurred " << (*It).second << " time(s)" << endl;
//          It++;
//      }
//      cout << endl;
//      m[12] = 123;//这又是啥意思
//      m[15] = 234;
//      m[18] = 345;
//      It = m.lower_bound(11);
//      cout << "lower_bound(11) = " << (*It).first << endl;
//      It = m.upper_bound(11);
//      cout << "upper_bound(11) = " << (*It).first << endl;
//      return 0;
 }
