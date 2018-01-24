# uires主配置文件
调用`UIConfig::LoadConfig(LPCTSTR v_relativepath = DEFAULT_RESFILE);`来加载配置文件，默认为`uires.xml`文件。

请保证`root`为唯一根节点。
## DLG设置
```xml
<res type="dlg" name="main" file="xml\main.xml" />
```
- `name`：xml名
- `file`：文件名

<br>
**注意！下面每项配置请保留唯一一条作为默认配置！**

**请保证语言设置在字体设置之前！否则默认字体将会异常！**
## 皮肤设置
```xml
<style type="skin" name="default" value="skin\default" default="1" />
<style type="skin" name="testskin" value="skin\testskin" />
<style type="skin" name="system" value="skin\system" system="1" />
```
- `name`：皮肤名
- `value`：皮肤目录路径
- `system`：默认为0，为1则为系统皮肤（更换皮肤后依然可用，可不唯一）
- `default`：默认为0，为1则是默认皮肤（请保留唯一一条作为默认配置）

*注：当`system`属性为`1`时`default`属性将被设为0*

## 语言设置
```xml
<res type="lang" lang="zh-cn" file="string\zh-CN.xml" default="1" />
<res type="lang" lang="en-us" file="string\en-US.xml" />
```
- `name`：语言名（建议使用语言代码）
- `file`：xml文件名
- `default`：默认为0，为1则是默认语言（请保留唯一一条作为默认配置）

## 字体设置
```xml
<style type="font" lang="zh-cn" name="default" font="Microsoft YaHei UI" size="12" default="1" />
<style type="font" lang="en-us" name="default" font="Segoe UI" size="12" default="1" />
```
- `lang`：语言名
- `name`：字体名
- `font`：字体名
- `size`：磅数
- `bold`：默认为0,，为1加粗
- `italic`：默认为0,，为1斜体
- `underline`：默认为0,，为1下划线
- `strikeout`：默认为0,，为1删除线
- `default`：默认为0，为1则是**当前语言**下的默认字体（请为**每个语言**保留唯一一条作为默认配置）
