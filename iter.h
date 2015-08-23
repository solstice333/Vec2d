#ifndef ITERATOR_H
#define ITERATOR_H

#include <iterator>

using namespace std;

template<typename T>
class Iter : public iterator<forward_iterator_tag, T> {
public:
   Iter(T *i);
   Iter(const Iter &i);
   Iter& operator=(T *i);
   Iter& set_iter(T *i);
   bool operator!=(const Iter &r);
   bool operator==(const Iter &r);
   Iter& operator++();
   Iter operator++(int zero);
   T& operator*();
private:
   T *_i;
};

template<typename T>
Iter<T>::Iter(T *i) : _i(i) {}

template<typename T>
Iter<T>::Iter(const Iter &I) : _i(I._i) {}

template<typename T>
Iter<T>& Iter<T>::operator=(T *i) {
   _i = i;
   return *this;
}

template<typename T>
Iter<T>& Iter<T>::set_iter(T *i) {
   _i = i;
   return *this;
}

template<typename T>
bool Iter<T>::operator!=(const Iter &r) {
   return this->_i != r._i;
}

template<typename T>
bool Iter<T>::operator==(const Iter &r) {
   return this->_i == r._i;
}

template<typename T>
Iter<T>& Iter<T>::operator++() {
   ++_i;
   return *this;
}

template<typename T>
Iter<T> Iter<T>::operator++(int zero) {
   Iter tmp(*this);
   operator++();
   return tmp;
}

template<typename T>
T& Iter<T>::operator*() {
   return *_i;
}

#endif
