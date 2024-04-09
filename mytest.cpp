/*
Name: Wei zhang weng
0;136;0cDate: 3/5/2020
Email: wweng2@umbc.edu
Project Name: mytest.cpp
Project Description: This is the testing file that test  everything
*/
#include "utree.h"
#include <random>

#define NUMACCTS 20
#define RANDDISC (distAcct(rng))

std::mt19937 rng(10);
std::uniform_int_distribution<> distAcct(0, 9999);

class Tester {
public:
    bool testBasicDTreeInsert(DTree& dtree);

    bool testBasicUTreeInsert(UTree& utree);


  
};

bool Tester::testBasicDTreeInsert(DTree& dtree) {
    bool allInserted = true;
    for(int i = 0; i < NUMACCTS; i++) {
        int disc = RANDDISC;
        Account newAcct = Account("", disc, 0, "", "");
        if(!dtree.insert(newAcct)) {
            cout << "Insertion on node " << disc << " did not return true" << endl;
            allInserted = false;
        }
    }
    return allInserted;
}

bool Tester::testBasicUTreeInsert(UTree& utree) {
    string dataFile = "accounts.csv";
    try {
        utree.loadData(dataFile);
    } catch(std::invalid_argument e) {
        std::cerr << e.what() << endl;
        return false;
    }
    return true;
}





int main() {
    Tester tester;
    cout<<"Testing the dtree first, starting with insert"<<endl;
    // Testing insert and all compents first
    DTree dtree;

    cout<<"Testing the insert when root is nullptr and nothing is in in it"<<endl;
    // Testing to check that when the root is nullptr the insert will put something there
        
    int disc = 2;
    Account newAct = Account("", disc, 0, "", "");
    
    int discsss = 3;
    Account newActed = Account("", discsss, 0, "", "");

    int discss = 4;
    Account newActex = Account("", discss, 0, "", "");

    int discssss = 5;
    Account newActce = Account("", discssss, 0, "", "");

    cout<<"Testing, when root has a node"<<endl;    
    int discs = 1;
    Account newAcct = Account("", discs, 0, "", "");
    
    if(dtree.insert(newAcct) == true){
      cout<< "Passed"<<endl;;
    }
    else{
      cout<<"Failed"<<endl;
    }
    // Testing the parts of insert
    cout<<"Testing retrieve now"<<endl;
    DNode * test;
    /// Testing normal 
    if(dtree.retrieve(1) != nullptr){
       cout<<"passed"<<endl;
     }
     else{
       cout<<"failed"<<endl;
     }
    // Testing when node doesn't exist
    if(dtree.retrieve(5) == nullptr){
       cout<<"passed"<<endl;
     }
     else{
       cout<<"failed"<<endl;
     }
    // Testing removed to check to if it removes
     cout<<"Testing removed"<<endl;
     if(dtree.remove(1,test) == true ){
       cout<<"passed"<<endl;
     }
     else{
       cout<<"failed"<<endl;
     }
     // Test to see f it will remove something that doesn't exist
     if(dtree.remove(5,test) == false){
       cout<<"passed"<<endl;
     }
     else{
       cout<<"failed"<<endl;
     }
   
     
     cout<<"Testing retrieve when vacant"<<endl;
     // When the node is vacant will retrive get it
     // And check if the node has been vacant
     if(dtree.retrieve(1) == nullptr ){
       cout<<"passed"<<endl;
     }
     else{
       cout<<"failed"<<endl;
     }
     cout<<"Testing getNumUsers"<<endl;
     // Testing to see if num vacant is update
     if(dtree.getNumUsers() != 0){
       cout<<"Failed "<<endl;
     }
     else{
       cout<<"Passed"<<endl;
     }
     dtree.clear();
     // Testing numuser when cleared
     if(dtree.getNumUsers() != 0){
       cout<<"Failed "<<endl;
     }
     else{
       cout<<"Passed"<<endl;
     }

     cout<<"Testing, the insert when root is delte and new root is added and see if the size if right"<<endl;
          dtree.insert(newAcct);
     
     if(dtree.getNumUsers() == 1){
       cout<<"Passed"<<endl;
	  }
     else{
       cout<<"Failed"<<endl;
     }
     
     //Testing clear
     cout<<"Testing clear "<<endl;
     cout<<"Testing clear when something is in it"<<endl;

     dtree.clear();
     // This check to see if some node is still in the tree
     if(dtree.getNumUsers() != 0){
       cout<<"Failed "<<endl;
     }
     else{
       cout<<"Passed"<<endl;
     }
     // clear on empty tree so repsonse and termnate
     cout<<"Expected outputed: This tree is empty"<<endl;
     dtree.clear();
      
     dtree.insert(newAcct);
     
     cout<<"Testing the insert function"<<endl;
     // Just testing to see if seg fault happen
    
     dtree.insert(newAct);
     
     //Testing num for two things
     if(dtree.getNumUsers() == 2){
       cout<<"Passed "<<endl;
     }
     else{
       cout<<"Passed"<<endl;
     }
     cout<<"Check to see if the thing was inserted"<<endl;

     if(dtree.retrieve(2) != nullptr){
       cout<<"passed"<<endl;
     }
     else{
       cout<<"failed"<<endl;
     }

     if(dtree.retrieve(0) == nullptr){
       cout<<"passed"<<endl;
     }
     else{
       cout<<"failed"<<endl;
     }
     
   
     


     dtree.clear();
     
     cout<<"Testing the tree constructions and the vacant repacement"<<endl;
     // Checking to see if all of the value sent in proerly
     DNode * check;
     dtree.insert(newActce);
     check = dtree.GetRoot();
     dtree.Recursive_Insert(check, newActex);
     dtree.Recursive_Insert(check, newActed);

     if(dtree.retrieve(3) != nullptr){
       cout<<"passed"<<endl;
     }
     else{
       cout<<"failed"<<endl;
     }

     
     if(dtree.retrieve(4) != nullptr){
       cout<<"passed"<<endl;
     }
     else{
       cout<<"failed"<<endl;
     }
       
     if(dtree.retrieve(5) != nullptr){
       cout<<"passed"<<endl;
     }
     else{
       cout<<"failed"<<endl;
     }
     

     cout<<"Testing vacany function for the bst search tree"<<endl;

     dtree.clear();

     dtree.insert(newActed);
     check = dtree.GetRoot();
     dtree.Recursive_Insert(check, newActex);
     dtree.Recursive_Insert(check, newActce);

     if(dtree.remove(5,test) == true){
       cout<<"passed"<<endl;
     }
     else{
       cout<<"failed"<<endl;
     }
     

     int discsssss = 6;
     Account newAc = Account("", discsssss, 0, "", "");
     
    dtree.Recursive_Insert(check, newAc);
    
    if(dtree.retrieve(6) != nullptr){
       cout<<"passed"<<endl;
     }
     else{
       cout<<"failed"<<endl;
     }
    
    if(dtree.retrieve(5) == nullptr){
       cout<<"passed"<<endl;
     }
     else{
       cout<<"failed"<<endl;
     }
     


    dtree.clear();
     
   
    // Works for everything that wasn;t a copy
             
    cout << "Testing DTree insertion...";
    if(tester.testBasicDTreeInsert(dtree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "Resulting DTree:" << endl;
    dtree.dump();
    cout << endl;
    dtree.clear();

   
   
	 


    // testing the parts of   Recursive_Vacant_and_size_Update and itself
    
    cout<<"Testing the parts of the Recursive_Vacant_and_size_Update "<<endl;

    cout<<"Testing the size update"<<endl;
    dtree.insert(newActed);
    check = dtree.GetRoot();
    dtree.Recursive_Insert(check, newActex);
    dtree.Recursive_Insert(check, newActce);
    
   

    test = dtree.retrieve(3);
    DNode * test2 = dtree.retrieve(4);

    dtree.updateSize(test2);
    dtree.updateSize(test);

    cout<<"Testing the update suze on root"<<endl;
    if(test->getSize() == 3){
      cout<<"passed"<<endl;
    }
    else{
      cout<<"failed"<<endl;
    }
    cout<<"Testing the node on the right side"<<endl;
    if(test2->getSize() == 2){
      cout<<"passed"<<endl;
    }
    else{
      cout<<"failed"<<endl;
    }
    //Testing to see if a leaf node when get its size change if they use update suze
    DNode* test3 = dtree.retrieve(5);
    dtree.updateSize(test3);
    cout<<"Testing update size on leaf node to make sure it doens't change"<<endl;
    if(test3->getSize() == 1){
      cout<<"passed"<<endl;
    }
    else{
      cout<<"failed"<<endl;
    }
    DNode * switched;

 
    //Testing vacant on root

	
    dtree.remove(3,switched);

    DNode* Rotted =  dtree.GetRoot();

    if(Rotted->getNumVacant() == 1){
      cout<<"passed"<<endl;
    }
    else{
      cout<<"failed"<<endl;
    }
    cout<<"Expected output the is self assigment "<<endl;
    
    dtree = dtree;

    dtree.clear();

    dtree.insert(newActce);
    
    dtree.insert(newActex);
    dtree.insert(newActed);
    
    cout<<"Last thing checking the balacning see if it works"<<endl;
    // when the difference is not 4


    cout<<"When the balacning is off by 5"<<endl;
    int discxx = 1;
    Account newActces = Account("", discxx, 0, "", "");
    int discx = 2;
    Account newActcess = Account("", discx, 0, "", "");
  
    dtree.insert( newActces );
    dtree.insert( newActcess );
    
 
    
   

    
    // Utree time
    
    UTree utree;
    if(utree.insert(newActces)){
      cout<<"Passed"<<endl;
    }
    else{
      cout<<"Passed"<<endl;
    }

    if(utree.insert(newActcess)){
      cout<<"Passed"<<endl;
    }
    else{
      cout<<"Passed"<<endl;
    }

      
    cout << "\n\nTesting UTree insertion...";
    if(tester.testBasicUTreeInsert(utree)) {
        cout << "test passed" << endl;
    } else {
        cout << "test failed" << endl;
    }

    cout << "Resulting UTree:" << endl;
    utree.dump();
    cout << endl;
    
    return 0;
     
}
