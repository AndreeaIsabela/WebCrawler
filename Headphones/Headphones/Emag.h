#include"Item.h"

class Emag
{
public:
	Emag(std::string aFileName = " ");
	void Write(map<string,vector<Item>> & aMap);
	void GetItemInf(const std::string& aFileText, std::vector<std::smatch> &aInf, string aRegexStr);
	

	string ReadFromFile();

private:
	std::ifstream mFileName;
	string  mPrice;
	string mId;
	string mTitle;
	string mUrl;
};
