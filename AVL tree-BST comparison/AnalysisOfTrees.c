



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



struct node{
	char word[100];
	struct node *left,*right;
	int height;
};
typedef struct node node;


void deleteNodeBST(node** root,char *word);
node* deleteNodeAVL(char* word,node* root);
node* insertAVL(char *word,node *root);
void insertBST(node **root,char *word);
node* minValueNode(node* root);
void printInOrder(node *root);
int height(node *root);
int getBalance(node *root);
int max(int a, int b);
node *newNode(char *word);
node* rightRotate(node *root);
void readInput(node **root1,node **root2);
node* leftRotate(node *root);
void deleteAll(node **root);


node *bst1,*avl1 = NULL;//root 
clock_t diff1,diff2,diff3,diff4;//timer

//delay the running system
void delay(){
	int i=0;
	for(;i<10000000;i++){
	}
}


//calculate height difference between root's right child and root's left child
int getBalance(node *root)
{
    if (root == NULL)
        return 0;
    return height(root->left) - height(root->right);
}

//find higher value between two numbers
int max(int a, int b)
{
    return (a > b)? a : b;
}

//calculate height that it desired root
int height(node *root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

//find the node's leftmost leaf
node* minValueNode(node* root)
{
    node *current = root;
 
    // loop down to find the leftmost leaf 
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

//rotate left according to given node
node* leftRotate(node *root)
{
    node *r = root->right;//root's right child
    node *rl = r->left;//root's rigtht child's left child
 
    // Perform rotation
    r->left = root;
    root->right = rl;
 
    //  Update heights
    root->height = max(height(root->left), height(root->right))+1;
    r->height = max(height(r->left), height(r->right))+1;
 	
	 // Return new root
	return r;

}

//rotate right according to given root
node* rightRotate(node *root)
{
    node *l = root->left;//root's left child
    node *lr = l->right;//root's left child's right child
 
    // Perform rotation
    l->right = root;
	root->left = lr;
 
    // Update heights
    root->height = max(height(root->left), height(root->right))+1;
    l->height = max(height(l->left), height(l->right))+1;
 
 	// Return new root
	return l;
}


//reading input and doing insert operation to tree
void readInput(node **root1,node **root2)
{
	FILE *filePtrIns;
	FILE *filePtrDel;
	char temp[100];//temp string for assign for LL data
	clock_t start1,start2;
	
	filePtrIns = fopen("input1.txt","r");
	filePtrDel = fopen("input1.txt","r");
	
	if(filePtrIns==NULL) printf("Your input file does not exist! "); //if file pointer is NULL
	
	//if file pointer is not NULL
	else {
		
		//insert time calculation for avl tree and bst
		while(!feof(filePtrIns)){
			fscanf(filePtrIns,"%s",temp);
			
			start1=clock();//return start time
			insertBST(root1,temp);//call insert for creat struct and insert BST	
			delay();//delay system for time observation
			diff1 = diff1 + clock() - start1;//calculation operation time
			
			start2 = clock();
			*root2 = insertAVL(temp,*root2);//call insert for creat struct and insert AVL tree
			delay();
			diff2 = diff2 + clock() - start2;
		}
		
		//delete time calculation for avl tree and bst (delete first sentence from my input1.txt)
		while(strcmp(temp,"doubt")){
			fscanf(filePtrDel,"%s",temp);
			
			start1=clock();
			deleteNodeBST(root1,temp);//call delete for delete node from bst
			delay(); 
			diff3 = diff3 + clock() -start1;
			
			start2 = clock();
			*root2 = deleteNodeAVL(temp,*root2);//call delete for delete node from avl tree
			delay();
			diff4 = diff4 + clock() -start2;
		}
		
	}
	fclose(filePtrIns);
	fclose(filePtrDel);
	
}

//create new node for tree with given word
node *newNode(char *word){
	node *newNode;
	newNode = (node *)malloc(sizeof(node));
	newNode->left = newNode->right = NULL;
	strcpy(newNode->word,word);
	newNode->height = 1;
	return newNode;
}

//insert for avl tree
// http://www.geeksforgeeks.org/avl-tree-set-1-insertion/
node* insertAVL(char *word,node *root)
{
	if(root == NULL){
		return newNode(word);
	} 
	
	if(strcmp(word,root->word)==-1)
		root->left = insertAVL(word,root->left);
	
	else if(strcmp(word,root->word)==1)
		root->right = insertAVL(word,root->right);
	
	else 
		return root;
	
	root->height = 1 + max(height(root->left),
                           height(root->right));
 
    /* 3. Get the balance factor of this ancestor
          root to check whether this root became
          unbalanced */
   int balance = getBalance(root);
 
    // If this root becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && strcmp(word,root->left->word)==-1)
        return rightRotate(root);
 
    // Right Right Case
    if (balance < -1 && strcmp(word,root->right->word)==1)
        return leftRotate(root);
 
    // Left Right Case
    if (balance > 1 && strcmp(word,root->left->word)==1)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Left Case
    if (balance < -1 && strcmp(word,root->right->word)==-1)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    /* return the (unchanged) root pointer */
    return root;

	
}

/* delete for avl tree
   http://www.geeksforgeeks.org/avl-tree-set-2-deletion/
   Recursive function to delete a node with given key
   from subtree with given root. It returns root of
  the modified subtree.
*/
node* deleteNodeAVL(char *word,node *root)
{
    // STEP 1: PERFORM STANDARD BST DELETE
 
    if (root == NULL)
        return root;
 
    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if ( strcmp(word,root->word)==-1 )
        root->left = deleteNodeAVL(word,root->left);
 
    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if( strcmp(word,root->word)==1 )
        root->right = deleteNodeAVL(word,root->right);
 
    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            node *temp = root->left ? root->left : root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
           		 *root = *temp; // Copy the contents of
         	              	// the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            node* temp = minValueNode(root->right);
 
            // Copy the inorder successor's data to this node
            strcpy(root->word,temp->word);
 
            // Delete the inorder successor
            root->right = deleteNodeAVL(temp->word,root->right);
    	}
    }
 
    // If the tree had only one node then return
    if (root == NULL)
      return root;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);    
	}
	return root;
}


//delete for bst
//taken from http://www.geeksforgeeks.org/binary-search-tree-set-2-delete/
//changed some place by me
void deleteNodeBST(node** root, char *word)
{
    // base case
    if (*root == NULL) return;

    // If the word to be deleted is smaller than the root's word,
    // then it lies in left subtree
    if (strcmp((*root)->word,word)>0)
        deleteNodeBST(&((*root)->left), word);
 
    // If the word to be deleted is greater than the root's word,
    // then it lies in right subtree
    else if (strcmp((*root)->word,word)<0)
        deleteNodeBST(&((*root)->right), word);
 
    // if word is same as root's word, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if( ((*root)->left == NULL) || ((*root)->right == NULL) )
        {
            node *temp = (*root)->left ? (*root)->left : (*root)->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = *root;
                *root = NULL;
            }
            else // One child case
           		 **root = *temp; // Copy the contents of
         	              	// the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            node* temp = minValueNode((*root)->right);
 
            // Copy the inorder successor's data to this node
            strcpy((*root)->word,temp->word);
 
            // Delete the inorder successor
            deleteNodeBST(&((*root)->right),temp->word);
    	}
    }
    return ;
}


//insert for bst
void insertBST(node **root,char *word)
{
	if(*root == NULL){
		*root = newNode(word);
		return ;
	} 
	//recursive 
	//find proper place for parameter word
	if(strcmp(word,(*root)->word)==-1)
	{
		insertBST(&((*root)->left),word);
	}
	else if(strcmp(word,(*root)->word)==1)
	{
		insertBST(&((*root)->right),word);
	}
	else return ;
	
	return ;
} 


void printInOrder(node *root)
{
	if(root!=NULL)
	{
		printInOrder(root->left);
		printf("\t%s\n",root->word);
		printInOrder(root->right);	
	}
	
}

//delete all node in tree (post order)
void deleteAll(node **root)
{
	if(*root!=NULL)
	{
		deleteAll(&((*root)->left));
		deleteAll(&((*root)->right));
		free(*root);
		*root=NULL;
	}
}



int main()
{
	char operations[100];
	
	readInput(&bst1,&avl1);
	
	//transform clock_t to long for time calculation
	long msec1 = diff1 * 1000 / CLOCKS_PER_SEC;
	long msec2 = diff2 * 1000 / CLOCKS_PER_SEC;
	long msec3 = diff3 * 1000 / CLOCKS_PER_SEC;
	long msec4 = diff4 * 1000 / CLOCKS_PER_SEC;
	
	printf("\n>>");
  	printf("1: time for BST insert operation\n  2: time for AVL tree insert operation\n");
  	printf("  3: time for BST delete operation\n  4: time for AVL tree delete operation\n  5: Print nodes in tree (inorder)\n  6: Exit \n\n>>");
	
	
	do
	{	
		scanf("%s",operations);
		if(operations[0]>54 || operations[0]<48 || operations[1])
		{
		printf("Wrong input format!\n\n");
		printf("\n>>");
		}
		else
		{
			switch(operations[0])
			{
				case '1': printf("BST insert time for input1.txt\n\n"); 
					      printf("Time taken %d seconds %d milliseconds\n\n", msec1/1000, msec1%1000);
						  printf("\n>>");
						break;
				case '2': printf("AVL tree insert time for input1.txt\n\n");
						  printf("Time taken %d seconds %d milliseconds\n\n", msec2/1000, msec2%1000);
						  printf("\n>>");
						break;
				case '3': printf("BST delete time for input1.txt(half of all word)\n\n"); 
					      printf("Time taken %d seconds %d milliseconds\n\n", msec3/1000, msec3%1000);
						  printf("\n>>");
						break; 
				case '4': printf("AVL tree delete time for input1.txt(half of all word)\n\n"); 
					      printf("Time taken %d seconds %d milliseconds\n\n", msec4/1000, msec4%1000);
						  printf("\n>>");
						break;
				case '5': printf("--- Inorder Tree Representation ---\n\n");//both avl tree and bst create same result (I use avl tree below)
						  printInOrder(avl1);
						  printf("\n>>");	
						break;
							 
				case '6': deleteAll(&bst1);
						  deleteAll(&avl1);
						break;	
						
			}
		}
	}while(operations[0] != '6');	
}
