#include <iostream>
#include <iomanip>

char * getline(std::istream & in, size_t & s)
{
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws)
  {
    in >> std::noskipws;
  }

  s = 10;
  size_t i = 0;
  char * result = new char[s];
  for (; in && i < s - 1; ++i)
  {
    in >> result[i];
  }
  result[i] = 0;
  if (is_skipws)
  {
    in >> std::skipws;
  }
  return result;
}

int main()
{
  size_t s = 0;
  std::cout << getline(std::cin, s);
}
