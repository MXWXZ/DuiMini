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

TEST(Utils_Utils, UIString) {
    UIString str = "1234567890";
    EXPECT_EQ(str.Str2LL(), 1234567890);
    str = "12345.6789";
    EXPECT_EQ(str.Str2Double(), 12345.6789);
    str = "abc123JKL";
    EXPECT_EQ(str.Str2Hex(), "6162633132334A4B4C");
    str = "6162633132334A4B4C";
    EXPECT_EQ(str.Hex2Str(), "abc123JKL");
    str = "1234567890";
    EXPECT_EQ(str.UL2Hex(), "499602D2");
    str = "499602D2";
    EXPECT_EQ(str.Hex2UL(), 1234567890);
}

TEST(Utils_Utils, UIUtils) {
    EXPECT_EQ(UIUtils::GetColorFromStr("#00000000"), UIColor(0, 0, 0, 0));
    EXPECT_EQ(UIUtils::GetColorFromStr("#FFFFFFFF"),
              UIColor(0xFF, 0xFF, 0xFF, 0xFF));
    EXPECT_EQ(UIUtils::GetColorFromStr("#67890A"),
              UIColor(0x67, 0x89, 0x0A, 0xFF));
    EXPECT_EQ(UIUtils::GetColorFromStr("black"), UIColor(0, 0, 0));
    EXPECT_EQ(UIUtils::GetColorFromStr("white"), UIColor(0xFF, 0xFF, 0xFF));
    EXPECT_EQ(UIUtils::GetColorFromStr("red"), UIColor(0xFF, 0, 0));
    EXPECT_EQ(UIUtils::GetColorFromStr("green"), UIColor(0, 0xFF, 0));
    EXPECT_EQ(UIUtils::GetColorFromStr("blue"), UIColor(0, 0, 0xFF));
    EXPECT_EQ(UIUtils::GetColorFromStr("yellow"), UIColor(0xFF, 0xFF, 0));
    EXPECT_EQ(UIUtils::GetColorFromStr("cyan"), UIColor(0, 0xFF, 0xFF));
    EXPECT_EQ(UIUtils::GetColorFromStr("purple"), UIColor(0xFF, 0, 0xFF));
    EXPECT_EQ(UIUtils::GetColorFromStr("gray"), UIColor(0xC0, 0xC0, 0xC0));
    EXPECT_EQ(UIUtils::GetColorFromStr("transparent"), UIColor(0, 0, 0, 0));
}
