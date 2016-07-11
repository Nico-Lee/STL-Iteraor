#include<iostream>
#include"list.h"
using namespace std;

struct InputIteratorTag{};
struct OutputIteratorTag{};
struct ForwardIteratorTag :public InputIteratorTag{};
struct BidirectionalIteratorTag :public InputIteratorTag{};
struct RandomAccessIteratorTag :public InputIteratorTag{};


//Distance是迭代器之间的距离
template<class T,class Distance>
struct InputIterator
{
	typedef InputIteratorTag CategoryIterator;
	typedef T ValueType;
	typedef Distance DifferenceType;
	typedef T* Pointer;
	typedef T& Reference;
};
template<class T, class Distance>
struct OutputIterator
{
	typedef OutputIteratorTag CategoryIterator;
	typedef T ValueType;
	typedef Distance DifferenceType;
	typedef T* Pointer;
	typedef T& Reference;
};

template<class T, class Distance>
struct ForwardIterator
{
	typedef ForwardIteratorTag CategoryIterator;
	typedef T ValueType;
	typedef Distance DifferenceType;
	typedef T* Pointer;
	typedef T& Reference;
};

template<class T, class Distance>
struct BidirectionalIterator
{
	typedef BidirectionalIteratorTag CategoryIterator;
	typedef T ValueType;
	typedef Distance DifferenceType;
	typedef T* Pointer;
	typedef T& Reference;
};


template<class T, class Distance>
struct RandomAccessIterator
{
	typedef RandomAccessIteratorTag CategoryIterator;
	typedef T ValueType;
	typedef Distance DifferenceType;
	typedef T* Pointer;
	typedef T& Reference;
};

//通过Distance来计算两个迭代器之间的距离
//通过Category来确定是前向迭代器还是双向迭代器，还是随机迭代器
template<class T, class Distance, class Category,
class Pointer = T*, class Reference = T&>
struct Iterator
{
	typedef Category CategoryIterator;//迭代器类型
	typedef T ValueType;				//迭代器所指对象的类型
	typedef Distance DifferenceType;	//两个迭代器之间的距离
	typedef Pointer Pointer;			//迭代器所指类型的指针
	typedef Reference Reference;		//迭代器所指类型的引用
};

//把迭代器传入萃取机，可以萃取出迭代器的内嵌类型或者是基本的类型（int等）
/*
每个Iterator内都有一个typedef的IteratorCategory，ValueType，DifferenceType，
Pointer，Reference。IteratorTraits只是一层封装
*/

template<class Iterator>
struct IteratorTraits
{
	typedef typename Iterator::CategoryIterator  IteratorCategory;
	typedef typename Iterator::ValueType ValueType;
	typedef typename Iterator::DifferenceType DifferenceType;
	typedef typename Iterator::Pointer Pointer;
	typedef typename Iterator::Reference Reference;
};


//偏特化原生的类型，为了原生类型而存在的特化
template<class T>
struct IteratorTraits<T*>
{
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef T ValueType;
	typedef ptrdiff_t DifferenceType;
	typedef T* Pointer;
	typedef T& Reference;
};


//如上
template<class T>
struct IteratorTraits<const T*>
{
	typedef RandomAccessIteratorTag IteratorCategory;
	typedef T ValueType;
	typedef ptrdiff_t DifferenceType;
	typedef const T* Pointer;
	typedef const T& Reference;
};


//Distance函数
template <class InputIterator>
inline typename IteratorTraits <InputIterator>::DifferenceType
Distance(InputIterator first, InputIterator last)
{
	//通过传入的InputIterator决定是哪个类型的IteratorCategory对象
	return _Distance(first, last, IteratorTraits <InputIterator>::IteratorCategory());
}


//前向和双向迭代器的Distance函数,都是通过遍历两个迭代器之间的元素实现的
template <class InputIterator>
inline typename IteratorTraits <InputIterator>::DifferenceType
_Distance(InputIterator first, InputIterator last, InputIteratorTag)
{
	IteratorTraits<InputIterator >::DifferenceType n = 0;
	while (first != last) {
		++first; ++n;
	}
	return n;
}

//随机迭代器的distance
template <class RandomAccessIterator>
inline typename IteratorTraits <RandomAccessIterator>::DifferenceType
_Distance(RandomAccessIterator first, RandomAccessIterator last,RandomAccessIteratorTag)
{
	return last - first;
}

// 测试Distance 算法
void Test3()
{
	List<int > l1;
	l1.PushBack(1);
	l1.PushBack(2);
	l1.PushBack(3);
	l1.PushBack(4);
	cout << "List Distance: " << Distance(l1.Begin(), l1.End()) << endl;
	/*Vector<int > v1;
	v1.PushBack(1);
	v1.PushBack(2);
	v1.PushBack(3);
	v1.PushBack(4);
	v1.PushBack(5);
	cout << "Vector Distance: " << Distance(v1.Begin(), v1.End()) << endl;*/
}

//Advance是让迭代器前进n步
template <class InputIterator, class Distance>
inline void Advance(InputIterator & i, Distance n)
{
	_Advance(i, n, IteratorTraits <InputIterator>::IteratorCategory());
}
template <class InputIterator, class Distance>
inline void _Advance(InputIterator & i, Distance n, InputIteratorTag)
{
	while (n--) ++i;
} 
template <class BidirectionalIterator, class Distance>
inline void _Advance(BidirectionalIterator & i, Distance n,
BidirectionalIteratorTag)
{
	if (n >= 0)
		while (n--) ++i;
	else
		while (n++) --i;
} 
template <class RandomAccessIterator, class Distance>
inline void __Advance(RandomAccessIterator & i, Distance n,
RandomAccessIteratorTag)
{
	i += n;
} 

