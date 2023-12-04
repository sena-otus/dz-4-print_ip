/**
 * @file main.cpp
 *
 *  Exercise 4, SFINAE. Call print_ip() with required parameters.
 *  */


#include "printip.h"


const int generic_errorcode = 102;


  // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  // NOLINTNEXTLINE(hicpp-named-parameter,readability-named-parameter)
int main(int, char const *[])
{
  try
  {
    print_ip(int8_t{-1}); // 255
    print_ip( int16_t{0} ); // 0.0
    print_ip( int32_t{2130706433} ); // 127.0.0.1
    print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
    print_ip( std::string{"Hello, World!"} ); // Hello, World!
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
    print_ip( std::make_tuple<int,int,int>(1,2,3)); // 1.2.3
    print_ip( std::make_tuple("one","two","three")); // one.two.three
      // print_ip( std::make_tuple(1, 2, 3.1)); // compiler error! all types must be equal!!!
  }
  catch(const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    return generic_errorcode;
  }
  return 0;
}
  // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
