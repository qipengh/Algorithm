
@(Hello Cpp)[code | c++]

# C++
[官网](http://www.cplusplus.com/)



## 容器

### vector

#### 列表

注：非备注，则为共有成员函数
**成员函数:**
```md
- (constructor)
Construct vector (public member function )
- (destructor)
Vector destructor (public member function )
- operator=
Assign content (public member function )
```

**Iterators(迭代器):**
```md
- begin
Return iterator to beginning (返回处于 起始 位置的迭代器)
- end
Return iterator to end (返回处于 末尾 位置的迭代器)
- rbegin
Return reverse iterator to reverse beginning (返回处于 反向起始 位置的 反向 迭代器)
- rend
Return reverse iterator to reverse end (返回处于 反向末尾 位置的 反向 迭代器)
- cbegin 
Return const_iterator to beginning (返回处于 起始 位置的 常量 迭代器). `C++11`
- cend 
Return const_iterator to end (返回处于 末尾 位置的 常量 迭代器). `C++11`
- crbegin 
Return const_reverse_iterator to reverse beginning (返回处于 反向起始 位置的 反向常量 迭代器). `C++11`
- crend 
Return const_reverse_iterator to reverse end (返回处于 反向末尾 位置的 反向常量 迭代器). `C++11`
```

**Capacity(容量):**
```md
- size
Return size (返回 尺寸)
- max_size
Return maximum size (返回 最大尺寸)
- resize
Change size (改变 尺寸). 
- capacity
Return size of allocated storage capacity (返回 已分配存储容量的大小)
- empty
Test whether vector is empty (测试 vector 是否为空)
- reserve
Request a change in capacity (请求改变 容量)
- shrink_to_fit 
Shrink to fit (缩小以适应). `C++11`
```

**Element access(元素访问):**
```md
- operator[]
Access element (访问 元素)
- at
Access element (访问 元素)
- front
Access first element (访问 第一个 元素)
- back
Access last element (访问 最后一个 元素)
- data 
Access data (访问 数据). `C++11`
```

**Modifiers(修改器):**
```md
- assign
Assign vector content (分配 vector 内容)
- push_back
Add element at the end (在 末尾 添加元素)
- pop_back
Delete last element (删除 最后一个 元素)
- insert
Insert elements (插入元素)
- erase
Erase elements (删除元素)
- swap
Swap content (交换内容)
- clear
Clear content (清除内容)
- emplace 
Construct and insert element (构造并插入元素). `C++11`
- emplace_back 
Construct and insert element at the end (构造并在末尾插入元素). `C++11`
```

**Allocator(分配器):**
```md
- get_allocator
Get allocator (获取分配器)
```

**Non-member function overloads(非成员函数重载):**
```md
- relational operators
Relational operators for vector (function template )
- swap
Exchange contents of vectors (function template )
```

**Template specializations(模板特殊化):**
```md
- vector<bool>
Vector of bool (class template specialization )
```

#####　初始化
```cpp

```
