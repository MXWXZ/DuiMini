/**
 * Copyright (c) 2019-2050
 * All rights reserved.
 *
 * @author  MXWXZ
 * @date    2019/02/28
 */
#include "googletest/googletest/include/gtest/gtest.h"
#include "Utils/UIUtils.h"
using namespace DuiMini;

#define TESTSTR "Test123!@#"

TEST(Utils_Utils, UIString) {
    // assume UIString::UIString(const char* str); must
    // correct
    UIString str1(TESTSTR);
    EXPECT_STREQ(str1.GetData(), TESTSTR);
    EXPECT_EQ(str1, TESTSTR);  // test "="
    UIString str2('a');
    EXPECT_EQ(str2, "a");
    UIString str3(TESTSTR, 4);
    EXPECT_EQ(str3, "Test");

    UIString str = TESTSTR;
    EXPECT_EQ(str, TESTSTR);
    EXPECT_EQ(str.IsEmpty(), false);
    str.Empty();
    EXPECT_EQ(str.IsEmpty(), true);
}
