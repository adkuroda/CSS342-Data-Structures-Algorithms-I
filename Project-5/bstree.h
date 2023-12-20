

#ifndef BSTREE_H_
#define BSTREE_H_
#include "account.h"

class BSTree{
public:
    BSTree();
    BSTree(const BSTree& tree);
    ~BSTree();
    bool Insert(Account* account);
    bool Retrieve(const int& account_id, Account*& account) const;
    // Used Corrano algorithm
    bool Delete(const int& account_id);

    BSTree& operator = (const BSTree& rhs);
 
    void Display() const;
    int Size() const;
private:
    struct Node
    {
    Account* p_acct = nullptr;
    Node* right = nullptr;
    Node* left = nullptr;
    };
    Node* root_ = nullptr;
    //Corrano Course book P.492 helper for insert
    Node* PlaceNode(Node* root, Account* account, bool& status);
    
    //Corrano Course book P.486 Helper for display
    void inorder_traverse(Node* node) const;
    void PreordeTraverse(Node* node);
    void DeleteTree(Node* node);
    void SizeHelper(Node * node, int& size) const;
    
    // algorithm from Corrano P. 498 and 499
    Node*  RemoveValue(Node* root, const int& account_id, bool& status);
    // algorithm from Corrano P. 498 and 499
    Node* RemoveNode(Node* root);

    bool RetrieveHelper(Node* node,const int& account_id, Account*& account) const;
   
};

#endif /* bstree_hpp */
