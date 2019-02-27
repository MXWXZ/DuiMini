#include "DuiMini.h"
#include <iostream>

using namespace DuiMini;
using namespace std;

int main() {
    UIResource::SetResMode(kRT_File, "uires");
    //     auto test = UIResource::LoadRes<UIRawLoader>("uires/1.txt");
    //     cout << (unsigned char*)test->GetFile() << endl;
    //     cout << test->GetFileSize();
    getchar();
    return 0;
}