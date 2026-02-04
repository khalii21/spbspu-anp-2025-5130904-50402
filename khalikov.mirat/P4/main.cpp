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
  char * result = reinterpret_cast< char * >(malloc(sizeof(char) * capacity));;
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

size_t excsnd(const char * data1, const char * data2, size_t size1, size_t size2)
{
  size_t size = 0;
  for (size_t i = 0; i < size1; i++)
  {
    size_t match = 0;
    for (size_t j = 0; j < size2; j++)
    {
      if (data1[i] == data2[j])
      {
        match++;
        break;
      }
    }
    if (match == 0)
    {
      size++;
    }
  }
  return size;
}

char * excsnd(char * res, const char * data1, const char * data2, size_t size1, size_t size2)
{
  size_t k = 0;
  for (size_t i = 0; i < size1; i++)
  {
    size_t match = 0;
    for (size_t j = 0; j < size2; j++)
    {
      if (data1[i] == data2[j])
      {
        match++;
        break;
      }
    }
    if (match == 0)
    {
      res[k++] = data1[i];
    }
  res[k] = 0;
  }
  return res;
}

size_t dgtsnd(const char * data1, const char * data2, size_t size1, size_t size2)
{
  size_t count = 0;
  for (size_t i = 0; i < size2; i++)
  {
    if (isdigit(data2[i]))
    {
      count++;
    }
  }
  return size1 + count;
}

char * dgtsnd(char * res, const char * data1, const char * data2, size_t size1, size_t size2)
{
  for (size_t i = 0; i < size1; i++)
  {
    res[i] = data1[i];
  }
  size_t k = size1;
  for (size_t i = 0; i < size2; i++)
  {
    if (isdigit(data2[i]))
    {
      res[k++] = data2[i];
    }
  }
  res[k] = 0;
  return res;
}

int main()
{
  size_t size1 = 0;
  size_t size2 = 0;
  char * data1 = getline(std::cin, size1);
  char * data2 = getline(std::cin, size2);
  size_t cap1 = excsnd(data1, data2, size1, size2);
  char * res1 = reinterpret_cast< char * >(malloc(sizeof(char) * cap1));;
  size_t cap2 = dgtsnd(data1, data2, size1, size2);
  char * res2 = reinterpret_cast< char * >(malloc(sizeof(char) * cap2));;
  std::cout << excsnd(res1, data1, data2, size1, size2) << "\n";
  std::cout << dgtsnd(res2, data1, data2, size1, size2) << "\n";
}
