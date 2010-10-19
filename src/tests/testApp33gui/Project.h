#include <string>
#include <vector>
#include "ofAddons.h"

using namespace std;

class CProject
{
public:
	CProject(void);
	CProject(string xmlfile);
	~CProject(void);

	int Load();
	int Load(string xmlfile);

	int AddObject(string objfile);

	string xml_proj_file;
	vector<string> objects;

};
