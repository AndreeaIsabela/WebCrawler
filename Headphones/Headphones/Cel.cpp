#include"stdafx.h"
#include "Cel.h"
#include "Mutex.h"

Cel::Cel(std::string aFileName)
	: mFileName(aFileName)
	, mPrice("<b\\sitemprop=\"price\"\\scontent=\"([0-9]+)\">([0-9]+)</b>")
	, mId("<div class=\"stoc_list\"><span id=\"s([0-9]+)-0\"></span></div>")
	, mTitle("<span\\sitemprop=\"name\">([^<]+)</span></a></h4>")
	, mUrl("<h4 class=\"productTitle\"><a href=\"([^\"]+)\" class=\"productListing-data-b product_link product_name\" ><span itemprop=\"name\">([^<]+)</span></a></h4>")
{

}

void Cel::Write(map<string, vector<Item>> & aMap)
{
	string str = ReadFromFile();
	vector<smatch> priceVector;
	vector<smatch> idVector;
	vector<smatch> titleVector;
	vector<smatch> urlVector;

	GetItemInf(str, priceVector, mPrice);
	GetItemInf(str, idVector, mId);
	GetItemInf(str, titleVector, mTitle);
	GetItemInf(str, urlVector, mUrl);

	for (int i = 0; i < priceVector.size(); ++i) {
		string title = titleVector[1][1].str();
		string price = priceVector[i][1].str();
		string url = urlVector[i][1].str();
		string id = idVector[i][1].str();
		Item item(move(title), move(price), move(url));
		std::lock_guard<std::mutex> lock(Mutex::Get());
		aMap[id].push_back(move(item));
	}
	

}

void Cel::GetItemInf(const std::string & aFileText, std::vector<std::smatch> &aInf, string aRegexStr)
{
	std::regex reg(aRegexStr, std::regex_constants::ECMAScript);

	aInf.clear();

	std::copy(sregex_iterator(aFileText.begin(), aFileText.end(), reg), sregex_iterator(), std::back_inserter(aInf));
}

string Cel::ReadFromFile()
{
	std::string str;

	mFileName.seekg(0, std::ios::end);
	str.reserve(mFileName.tellg());
	mFileName.seekg(0, std::ios::beg);

	str.assign((std::istreambuf_iterator<char>(mFileName)),
		std::istreambuf_iterator<char>());
	return str;
}

