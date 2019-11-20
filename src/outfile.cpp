#include <iomanip>
#include "outfile.hpp"
#include "excp.hpp"

OutFile::OutFile() {
}

OutFile::OutFile(std::string filename) {
  out_stream.open(filename);
  if (!out_stream)
    throw a27Error ("Problem opening output file.");
}

OutFile::~OutFile() {
  if (out_stream.is_open())
    out_stream.close();
}

void OutFile::write(std::string message) {
  std::lock_guard<std::mutex>	lock(mu);
  out_stream << message  << std::endl;
}

void OutFile::writeHEX(int msg) {
  std::lock_guard<std::mutex>	lock(mu);
  out_stream << std::hex << std::uppercase << std::setfill('0') << std::setw(8) << msg  << std::endl;
}
