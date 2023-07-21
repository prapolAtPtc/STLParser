#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Facet.h"


using namespace std;

class STLParser
{
private:
	void read_ascii_stl(string fname, vector<facet> &facets);
	void read_binary_stl(string fname, vector<facet> &facets);
	void getTriangle(string x, string y, string z, vtx &out);
public:
	STLParser();
	void read_stl(string fname, vector<facet> &facets);
};