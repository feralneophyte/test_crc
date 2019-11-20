#include "params.hpp"
#include "infile_m.hpp"
#include "outfile.hpp"
#include "excp.hpp"
#include <boost/crc.hpp>
#include <boost/program_options.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <thread> 

namespace po = boost::program_options;
//namespace bi = boost::interprocess;

using namespace std; 
  
#define chunk_size 1048576

void crcCalc (InFile *inf, OutFile *outf, unsigned long long size) {

  std::unique_ptr<char[]> buf(new char[size]);

  if (buf != nullptr) {
    try {
      while(!inf->eof()) {
        inf->read (buf.get(), size);
        boost::crc_32_type result;
        result.process_bytes(buf.get(), size);
        outf->writeHEX (result.checksum());
      }
    } catch (a27Eof & ex) { }
  } else {
    throw a27Error ("Not enough memory.");
  }
}

auto main(int argc, const char *argv[]) -> int
{
  unsigned int con_threads; 
  Params param;

  con_threads = thread::hardware_concurrency();
  param.ParseParams(argc, argv);

  try {
    InFile  inf(param.getInfile());
    OutFile outf(param.getOutfile());

    std::cout << "Size = " << param.getSize() << std::endl;

    std::thread t[con_threads];
 
    for (int i = 0; i < con_threads; i++) {
        t[i] = std::thread (crcCalc, &inf, &outf, param.getSize());
    }

    for (int i = 0; i < con_threads; i++) {
        t[i].join(); 
    }
  } 
  catch (a27Error ex) {
    cerr << ex << std::endl;
  }

  return 0; 
}
