/**
 * CMSC 341 - Spring 2021
 * Project 2 - Binary Trees
 * UserTree.h
 * An interface for the UTree class.
 */

#pragma once

#include "dtree.h"
#include <fstream>
#include <sstream>

#define DEFAULT_HEIGHT 0

class Grader;   /* For grading purposes */
class Tester;   /* Forward declaration for testing class */

class UNode {
    friend class Grader;
    friend class Tester;
    friend class UTree;
public:
    UNode() {
        _dtree = new DTree();
        _height = DEFAULT_HEIGHT;
        _left = nullptr;
        _right = nullptr;
    }

    ~UNode() {
        delete _dtree;
        _dtree = nullptr;
    }

    /* Getters */
    DTree*& getDTree() {return _dtree;}
    int getHeight() const {return _height;}
    string getUsername() const {return _dtree->getUsername();}

private:
    DTree* _dtree;
    int _height;
    UNode* _left;
    UNode* _right;

    /* IMPLEMENT (optional): Additional helper functions */

};

class UTree {
    friend class Grader;
    friend class Tester;

public:
    UTree():_root(nullptr){}

    /* IMPLEMENT: destructor */
    ~UTree();

    /* IMPLEMENT: Basic operations */
  
  void loadData(string infile, bool append = true);
  bool insert(Account newAcct);
  bool removeUser(string username, int disc, DNode*& removed);
  UNode* retrieve(string username);
  DNode* retrieveUser(string username, int disc);
  int numUsers(string username);
  void clear();
  void printUsers() const;
  void dump() const {dump(_root);}
  void dump(UNode* node) const;
  void RecursiveClear(UNode*& node);
  UNode*  recursiveRetrieve( string username , UNode*& node);
  void recursivePrint( UNode* node) const;
  UNode* RecursiveInsert(Account Acct, UNode *& node);  
  void  RecursiveUpdateHeight(UNode *& node);
  void Check_Fix_Imbalance(UNode *& node);
  
  UNode* rightRotate(UNode *& y);
 

  UNode* leftRotate(UNode *& x);
  UNode* recursiveRemove(string username,UNode *& node);
  UNode* minvalueNode(UNode* node);
  bool InsertDtree(Account newAcct, UNode *& node);



  /* IMPLEMENT: "Helper" functions */
    
    void updateHeight(UNode* node);
    int checkImbalance(UNode* node);
    //----------------
    void rebalance(UNode*& node);
    // -- OR --
  //    UNode* rebalance(UNode* node);
    //----------------

private:
    UNode* _root;

    /* IMPLEMENT (optional): any additional helper functions here! */
};
