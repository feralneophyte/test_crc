#include "excp.hpp"

a27Error::a27Error() {
  msg = "";
}

a27Error::a27Error(std::string message) {
  msg = message;
}

a27Error::~a27Error() {
}

std::ostream& operator<< (std::ostream &out, const a27Error &excp)
{
    out << excp.msg;
 
    return out;
}
