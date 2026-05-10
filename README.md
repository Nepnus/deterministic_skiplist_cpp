<img width="1463" height="414" alt="skiplist_example" src="https://github.com/user-attachments/assets/d988f662-c881-46eb-94d3-5eb8f9a8de82" />

## 简介

这是一个基于C++的1-2-3确定性跳跃表模板，做到了以O(log N)的时间复杂度执行查找、增加、(非惰性)删除节点。同时，为了高效执行查增删操作，内部还实现了一个小型的内存池。

## 使用

1. 你需要提前编译所有`mempool_*.cpp`文件。

2. 使用如下代码生成一个针对类型T的最大高度为100的跳跃表对象`list_obj`。其中，最大高度可以缺省，缺省值为60，类型T必须定义了运算符"<"和"=="。

``` C++
#include "skiplist.h"
skipList<T, 100> list_obj;
```

3. 向跳跃表中增加元素`a`的成员函数的声明如下。返回值为0代表插入成功，1代表因跳跃表已经达到最大高度而无法插入，2代表因堆内存空间不足而无法插入，3代表跳跃表中已存在该元素而无法插入。注意，该跳跃表模板不支持重复元素。

``` C++
short skipList<T, maxheight, iftypeok>::insert(const T& a);
```

4. 向跳跃表中删除元素`a`的成员函数的声明如下。返回值为0代表删除成功，1代表跳跃表中无该元素，2代表因堆内存空间不足而无法删除。

``` C++
short skipList<T, maxheight, iftypeok>::del(const T& a);
```

5. 向跳跃表中查找元素`a`是否存在的成员函数的声明如下。返回值为`true`代表跳跃表中存在该元素，`false`则反之。

``` C++
bool skipList<T, maxheight, iftypeok>::find(const T& a);
```

6. 清理内部内存池空闲空间的成员函数的声明如下。注意，该操作不会对跳跃表的内部结构产生任何影响，也不会向跳跃表增加/删除任何元素，该操作仅仅是将内部内存池的空闲内存页释放，

``` C++
void skipList<T, maxheight, iftypeok>::free_memory();
```

## 注意

1. 跳跃表内部存储的是指向元素的指针，所以，请你确保元素的生命周期不小于跳跃表对象的生命周期。如果确实存在元素的生命周期要小于跳跃表对象的情况，请提前调用成员函数`del(const T& a)`删除之。

2. 该跳跃表模板禁用复制构造函数与赋值运算，未添加移动构造函数。

