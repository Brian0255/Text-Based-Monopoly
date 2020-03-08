#pragma once

#include"Space.h"
#include<string>

class TaxSpace : public Space
{
public:
	TaxSpace(std::string name, std::string type, int cost);
	~TaxSpace();
private:
	std::string name;
	std::string type;
	int cost;
};
