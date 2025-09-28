#include <iostream>
#include <cstdlib>
using namespace std;
struct node{
	node *next=0;
	float pay=0;
	
	node(float f, node *n){
		pay=f;
		next=n;
	}
};

class list{
	node *base=new node(0,0); // base node, containds no data and points to head. essentially node[-1]. it might be weird but it makes this code far more succinct than if i wrote this without it
	node *nodeI(int i){
		node *nodeCurrent=base; // start at base
		for(int j=-1; j<i; j++){ // increment through as long as next exists, else return null
			if(nodeCurrent->next)
				nodeCurrent=nodeCurrent->next;
			else
				return 0;
		}
		return nodeCurrent;
	}
	
	public:
	node *&head=base->next; // special name for first data node
	
	list(float f){
		head=new node(f,0);
	}
	void insert(float f, int i){ // if node[i-1] exists, update its next as we create the new node[i] pointing to the previous node[i]
		nodeI(i-1)->next=new node(f,nodeI(i));

	}
	void del(int i){ // update previous node to skip node[i] and free node[i]
		node *temp=nodeI(i);
		nodeI(i-1)->next=nodeI(i)->next;
		free(temp);

	}
	void print(){ // print each payload in order as long as the node exists
		node *currentNode=head;
		while(currentNode){
			cout<<currentNode->pay<<" ";
			currentNode=currentNode->next;
		}
	}
	int length(){ // increment count for each existing data node
		node *currentNode=head;
		int count=0;
		while(currentNode){
			count++;
			currentNode=currentNode->next;
		}
		return count;
	}
	float &operator[](int i){
		return nodeI(i)->pay;
	}
};