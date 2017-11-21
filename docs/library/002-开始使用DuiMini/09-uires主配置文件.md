# uires主配置文件
## 皮肤设置
```xml
<style type="skin" name="default" value="skin\default" />
<style type="skin" name="testskin" value="skin\testskin" />
<style type="skin" name="system" value="skin\system" system="1" />
```
`name`：皮肤名，默认名称为`default`的皮肤
`value`：皮肤目录路径
`system`：默认为0，为1则为系统皮肤（更换皮肤后依然可用，可不唯一）

## 字体设置
```xml
<style type="font" lang="zh-cn" name="default" font="Microsoft YaHei UI" size="12" />
<style type="font" lang="en-us" name="default" font="Segoe UI" size="12" />
```
`lang`：语言名
`name`：`default`为默认字体
`font`：字体名
`size`：磅数

## 语言设置
```xml
<res type="lang" name="zh-cn" file="string\zh-CN.xml" />
```
`name`：语言名（建议使用语言代码）
`file`：xml文件名
