/** @file
 * Main function for all test.
 *
 * @author  MXWXZ
 * @date    2019/03/09
 */
#include "googletest/googletest/include/gtest/gtest.h"

GTEST_API_ int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}