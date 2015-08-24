#ifndef VEC2D_H
#define VEC2D_H

#include <vector>
#include "iter.h"

using namespace std;

template<typename T> 
class Vec2d {
   enum Pos {BEG, END};
public:
   class iterator : public Iter<T> {
   public:
      iterator(vector< vector<T> > &vv, Pos p = BEG);
      iterator(const iterator &i);
   };

   // default constructor : constructs empty 2d vector
   Vec2d();

   // second constructor : constructs 2d vector of |row| rows and |col|
   // columns. Populates indices with copies of |obj|. Uses the default
   // constructor T() if |obj| isn't specified.
   Vec2d(int row, int col, T obj = T());

   // vector<T>& operator[](const int idx) : overloads operator []. Accesses
   // row |idx| and returns a vector<T>. A secondary [] will access the integer
   // at that column specified. For example, matrix[row][column] will return
   // a value of type T, whereas matrix[row] will return a vector<T>.
   vector<T>& operator[](const int idx);

   // int get_num_rows() : returns the number of rows in the 2d vector
   int get_num_rows();

   // int get_num_cols() : return the maximum number of columns that the
   // 2d vector has
   int get_num_cols();

   // int add_rows(int rows = 1, T obj = T()) : adds |rows| rows to the Vec2d
   // object where each row contains |obj|. Returns the new number of rows.
   int add_rows(int rows = 1, T obj = T());

   // int add_cols(int cols = 1, T obj) : adds |cols| columns to the Vec2d
   // object containing |obj|. Returns the new number of columns.
   int add_cols(int cols = 1, T obj = T());

   // iterator begin(): returns a forward iterator object. The iterator will
   // traverse the 2d vector left to right, top to bottom using the 
   // post-increment or pre-increment operator. If used on an empty Vec2d,
   // begin() and end() return the same result.
   iterator begin();

   // iterator end(): returns an iterator pointing to passed the end of the 
   // 2d vector which is a non-element. Thus, do not dereference this. If
   // used on an empty Vec2d, begin() and end() return the same result.
   iterator end();

private:
   vector< vector<T> > _v;
};

template<typename T> 
Vec2d<T>::Vec2d() {}

template<typename T> 
Vec2d<T>::Vec2d(int row, int col, T obj) : _v(row) {
   for (int i = 0; i < _v.size(); ++i)
      _v[i].resize(col, obj);
}

template<typename T> 
int Vec2d<T>::get_num_rows() {
   return _v.size();
}

template<typename T> 
int Vec2d<T>::get_num_cols() {
   int largest_size = 0;

   if (_v.size() > 0) {
      largest_size = _v[0].size();
      for (int i = 1; i < _v.size(); ++i) {
         int num_cols = _v[i].size();
         if (num_cols > largest_size)
            largest_size = num_cols;
      }
   }

   return largest_size;
}

template<typename T>
int Vec2d<T>::add_rows(int rows, T obj) {
   int cols = get_num_cols();
   if (!cols)
      cols = 1;

   vector<T> new_row(cols, obj);
   for (int i = 0; i < rows; ++i)
      _v.push_back(new_row);
   return get_num_rows();
}

template<typename T>
int Vec2d<T>::add_cols(int cols, T obj) {
   int rows = get_num_rows();
   if (!rows) {
      vector<T> r;
      _v.push_back(r);
   }

   for (int i = 0; i < _v.size(); ++i)
      for (int j = 0; j < cols; ++j)
         _v[i].push_back(obj);

   return get_num_cols();
}

template<typename T> 
vector<T>& Vec2d<T>::operator[](const int idx) {
   return _v[idx];
}

template<typename T> 
typename Vec2d<T>::iterator Vec2d<T>::begin() {
   return iterator(this->_v);
}

template<typename T> 
typename Vec2d<T>::iterator Vec2d<T>::end() {
   return iterator(this->_v, END);
}

template<typename T> 
Vec2d<T>::iterator::iterator(vector< vector<T> > &vv, Pos p) : 
 Iter<T>(vv, static_cast<typename Iter<T>::Pos>(p)) {}

template<typename T> 
Vec2d<T>::iterator::iterator(const iterator &i) : 
 Iter<T>(i) {}

#endif
