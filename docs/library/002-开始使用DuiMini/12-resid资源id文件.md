# resid资源id文件
- 每个皮肤目录下都有一个`resid.xml`文件来配置当前皮肤的资源id，可修改`DEFAULT_RESIDFILE`宏来更改此文件名。
- 通过本文件来建立一个资源文件和一个字符串ID的映射，在DLG布局文件中可以直接使用该字符串ID来表示此文件，方便修改和重用。
- 请保证`root`为唯一根节点。
格式：
```xml
<res type="RESTYPE" name="IDNAME" file="FILEPATH" />
```
`type`可以自由定义，资源类型标志
`name`为映射的字符串，注意必须保证唯一且不能出现`.`字符
`file`为文件相对于资源目录路径，如`skin\default\main\eg.png`，所有路径必须出现`.`字符
