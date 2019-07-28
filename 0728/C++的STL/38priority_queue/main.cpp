// Priority Queues are like queues, but the
// elements inside the data structure are
// ordered by some predicate.
//all priority_queue functions
#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;
int main ()
{
     priority_queue<int, vector<int>, less<int> > ipq;
     ipq.push(100);
     ipq.push(200);
     ipq.push(300);
     cout << "size of priority_queue ipq = "
     << ipq.size() << endl;
     cout << "ipq <int,vector<int>, less<int> > = ";
     while ( !ipq.empty() )
     {
         cout << ipq.top() << " ";//²»ÊÇÏÈ100Âð£¿£¿£¿
         ipq.pop();
     }
     cout << endl << endl;
     cout << "priority_queue<string,vector<string> > spq;"
     << endl;
     priority_queue<string,vector<string> > spq;
     for ( int i=1; i<10; i++ )
        spq.push(string(i,'*'));
     while ( !spq.empty() )
     {
         cout << spq.top() << endl;
         spq.pop();
     }
     return 0;
 }
