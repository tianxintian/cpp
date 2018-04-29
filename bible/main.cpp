 ///
 /// @file    main.cpp
 /// @author  haowang(improvesf@163.com)
 /// @date    2018-04-24 22:37:46
 ///
 
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <string>
#include <string.h>
#include <time.h>
using namespace std;

class Dictionary
{
public:
	Dictionary()
	{
		cout<<"start!"<<endl;
	}
	void read(const string & filename)
	{
		ifstream ifs(filename);
		if(!ifs)
		{
			cout<<"ifstream open error!"<<endl;
			return;
		}
		string line;
		while(getline(ifs,line))
		{
			istringstream iss(line);
			string word;
			while(iss>>word)
			{
				if(isWord(word))
				{
					_dict[word]++;
				}
			}
		}
	}
	void store(const string & filename)
	{
		ofstream ofs(filename);
		if(!ofs)
		{
			cout<<"ofstream open error!"<<endl;
			return;
		}
		for (auto & record: _dict)
		{
			ofs<<record.first<<"    "<<record.second<<"\n";
		}
		ofs.close();
	}
	~Dictionary()
	{
		cout<<"over!"<<endl;
	}	
private:
	bool isWord(const string & word)
	{
		for(size_t idx=0;idx != word.size();++idx)
		{
			if(isdigit(word[idx]))
			{
				return false;
			}
		}
		return true;
	}
private:
	map<string,int> _dict;
};

int main()
{
	Dictionary dictionary;
	clock_t start,finish;
	double duration;
	start=clock();
	dictionary.read("The_Holy_Bible.txt");
	dictionary.store("st.txt");
	finish=clock();
	duration=(double)(finish-start)/CLOCKS_PER_SEC;
	cout<<"duration is "<<duration<<endl;
	return 0;
}

