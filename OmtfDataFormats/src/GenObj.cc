#include "UserCode/OmtfDataFormats/interface/GenObj.h"
#include <iomanip>

ClassImp(GenObj)

std::ostream & operator<< (std::ostream &out, const GenObj &o)
{
  out<<"Dummy output for gen muon" << std::endl;
  return out;
}

