#include<iostream>
#include<stdexcept>

using std::cin;
using std::cout;
using std::endl;
using std::invalid_argument;
int main()
{
	int iPrior,iEnd;
	try {	
		cin >> iPrior >> iEnd;
		if(!iEnd){
			cout<<234<<endl;
			throw invalid_argument("123");
		}
		cout << iPrior / iEnd << endl;
	
	}catch(invalid_argument err)
	{
		cout<<err.what()<<endl;
		cout<<"exception handle"<<endl;
	}
	return 0;
}