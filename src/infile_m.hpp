#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>
#include <iostream>
#include <mutex>
#include <string>

using boost::iostreams::mapped_file_source;
using boost::iostreams::stream;

class InFile
{
  private:
    std::mutex    mu;
    mapped_file_source mmap;
    stream<mapped_file_source> is;
  public:
    InFile();
    InFile(std::string filename);
    ~InFile();

    void read(char * buf, unsigned long long size); 

    bool eof(void); 
};
