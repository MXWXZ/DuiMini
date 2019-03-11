/** @file
 * Test for resource style and resloader
 *
 *
 * @author  MXWXZ
 * @date    2019/03/09
 */
#include "googletest/googletest/include/gtest/gtest.h"
#include "Core/Resource/UIResource.h"
#include "Core/Resource/UIResLoader.hpp"
#include <fstream>
#include <iterator>
#include <algorithm>
#include <cstdlib>

using namespace std;
using namespace DuiMini;

bool WriteFile(const char* filename, const void* buffer, long size);
bool CmpFile(const char* file1, const char* file2);
bool TestLoad();

TEST(Core_Resource, UIResource) {
    // plain file
    UIResource::SetResMode(kRT_File, "TestRes/uires");
    EXPECT_TRUE(TestLoad());

    // zip file
    UIResource::SetResMode(kRT_Package, "TestRes/uires.zip");
    EXPECT_TRUE(TestLoad());

    // raw file
#ifdef _WIN32
    system("ResPacker.exe HostFile.exe TestRes/uires.zip");
    system("HostFile.exe");
    UIResource::SetResMode(kRT_Raw, "HostFile.exe");
    EXPECT_TRUE(TestLoad());
    EXPECT_EQ(remove("HostFile.exe"), 0);
    EXPECT_EQ(rename("HostFile.exe.bak", "HostFile.exe"), 0);
#else
    system("./ResPacker HostFile TestRes/uires.zip");
    system("chmod +x HostFile");
    system("./HostFile");
    UIResource::SetResMode(kRT_Raw, "HostFile");
    EXPECT_TRUE(TestLoad());
    EXPECT_EQ(remove("HostFile"), 0);
    EXPECT_EQ(rename("HostFile.bak", "HostFile"), 0);
    system("chmod +x HostFile");
#endif
}

TEST(Core_Resource, UIResLoader) {
    UIResource::SetResMode(kRT_File, "TestRes");
    auto file = UIResource::LoadRes<UIXmlLoader>("testxml.xml", true);
    ASSERT_TRUE(file);

    auto root = file->GetRoot();
    ASSERT_TRUE(root);
    EXPECT_EQ(root.GetName(), "root");
    EXPECT_EQ(root.FirstAttribute().GetName(), "title");
    EXPECT_EQ(root.FirstAttribute().GetValue(), "abc");
    ASSERT_FALSE(root.FirstAttribute().NextAttribute());
    ASSERT_FALSE(root.NextSibling());

    root = root.FirstChild();
    ASSERT_TRUE(root);
    EXPECT_EQ(root.GetName(), "inroot");
    ASSERT_FALSE(root.FirstAttribute());

    auto inner = root.FirstChild();
    ASSERT_TRUE(inner);
    EXPECT_EQ(inner.GetName(), "ctrl");
    EXPECT_EQ(inner.FirstAttribute().GetName(), "name");
    EXPECT_EQ(inner.FirstAttribute().GetValue(), "123");
    EXPECT_EQ(inner.GetAttrValue("pos"), "4,5");

    inner = inner.NextSibling();
    ASSERT_TRUE(inner);
    EXPECT_EQ(inner.GetName(), "ctrl");
    ASSERT_FALSE(inner.FirstAttribute());
    ASSERT_FALSE(inner.NextSibling());

    root = root.NextSibling();
    ASSERT_TRUE(root);
    EXPECT_EQ(root.GetName(), "ctrl2");
    EXPECT_EQ(root.GetAttrValue("name"), "abc");
    ASSERT_FALSE(root.NextSibling());
}

bool TestLoad() {
    shared_ptr<UIRawLoader> file;
    if (!(file = UIResource::LoadRes<UIRawLoader>("picture.png")) ||
        !WriteFile("test.png", file->GetFile(), file->GetFileSize()) ||
        !CmpFile("TestRes/uires/picture.png", "test.png") || remove("test.png"))
        return false;
    if (!(file = UIResource::LoadRes<UIRawLoader>("plaintext.txt")) ||
        !WriteFile("test.txt", file->GetFile(), file->GetFileSize()) ||
        !CmpFile("TestRes/uires/plaintext.txt", "test.txt") ||
        remove("test.txt"))
        return false;
    if (!(file = UIResource::LoadRes<UIRawLoader>("inner/picture.png")) ||
        !WriteFile("test.png", file->GetFile(), file->GetFileSize()) ||
        !CmpFile("TestRes/uires/inner/picture.png", "test.png") ||
        remove("test.png"))
        return false;
    if (!(file = UIResource::LoadRes<UIRawLoader>("inner/plaintext.txt")) ||
        !WriteFile("test.txt", file->GetFile(), file->GetFileSize()) ||
        !CmpFile("TestRes/uires/inner/plaintext.txt", "test.txt") ||
        remove("test.txt"))
        return false;
    return true;
}

bool WriteFile(const char* filename, const void* buffer, long size) {
    auto fp = shared_ptr<FILE>(fopen(filename, "wb"), [](FILE* fp) {
        if (fp)
            fclose(fp);
    });
    if (!fp)
        return false;
    if (fwrite(buffer, size, 1, fp.get()) != 1)
        return false;
    return true;
}

bool CmpFile(const char* file1, const char* file2) {
    ifstream f1(file1, ifstream::binary | ifstream::ate);
    ifstream f2(file2, ifstream::binary | ifstream::ate);

    if (f1.fail() || f2.fail())
        return false;
    if (f1.tellg() != f2.tellg())
        return false;

    f1.seekg(0, ifstream::beg);
    f2.seekg(0, ifstream::beg);
    return equal(istreambuf_iterator<char>(f1.rdbuf()),
                 istreambuf_iterator<char>(),
                 istreambuf_iterator<char>(f2.rdbuf()));
}
