#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;

class Debug
{
	public:
		constexpr Debug(bool i,bool h,bool o):io(i),hw(h),other(o){}
		constexpr Debug() = default;
		constexpr bool any(){return io||hw||other;}
		void set_io(bool b){io = b;}
		void set_hw(bool b){hw = b;}
		void set_other(bool b){other = b;}
		
	private:
		bool io = false;
		bool hw = false;
		bool other = false;
		
};

int main()
{
	constexpr Debug db(false,false,false);
	if(!db.any())
	{
		db.set_io(true);
	}
	Debug db1 = db;
	if(!db1.any())
	{
		
	}
	cout<<"All right "<<endl;
	return 0;
}