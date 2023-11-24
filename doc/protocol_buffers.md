# Protocol Buffers with Reflection

## 如何用 PB 在 C++ 程序里实现函数反射？

反射编程 (reflection programming) 的目的是使的程序在运行时对自身信息 (metadata 元数据) 的检测 (内省 type introspection)，以及改变程序状态和结构 (反射 reflection)。

反射编程的核心是元数据（关于数据的数据），即程序解释自身的数据。

C++的编译结果中只会包含变量、函数地址偏移、函数关系等。

Protocol Buffers 是 Google 的数据序列化工具。//Google's data interchange format

用法：->设计数据结构体 `.proto` -> `proto.exe` 编译-> 自动生成 `.cc .h` 文件 -> 加入工程 -> 使用 `.cc .h` 提供的输入输出处理文件。

### 如何从 protobuf 序列化的文件中通过反射程序获取任意关键字的值？







