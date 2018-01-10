#include"stdafx.h"
#include "Emag.h"
#include "Mutex.h"

Emag::Emag(std::string aFileName) 
	: mFileName(aFileName)
	, mPrice("<p\\sclass=\"product-new-price\">[^0-9%]*([0-9\\.]+)[^>]*>[^0-9%]*([0-9]+)</sup> <span>Lei</span></p>")
	,mId("<input\\stype=\"hidden\"\\sname=\"product\\[\\]\"\\svalue=\"([0-9]+)\">")
	,mTitle("class=\"product-title\\sjs-product-url\"\\sdata-zone=\"title\">([^\"]+)</a>")
	,mUrl("<a href=\"([^\"]+)\" data-ref=\"[^\"]*\" class=\"[^\"]*\" data-zone=\"[^\"]*\">([^<]+)</a>")
	                                                    
{

}




void Emag::Write(map<string, vector<Item>> & aMap)	
{
	string str = ReadFromFile();
	vector<smatch> priceVector;
	vector<smatch> idVector;
	vector<smatch> titleVector;
	vector<smatch> urlVector;

	GetItemInf(str, priceVector,mPrice);
	GetItemInf(str, idVector, mId);
	GetItemInf(str, titleVector, mTitle);
	GetItemInf(str, urlVector, mUrl);

	for (int i = 0; i < priceVector.size(); ++i) { 
		string title = titleVector[1][1].str();
		string price = priceVector[i][1].str() + '.'+priceVector[i][2].str();
		string url = urlVector[i][1].str();
		string id = idVector[i][1].str();
		Item item(move(title), move(price), move(url));
		std::lock_guard<std::mutex> lock(Mutex::Get());
		aMap[id].push_back(move(item));
	}
	int x = 0;
	x++;
}

void Emag::GetItemInf(const std::string & aFileText, std::vector<std::smatch> &aInf, string aRegexStr)
{
	std::regex reg(aRegexStr, std::regex_constants::ECMAScript);
	
	aInf.clear();

	std::copy(sregex_iterator(aFileText.begin(), aFileText.end(), reg), sregex_iterator(), std::back_inserter(aInf));
}

string Emag::ReadFromFile()
{
	std::string str;

	mFileName.seekg(0, std::ios::end);
	str.reserve(mFileName.tellg());
	mFileName.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(mFileName)),
		std::istreambuf_iterator<char>());
	return str;
}
