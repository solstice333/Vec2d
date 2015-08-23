#include <cstdio>
#include <cstring>
#include <iostream>
#include <assert.h>
#include "iter.h"
#include "vec2d.h"

using namespace std;

// iterator_tests_int_array() : iterator tests using single dimension vector
void iterator_tests_int_array() {
   int my_ints[] = {0, 1, 2, 3, 4};
   Iter<int> my_iter_beg(my_ints); 
   Iter<int> my_iter_end(my_ints + sizeof(my_ints)/sizeof(int));

   Iter<int> my_iter_beg1(my_iter_beg);
   Iter<int> my_iter_end1(my_ints + sizeof(my_ints)/sizeof(int));

   assert(my_iter_beg == my_iter_beg1);
   assert(!(my_iter_beg == my_iter_end));
   assert(my_iter_beg != my_iter_end);
   assert(!(my_iter_beg != my_iter_beg1));

   Iter<int> my_iter_next(my_ints + 1);
   assert(typeid(Iter<int>) == typeid(my_iter_beg));
   assert(typeid(Iter<int>) == typeid(++my_iter_beg));
   assert(typeid(Iter<int>) == typeid(my_iter_next));

   assert(my_iter_beg == my_iter_beg1);
   assert(++my_iter_beg != my_iter_beg1);
   my_iter_beg = my_ints;
   assert(my_iter_beg == my_iter_beg1);
   assert(my_iter_beg++ == my_iter_beg1);
   assert(my_iter_beg != my_iter_beg1);

   my_iter_beg = my_ints;
   Iter<int> *my_iter_ptr = new Iter<int>(my_ints);
   assert(*my_iter_ptr == my_iter_beg);
   my_iter_ptr->set_iter(my_ints + 1);
   assert(**my_iter_ptr == 1);
   delete my_iter_ptr;
}

void iterator_tests_vector() {
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
}

void constructor_tests_vec2d() {
   Vec2d<int> matrix;
   Vec2d<int> matrix1(3, 2);

   assert(matrix1.get_num_rows() == 3);
   matrix1[0][0] = 90;
   assert(matrix1[0][0] == 90);
   matrix1[0][1] = 80;
   assert(matrix1[0][1] == 80);
   matrix1[0][0] = 100;
   assert(matrix1[0][0] == 100);
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