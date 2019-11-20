#include <string.h>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

using namespace boost::program_options; 

#define chunk_size 1048576

class Params {
  private:
    po::options_description desc;
    po::variables_map results;

    std::string infile;
    std::string outfile;
    std::string size;
    unsigned long long ULsize;

  public:
    Params();
    ~Params();

  std::string getInfile();
  std::string getOutfile();
  unsigned long long getSize();

  void printHelp();

  void ParseParams(int argc, const char* argv[]);
};