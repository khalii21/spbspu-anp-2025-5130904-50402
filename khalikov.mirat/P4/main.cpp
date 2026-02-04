#include <iostream>
#include <iomanip>
#include <stdlib.h>

void extend(char ** data, size_t & capacity)
{
  size_t new_capacity = capacity * 2;
  char * new_array = reinterpret_cast< char * >(malloc(sizeof(char) * capacity));;
  if (new_array == nullptr)
  {
    throw std::bad_alloc();
  }
  else
  {
    for (size_t i = 0; i < capacity; i++)
    {
      new_array[i] = (*data)[i];
    }
    free(*data);
    *data = new_array;
    capacity = new_capacity;
  }
}

char * getline(std::istream & in, size_t & s)
{
  bool is_skipws = in.flags() & std::ios_base::skipws;
  if (is_skipws)
  {
    in >> std::noskipws;
  }
  char ch = 0;
  size_t i = 0;
  size_t capacity = 2;
  char * result = (char*)malloc(capacity * sizeof(char));
  if (result == nullptr)
  {
    throw std::bad_alloc();
  }
  while (in >> ch && ch != '\n')
  {
    if (i >= capacity-1)
    {
      extend(&result, capacity);
    }
    result[i++] = ch;
  }
  result[i] = 0;
  s = i;
  if (is_skipws)
  {
    in >> std::skipws;
  }
  return result;
}

int main()
{
  size_t s = 0;
  std::cout << getline(std::cin, s) << "\n";
}
