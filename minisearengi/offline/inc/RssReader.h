 ///
 /// @file    RssReader.h
 /// @author  hw(improvesf@163.com)
 /// @date    2018-05-22 18:12:43
 ///
 
#ifndef RSSREADER_H
#define RSSREADER_H

#include "tinyxml2.h"
#include <string>
#include <vector>
#include <memory>
using std::string;
using std::vector;
using std::shared_ptr;
using namespace tinyxml2;

struct RssItem
{
	string _title;
	string _link;
	string _pubData;
	string _content;
};

class RssReader
{
public:
	RssReader(vector<string> &files);
	~RssReader();
	void loadFeedFiles();
	void loadFeedFile(const string & filename);
	void makePages(vector<string> &pages);
private:
	void parseRss(XMLDocument &doc);
private:
	vector<shared_ptr<RssItem>> _items;
	vector<string> & _files;
};

#endif


