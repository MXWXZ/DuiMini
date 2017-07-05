# 创建一个新的DuiMini程序
创建一个WIN32应用程序，然后拷贝DuiMini文件夹到你的工程目录，将其添加入您的“*附加包含目录*”和“*附加库目录*”中，然后在程序中引用  
`#include "DuiMini.h"`  
接着拷贝DuiMini.lib到工程目录下，添加链接库  
`#pragma comment(lib, "DuiMini.lib")`  
最后使用命名空间  
`using namespace DuiMini;`  
整个准备工作就完成了！
