#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <map>

int parse(std::string);

struct Value
{
	virtual ~Value() = default;
	virtual int weight(std::string str) const = 0;
};

struct Literal:Value
{
	virtual int weight(std::string str) const
	{
		return 1;
	}
};

struct Null:Literal
{
};

struct Bool:Literal
{
};

struct Num:Literal
{
};

struct String:Literal
{
};

struct Array:Value
{
    int weight(std::string str) const
	{
		int weightArray = 1;
		weightArray += parse(str);
		return weightArray;
	}
};

struct Object:Value
{
    int weight(std::string str) const
	{
		int weightObject = 1;
		weightObject += parse(str);
		return weightObject;
	}
};

//--------------------------------------------------------------------

int parse(std::string List)
{
    int weightAll = 0;
    int i = 0;

    for(int i = 0; i < List.size(); i++)
    {
        if(List.at(i) == ' ' || List.at(i) == ',' || List.at(i) == '.')
        {
            i++;
        }

        else if(List.at(i) == '\\')
        {
            i++;
        }

        else if(isdigit(List.at(i)))
        {
            if(i != 0)
            {
                if(!(isdigit(List.at(i-1))))
                {
                    Num numVal;
                    weightAll += numVal.weight(List);
                }
            }
            ++i;
        }

        else if(List.at(i) == 'n')
        {
            Null nullVal;
            weightAll += nullVal.weight(List);
            i += 3;
        }

        else if(List.at(i) == 't')
        {
            Bool boolVal;
            weightAll += boolVal.weight(List);
            i += 3;
        }

        else if(List.at(i) == 'f')
        {
            Bool boolVal;
            weightAll += boolVal.weight(List);
            i += 4;
        }

        else if(List.at(i) == '"')
        {
            int j = i;
            bool loopFlag = true;
            while(j < List.size() && loopFlag == true)
            {
                if(List.at(j) == '"')
                {
                    i= j;
                    loopFlag = false;
                }
                else
                {
                    j++;
                }
            }
            String strVal;
            weightAll += strVal.weight(List);
        }

        else if(List.at(i) == '{')
        {
            int j = i;
            bool loopFlag = true;
            while(j < List.size() && loopFlag == true)
            {
                if(List.at(j) == '}')
                {
                    loopFlag = false;
                }
                else
                {
                    j++;
                }
            }


            std::string List2= "   ";
            List2 = List.substr(i + 1, j-i-1);
            Object objectVal;
            weightAll += objectVal.weight(List2);
            i = ++j;
        }

        else if(List.at(i) == '[')
        {
            int j = i;
            bool loopFlag = true;
            while(j < List.size() && loopFlag == true)
            {
                if(List.at(j) == ']')
                {
                    i= j;
                    loopFlag = false;
                }
                else
                {
                    j++;
                }
            }
            std::string List2 = List.substr(i + 1, j-i);
            Array arrayVal;
            weightAll += arrayVal.weight(List2);
            i = ++j;
        }
    }
    return weightAll;
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

    cout << parse(List);


    return 0;
}
