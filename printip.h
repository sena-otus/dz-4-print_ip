#pragma once

/**
 * @file printip.h
 * Template function print_ip for the strange IP-like printing
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
 * Print byte components of the arbitrary integral type.
 *
 * This function will be only available if argument is integral.
 * @tparam T argument type that must be of integral type
 * @param integral value to convert
 * */
template <typename T>
typename std::enable_if<std::is_integral<T>::value>::type
print_ip(T && integral)
{
  auto biguint = static_cast<uint64_t>(std::forward<T>(integral));
  std::string delim;
  for(unsigned ii = sizeof(T); ii > 0; --ii)
  {
    std::cout << delim << ((biguint >> ((ii-1) * CHAR_BIT)) & maxuint8);
    delim = ".";
  }
  std::cout << "\n";
}



/**
 * Print string as is.
 *
 * This function will be only available if argument is std::string.
 * Simplest will be to have non-template function, like following:
 * @code
 * void print_ip(std::string && strval)
 * @endcode
 * but we need to fullfill the requirements...
 * @tparam T type of argument that must be of string type
 * @param strval string to print
 * */
template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value>::type
print_ip(T && strval)
{
  std::cout << std::forward<std::string>(strval);
  std::cout << "\n";
}


/**
 * Print container members separated by dot.
 *
 * This function will be only available if argument is std::list or std::vector.
 * @tparam T type of passed argument that must be of list or vector type
 * @param vecT container to print
 * */
template <typename T>
typename std::enable_if<std::is_same<T, std::vector<typename T::value_type>>::value ||
                        std::is_same<T, std::list<typename T::value_type>>::value>::type
print_ip(T && vecT)
{
  std::string delim;
  for(auto && val : std::forward<T>(vecT))
  {
    std::cout << delim << val;
    delim = ".";
  }
  std::cout << "\n";
}


/**
 * Print tuple members separated by dot.
 *
 * This function will be only available if argument is std::tuple.
 * Additional restriction: all tuple types must be equal.
 * @tparam C type of passed argument that must be of tuple type
 * @param tpl tuple to print
 * */
template <template<typename...> class C, typename... Types>
typename std::enable_if<std::is_same_v<class C<Types...>, std::tuple<Types...>>>::type
print_ip(C<Types...> && tpl)
{
  std::apply([](auto&& arg, auto&&... args) {
    using ArgType = decltype(arg);
    std::cout << std::forward<ArgType>(arg);
    ((std::cout << "." << std::forward<decltype(args)>(args)), ...);

      // compile-time check that all tuple types are equal:
    static_assert(std::conjunction_v<std::is_same<ArgType, decltype(args)>...>, "all tuple types must be equal");
  }, std::forward<decltype(tpl)>(tpl));;
  std::cout << "\n";
}
