#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include "ConstIterator.h"

template<typename Type>
ConstIterator<Type>::ConstIterator() //: BaseIterator<Type>()
{
}

template<typename Type>
ConstIterator<Type>::ConstIterator(const ConstIterator<Type> &it) : BaseIterator<Type>(it)
{
}

template<typename Type>
ConstIterator<Type>::ConstIterator(shared_ptr<Type[]> ptr, int num, int index) : BaseIterator<Type>(ptr, num, index)
{
}

#endif // CONSTITERATOR_HPP
