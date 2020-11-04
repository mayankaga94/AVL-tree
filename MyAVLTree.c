#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>


// data type for avl tree nodes
typedef struct AVLTreeNode {
	int key; //key of this item
	int  value;  //value (int) of this item 
	int height; //height of the subtree rooted at this node
	struct AVLTreeNode *parent; //pointer to parent
	struct AVLTreeNode *left; //pointer to left child
	struct AVLTreeNode *right; //pointer to right child
} AVLTreeNode;

//data type for AVL trees
typedef struct AVLTree{
	int  size;      // count of items in avl tree
	AVLTreeNode *root; // root
} AVLTree;

// create a new AVLTreeNode
AVLTreeNode *newAVLTreeNode(int k, int v )
{
	AVLTreeNode *new;
	new = malloc(sizeof(AVLTreeNode));
	assert(new != NULL);
	new->key = k;
	new->value = v;
	new->height = 0; // height of this new node is set to 0
	new->left = NULL; // this node has no child
	new->right = NULL;
	new->parent = NULL; // no parent
	return new;
}

// create a new empty avl tree
AVLTree *newAVLTree()
{
	AVLTree *T;
	T = malloc(sizeof (AVLTree));
	assert (T != NULL);
	T->size = 0;
	T->root = NULL;
	return T;
}

typedef struct tTuple {
	int key;
	int value;
} tTuple;

tTuple *new_tuple(int key, int value){
	tTuple *new;
	new = malloc(sizeof(tTuple));
	new -> key = key;
	new -> value = value;
	return new;
}

//do not remove
int InsertNode(AVLTree *T,int k,int v); 
void PrintAVLTree(AVLTree *T);

//  ********************Auxilliary Functions********************
//	********************										********************
AVLTreeNode *search_tree(AVLTreeNode *root,int key,int value){
    if(root == NULL){ //tree is empty
        return NULL;
    }
	if ( root -> left == NULL && root -> right == NULL){ // Leaf node
        if ( root -> value == value && root -> key == key){
            return root;
        } else return NULL;
	}
	if ( root->key > key){ // If key is smaller go left
		search_tree(root->left,key,value);
	} else if ( root->key < key ){ // If key is greater go right
		search_tree(root->right,key,value);
	} else if ( root->key == key ){ // If key is equal
		if ( root->value > value ){ // If value is smaller go left
			search_tree(root->left,key,value);
		} else if( root->value < value ){ // If value is greater go right
            search_tree(root->right,key,value);
        } else if ( root->value == value ){ // If key and value are equal 
            return root;
        }
	}
}

void update_height(AVLTreeNode *node){ // Update Height after insertion
	if ( node->left == NULL && node->right == NULL){
		node->height = 0;
	} else if (node->left == NULL){
		node->height = node->right->height+1;
	} else if (node->right == NULL){
		node->height = node->left->height+1;
	} else {
		if(node->left->height > node->right->height) node->height = node->left->height+1;
		else node->height = node->right->height+1;
	}
    if(node->parent == NULL) return; //break statement
	update_height(node->parent);
}

//balance factor = height of right subtree - height of left subtree
int balance_factor(AVLTreeNode *node){ //returns the balance factor of a node
    int lh,rh;
    if(node->left == NULL) {
        lh = 0;
    } else lh = node->left->height + 1;
    if(node->right == NULL) {
        rh = 0;
    } else rh = node->right->height + 1;
    return rh - lh;
}

// Checks if tree is balanced, returns the unbalanced node else returns NULL if tree is balanced
AVLTreeNode *check_balance(AVLTreeNode *node){
    int i = balance_factor(node);
    //printf("i, key: %d %d\n",i,node->key);
    if (i < -1 || i > 1) return node; //If node is unblanced return it
    if (node->parent == NULL) return NULL; //break statement
    else check_balance(node->parent); //check its ancestor
}

void print_inorder(AVLTreeNode *node){
	if(node == NULL) return;
	print_inorder(node->left);
	printf("(%d, %d), %d\n",node->key,node->value,node->height);
	print_inorder(node->right);
}

// void traverse_inorder(AVLTree *T,AVLTreeNode *node){
// 	if(node == NULL) return;
// 	traverse_inorder(node->left);
// 	int j = InsertNode(T,node->key,node->value);
// 	traverse_inorder(node->right);
// }

void rotate_right(AVLTreeNode *z,AVLTree *T){
	AVLTreeNode *y,*parent;
	y = z->left;
	z->left = y->right;
	y->right = z;
	parent = z->parent;
	z->parent = y;
	y->parent = parent;
    if(parent != NULL){
        if(parent->left->key == z->key && parent->left->value == z->value){
		    parent->left = y;
	} else parent->right = y;
    } else T->root = y; //Make new root node (as unbalanced node was root itself)
	
	update_height(z); // Check for errors
}
void rotate_left(AVLTreeNode *z,AVLTree *T){
	AVLTreeNode *y,*parent;
	parent = z->parent;
	y = z->right;
	z->right = y->left;
	z->parent = y;
    y->left = z;
	y->parent = parent;
	if (parent != NULL){
		if(parent->left->key == z->key && parent->left->value == z->value){
			parent->left = y;
	} else parent->right = y;
	} else T->root = y;
	update_height(z);
}
void LL(AVLTreeNode *node,AVLTree *T){
	rotate_right(node,T);
}
void LR(AVLTreeNode *node,AVLTree *T){
	rotate_left(node->left,T);
	rotate_right(node,T);
}
void RL(AVLTreeNode *node,AVLTree *T){
	rotate_right(node->right,T);
	rotate_left(node,T);
}
void RR(AVLTreeNode *node,AVLTree *T){
	rotate_left(node,T);
}
void balance_tree(AVLTreeNode *node,AVLTree *T){
	int balance = balance_factor(node);
	if (balance > 1){ // Right Heavy
		//Check RR
		if (balance_factor(node->right) >= 0) RR(node,T);
		//Check RL
		else RL(node,T);
	} else if ( balance < -1 ){ // Left Heavy
		//Check LL
		if (balance_factor(node->left) <= 0) LL(node,T);
		//Check LR
		else LR(node,T);
	}
}
// put your time complexity analysis of CreateAVLTree() here


AVLTree *CreateAVLTree(const char *filename)
{
	AVLTree *T;
	T = newAVLTree();
	FILE *fp;
  if (filename == "stdin") {
		char ch;
		char t_num[5]; //temp number
		int key,value;
		int tnum_counter = 0, num1, num2;
		int is_tuple = 0, is_num = 0;
		// Get nodes from file or stdin
		int first_char = 0;
		while ( (ch = fgetc(stdin)) != EOF){
			first_char++;
			if( first_char == 1 && ch == '\n'){
				break;
			} else if( ch == '\n'){
				first_char = 0;
				continue;
			}
			else if ( ch == ' ') continue;
			else if ( ch == ',' ){ //Get the first number
					long l;
					char *stopstring;
					l = strtol(t_num,&stopstring,10);
					num1 = (int) l;
					//printf("num1:%d\n",num1);
					is_tuple = 1;
					strcpy(t_num,""); //reset temp num
					tnum_counter = 0; // reset counter 
					continue ;
			} else if ( ch == ')'){ // Get the second number and make tuple,store in array
					long l;
					char *stopstring;
					l = strtol(t_num,&stopstring,10);
					num2 = (int) l;
					//AVLTreeNode *node;
					//node = newAVLTreeNode(num1,num2);
					int j = InsertNode(T,num1,num2); // Create a (key,value) tuple
					is_tuple = 0; // Reset
					is_num = 0; //Reset
					for (int z = 0; z < 5;z++){
							t_num[z] = '\0';
					}
					tnum_counter = 0;
			} else if ( ch == '('){ // Number starts after opening brackets
					is_num = 1;
					continue;
			} 
			if ( is_tuple == 0 && is_num == 1){ // First number
				t_num[tnum_counter] = ch;
				tnum_counter = tnum_counter + 1; //increment counter
			} else if ( is_tuple == 1 && is_num == 1){ // Second number
				t_num[tnum_counter] = ch;
				tnum_counter = tnum_counter + 1; //increment counter
			}
			}
  } else {
    
		fp = fopen(filename,"r");
		if ( fp == NULL){
				printf("Cannot open file");
				exit(-1);
		}
		char ch;
		char t_num[5]; //temp number
		int key,value;
	//counter for the array
		//tTuple *t; // tuple object
		int tnum_counter = 0, num1, num2;
		int is_tuple = 0, is_num = 0;
		
		// Get nodes from file or stdin
		while ( (ch = fgetc(fp)) != EOF){
			if ( ch == ' ') continue;
			else if ( ch == ',' ){ //Get the first number
					long l;
					char *stopstring;
					l = strtol(t_num,&stopstring,10);
					num1 = (int) l;
					//printf("num1:%d\n",num1);
					is_tuple = 1;
					strcpy(t_num,""); //reset temp num
					tnum_counter = 0; // reset counter 
					continue ;
			} else if ( ch == ')'){ // Get the second number and make tuple,store in array
					long l;
					char *stopstring;
					l = strtol(t_num,&stopstring,10);
					num2 = (int) l;
					//AVLTreeNode *node;
					//node = newAVLTreeNode(num1,num2);
					int j = InsertNode(T,num1,num2); // Create a (key,value) tuple
					is_tuple = 0; // Reset
					is_num = 0; //Reset
					//strcpy(t_num,""); //reset temp num
					for (int z = 0; z < 5;z++){
							t_num[z] = '\0';
					}
					tnum_counter = 0;
			} else if ( ch == '('){ // Number starts after opening brackets
					is_num = 1;
					continue;
			} 
			if ( is_tuple == 0 && is_num == 1){ // First number
				t_num[tnum_counter] = ch;
				tnum_counter = tnum_counter + 1; //increment counter
			} else if ( is_tuple == 1 && is_num == 1){ // Second number
				t_num[tnum_counter] = ch;
				tnum_counter = tnum_counter + 1; //increment counter
			}
			}
			
		}
		//int j;
		// for ( j = 0; j < nodes_counter; j++){
		//     printf("Key : %d, Value : %d\n",nodes[j]->key,nodes[j]->value);
		// }
	// Sort the array (O(nlogn)
	return T;
}

// put your time complexity analysis for CloneAVLTree() here
AVLTreeNode *CloneNode(AVLTreeNode *node,AVLTreeNode *parent_node){
	if (node == NULL) return NULL;
	AVLTreeNode *new_node;
	new_node = newAVLTreeNode(node->key,node->value);
	new_node->height = node->height;
	new_node->parent = parent_node;
	new_node->left = CloneNode(node->left,new_node);
	new_node->right = CloneNode(node->right,new_node);
	return new_node;
}
AVLTree *CloneAVLTree(AVLTree *T)
{
 // put your code here
  AVLTree *T2;
	T2 = newAVLTree();
	T2->root = CloneNode(T->root,NULL);
	return T2;
}
 
void store_tree_in_array(AVLTreeNode *node,tTuple *arr[],int *i){
	if(node == NULL) return;
	store_tree_in_array(node->left,arr,i);
	tTuple *t;
	t = new_tuple(node->key,node->value);
	arr[*i] = t;
	i++;
	store_tree_in_array(node->right,arr,i);
}



// put your time complexity for ALVTreesUNion() here
AVLTree *AVLTreesUnion(AVLTree *T1, AVLTree *T2)
{
	//put your code here
	tTuple *arr1[T1->size];
	tTuple *arr2[T2->size];
	int i = 0;
	store_tree_in_array(T1->root,arr1,&i);
	int j = 0;
	store_tree_in_array(T2->root,arr2,&j);
}

// put the time complexity analysis for InsertNode() here    O(log(n))
int InsertNode(AVLTree *T, int k, int v)
{
	//printf("Insertion of node (%d,%d)\n",k,v);
	AVLTreeNode *next,*last;
	//put your code here
	if(T->root == NULL){ // Tree is empty
		AVLTreeNode *node;
		node = newAVLTreeNode(k,v);
		T->root = node;
		return 1;
	}
	next = T->root;
	while(next != NULL){
		last = next;
		if(next->key > k) {
			next = next->left;
		} else if(next->key < k){
			next = next->right;
		} else if(next->key == k){
			if(next->value > v){
				next = next->left;
			} else if(next->value < v){
				next = next->right;
			} else return 0;
		}
	} // End while loop 
	AVLTreeNode *node;
	node = newAVLTreeNode(k,v);
	if(last->key > k) last->left = node;
	if(last->key < k) last->right = node;
    if(last->key == k){
        if(last->value > v) last->left = node;
	    if(last->value < v) last->right = node;
    }
	node->parent = last;
	node->height = 0;
  update_height(node);
	T->size++;
	AVLTreeNode *unbalanced_node;
	unbalanced_node = check_balance(last);
	
	if ( unbalanced_node != NULL) {
		//printf("Key %d and Value %d: \n",unbalanced_node->key,unbalanced_node->value);
		balance_tree(unbalanced_node,T);
	} //else printf("Good node Key %d and Value %d: \n",node->key,node->value);
  return 1;
}

// put your time complexity analysis for Search() here
AVLTreeNode *Search(AVLTree *T, int k, int v)
{ 
	AVLTreeNode *node;
  node = search_tree(T->root,k,v);
	return node;
}

// put your time complexity analysis for freeAVLTree() here
void freeNode(AVLTreeNode *node){
	if (node == NULL) return;
	if(node != NULL){
		freeNode(node->left);
		freeNode(node->right);
		free(node);
	}
}
void FreeAVLTree(AVLTree *T)
{
// put your code here
	freeNode(T->root);
	free(T);
}

// put your time complexity analysis for PrintAVLTree() here -- O(n)
void PrintAVLTree(AVLTree *T)
{
 // put your code here
 printf("\nPrinting Tree\n");
	print_inorder(T->root);
	printf("\nEnd of Tree\n");
}

int main() //sample main for testing 
{ int i,j;
 AVLTree *tree1, *tree2, *tree3, *tree4, *tree5, *tree6, *tree7, *tree8;
 AVLTreeNode *node1;
 
 tree1=CreateAVLTree("stdin");
 PrintAVLTree(tree1);
 FreeAVLTree(tree1);
 //you need to create the text file file1.txt
 // to store a set of items without duplicate items
 tree2=CreateAVLTree("File1.txt"); 
 PrintAVLTree(tree2);
 tree3=CloneAVLTree(tree2);
 printf("Tree3  \n");
 PrintAVLTree(tree3);
 FreeAVLTree(tree2);
 FreeAVLTree(tree3);
 //Create tree4 
 tree4=newAVLTree();
 j=InsertNode(tree4, 10, 10);
 for (i=0; i<15; i++)
  {
   j=InsertNode(tree4, i, i);
   if (j==0) printf("(%d, %d) already exists\n", i, i);
  }
  PrintAVLTree(tree4);
  node1=Search(tree4,20,20);
  if (node1!=NULL)
    printf("key= %d value= %d\n",node1->key,node1->value);
  else 
    printf("Key 20 does not exist\n");
  
  for (i=17; i>0; i--)
  {
    j=DeleteNode(tree4, i, i);
	if (j==0) 
	  printf("Key %d does not exist\n",i);  
    PrintAVLTree(tree4);
  }
 FreeAVLTree(tree4);
 //Create tree5
 tree5=newAVLTree();
 j=InsertNode(tree5, 6, 25);
 j=InsertNode(tree5, 6, 10);
 j=InsertNode(tree5, 6, 12);
 j=InsertNode(tree5, 6, 20);
 j=InsertNode(tree5, 9, 25);
 j=InsertNode(tree5, 10, 25);
 PrintAVLTree(tree5);
 //Create tree6
 tree6=newAVLTree();
 j=InsertNode(tree6, 6, 25);
 j=InsertNode(tree6, 5, 10);
 j=InsertNode(tree6, 6, 12);
 j=InsertNode(tree6, 6, 20);
 j=InsertNode(tree6, 8, 35);
 j=InsertNode(tree6, 10, 25);
 PrintAVLTree(tree6);
 tree7=AVLTreesIntersection(tree5, tree6);
 tree8=AVLTreesUnion(tree5,tree6);
 PrintAVLTree(tree7);
 PrintAVLTree(tree8);
 return 0; 
}
