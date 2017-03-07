#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <map>

struct Value
{
	virtual ~Value() = default;
	virtual int weight() const = 0;
};

struct Literal:Value
{
	int weight() const
	{
		return 1;
	}
};

struct Null
{

};

struct Bool
{

};

struct Num
{

};

struct String:Literal,std::string
{

};

struct Array:Value,std::vector<Value*>
{
	~Array()
    {
        for(Value *v: *this)
            delete v;
    }

    int weight() const
	{
		int n = 0;
		for(Value* v: *this)
			n += v->weight();
		return n;
	}
};
/*
struct Array:Value,std::vector<std::unique_ptr<Value*>>  // smart ptr can not copy
{
	using vector<Value*>::vector
	~Array()
    {
        for(Value *v: *this)
            delete v;
    }

	int weight() const
	{
		int n = 0;
		for(Value* v: *this)
		{
			n += v->weight();
		}
		return n;
	}
};
*/

struct Object:Value
{
	std::map <std::string, Value*> Valuelist;
};

//--------------------------------------------------------------------

Value* parse(char* F, char L)
{

}

Value* parse_Array(char* F, char L)
{
	++F;
	Array* a = new Array();

	Value* v;

	while(true)
	{
		v = parse(F,L);
	}

	v = parse(F,L);

}

//If you see a number copy until a comma or white space

//if you see a blackslash skip to next char
using namespace std;

int main(int argc, const char* argv[])
{
	string infile1 = "front.json";
    
    ifstream inputFile;
    string List;

    inputFile.open(infile1.c_str());
    getline(inputFile, List);
    
    cout << List << endl;


    cout << "Hello world!" << endl;
    return 0;
}
