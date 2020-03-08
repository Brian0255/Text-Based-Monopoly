#include "TaxSpace.h"
TaxSpace::TaxSpace(std::string n, std::string t, int c)
	:Space(n, t), cost{ c } {}

TaxSpace::~TaxSpace()
{
}
;
