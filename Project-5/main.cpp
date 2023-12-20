#include <iostream>
#include "customer.h"
#include "fund.h"
#include "account.h"
#include "bank.h"
#include "bstree.h"


// Driver for the class 
int main(int argc, const char * argv[]) {
    if (argc == 2){
        string file_name = argv[1];
        Bank bank;
        bank.ParseText(file_name);
        bank.ProcessTransaction();
        bank.Display();
    }else{
        cerr << "ERROR: Please provide filename" << endl; 
    }
   /** In case Tesing Remove method*/
    // BSTree bs;
    // Account* a = new Account(1, "adam", "Mak");
    // Account* b = new Account(2, "adam", "Mak");
    // bs.Insert(a);
    // bs.Insert(b);
    // //bs.Display();
    // bs.Delete(2);
    //  bs.Display();
    return 0;

}

