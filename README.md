# crc

CRC-8 CRC-16 CRC-32 循环冗余校验码 代码实现

技术博文参考：<https://seedeer.github.io/2022/03/20/crc/>

网页在线计算：<http://www.ip33.com/crc.html>

bilibili:<https://www.bilibili.com/video/BV1V4411Z7VA/?spm_id_from=333.337.search-card.all.click&vd_source=7a95184f6ac08f37f2e1fc1ee4a4467c>

`scripts` 路径下有python3版本

使用cmake 可以编译为so文件，编译选项`CUSTOM_COMPILE_OPTIONS`设置为"1"为编译为so，"0"就是可执行文件

其中，编译为so文件时，会将头文件一并放入编译路径，与so同路径

如果要加入到其它cmake工程中：

需要在`CMakeLists.txt`文件末尾加入：`add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/crc)`

这里假设crc这个文件夹放到了与外层cmake文件同级的路径

`crc.h`头文件和`libcrc.so`文件会被放到主cmake路径下生成的build内的crc文件夹里
