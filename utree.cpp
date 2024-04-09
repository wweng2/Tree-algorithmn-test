/*
Name: Wei zhang weng
Date: 3/5/2020
Email: wweng2@umbc.edu
Project Name: utree.cpp
Project Description: The is the cpp file for the dtree cpp and store the
functions that allow the user to make a utree


 * CMSC 341 - Spring 2021
 * Project 2 - Binary Trees
 * UserTree.h
 * Implementation for the UTree class.
 */

#include "utree.h"

/**
 * Destructor, deletes all dynamic memory.
 */
UTree::~UTree() {
  clear();// Helper function that delet everything and set the root to nullptr
 
  }

/**
 * Sources a .csv file to populate Account objects and insert them into the UTree.
 * @param infile path to .csv file containing database of accounts
 * @param append true to append to an existing tree structure or false to clear before importing
 */ 
void UTree::loadData(string infile, bool append) {
       std::ifstream instream(infile);
    string line;
    char delim = ',';
    const int numFields = 5;
    string fields[numFields];
  
    /* Check to make sure the file was opened */
  
  if(!instream.is_open()) {
        std::cerr << __FUNCTION__ << ": File " << infile << " could not be opened or located" << endl;
        exit(-1);
    }

    /* Should we append or clear? */
  
  if(!append) this->clear();

    /* Read in the data from the .csv file and insert into the UTree */
  
  while(std::getline(instream, line)) {
        std::stringstream buffer(line);
	
        /* Quick check to make sure each line is formatted correctly */
  
  int delimCount = 0;
        for(unsigned int c = 0; c < buffer.str().length(); c++) if(buffer.str()[c] == delim) delimCount++;
        if(delimCount != numFields - 1) {
            throw std::invalid_argument("Malformed input file detected - ensure each line contains 5 fields deliminated by a ','");
        }

        /* Populate the account attributes - 
         * Each line always has 5 sections of data */
 
  for(int i = 0; i < numFields; i++) {
            std::getline(buffer, line, delim);
            fields[i] = line;
        }
        Account newAcct = Account(fields[0], std::stoi(fields[1]), std::stoi(fields[2]), fields[3], fields[4]);
        this->insert(newAcct);
    }
  
      return ;
}

/**
 * Dynamically allocates a new UNode in the tree and passes insertion into DTree. 
 * Should also update heights and detect imbalances in the traversal path after
 * an insertion.
 * @param newAcct Account object to be inserted into the corresponding DTree
 * @return true if the account was inserted, false otherwise
 */
bool UTree::insert(Account newAcct) {

   if(_root != nullptr){
     

     if(retrieve(newAcct.getUsername())  == nullptr ){// If the there is no node with the username then create a new one and update the hight and check for imbalances
       
       RecursiveInsert(newAcct, _root);
       RecursiveUpdateHeight(_root);
       Check_Fix_Imbalance(_root);
       return true;
     }
     else{
      
       // Into existing node and such no new node add and such no imbalnce or hieght update and checks
       /* if(InsertDtree(newAcct,_root) == true){
	 return true;
      }
       else{
	 return false;
      }
       
       */
     }
     
   }  
    
   else{
     // The root doesn't need to check the hieght hieght or imbalnce when its the first thing in the tree
     _root = new UNode();// If the tree is vacant than just make a now
    _root->_dtree->insert(newAcct);
    return true;
   }
   return 0;
}

/**
 * Removes a user with a matching username and discriminator.
 * @param username username to match
 * @param disc discriminator to match
 * @param removed DNode object to hold removed account
 * @return true if an account was removed, false otherwise
 */
bool UTree::removeUser(string username, int disc, DNode*& removed) {

  // retreusernmae, retive disc, if nullptr num vacant, recursive delte(node)
  // RECURSIVE hieght and fix and check imbalance
  if(retrieve(username) != nullptr){// If the there is node with the user name
      UNode* temp = retrieve(username);

      if(temp->_dtree->getNumUsers() != 0){// If the there is still none vacant ones
	
	temp->_dtree->remove(disc,removed);// removed
	if(temp->_dtree->getNumUsers() == 0){// Then check to see if there is none left and if it does than delete
	   recursiveRemove(username,_root);

	}
	return true;
      }
      else{// If there isnothing return false as ntohing to remove and delete it
	 recursiveRemove(username,_root);
	 return false;
      }
  }
    else{
      return false;
    }
  return 0;
}

/**
 * Retrieves a set of users within a UNode.
 * @param username username to match
 * @return UNode with a matching username, nullptr otherwise
 */
UNode* UTree::retrieve(string username) {
  UNode* Goal = recursiveRetrieve(username,_root);// Return unode if possible if not nullptr

  
  return Goal;
}

/**
 * Retrieves the specified Account within a DNode.
 * @param username username to match
 * @param disc discriminator to match
 * @return DNode with a matching username and discriminator, nullptr otherwise
 */
DNode* UTree::retrieveUser(string username, int disc) {
  DNode* Goal = nullptr; 
  UNode* check = nullptr;
  if(retrieve(username) != nullptr){// if node exist use treive of the dtree to find the node and return it
    check = retrieve(username);

    Goal = check->_dtree->retrieve(disc);
  }
  else{
    Goal = nullptr;
  }
  
  return Goal;
}

/**
 * Returns the number of users with a specific username.
 * @param username username to match
 * @return number of users with the specified username
 */
int UTree::numUsers(string username) {

  UNode* goal = retrieve(username);
  
  int numUser = 0;

  if(goal != nullptr){// If the node esit than use the getnumuser and return that 
    numUser = goal->_dtree->getNumUsers();
  }
  else{
    cout<<"The node doens't exist"<<endl;
  }
  return numUser;
}

/**
 * Helper for the destructor to clear dynamic memory.
 */
void UTree::clear() {
  if( _root != nullptr){// checks to see if the tree is empty or not and if it is not than it will delete evertyhing by calling a helper function
    RecursiveClear(_root);
    _root = nullptr;
  }
  else{
    cout<<"There is nothing to clear, as the bst tree is empty"<<endl;
  }

}

/**
 * Prints all accounts' details within every DTree.
 */
void UTree::printUsers() const {
  if(_root != nullptr){// If node exist than use root as the base and print all
    UNode* start = _root;
    recursivePrint(start);
  }
  else{
    cout<<"The tree doesn't exist"<<endl;
    
  }
}
/**
 * Dumps the UTree in the '()' notation.
 */
void UTree::dump(UNode* node) const {
    if(node == nullptr) return;
    cout << "(";
    dump(node->_left);
    cout << node->getUsername() << ":" << node->getHeight() << ":" << node->getDTree()->getNumUsers();
    dump(node->_right);
    cout << ")";
}

/**
 * Updates the height of the specified node.
 * @param node UNode object in which the height will be updated
 */
void UTree::updateHeight(UNode* node) {
  // height of choldren
  if(node->_left == nullptr && node->_right == nullptr){// If leaf node than 0
    node->_height = 0;
  }

  else if (node->_left != nullptr && node->_right == nullptr){// If left exist than the hieght of left plus 1
    node->_height = node->_left->_height + 1;
  }

  else if (node->_left == nullptr && node->_right != nullptr){// If right exist than itss height + 1
    node->_height = node->_right->_height + 1;

  }
  else{
    if( node->_right->_height > node->_left->_height ){// If both exist than compare and which is bigger, than + 1
       node->_height = node->_right->_height + 1;
    }
    else{
      node->_height = node->_left->_height + 1;

    }
    
  }
  return ;
}

/**
 * Checks for an imbalance, defined by AVL rules, at the specified node.
 * @param node UNode object to inspect for an imbalance
 * @return (can change) returns true if an imbalance occured, false otherwise
 */
int UTree::checkImbalance(UNode* node) {
  // chilfdren and -1 or 1 ten return
  int factor = 0;
  int leftHeight = 0;
  int rightHeight = 0;
  if(node->_left == nullptr && node->_right == nullptr){// If leaf node than 0
    leftHeight = 0;
    rightHeight =0;

  }
  
  else if (node->_left != nullptr && node->_right == nullptr){// if left exist that its hieght and right is 0
    leftHeight = node->_left->_height;
    rightHeight = 0;

  }

  else if (node->_left == nullptr && node->_right != nullptr){// IF right exist than it height and left is zero
    leftHeight = 0;
    rightHeight = node->_right->_height;

    
  }
  else{// IF both exist than the hight is its size
    leftHeight = node->_left->_height;
    rightHeight = node->_right->_height;

  }
  factor = leftHeight - rightHeight;// Return the height

  return factor;
}

//----------------
/**
 * Begins and manages the rebalance procedure for an AVL tree (pass by reference).
 * @param node UNode object where an imbalance occurred
 */
void UTree::rebalance(UNode*& node) {
  // recursive balnce // left, right rotations
  // height update

  if(node->_right == nullptr){// IF the right is empty than use the left as this has to exist for the balance ot be called


    if (checkImbalance(node) > 1 && node->getUsername() < node->_left->getUsername()){
      rightRotate(node);
 
  }
    if (checkImbalance(node) > 1 &&  node->getUsername() > node->_left->getUsername())
    {
        node->_left = leftRotate(node->_left);
        rightRotate(node);
    }

  }
  else if(node->_left == nullptr){// IF the left is empty than use the right as this has to exist for the balance ot be called
    if (checkImbalance(node) < -1 && node->getUsername() > node->_right->getUsername()){
        leftRotate(node);
    }
    
 
    
    if (checkImbalance(node) < -1 && node->getUsername()  < node->_right->getUsername())
      {
        node->_right = rightRotate(node->_right);
        leftRotate(node);
    }
  }
  // No clause for a leaf node since that can't be imbalance
  return;
  
  
}
// -- OR --


/**
 * Begins and manages the rebalance procedure for an AVL tree (returns a pointer).
 * @param node UNode object where an imbalance occurred
 * @return UNode object replacing the unbalanced node's position in the tree
 */
//UTree* UTree::rebalance(UNode* node) {
  
//}
//----------------
void UTree::RecursiveClear(UNode*& node){
    if(node == nullptr){
      return;
    }
    else{// Called everything so that the root is the last deleted
      RecursiveClear(node->_left);

      RecursiveClear(node->_right);
      delete node;
    }
    
}

 UNode* UTree::recursiveRetrieve( string username , UNode*& node){
  
     // if the user name is the right one return the node

   
   if(node == nullptr){
     return nullptr;
   }
   else if (node->getUsername() == username){
     return node;
     }

   else{
        
     recursiveRetrieve( username , node->_left);
     recursiveRetrieve( username , node->_right);
     
   }
 }

 void UTree::recursivePrint( UNode* node)const  {
   if(node == nullptr){
     return;
   }
   else{// Call the left and right chold than print the accounts
     recursivePrint( node->_left);
     recursivePrint( node->_right);
     node->_dtree->printAccounts();
   }
 }

UNode*  UTree::RecursiveInsert(Account Acct,UNode *& node){
  if(node == nullptr){// If the node is empty than create new node and insert it onto it
    node = new UNode();
    node->_dtree->insert(Acct);
  }


  else{
    // Will call the function again with the node going to the right or left depending on the values and how it compares
     if(node->getUsername() > Acct.getUsername()){
       
       node = RecursiveInsert(Acct,node->_left);

     }
     else {
       
       node = RecursiveInsert(Acct,node->_right);
    }
     
  }

  
  
  return node ;
}

void  UTree::RecursiveUpdateHeight(UNode *& node){
    if (node == nullptr){
      return;
    }
    else{// Call all function and called it in the order so the root get update last so it will acaully work
      
      RecursiveUpdateHeight(node->_left);
      
      RecursiveUpdateHeight(node->_right);
      updateHeight(node);
     
    }

  

}

void UTree::Check_Fix_Imbalance(UNode *& node){
  if(node == nullptr){
    return;
     }
  
  else if(checkImbalance(node)  < -1 || checkImbalance(node)  > 1 ){// If imbalnce is true than balance it
    
    rebalance(node);
  }
  else{
    
    Check_Fix_Imbalance(node->_left);
    Check_Fix_Imbalance(node->_right);
    
  }
}


UNode* UTree::rightRotate(UNode *& y){
    UNode *x = y->_left;
    UNode *T2 = x->_right;
 
    // Perform rotation
    x->_right = y;
    y->_left = T2;
 
    // Update heights
    updateHeight(y);
    updateHeight(x);

 
    // Return new root
    return x;
}

UNode* UTree::leftRotate(UNode *& x){
    UNode *y = x->_right;
    UNode *T2 = y->_left;
 
    // Perform rotation
    y->_left = x;
    x->_right = T2;
 
    // Update heights
    updateHeight(x);

    updateHeight(y);

 
    // Return new root
    return y;
}
 
UNode* UTree::recursiveRemove(string username,UNode *& node){
  if(node == nullptr){
    return nullptr;
  }
  if(node->getUsername() > username){// If the the username of the node is bigger go left
    node->_left = recursiveRemove(username,node->_left);
  }
  else if (node->getUsername() < username){// if the username is bigger go right
    node->_right = recursiveRemove(username,node->_right);
  }
  else{// If no comparson than its the node
    if (node->_left == nullptr && node->_right == nullptr){
      UNode* temp = node;
      node = nullptr;
      delete temp;
    }
    else if (node->_left == nullptr){
      UNode* temp = node;
      node = node->_right;
      delete temp;
    }
    else if (node->_right == nullptr){
      UNode* temp = node;
      node = node->_left;
      delete temp;
      
	}
    else{// If both chold exist than get the samllest right one than impoertn the info from that to the node and delte th child
      UNode * temp = minvalueNode(node->_right);

      node->_dtree = temp->_dtree;
      node->_right = recursiveRemove(temp->getUsername(), node->_right);
					      
      
    }
  }

}

UNode* UTree::minvalueNode(UNode* node){
  if(node->_left == nullptr){// Goes until there is chld left node than return this further left node
    return node;
  }
  else{
    node->_left = minvalueNode(node->_left);
  }
}

bool UTree::InsertDtree(Account newAcct, UNode *& node){
  if(node == nullptr){
    return false;
  }
  else if(node->getUsername() == newAcct.getUsername()){
    if(node->_dtree->insert(newAcct) == true){
      return true;
    }
    else{
      return false;
    }
  }
  else{
    InsertDtree(newAcct, node->_left);
    InsertDtree(newAcct, node->_right);
  }
}
