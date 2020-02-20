#pragma once

#include"Space.h"
#include<string>

class TaxSpace : public Space
{
public:
	//the constructor
	TaxSpace(std::string name, std::string type, int cost);

	//overrided destructor
	~TaxSpace();
private:
	//the name of the space
	std::string name;

	//the type of the space
	std::string type;

	//the cost for the taxes
	int cost;
};
