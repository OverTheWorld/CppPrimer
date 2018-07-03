#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::istream_iterator;
using std::ostream_iterator;

int main()
{
	istream_iterator<int> in(ref(cin)),eof;
	ostream_iterator<int> out(ref(cout)," ");
	vector<int> vecInt;
	auto bIter = back_inserter(vecInt);
	copy(in,eof,bIter);
	sort(vecInt.begin(),vecInt.end(),[](int a,int b){return a>=b;});
	for_each(vecInt.cbegin(),vecInt.cend(),[&](int num){*out = num;});
	cout<<endl;
}