#include <string>
using namespace std;

#ifndef ParsingErrorException_H
#define ParsingErrorException_H



class ParsingErrorException : public exception
{
public:
  ParsingErrorException(string m="exception!") : msg(m) {}
  ~ParsingErrorException() throw() {

  }
  const char* what() const throw() { return msg.c_str(); }

private:
  string msg;
};

#endif