#ifndef VEC2D_H
#define VEC2D_H

#include <vector>
#include <iterator>

using namespace std;

template<typename T> 
class Vec2d {
public:
   Vec2d();
   Vec2d(int row, int col);
   vector<T>& operator[](const int idx);
   int get_num_rows();

   class Iterator : public iterator<forward_iterator_tag, T> {
   public:
      Iterator(T *i);
      Iterator(const Iterator &i);
      Iterator& operator=(T *i);
      Iterator& set_iter(T *i);
      bool operator!=(const Iterator &r);
      bool operator==(const Iterator &r);
      Iterator& operator++();
      Iterator operator++(int zero);
      T& operator*();
   private:
      T *_i;
   };
   
private:
   vector< vector<T> > _v;
};

template<typename T> 
Vec2d<T>::Vec2d() {}

template<typename T> 
Vec2d<T>::Vec2d(int row, int col) : _v(row) {
   for (int i = 0; i < _v.size(); ++i)
      _v[i].resize(col);
}

template<typename T> 
int Vec2d<T>::get_num_rows() {
   return _v.size();
}

template<typename T> 
vector<T>& Vec2d<T>::operator[](const int idx) {
   return _v[idx];
}

template<typename T>
Vec2d<T>::Iterator::Iterator(T *i) : _i(i) {}

template<typename T>
Vec2d<T>::Iterator::Iterator(const Iterator &I) : _i(I._i) {}

template<typename T>
typename Vec2d<T>::Iterator& Vec2d<T>::Iterator::operator=(T *i) {
   _i = i;
   return *this;
}

template<typename T>
typename Vec2d<T>::Iterator& Vec2d<T>::Iterator::set_iter(T *i) {
   _i = i;
   return *this;
}

template<typename T>
bool Vec2d<T>::Iterator::operator!=(const Iterator &r) {
   return this->_i != r._i;
}

template<typename T>
bool Vec2d<T>::Iterator::operator==(const Iterator &r) {
   return this->_i == r._i;
}

template<typename T>
typename Vec2d<T>::Iterator& Vec2d<T>::Iterator::operator++() {
   ++_i;
   return *this;
}

template<typename T>
typename Vec2d<T>::Iterator Vec2d<T>::Iterator::operator++(int zero) {
   Iterator tmp(*this);
   operator++();
   return tmp;
}

template<typename T>
T& Vec2d<T>::Iterator::operator*() {
   return *_i;
}

#endif
