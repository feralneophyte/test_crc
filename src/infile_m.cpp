#include "infile_m.hpp"
#include "excp.hpp"

InFile::InFile() {
}

InFile::InFile(std::string filename) {
  try {
    mmap.open(filename);
  } catch ( ... ) {
    throw a27Error ("Input file opening error.");
  }

  try {
    is.open(mmap, std::ios::binary);
  } catch ( ... ) {
    throw a27Error ("Stream open error.");
  }
}

InFile::~InFile() {
  if (is.is_open())
    is.close();
  if (mmap.is_open())
    mmap.close();
}

void InFile::read(char * buf, unsigned long long size) {

  std::lock_guard<std::mutex>	lock(mu);

  is.read (buf, size);

  if (is.eof() && is.gcount() == 0)
    throw a27Eof();

  if (is.eof() && is.gcount() < size) {
    char *endptr = buf + size;
    char *bufptr = buf + is.gcount();
    while (bufptr < endptr)
      *bufptr++ = 0x00;
  }
}

bool InFile::eof(void) {
  return is.eof();
}
