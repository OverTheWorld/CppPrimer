#include<iostream>
#include<vector>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
int main()
{
	vector<int> vi;
	cout<<"size:"<<vi.size()<<"  "
	<<"capacity:"<<vi.capacity()<<endl;
	
	for(int i = 0;i<13;++i)
	{
		vi.push_back(i);
		cout<<"size:"<<vi.size()<<"  "
		<<"capacity:"<<vi.capacity()<<endl;
	}
		
	
	cout<<"size:"<<vi.size()<<"  "
	<<"capacity:"<<vi.capacity()<<endl;
	
	vi.reserve(50);
	
	cout<<"size:"<<vi.size()<<"  "
	<<"capacity:"<<vi.capacity()<<endl;
	
	vi.resize(50);
	vi.push_back(0);
	
	cout<<"size:"<<vi.size()<<"  "
	<<"capacity:"<<vi.capacity()<<endl;
	
	vi.resize(30);
	
	cout<<"size:"<<vi.size()<<"  "
	<<"capacity:"<<vi.capacity()<<endl;
	
	vi.shrink_to_fit();
	
	cout<<"size:"<<vi.size()<<"  "
	<<"capacity:"<<vi.capacity()<<endl;
	
	return 0;
}