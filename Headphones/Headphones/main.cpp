#include"stdafx.h"
#include "Item.h"
#include "Cel.h"
#include "Emag.h"



ifstream cel("CelIn.txt");
ifstream emag("EmagIn.txt");

int nrOfThreads = 6;
map < string, vector<Item>> ItemMap;

class Parser
{
public:
	void operator() (string aEmag,string aCel)
	{
		Emag emagFie(aEmag);
		Cel celFile(aCel);
		

		emagFie.Write(ItemMap);
		celFile.Write(ItemMap);
	}
};


int main()
{
	vector<thread> vThread;
	string emagFile, celFile;
	for (int i = 0; i < nrOfThreads; ++i) 
	{
		cel >> celFile;
		emag >> emagFile;
		vThread.push_back(thread(Parser(),emagFile,celFile));
	}
	for (auto &it : vThread)
		it.join();
	for (auto it : ItemMap) {
		cout<<it.first<<endl;
	if(it.second.size() == 1 || stod(it.second[0].mPrice)<stod(it.second[1].mPrice))
	{
		cout <<"Name: "<< it.second[0].mObjectTitle << endl;
		cout << stod(it.second[0].mPrice) << endl;
		cout << it.second[0].mUrl << endl;
		cout << "--------------------------------------------" << endl;
	}
	else
	{
		cout << "Name: " << it.second[1].mObjectTitle << endl;
		cout << stod(it.second[1].mPrice) << endl;
		cout << it.second[1].mUrl << endl;
		cout << "--------------------------------------------" << endl;
	}


		
	}

	return 0;
}