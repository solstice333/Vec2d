#include <cstdio>
#include <cstring>
#include <iostream>
#include <assert.h>
#include "vec2d.h"

#define ITER_PUBLIC 1

using namespace std;

#if ITER_PUBLIC == 1
typedef Vec2d<int>::Iterator Iterator;
#endif

void iterator_tests_int_array() {
#if ITER_PUBLIC == 1
   // iterator tests using single dimension vector
   int my_ints[] = {0, 1, 2, 3, 4};
   Iterator my_iter_beg(my_ints); 
   Iterator my_iter_end(my_ints + sizeof(my_ints)/sizeof(int));

   Iterator my_iter_beg1(my_iter_beg);
   Iterator my_iter_end1(my_ints + sizeof(my_ints)/sizeof(int));

   assert(my_iter_beg == my_iter_beg1);
   assert(!(my_iter_beg == my_iter_end));
   assert(my_iter_beg != my_iter_end);
   assert(!(my_iter_beg != my_iter_beg1));

   Iterator my_iter_next(my_ints + 1);
   assert(typeid(Iterator) == typeid(my_iter_beg));
   assert(typeid(Iterator) == typeid(++my_iter_beg));
   assert(typeid(Iterator) == typeid(my_iter_next));

   assert(my_iter_beg == my_iter_beg1);
   assert(++my_iter_beg != my_iter_beg1);
   my_iter_beg = my_ints;
   assert(my_iter_beg == my_iter_beg1);
   assert(my_iter_beg++ == my_iter_beg1);
   assert(my_iter_beg != my_iter_beg1);

   my_iter_beg = my_ints;
   Iterator *my_iter_ptr = new Iterator(my_ints);
   assert(*my_iter_ptr == my_iter_beg);
   my_iter_ptr->set_iter(my_ints + 1);
   assert(**my_iter_ptr == 1);
   delete my_iter_ptr;
#endif
}

void iterator_tests_vector() {
#if ITER_PUBLIC
   vector< vector<int> > v(2);
   int val = 0;

   // populate 2d vec
   for (auto i = v.begin(), end_i = v.end(); i != end_i; ++i) {
      i->resize(2);
      for (auto j = i->begin(), end_j = i->end(); j != end_j; ++j)
         *j = ++val;
   }

   // test print
   val = 0;
   for (int i = 0; i < v.size(); ++i) {
      for (int j = 0; j < v[i].size(); ++j)
         assert(v[i][j] == ++val);
   }

   // test iterator with 2d vecs
   // Iterator my_iter(&v);
#endif 
}

void constructor_tests_vec2d() {
   Vec2d<int> matrix;
   Vec2d<int> matrix1(3, 2);

   cout << matrix1.get_num_rows() << endl;
   matrix1[0][0] = 90;
   cout << matrix1[0][0] << endl;
   matrix1[0][1] = 80;
   cout << matrix1[0][1] << endl;
   matrix1[0][0] = 100;
   cout << matrix1[0][0] << endl;
}

int main() {
   constructor_tests_vec2d();
   iterator_tests_int_array();
   iterator_tests_vector();

   /*
   vector< vector<int> > v(2);
   v[0].push_back(1);
   v[0].push_back(2);
   v[1].push_back(3);
   v[1].push_back(4);

   vector<int> v1;
   v.push_back(v1);
   v[2].push_back(5);
   v[2].push_back(6);

   vector< vector<int> >::iterator row, r_end;
   vector<int>::iterator col, c_end;
   for (row = v.begin(), r_end = v.end(); row != r_end; ++row) {
      for (col = row->begin(), c_end = row->end(); col != c_end; ++col) {
         cout << *col << endl;
      }
   }
   */
}