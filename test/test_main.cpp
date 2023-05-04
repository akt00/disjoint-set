#include <iostream>
#include "../src/disjoint_set.h"
using namespace std;


int main(void) {
	try {
		union_find::DisjointSet ds;
		ds.make_set(1);
		ds.make_set(2);
		ds.make_set(3);
		ds.make_set(4);
		ds.make_set(5);

		ds.make_union(1, 2);
		ds.make_union(2, 3);
		ds.make_union(4, 5);
		ds.make_union(1, 4);

		ds._show_sets();
		cout << ds.set_size() << endl;
	}
	catch (exception e) {
		cout << "error" << endl;
	}
}