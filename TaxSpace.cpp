#include "TaxSpace.h"

//not much to explain here

TaxSpace::TaxSpace(std::string n, std::string t, int c)
	:Space(n, t), cost{ c } {}

TaxSpace::~TaxSpace()
{
}
;
