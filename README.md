# AVL-tree
###Data Structures and Algorithm.
Implemented AVL tree and a set of functions associated with AVL tree.

##For Simplicity we make the following assumptions,
1. Each item of an AVL tree contains an integer key and an integer value.

2. No AVL tree contains duplicate items. Two items (k1, v1) and (k2, v2) are duplicates
iff k1=k2 and v1=v2 hold.

3. An AVL tree may contains multiple items with the same key and the number of
duplicate keys is a constant.

##A quick description of all implemented functions:

1. AVLTree *CreateAVLTree(const char *filename). This function creates an AVL tree by reading all the items from a text file or from the standard input (keyboard) depending on the argument filename. If filename is “stdin”, this function will read all the items from the standard input. Otherwise, it will read all the items from a text file with filename as its full path name.

2. AVLTree *CloneAVLTree(AVLTree *T). This function creates an identical copy (clone) of the input AVL tree T, and returns a pointer to the clone tree.

3. AVLTree *AVLTreesUnion(AVLTree *T1, AVLTree *T2). This function computes the union tree of two AVL trees T1 and T2 and returns a pointer to the union tree. The union tree of two AVL trees T1 and T2 is an AVL tree that contains all the items of both T1 and T2 without duplicate items. Assume that neither T1 nor T2 contains duplicate items. Note that this function does not make any change to T1 and T2.

4. int InsertNode(AVLTree *T, int k, int v). If the item (k, v) exists in the tree, this function simply returns 0 without adding the new item (k, v) to the tree. Otherwise, it inserts the new item (k, v) into the AVL tree T, increases the tree size by one and returns 1.

5. AVLTreeNode *Search(AVLTree *T, int k, int v). This function search for the item (k, v) in the AVL tree T. If the item is found, it returns a pointer to the node containing
the item. Otherwise, it returns NULL.

6. void FreeAVLTree(AVLTree *T). This function frees up the heap space occupied by the AVL tree T.

7. void PrintAVLTree(AVLTree *T). This function prints all the items and their heights stored in the AVL tree T sorted in non-decreasing order of keys on the standard output (screen). Each item is denoted by (key, value) with one item per line.
