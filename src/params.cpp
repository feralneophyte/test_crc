#include "params.hpp"
#include "excp.hpp"

using namespace boost::program_options; 

Params::Params() {
  ULsize = chunk_size;

  desc.add_options()
    ("help,h", "Help screen")
    ("infile,i", po::value<std::string>(&infile), "Input file name")
    ("outfile,o", po::value<std::string>(&outfile), "Output file name")
    ("size,s", po::value<std::string>(&size), "Chunk size <default 1M>")
  ;
}

Params::~Params() {
}

std::string Params::getInfile() {
  if(!results.count("infile")) {
    printHelp();
    throw a27Error ("");
  }

  return results["infile"].as<std::string>();
}

std::string Params::getOutfile() {
  if(!results.count("outfile")) {
    printHelp();
    throw a27Error ("");
  }

  return results["outfile"].as<std::string>();
}

unsigned long long Params::getSize() {
  if(!results.count("size")) {
    ULsize = chunk_size;
  }

  return ULsize;
}

void Params::printHelp() {
  std::cout << "Usage:" << std::endl << desc << std::endl;
}

void Params::ParseParams(int argc, const char* argv[]) {

  try {
    store( parse_command_line( argc, argv, desc ), results );
  } catch ( ... ) {
    throw a27Error ("Option parsing error.");
  }

  notify( results );

  if(!results.count("infile") || !results.count("outfile") ) {
    printHelp();
    throw a27Error ("");
  }

  if(results.count("size")) {
    std::string pTmp = results["size"].as<std::string>();
    bool   pOnlyDigits  = true;
    bool   pOnlyOneLtr  = false;
    bool   pBadSize     = false;
    int    pLtrPosition = 0;

    int l = pTmp.length();
    for( int i = 0; i < l; i++ ) {
      if (pTmp.at(i) < '0' || pTmp.at(i) > '9') {
        pOnlyDigits = false;
        switch( pTmp.at(i) ) {
          case 'k':
          case 'K':
          case 'm':
          case 'M':
          case 'g':
          case 'G':
            pLtrPosition = i;

            if( !pOnlyOneLtr )
              pOnlyOneLtr = true;
            else
              pBadSize = true;
          break;

          default:  // wrong letter
            pBadSize = true;
            break;
        }

        if( pBadSize ) break;
      }
    } //for

    if( pBadSize || (pOnlyOneLtr && pLtrPosition == 0) )
      ULsize = chunk_size;
    else {

      if( pOnlyDigits )
        ULsize = stoul(pTmp);

      if( pOnlyOneLtr ) {
        std::size_t pPos = pLtrPosition;
        ULsize = stoul( pTmp, &pPos );

        switch( pTmp.at(pLtrPosition) ) {
          case 'k':
            ULsize *= 1000;
            break;
          case 'K':
            ULsize *= 1024;
            break;
          case 'm':
            ULsize *= 1000000;
            break;
          case 'M':
            ULsize *= 1024*1024;
            break;
          case 'g':
            ULsize *= 1000000000;
            break;
          case 'G':
            ULsize *= 1024*1024*1024;
            break;
          default:
            break;
        }
      }
    }

    if( ULsize == 0 )
      ULsize = chunk_size;
  }
}

