#include <cstdio>
#include <cstring>
#include <iostream>
#include <assert.h>
#include "iter.h"
#include "vec2d.h"

using namespace std;

// iterator_tests() : tests the public Iter class logic.
void iterator_tests() {
   vector< vector<int> > vv(2);
   int val = 0;

   // populate 2d vec
   for (auto i = vv.begin(), end_i = vv.end(); i != end_i; ++i) {
      i->resize(2);
      for (auto j = i->begin(), end_j = i->end(); j != end_j; ++j)
         *j = ++val;
   }

   // test print
   val = 0;
   cout << "2d vector contents" << endl;
   for (int i = 0; i < vv.size(); ++i) {
      for (int j = 0; j < vv[i].size(); ++j) {
         if (j > 0)
            cout << ", ";
         assert(vv[i][j] == ++val);
         cout << vv[i][j];
      }
      cout << endl;
   }
   cout << "end of contents" << endl;

   // test iterator pre-incr with 2d vecs
   Iter<int> itr(vv);
   int columns;

   if (vv.size() > 0)
      columns = vv[0].size();

   for (int i = 0; i < vv.size() * columns; ++i, ++itr)
      assert(*itr == i + 1);

   // test iter set_iter, get_end, != overload, post-incr, * deref
   vector<int> v(2);
   v[0] = 5;
   v[1] = 6;
   vv.push_back(v); 

   itr.set_iter(vv);
   Iter<int> end(vv, Iter<int>::END);

   for (int val = 1; itr != end; itr++, ++val)
      assert(*itr == val);

   // test == overload
   itr.set_iter(vv);
   Iter<int> other_itr(vv);
   assert(itr == other_itr);
   assert(!(++itr == other_itr));

   // test copy constructor
   Iter<int> copy_itr(itr++);
   assert(copy_itr != itr);
   ++itr;
   assert(copy_itr != itr);
   ++copy_itr;
   ++copy_itr;
   assert(copy_itr == itr);

   // test assignment overload
   itr.set_iter(vv);
   copy_itr = itr;
   ++itr;
   assert(copy_itr != itr);
   ++copy_itr;
   assert(copy_itr == itr);
}

// internal_iterator_tests() : tests the iterator interface within Vec2D
void internal_iterator_tests() {
   Vec2d<int> matrix(3, 2);
   Vec2d<int>::iterator test_begin = matrix.begin();
   Vec2d<int>::iterator test_end = matrix.end();

   for (int i = 0; i < matrix.get_num_rows(); ++i) {
      for (int j = 0; j < matrix.get_num_cols(); ++j)
         matrix[i][j] = i + j;
   }

   cout << "2d vector contents" << endl;
   for (int i = 0; i < matrix.get_num_rows(); ++i) {
      for (int j = 0; j < matrix.get_num_cols(); ++j) {
         if (j > 0)
            cout << ", ";
         cout << matrix[i][j];
      }
      cout << endl;
   }
   cout << "end of contents" << endl;

   int cols = matrix.get_num_cols();
   int rows = matrix.get_num_rows();
   int i = 0, j = 0;
   for (auto itr = matrix.begin(), end = matrix.end(); itr != end; ++itr) {
      cout << *itr << endl;

      if (i >= cols) {
         i = 0;
         ++j;
      }
      assert(*itr == matrix[j][i++]);
   }
}

// constructor_tests_vec2d() : tests constructor and a few helper methods
void constructor_tests_vec2d() {
   Vec2d<int> matrix;
   Vec2d<int> matrix1(3, 2);

   assert(matrix1.get_num_rows() == 3);
   assert(matrix1.get_num_cols() == 2);
   matrix1[0][0] = 90;
   assert(matrix1[0][0] == 90);
   matrix1[0][1] = 80;
   assert(matrix1[0][1] == 80);
   matrix1[0][0] = 100;
   assert(matrix1[0][0] == 100);
}

int main() {
   constructor_tests_vec2d();
   iterator_tests();
   internal_iterator_tests();
}