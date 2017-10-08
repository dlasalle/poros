/**
 * @file DomTest.hpp
 * @brief Top level header for DomTest 
 * @author Dominique LaSalle <dominique@solidlake.com>
 * Copyright 2015-2017
 * @version 1
 * @date 2015-08-22
 */




#ifndef DOMTEST_HPP
#define DOMTEST_HPP




#include <stdexcept>
#include <exception>
#include <string>
#include <iostream>




/******************************************************************************
* MACROS **********************************************************************
******************************************************************************/


#define testEqual(a,b) \
  if ((a) != (b)) { \
    std::cerr << "Test Failed: " << #a << ":'" << (a) << "' != " << #b << ":'" \
        << (b) << "' at " << __LINE__ << std::endl; \
    throw DomTest::TestFailed("Equal Failed"); \
  }


#define testStringEqual(a,b) \
  if ((a).compare(b) != 0) { \
    std::cerr << "Test Failed: " << #a << ":'" << (a) << "' != " << #b << ":'" \
        << (b) << "' at " << __LINE__ << std::endl; \
    throw DomTest::TestFailed("Equal Failed"); \
  }


#define testTrue(a) \
  if (!(a)) { \
    std::cerr << "Test Failed: '" << #a << "' is false at: " << __LINE__ \
      << std::endl; \
    throw DomTest::TestFailed("True Failed"); \
  }


#define testFalse(a) \
  if (a) { \
    std::cerr << "Test Failed: '" << #a << "' is true at: " << __LINE__ \
      << std::endl; \
    throw DomTest::TestFailed("False Failed"); \
  }


#define testGreater(a,b) \
  if ((a) <= (b)) { \
    std::cerr << "Test Failed:" << #a << ":'" << (a) << "' <= " << #b << ":'" \
        << (b) << "' at " << __LINE__ << std::endl; \
    throw DomTest::TestFailed("Greater Than Failed"); \
  }

#define testLess(a,b) \
  if ((a) >= (b)) { \
    std::cerr << "Test Failed:" << #a << ":'" << (a) << "' >= " << #b << ":'" \
        << (b) << "' at " << __LINE__ << std::endl; \
    throw DomTest::TestFailed("Less Than Failed"); \
  }

#define testGreaterOrEqual(a,b) \
  if ((a) < (b)) { \
    std::cerr << "Test Failed:" << #a << ":'" << (a) << "' < " << #b << ":'" \
        << (b) << "' at " << __LINE__ << std::endl; \
    throw DomTest::TestFailed("Greater Than Or Equal Failed"); \
  }


#define testLessOrEqual(a,b) \
  if ((a) > (b)) { \
    std::cerr << "Test Failed:" << #a << ":'" << (a) << "' > " << #b << ":'" \
        << (b) << "' at " << __LINE__ << std::endl; \
    throw DomTest::TestFailed("Greater Than Or Equal Failed"); \
  }


#define UNITTEST(CLASS, TEST) \
  void _unittest_ ## CLASS ## _ ## TEST ## _func(void); \
  bool _unittest_ ## CLASS ## _ ## TEST ## _result = \
      DomTest::UnitTest( \
          __FILE__":"#CLASS"->"#TEST, \
          _unittest_ ## CLASS ## _ ## TEST ## _func); \
  void _unittest_ ## CLASS ## _ ## TEST ## _func(void) \


/******************************************************************************
* CLASSES AND TYPES ***********************************************************
******************************************************************************/

namespace DomTest
{

volatile int numberFailed = 0;
volatile int numberPassed = 0;


namespace
{

class TestFailed : public std::logic_error
{
  public:
    TestFailed(std::string const & str) :
        std::logic_error(str)
    {
    }
};


bool UnitTest(
    char const * name,
    void (*test)(void))
{
  try {
    test();
    std::cerr << "Test " << name << " PASSED." << std::endl;
    ++numberPassed;
    return true;
  } catch (TestFailed const & e) {
    std::cerr << "Test " << name << " FAILED." << std::endl;
    ++numberFailed;
    return false;
  }
}

}


}

/******************************************************************************
* MAIN ************************************************************************
******************************************************************************/


int main(
    int argc,
    char ** argv)
{
  // make sure we don't have any useless arguments
  if (argc > 1) {
    for (int i=1; i<argc; ++i) {
      std::cerr << "Unused parameter: " << argv[i] << std::endl;
    }
    return 2;
  }



  if (DomTest::numberPassed == 0 && DomTest::numberFailed == 0) {
    std::cerr << "No tests run." << std::endl;
    return 3;
  }

  std::cout << DomTest::numberPassed << " tests passed." << std::endl;
  std::cout << DomTest::numberFailed << " tests failed." << std::endl;
  
  if (DomTest::numberFailed == 0) {
    return 0;
  } else {
    return 1;
  }
}




#endif
