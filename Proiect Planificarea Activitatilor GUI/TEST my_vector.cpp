//#include "TEST my_vector.h"
//#include <assert.h>
//
//
//void test_all_my_vector()
//{
//	test_mv_push_back();
//	test_mv_get_set_el();
//	test_mv_iterator();
//}
//
//void test_mv_push_back()
//{
//	vector<int> new_vector;
//
//	assert(new_vector.size() == 0);
//
//	new_vector.push_back(3);
//	assert(new_vector.size() == 1);
//
//	new_vector.push_back(15);
//	new_vector.push_back(10);
//	new_vector.push_back(20);
//	new_vector.push_back(16);
//
//	assert(new_vector.size() == 5);
//
//	const int a = 10, b = 12, c = 11;
//	new_vector.push_back(a);
//	new_vector.push_back(b);
//	new_vector.push_back(c);
//
//	assert(new_vector.size() == 8);
//}
//
//void test_mv_get_set_el()
//{
//	vector<int> new_vector;
//
//	new_vector.push_back(15);
//	new_vector.push_back(1);
//	new_vector.push_back(0);
//	new_vector.push_back(13);
//	new_vector.push_back(56);
//
//	assert(new_vector.at(0) == 15);
//	assert(new_vector.at(1) == 1);
//	assert(new_vector.at(4) == 56);
//
//	assert(new_vector[0] == 15);
//	assert(new_vector[1] == 1);
//	assert(new_vector[4] == 56);
//
//	const int a = new_vector.at(1);
//	assert(a == 1);
//
//	const int b = new_vector[2];
//	assert(b == 0);
//
//	new_vector.at(1) = 3;
//	assert(new_vector.at(1) == 3);
//	new_vector.at(1) = 5;
//	assert(new_vector.at(1) == 5);
//	
//	new_vector[1] = 3;
//	assert(new_vector[1] == 3);
//	new_vector[1] = 5;
//	assert(new_vector[1] == 5);
//}
//
//void test_mv_iterator()
//{
//	vector<int> new_vector;
//
//	new_vector.push_back(15);
//	new_vector.push_back(1);
//	new_vector.push_back(0);
//	new_vector.push_back(13);
//	new_vector.push_back(56);
//
//	vector<int> copy_vector{ new_vector };
//	assert(copy_vector[0] == 15);
//	assert(copy_vector[1] == 1);
//	assert(copy_vector[4] == 56);
//
//	IteratorVector<int> it = new_vector.begin();
//	assert(it.element() == 15);
//
//	const IteratorVector<int> it2 = new_vector.end();
//	assert(it2.valid() == false);
//
//	it.next();
//	assert(it.element() == 1);
//	it.next();
//	assert(it.element() == 0);
//
//	++it;
//	assert(*it == 13);
//	++it;
//	assert(*it == 56);
//	assert(it != it2);
//
//	++it;
//	assert(it.valid() == false);
//
//	assert(it == it2);
//
//	int i = 0;
//	for (const auto& el : new_vector)
//	{
//		assert(el == new_vector[i]);
//		i++;
//	}
//}