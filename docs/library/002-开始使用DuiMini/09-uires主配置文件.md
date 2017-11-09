# uires主配置文件
## 皮肤设置
```xml
<style type="skin" name="default" value="skin\default" />
<style type="skin" name="testskin" value="skin\testskin" />
<style type="skin" name="system" value="skin\system" system="1" />
```
`name`：皮肤名，调用`UISystem::SetDefaultSkin`来设置默认皮肤（默认为名称为`default`的皮肤）
`value`：皮肤目录路径
`system`：默认为0，为1则为系统皮肤（更换皮肤后依然可用，可不唯一）

## 语言设置
```xml
<res type="lang" name="zh-cn" file="string\zh-CN.xml" />
```
`name`：语言名（建议使用语言代码）
`file`：xml文件名
