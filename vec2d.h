#ifndef VEC2D_H
#define VEC2D_H

#include <vector>
#include "iter.h"

using namespace std;


template<typename T> 
class Vec2d {
   enum Pos {BEG, END};
public:
   Vec2d();
   Vec2d(int row, int col);
   vector<T>& operator[](const int idx);
   int get_num_rows();

   class iterator : public Iter<T> {
      iterator(vector< vector<T> > &vv, Pos p = BEG);
      iterator(const iterator &i);
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
Vec2d<T>::iterator::iterator(vector< vector<T> > &vv, Pos p) : 
 Iter<T>(vv, p) {}

template<typename T> 
Vec2d<T>::iterator::iterator(const iterator &i) : 
 Iter<T>(i) {}

#endif
