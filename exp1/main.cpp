#include "SimSearcher.h"
#include <iostream>
using namespace std;
int main()
{
SimSearcher searcher;
vector<pair<unsigned, unsigned> > resultED;
vector<pair<unsigned, double> > resultJaccard;
unsigned q = 3, edThreshold = 1;
double jaccardThreshold = 0.75;
cout << "build index:" << searcher.createIndex("test", q)<<endl;;
searcher.searchJaccard("hello world", jaccardThreshold, resultJaccard);
cout << "jaccard result" << endl;
for (unsigned i = 0; i < resultJaccard.size(); i++)
cout << resultJaccard[i].first << " " << resultJaccard[i].second << endl;
searcher.searchED("a", edThreshold, resultED);
cout << "ed result" << endl;
for (unsigned i = 0; i < resultED.size(); i++)
cout << resultED[i].first << " " << resultED[i].second << endl;
q = 2; edThreshold = 2;
cout << "build index:" << searcher.createIndex("test", q)<<endl;;
resultJaccard.clear();
searcher.searchJaccard("qrewre", jaccardThreshold, resultJaccard);
cout << "jaccard result" << endl;
for (int i = 0; i < resultJaccard.size(); i++)
cout << resultJaccard[i].first << " " << resultJaccard[i].second << endl;
resultED.clear();
searcher.searchED("Tom Hank", edThreshold, resultED);
cout << "ed result" << endl;
for (int i = 0; i < resultED.size(); i++)
cout << resultED[i].first << " " << resultED[i].second << endl;
return 0;
}

