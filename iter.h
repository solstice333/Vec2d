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
   Iter& set_iter(vector< vector<T> > &vv, Pos p = BEG);
   bool operator!=(const Iter &r);
   bool operator==(const Iter &r);
   Iter& operator++();
   Iter operator++(int zero);
   T& operator*();

private:
   void dynamic_construction(Pos p);

   typename vector<T>::iterator _i;
   vector< typename vector<T>::iterator > _ends;
   vector< vector<T> > *_vv;
   vector< vector<T> > _dummy;
   int _row, _last_row;
};

template<typename T>
void Iter<T>::dynamic_construction(Pos p) {
   if (_vv->size() > 0) {
      _i = _vv->begin()->begin();
      for (int i = 0; i < _vv->size(); ++i)
         _ends.push_back((*_vv)[i].end());

      if (p == END) {
         _row = _last_row;
         _i = (*_vv)[_last_row].end(); 
      }
   }
   else {
      _i = _dummy[0].begin();
      _row = _last_row = 0;
   }
}

template<typename T>
Iter<T>::Iter(vector< vector<T> > &vv, Pos p) : _row(0),
 _last_row(static_cast<int>(vv.size()) - 1), _vv(&vv), _dummy(1) {
    dynamic_construction(p);
}

template<typename T>
Iter<T>::Iter(const Iter &i) : _i(i._i), _ends(i._ends), _row(i._row), 
 _vv(i._vv), _last_row(i._last_row), _dummy(i._dummy) {}

template<typename T>
Iter<T>& Iter<T>::operator=(const Iter &i) {
   _i = i._i;
   _ends = i._ends;
   _row = i._row;
   _last_row = i._last_row;
   _vv = i._vv;
   _dummy = i._dummy;
   return *this;
}

template<typename T>
Iter<T>& Iter<T>::set_iter(vector< vector<T> > &vv, Pos p) {
   _row = 0;
   _last_row = static_cast<int>(vv.size()) - 1;
   _vv = &vv;
   _dummy.resize(1);
   dynamic_construction(p);
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
