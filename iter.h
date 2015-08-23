#ifndef ITERATOR_H
#define ITERATOR_H

#include <iterator>
#include <vector>

using namespace std;

template<typename T>
class Iter : public iterator<forward_iterator_tag, T> {
public:
   enum Pos {BEG, END};

   Iter(vector< vector<T> > &vv, Pos p = BEG);
   Iter(const Iter &i);
   Iter& operator=(const Iter &i);
   Iter& set_iter(vector< vector<T> > &vv);
   bool operator!=(const Iter &r);
   bool operator==(const Iter &r);
   Iter& operator++();
   Iter operator++(int zero);
   T& operator*();

private:
   typename vector<T>::iterator _i;
   vector< typename vector<T>::iterator > _ends;
   vector< vector<T> > *_vv;
   int _row, _last_row;
};

template<typename T>
Iter<T>::Iter(vector< vector<T> > &vv, Pos p) : _i(vv.begin()->begin()), _row(0),
 _last_row(vv.size() - 1), _vv(&vv) {
   for (int i = 0; i < vv.size(); ++i)
      _ends.push_back(vv[i].end());

   if (p == END) {
      _row = _last_row = vv.size() - 1;
      _i = vv[_last_row].end();
   }
}

template<typename T>
Iter<T>::Iter(const Iter &i) : _i(i._i), _ends(i._ends), _row(i._row), 
 _vv(i._vv), _last_row(i._last_row) {}

template<typename T>
Iter<T>& Iter<T>::operator=(const Iter &i) {
   _i = i._i;
   _ends = i._ends;
   _row = i._row;
   _last_row = i._last_row;
   _vv = i._vv;
   return *this;
}

template<typename T>
Iter<T>& Iter<T>::set_iter(vector< vector<T> > &vv) {
   _i = vv.begin()->begin();
   _row = 0;
   for (int i = 0; i < vv.size(); ++i)
      _ends.push_back(vv[i].end());
   _last_row = vv.size() - 1;
   _vv = &vv;
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
   if (++_i == _ends[_row] && _row != _last_row)
      _i = (*_vv)[++_row].begin();
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
