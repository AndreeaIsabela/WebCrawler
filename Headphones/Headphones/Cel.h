#pragma once
#include"Item.h"


class Cel
{
public:
	Cel(std::string aFileName=" ") ;
	void Write(map<string, vector<Item>> & aMap);
	void GetItemInf(const std::string& aFileText, std::vector<std::smatch> &aInf, string aRegexStr);


	string ReadFromFile();
private:
	std::ifstream mFileName;
	std::string mPrice;
	std::string mId;
	std::string mTitle;
	std::string mUrl;
};

