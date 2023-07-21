

#include "stdafx.h"

#include "STLParser.h"


int _tmain(int argc, _TCHAR* argv[])
{
	//"Julia_Vase_002_Yin_Yang_Combined_Shape.stl";
	string path = "stl//Julia_Vase_002_Yin_Yang_Full_Color.stl";//Julia_Vase_002_Yin_Yang_Black.stl";//Julia_Vase_002_Yin_Yang_Full_Color.stl";//Julia_Vase_002-Yin_Yang_White.stl";//Julia_Vase_002_Yin_Yang_Black.stl";//"stl//cube.stl";	//
	vector<facet> facets;

	STLParser parser;
	parser.read_stl(path, facets);

	size_t i = 0;
	cin>>i;

	return 0;
}