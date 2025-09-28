#include <iostream>
#include "list.h"
#include "tree.h"
using namespace std;
int main(){
	
	list a(0);
	for(int i=1;i<10;i++){// appends increasing numbers to head of the list
		a.insert(i,0);
	}
	a.print();
	cout<<endl<<a.length();
	
	a.del(4); // delete 5th element, append 10 to the end of the list, and change first element to 0.5
	a.insert(10,9);
	a[0]=.5;
	cout<<endl;
	a.print();
	cout<<"\n\n\n";
	
	// trying to delete from an empty list crashes the program as it tries to access nonexistant memory, same issue with trying to access out of bounds indices
	
	
	
	/**/
	float test[]={14,-4,-1,8,2,4,15,11,13,9,7,-5,6,-3,-2,1,3,5,12,10};
	tree b(0);
	for(int i=0;i<(sizeof(test)/sizeof(test[0]));i++){
		b.add(test[i]);
	}
	b.print();
	cout<<endl<<b.height(b.root->left)<<" left height of root, right height: "<<b.height(b.root->right)<<endl;
	cout<<b.height(b.root->left->left)<<" left height of left node, right height: "<<b.height(b.root->left->right)<<endl;
	b.del(8);
	b.del(-1);
	cout<<endl;
	b.print();
	
	cin.get(); // make executable wait for me
	return 0;
}