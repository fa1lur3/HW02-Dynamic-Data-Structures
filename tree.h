#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cfloat>
using namespace std;

#define NEXTCOMPARED(f,n) n->leftRight[f>n->pay] // this evaluates to appropriate next node by comparing f to payload. macro is better than pasting it all over the place

struct nodeT{
	nodeT *leftRight[2]={0,0}; // array to allow numerical access
	nodeT *&left=leftRight[0], *&right=leftRight[1]; // explicit left/right for conveninece
	float pay=0;
	
	nodeT(float f, nodeT *l, nodeT *r){
		leftRight[0]=l;
		leftRight[1]=r;
		pay=f;
	}
};

class tree{
	nodeT *base=new nodeT(FLT_MAX,0,0); // base node, parent of root node with maximum float value so all children are on left. janky but helpful
	nodeT *findParent(float f, nodeT *n=0){ // find parent of a node with payload f and address n
		nodeT *parent=base, *current=root;
		while(f!=current->pay || (n!=current && n!=0)){ // traverse while we havent already found f and n, ignore n if left blank
			parent=current;
			current=NEXTCOMPARED(f,current);
		}
		return parent;
	}
	nodeT *&find(float f, nodeT *n=0){ // find node containing f and address n,  return as refrence to parent node left/right
		return NEXTCOMPARED(f,findParent(f,n));
	}
	nodeT *&findNextLowest(float f){ // finds next lowest node, return as refrence to parent left/right
		nodeT *lowerParentGuess=find(f), *lowerGuess=lowerParentGuess->left;
		if(!lowerGuess || !lowerGuess->right)
			return lowerParentGuess->left;
		while(lowerGuess && lowerGuess->right){
			lowerParentGuess=lowerGuess;
			lowerGuess=lowerGuess->right;
		}
		return lowerParentGuess->right;
	}
	void print(nodeT *n){ // recursive to print any node and all children in order
		if(!n) // do nothing if n doesnt exist
			return;
		if(height(n)==-1) // if n is a leaf print it
			cout<<n->pay<<" ";
		else{
			print(n->left); // print left side, print n, print right side
			cout<<n->pay<<" ";
			print(n->right);
		}
	}
	void rotate(nodeT *&n, int lr){ // rotate right/left based on lr, input reference to parent l/r value as n
		nodeT *temp=n;
		n=n->leftRight[!lr];
		temp->leftRight[!lr]=n->leftRight[lr];
		n->leftRight[lr]=temp;
	}
	void balance(nodeT *nd){ // recurse up the tree to balance
		nodeT *&n=find(nd->pay,nd); // get reference to parent l/r instead of just address nd
		if(height(n->left)-height(n->right)>1){
			if(height(n->left->left)<height(n->left->right))
				rotate(n->left,0);
			rotate(n,1);
		}
		else if(height(n->left)-height(n->right)<-1){
			if(height(n->right->right)<height(n->right->left))
				rotate(n->right,1);
			rotate(n,0);
		}
		if(n!=root){
			nodeT *parent=findParent(n->pay,n);
			balance(parent);
		}
	}
	
	public:
	
	nodeT *&root=base->left;
	
	tree(float f){
		root=new nodeT(f,0,0);
	}
	int height(nodeT *n){ // resursive to find height of node n. i really like this function
		if(!n)
			return -1;
		return 1+max(height(n->left),height(n->right));
	}
	void add(float f){ // start at root, update currentNode if appropriate next node already exists
		nodeT *current=base;
		while(NEXTCOMPARED(f,current)){
			current=NEXTCOMPARED(f,current);
		}
		NEXTCOMPARED(f,current)=new nodeT(f,0,0);
		balance(NEXTCOMPARED(f,current));
	}
	void del(float f){
		nodeT *&delNode=find(f), // these are the location of the respective nodes as contained in their parent nodes
			  *&delReplace=findNextLowest(f),
			  *delLater=delNode, // just to save for freeing
			  *delParent=findParent(f);
			  
		if(!delReplace)
			delNode=delNode->right;
		else{
			delReplace->right=delNode->right;
			delReplace->left=delNode->left;
			delNode=delReplace;
			delReplace=0;
		}
		free(delLater);

		if(delNode)
			balance(delNode);
		else
			balance(delParent);
	}
	void print(){ // uses print on root for user conveniece
		print(root);
	}
};