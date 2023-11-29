#include <gtest/gtest.h>

#include "printip.h"
#include <list>
#include <new>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

  TEST(Google_test, test_integral) {
    {
      std::stringstream ss;
      os_ip(int8_t{-1}, ss);
      EXPECT_EQ(ss.str(), "255");
    }
    {
      std::stringstream ss;
      os_ip( int16_t{0}, ss );
      EXPECT_EQ(ss.str(), "0.0");
    }
    {
      std::stringstream ss;
      os_ip( int32_t{2130706433}, ss );
      EXPECT_EQ(ss.str(), "127.0.0.1");
    }
    {
      std::stringstream ss;
      os_ip( int64_t{8875824491850138409}, ss);
      EXPECT_EQ(ss.str(), "123.45.67.89.101.112.131.41");
    }
  }

  TEST(Google_test, test_string) {
    {
      std::stringstream ss;
      os_ip(std::string{"Hello, World!"}, ss);
      EXPECT_EQ(ss.str(), "Hello, World!");
    }
  }


  TEST(Google_test, test_vector) {
    {
      std::stringstream ss;
      os_ip( std::vector<int>{100, 200, 300, 400}, ss );
      EXPECT_EQ(ss.str(), "100.200.300.400");
    }
  }

  TEST(Google_test, test_list) {
    {
      std::stringstream ss;
      os_ip( std::list<short>{400, 300, 200, 100}, ss );
      EXPECT_EQ(ss.str(), "400.300.200.100");
    }
  }
}
