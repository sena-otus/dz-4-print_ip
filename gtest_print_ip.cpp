#include <gtest/gtest.h>

#include "printip.h"
#include <list>
#include <new>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

namespace {

   // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  TEST(Google_test, test_sizes) {
    {
      EXPECT_EQ(maxuint8, 255);
      EXPECT_EQ(bytesize, 8);
    }
  }

  TEST(Google_test, test_integral) {
    {
      testing::internal::CaptureStdout();
      print_ip(int8_t{-1});
      EXPECT_EQ(testing::internal::GetCapturedStdout(), "255\n");
    }
    {
      testing::internal::CaptureStdout();
      print_ip( int16_t{0});
      EXPECT_EQ(testing::internal::GetCapturedStdout(), "0.0\n");
    }
    {
      testing::internal::CaptureStdout();
      print_ip( int32_t{2130706433} );
      EXPECT_EQ(testing::internal::GetCapturedStdout(), "127.0.0.1\n");
    }
    {
      testing::internal::CaptureStdout();
      print_ip( int64_t{8875824491850138409});
      EXPECT_EQ(testing::internal::GetCapturedStdout(), "123.45.67.89.101.112.131.41\n");
    }
  }

  TEST(Google_test, test_string) {
    {
      testing::internal::CaptureStdout();
      print_ip(std::string{"Hello, World!"});
      EXPECT_EQ(testing::internal::GetCapturedStdout(), "Hello, World!\n");
    }
  }


  TEST(Google_test, test_vector) {
    {
      testing::internal::CaptureStdout();
      print_ip( std::vector<int>{100, 200, 300, 400} );
      EXPECT_EQ(testing::internal::GetCapturedStdout(), "100.200.300.400\n");
    }
  }

  TEST(Google_test, test_list) {
    {
      testing::internal::CaptureStdout();
      print_ip( std::list<short>{400, 300, 200, 100} );
      EXPECT_EQ(testing::internal::GetCapturedStdout(), "400.300.200.100\n");
    }
  }


  TEST(Google_test, test_tuple) {
    {
      testing::internal::CaptureStdout();
      print_ip( std::make_tuple<short,short,short,short>(21, 22, 23, 24) );
      EXPECT_EQ(testing::internal::GetCapturedStdout(), "21.22.23.24\n");
    }
    {
      testing::internal::CaptureStdout();
      print_ip( std::make_tuple("one","two","three") );
      EXPECT_EQ(testing::internal::GetCapturedStdout(), "one.two.three\n");
    }
  }
    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
}
