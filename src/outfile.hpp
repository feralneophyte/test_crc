#include <iostream>
#include <mutex>
#include <fstream>
#include <string>

class OutFile
{
  private:
    std::ofstream out_stream;
    std::mutex    mu;

  public:
    OutFile();
    OutFile(std::string filename);
    ~OutFile();

    void write(std::string message); 
    void writeHEX(int msg); 
};
