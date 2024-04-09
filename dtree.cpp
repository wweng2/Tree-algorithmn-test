/*
Name: Wei zhang weng
Date: 3/5/2020
Email: wweng2@umbc.edu
Project Name: dtree.cpp
Project Description: The is the cpp file for the dtree cpp and store the 
functions that allow the user to make a dtree
*/

/**
 * CMSC 341 - Spring 2021
 * Project 2 - Binary Trees
 * DiscriminatorTree.cpp
 * Implementation for the DTree class.
 */

#include "dtree.h"

/**
 * Destructor, deletes all dynamic memory.
 */
DTree::~DTree() {
  clear();// Clears everything and check to make sure there is something to delete

}

/**
 * Overloaded assignment operator, makes a deep copy of a DTree.
 * @param rhs Source DTree to copy
 * @return Deep copy of rhs
 */
DTree& DTree::operator=(const DTree& rhs) {

  if(this != &rhs){// If there is no self assgment 
    clear();
    RecursiveAssgiment(_root, rhs._root);// Calls helper function that will copy everything from the rhs tree to the other tree
  }
  else{
    cout<<"The action that was taken was self assigment and such didn't work"<<endl;
  }
  return *this;
  }



/**
 * Dynamically allocates a new DNode in the tree. 
 * Should also update heights and detect imbalances in the traversal path
 * an insertion.
 * @param newAcct Account object to be contained within the new DNode
 * @return true if the account was inserted, false otherwise
 */
bool DTree::insert(Account newAcct) {
  if(_root != nullptr){// If there is something in the tree aleardy find the place and insert the node 
 

    int discrimnator = newAcct.getDiscriminator();

  
 
    if(retrieve(discrimnator) == nullptr ){// If there is no node that is the same as the one the user put put in insert it
      //   insert the thing, then update size and vacant then check and fix the imbalance
      Recursive_Insert(_root, newAcct);
      Recursive_Vacant_and_size_Update(_root);
      Recursive_check_imbalance_and_Fix_imblance(_root);
      return true;
    }
    else{// Else do nothing and return false
      return false;
    }
      

  }
  else{// Set the roor to the new node
  
  
    _root  = new DNode(newAcct); 
    return true;
  }
}

/**
 * Removes the specified DNode from the tree.
 * @param disc discriminator to match
 * @param removed DNode object to hold removed account
 * @return true if an account was removed, false otherwise
 */
bool DTree::remove(int disc, DNode*& removed) {

  removed = RecursiveRemove(_root, disc);// Use roo as the starting node to find the node

  if(removed != nullptr){// If there is the node the user wants then call the helper function that turns _vacant true
    updateNumVacant(_root);
    return true;
  }
  else{
    return false;
  }
    
 
}

/**
 * Retrieves the specified Account within a DNode.
 * @param disc discriminator int to search for
 * @return DNode with a matching discriminator, nullptr otherwise
 */
DNode* DTree::retrieve(int disc) {
  DNode *Goal;

  Goal = RecursiveRetrieve(_root,disc);// call the helpr function is there a node then the node , else nullptr is returned

  return Goal;
  
}

/**
 * Helper for the destructor to clear dynamic memory.
 */
void DTree::clear() {
  if( _root != nullptr){// checks to see if the tree is empty or not and if it is not than it will delete evertyhing by calling a helper function
    RecursiveClear(_root);
    _root = nullptr;
  }
  else{
    cout<<"There is nothing to clear, as the bst tree is empty"<<endl;
  }
      

}

/**
 * Prints all accounts' details within the DTree.
 */
void DTree::printAccounts() const {
  RecursivePrint(_root);
}

/**
 * Dump the DTree in the '()' notation.
 */
void DTree::dump(DNode* node) const {
    if(node == nullptr) return;
    cout << "(";
    dump(node->_left);
    cout << node->getAccount().getDiscriminator() << ":" << node->getSize() << ":" << node->getNumVacant();
    dump(node->_right);
    cout << ")";
}

/**
 * Returns the number of valid users in the tree.
 * @return number of non-vacant nodes
 */
int DTree::getNumUsers() const {


  int numUser;
  if(_root != nullptr){// If the tree exist than the num user is the total nodes in the tree - the vacant nodes
    numUser = _root->getSize() - _root->_numVacant;
  }
  else{
    numUser = 0;
  }
  return numUser;
}

/**
 * Updates the size of a node based on the imedaite children's sizes
 * @param node DNode object in which the size will be updated
 */
void DTree::updateSize(DNode* node) {
  if( node->_right != nullptr && node->_left != nullptr ){// If the childern both exist then the size if the both plus 1
    node->_size = node->_right->_size + node->_left->_size + 1;
}
  else if(node->_right == nullptr && node->_left == nullptr ){// IF its none then the size is one
    node->_size  = 1;
  }
  else if(node->_right == nullptr &&  node->_left != nullptr){// if the only the left children exist than it will that children size plus 1
	node->_size = node->_left->_size + 1;
      }
  else if (node->_right != nullptr &&  node->_left == nullptr){// This is for the right side
	node->_size = node->_right->_size + 1;
      }
      

}
/**
 * Updates the number of vacant nodes in a node's subtree based on the immediate children
 * @param node DNode object in which the number of vacant nodes in the subtree will be updated
 */
void DTree::updateNumVacant(DNode* node) {
  RecursiveVacant(node);
}

/**
 * Checks for an imbalance, defined by 'Discord' rules, at the specified node.
 * @param checkImbalance DNode object to inspect for an imbalance
 * @return (can change) returns true if an imbalance occured, false otherwise
 */
bool DTree::checkImbalance(DNode* node) {
  int leftSize ;
  int RightSize;
  // Thises condital will assgign the leftsize and right size the right values as the null will be 0
  if(node->_left != nullptr && node->_right == nullptr){
    leftSize = node->_left->getSize();
  
    RightSize = 0;
  }

  else if(node->_left == nullptr && node->_right != nullptr){
    leftSize = 0;

    RightSize = node->_right->getSize();
      }
   else if (node->_left != nullptr && node->_right != nullptr){
    leftSize = node->_left->getSize();
    RightSize = node->_right->getSize();

    
  }
  else{
    leftSize = 0;
    RightSize = 0;
   
  }
 

  if(leftSize < 4 && RightSize < 4){// If both are less then 4 than no imbalance
    return false;
  }
  else if ( leftSize >= 4 || RightSize >= 4){// If one is bogger then 4 
    if(leftSize + RightSize - 4 >= 2){// It willl then add up then mius for and if its 2whihc is 50 percent 
       return true;
       }
    else{
      return false;
    }
  }
  else{
    return false;
  }
}

//----------------
/**
 * Begins and manages the rebalancing process for a 'Discrd' tree (pass by reference).
 * @param node DNode root of the subtree to balance
 */
void DTree::rebalance(DNode*& node) {
  int i = 0;
  int start = 0;
  int end = getNumUsers();
  DNode* array[getNumUsers()];// the array that will store the nodes
  RecursiveSortArray(node , array, i);
  
  RecursiveCorrect(array, start,end);
  Recursive_Vacant_and_size_Update(_root);
  // update all the existing nodes left to the correct size and vacant num
  
    }


    
// -- OR --

/**
 * Begins and manages the rebalancing process for a 'Discrd' tree (returns a pointer).
 * @param node DNode root of the subtree to balance
 * @return DNode root of the balanced subtree
 */
//DNode* DTree::rebalance(DNode*& node) {
    
//}
//----------------

/**
 * Overloaded << operator for an Account to print out the account details
 * @param sout ostream object
 * @param acct Account objec to print
 * @return ostream object containing stream of account details
 */
void DTree::RecursiveAssgiment(DNode*& node, DNode* Rhsnode){
    if(Rhsnode == nullptr){
      return ;
    }
    else{// Called both sides and copy them
    

      RecursiveAssgiment(node->_left, Rhsnode->_left);
      RecursiveAssgiment(node->_right, Rhsnode->_right);
      
      node = Rhsnode;
	    
    }
    
  }


DNode* DTree::Recursive_Insert(DNode*& node,Account newAcct){

 


  if(node  == nullptr){// If the node that was reached is empty than make the node
    node = new DNode(newAcct);
    return node;
  }
  else if(node->_vacant == true){// If vacant is true
      int newDis = newAcct.getDiscriminator();
      // These conditional will check to see if bst is maintained based on what choldren the orgianl node has
      
      if(node->_left != nullptr && node->_right == nullptr){
	if(node->_left->getDiscriminator() < newDis){
	  
	  node->_account = newAcct;// If the node is bst than the account will be changes and replaced, easier this way
	  node->_vacant = false;// The vacant is set false
	
	
	}

      }
      
      else if(node->_left == nullptr && node->_right != nullptr){
        if(node->_right->getDiscriminator() > newDis){
	  node->_account = newAcct;
	  node->_vacant = false;
	  

      
        }
      }
      else if(node->_left != nullptr && node->_right != nullptr){
        if(node->_right->getDiscriminator() > newDis && node->_left->getDiscriminator() < newDis){
	  node->_account = newAcct;
	  node->_vacant = false;
	
	  
	  
        }
      }
      else{// IF the node that is vacant has no children repplace it
	node->_account = newAcct;
        node->_vacant = false;

	
	
      }
    
      return node;

}  



 else{
   // Will call the function again with the node going to the right or left depending on the values and how it compares
    if(node->getDiscriminator() > newAcct.getDiscriminator()){
      
      node = Recursive_Insert(node->_left, newAcct);
      
    }
    else {
      
      node = Recursive_Insert(node->_right , newAcct);
    }
    
 }
  
  
  
  return node ;
}

void DTree::Recursive_Vacant_and_size_Update(DNode*& node ){
    if (node == nullptr){
      return;
    }
    else{// Call all function and called it in the order so the root get update last so it will acaully work

      Recursive_Vacant_and_size_Update(node->_left);
      
      Recursive_Vacant_and_size_Update(node->_right);
      updateNumVacant(node);
      updateSize(node);
    }
}

void DTree::Recursive_check_imbalance_and_Fix_imblance(DNode*& node){
  if(node == nullptr){
     return;
     }

  else if(checkImbalance(node) == true){// If imbalnce is true than balance it 
        
    rebalance(node);
  }
  else{
    
    Recursive_check_imbalance_and_Fix_imblance(node->_left);
    Recursive_check_imbalance_and_Fix_imblance(node->_right);
    
  }
}


DNode* DTree::RecursiveRemove(DNode*& node, int discrimnator ){
  
  if(node == nullptr){
    return nullptr;

  }// Return the node if the node discrimnator is the one it's looking for
  else if(node->getDiscriminator() == discrimnator ){
    node->_vacant = true;
    return node;
  }
  else{
    RecursiveRemove(node->_left, discrimnator  );
    RecursiveRemove(node->_right, discrimnator  );
  }
}
DNode* DTree::RecursiveRetrieve(DNode*& node, int discrimnator ){
  
  
  if(node == nullptr){
  
    return nullptr;
  }// If the node is not vacant and has the right discrimnator than return the node
  else if(node->getDiscriminator() == discrimnator && node->_vacant == false){
      return node;
  }
  
  else{
    

    RecursiveRetrieve(node->_left, discrimnator);
    RecursiveRetrieve(node->_right,discrimnator);
    
    
  }
}


void DTree::RecursiveClear(DNode*& node){
    if(node == nullptr){
      return;
    }
    else{// Called everything so that the root is the last deleted
      RecursiveClear(node->_left);
      
      RecursiveClear(node->_right);
      delete node;
    }
    
}

void DTree::RecursivePrint(DNode* node) const{
  if(node == nullptr){
    return;
  }
  else if (node->_vacant != true){// If vacant is not true than use dump to print informaton
          dump(node);
      }
    

  else{
    RecursivePrint(node->_left);
    RecursivePrint(node->_right);
  }
  }


void DTree::RecursiveVacant(DNode *& node){
  if (node == nullptr){
    return ;
  }
    else{
      RecursiveVacant(node->_left);
      RecursiveVacant(node->_right);
      if(node->_vacant == true){

	if(node->_left == nullptr && node->_right != nullptr){// This is if the right eixst thann its the right plus the node
	  node->_numVacant = 1 +node->_right->_numVacant ;
	}
	else if(node->_right == nullptr && node->_left != nullptr){// If only the left exist than its the node plus the left children
	  node->_numVacant = 1 +node->_left->_numVacant ;
	}
	else if (node->_right != nullptr && node->_left != nullptr){// If both the left and right exist than use those numbers
	     node->_numVacant = 1 +node->_left->_numVacant + node->_right->_numVacant ;
	  }
	else{// If the node is vacant and only it slef is vacant than its 1
	  node->_numVacant = 1;
	}
      }
	  
      
      else{// If vacant is not true tha it willbe based on the children and such 
	if(node->_left == nullptr && node->_right != nullptr){
          node->_numVacant = node->_right->_numVacant ;
        }
        else if(node->_right == nullptr && node->_left != nullptr){
          node->_numVacant = node->_left->_numVacant ;
        }
	else if (node->_right != nullptr && node->_left != nullptr){
             node->_numVacant = node->_left->_numVacant + node->_right->_numVacant ;
          }
	  
	  else{
	    node->_numVacant = 0;// if no children than it will 0
	  }
	  
      }
	
    }
}

void DTree::RecursiveSortArray(DNode *& node , DNode *array[] , int &i){
  if(node->_left != nullptr){// If the node is not nulptr
      RecursiveSortArray( node->_left , array , i);
    }
      if(node->_vacant != true){
	array[i++] = node;// Add the node ot the array
      }
      else{// If its vacant delete it
	delete node;
      }
      if(node->_right != nullptr){// This goes to the right
	RecursiveSortArray( node->_right , array, i);
      }
  }

  DNode* DTree::RecursiveCorrect(DNode *array[], int start, int end){
      
    if (start > end){ // If the start is going to reach the end than stop
      return nullptr; 
    }
    else{
      int mid = (start + end)/2; // The mid
      _root = array[mid]; // the new root is the mid 
      // Then the rest if going to the right and left and inserting the left and right children
      _root->_left = RecursiveCorrect(array, start,mid - 1); 
      _root->_right = RecursiveCorrect(array, start,mid + 1);
      
    }
  }
  
ostream& operator<<(ostream& sout, const Account& acct) {
  sout << "Account name: " << acct.getUsername() << 
    "\n\tDiscriminator: " << acct.getDiscriminator() <<
    "\n\tNitro: " << acct.hasNitro() << 
    "\n\tBadge: " << acct.getBadge() << 
            "\n\tStatus: " << acct.getStatus();
  return sout;
}
