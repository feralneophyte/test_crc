#include <iostream>
#include <string>
#include <exception>

class a27Error : public std::exception
{
  private:
    std::string msg;

  public:
    a27Error();
    a27Error(std::string message);
    ~a27Error();

    friend std::ostream& operator<< (std::ostream &out, const a27Error &excp);
};

class a27Eof : public  a27Error {};