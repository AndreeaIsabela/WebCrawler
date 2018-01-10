#pragma once
#include"stdafx.h"

class Item
{
public:
	Item( std::string aObject,std::string aPrice, std::string aUrl) : mObjectTitle(aObject),mPrice(aPrice),mUrl(aUrl) {};
	bool operator==(Item aOtherItem){return aOtherItem.mPrice == mPrice;}
	bool operator<(Item aOtherItem){return aOtherItem.mPrice < mPrice;}
	

	std::string mPrice;
	std::string mUrl;
	std::string mObjectTitle;


};

