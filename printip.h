#pragma once

/**
 * @file printip.h
 * Header-only function print_ip for the strange IP-like printing
 *  */

#include <climits>
#include <cstdint>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <list>
#include <tuple>
#include <type_traits>

/**
 *  Max uint8_t, that must be 255, for print_ip to work
 *  That is checked in gtest_printip.cpp
 *  */
const uint8_t maxuint8 = std::numeric_limits<uint8_t>::max();

/**
 *  Byte size, that must be 8 for print_ip to work
 *  That is checked in gtest_printip.cpp
 *  */
const size_t bytesize = CHAR_BIT;


/**
 * Print byte components of the arbitrary integral type
 * @tparam T integral type
 * @param integral value to convert
 * @param os output stream
 * */
template <typename T>
typename std::enable_if<std::is_integral<T>::value>::type
os_ip(T && integral, std::ostream &os)
{
  auto biguint = static_cast<uint64_t>(std::forward<T>(integral));
  std::string delim;
  for(unsigned ii = sizeof(T); ii > 0; --ii)
  {
    os << delim << ((biguint >> ((ii-1) * CHAR_BIT)) & maxuint8);
    delim = ".";
  }
}



/**
 * Print string as is.
 * Simplest will be to have non-template function, like following:
 * @code
 * void os_ip(std::string && strval, std::ostream &os)
 * @endcode
 * but we need to fullfill the requirements...
 * @tparam T string type
 * @param strval string to print
 * @param os output stream
 * */
template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value>::type
os_ip(T && strval, std::ostream &os)
{
  os << std::forward<std::string>(strval);
}



/**
 * Print container members separated by dot.
 * @tparam T container class
 * @param vecT container to print
 * @param os output stream
 * */
template <typename T>
typename std::enable_if<std::is_same<T, std::vector<typename T::value_type>>::value ||
                        std::is_same<T, std::list<typename T::value_type>>::value>::type
os_ip(T && vecT, std::ostream &os)
{
  std::string delim;
  for(auto && val : std::forward<T>(vecT))
  {
    os << delim << val;
    delim = ".";
  }
}


/** Print tuple members separated by dot.
 * */
template <template<typename...> class C, typename... Types>
typename std::enable_if<std::is_same<class C<Types...>, std::tuple<Types...>>::value>::type
os_ip(C<Types...> && tpl, std::ostream &os)
{
  std::apply([&os](auto&&... args) {((os << args << '.'), ...);}, std::forward<C<Types...>>(tpl));;
}


/**
 * Fancy ip-like print to std::cout
 * - print integral byte by byte, separated with dots
 * - print string as-is
 * - print container elements separated with dots
 * - print tuple members separated by dot
 * @tparam T type to print
 * @param val value to print
 * */
template <typename T>
void print_ip(T &&val)
{
  os_ip(std::forward<T>(val), std::cout);
  std::cout << "\n";
}



// print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0
