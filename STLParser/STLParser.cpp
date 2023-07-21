// STLParser.cpp : Defines the entry point for the console application.
//

#include "STLParser.h"

STLParser::STLParser()
{
	//Default constructor
}


void STLParser::getTriangle(string x, string y, string z, vtx &out)
{
	out = vtx(x.c_str(),y.c_str(),z.c_str());
}

void STLParser::read_ascii_stl(string fname, vector<facet> &facets)
{
	ifstream inFile(fname.c_str(), ios::in);

	string temp;
	vtx n, v1, v2, v3;

	if(inFile.is_open())
	{
		inFile.seekg(std::ios::beg);
		while (!inFile.eof())
		{
			inFile>>temp;
			if((temp[0] =='f' || temp[0] == 'F') && (temp[1] =='a' || temp[1] == 'A') &&
				(temp[2] =='c' || temp[2] == 'C') && (temp[3] =='e' || temp[3] == 'E') && (temp[4] =='t' || temp[4] == 'T'))
			{
				string x="",y="",z="";
				bool firstTime = true;
				while (1)
				{
					if(firstTime){
						inFile>>temp;
						firstTime = false;
					}
					else
					{
						inFile>>x>>y>>z;
						getTriangle(x,y,z,n);
						break;
					}
				}
			}
			else if((temp[0] =='v' || temp[0] == 'V') && (temp[1] =='e' || temp[1] == 'E') && (temp[2] == 'r' || temp[2] == 'R') && 
				(temp[3] =='t' || temp[3] == 'T') && (temp[4] =='e' || temp[4] == 'E') && (temp[5] =='x' || temp[5] == 'X'))
			{
				string x="",y="",z="";
				temp = "";
				inFile.seekg(-7, ios::cur);
				for (size_t i = 1; i <= 3 ; ++i)
				{
					inFile>>temp>>x>>y>>z;
					switch (i)
					{
						case 1:getTriangle(x,y,z,v1);break;
						case 2:getTriangle(x,y,z,v2);break;
						case 3:getTriangle(x,y,z,v3);break;
						default:break;
					}
				}
			}
			else if((temp[0] =='e' || temp[0] == 'E') && (temp[1] =='n' || temp[1] == 'N') && (temp[2] == 'd' || temp[2] == 'D') &&
				(temp[3] =='f' || temp[3] == 'F') && (temp[4] =='a' || temp[4] == 'A') && (temp[5] =='c' || temp[5] == 'C') &&
				(temp[6] =='e' || temp[6] == 'E') && (temp[7] =='t' || temp[7] == 'T'))
			{
				// if end of facet loop found, then inserting data into facet
				facets.push_back(facet(v1,v2,v3,n));
			}
			else
			{
				// Ignoring all other lines
				inFile.ignore(numeric_limits<streamsize>::max(),'\n');
			}
			temp = "";
		}
	}
	inFile.close();
	return;
}

void STLParser::read_binary_stl(string fname, vector<facet> &facets)
{
	ifstream inFile(fname.c_str(), ios::in | ios::binary);

	char header_info[80] = "";
	char nTri_bin[4];
	unsigned long numberOfTri;
	//vector<facet> facets;

	//80 byte header
	if (inFile) {
		inFile.read (header_info, 80);
		cout <<"header: " << header_info << endl;

		//string bitStr;
		//char buffer[9] = "";
		//for(size_t i = 6; i < 10; i++) {
		//	sprintf(buffer, "%c%c%c%c%c%c%c%c", 
		//										(header_info[i] & (1 << 7)) ? '1':'0', 
		//										(header_info[i] & (1 << 6)) ? '1':'0', 
		//										(header_info[i] & (1 << 5)) ? '1':'0',
		//										(header_info[i] & (1 << 4)) ? '1':'0',
		//										(header_info[i] & (1 << 3)) ? '1':'0',
		//										(header_info[i] & (1 << 2)) ? '1':'0',
		//										(header_info[i] & (1 << 1)) ? '1':'0',
		//										(header_info[i] & (1 << 0)) ? '1':'0');
		//	//_itoa(header_info[i], buffer, 2);
		//	strncat((char *)bitStr.c_str(), buffer, 8);
		//	buffer[0] = '\0';
		//}
		cout<<"done"<<endl;
	}
	else{
		cout << "error" << endl;
	}

	//read 4-byte No
	if (inFile) {
		inFile.read (nTri_bin, 4);
		numberOfTri = *((unsigned long*)nTri_bin) ;
		cout <<"n Tri: " << numberOfTri << endl;
	}
	else{
		cout << "error" << endl;
	}

	for(unsigned int i = 0; i < numberOfTri && inFile; i++){

		char bin_facet[50];
		if (inFile)
		{
			//read one 50-byte - Triangle(48 bytes for face normal and triangle vertex, last 2 bytes unused )
			inFile.read (bin_facet, 50);

			//first 12 bytes for face normal
			vtx n(bin_facet);
			// next 12 bytes first vertexqw
			vtx p1(bin_facet+12);
			// next 12 second vertex
			vtx p2(bin_facet+24);
			// next 12 third vertext
			vtx p3(bin_facet+36);

			char colorBytes[] = {bin_facet[48], bin_facet[49]};
			//cout<<colorBytes[0]<<" "<<colorBytes[1]<<endl;
			facets.push_back(facet(p1,p2,p3,n));
		}
	}
	inFile.close();
	return;// facets;
}

void STLParser::read_stl(string fname, vector<facet> &facets){

	ifstream inFile(fname.c_str(), ios::in);

	bool binary = true;
	//char solid[];
	string solid;
	inFile>>solid;

	if((solid[0] == 's' || solid[0] == 'S') && (solid[1] == 'o' || solid[1] == 'O') && (solid[2] == 'l' || solid[2] == 'L') && (solid[3] == 'i' || solid[3] == 'I') && (solid[4] == 'd' || solid[4] == 'D'))
	{
		binary = false;
	}
	inFile.close();
	if(binary){
		read_binary_stl(fname, facets);
	}
	else{
		read_ascii_stl(fname, facets);
	}
	return;
}
