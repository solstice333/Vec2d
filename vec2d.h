#ifndef VEC2D_H
#define VEC2D_H

#include <vector>

using namespace std;

template<typename T> 
class Vec2d {
public:
   Vec2d();
   Vec2d(int row, int col);
   vector<T>& operator[](const int idx);
   int get_num_rows();
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



#endif
