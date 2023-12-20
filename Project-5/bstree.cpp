
#include "bstree.h"
// Default Constructor 
BSTree::BSTree(){
    root_ = nullptr;
}
// Constructor: Assignment 
BSTree::BSTree(const BSTree& tree){
    *this = tree;
}

// Operator overload 
BSTree& BSTree::operator = (const BSTree& rhs){
    DeleteTree(root_);
    Node * current = rhs.root_;
    PreordeTraverse(current);
    return *this;
}
// Helper to implement BSTree = operator overload 
void BSTree::PreordeTraverse(Node* node){
    if (node != nullptr){
        Account* in_acc = new Account(*(node -> p_acct));
        Insert(in_acc);
        PreordeTraverse(node -> left);
        PreordeTraverse(node -> right);
    }
}

// Utilizes PlaceNode helper function to implement the code. 
bool BSTree::Insert(Account* account){
    bool status = false;
    Node* root = root_;
    root_ = PlaceNode(root, account, status);
    return status;
}
// Helper function to insert a node. Utilized Corrano Course book P.492
// to implement this code. 
BSTree::Node* BSTree::PlaceNode(Node* root, Account* account, bool& status){
    if (root == nullptr){
        Node* ret_node = new Node();
        ret_node -> p_acct = account;
        status = true;
        return ret_node;
    }
//    if (*(root -> p_acct) == *account){
//        return root;
//    }
    else if(*(root -> p_acct) > *account){
        root -> left = PlaceNode(root -> left, account, status);
    }
    else if (*(root -> p_acct) < *account){
        root -> right = PlaceNode(root -> right, account, status);
    }
    return root;
}
// Displays the tree 
void BSTree::Display() const{
    Node * node = root_;
    inorder_traverse(node);
}
// Helper function to display the node values 
void BSTree::inorder_traverse(Node* node)const{
    if (node != nullptr){
        inorder_traverse(node -> left);
        cout << *(node -> p_acct);
        inorder_traverse(node -> right);
    }
}


bool BSTree::Retrieve(const int& account_id, Account*& account) const{
    Node* node = root_;
    return RetrieveHelper(node, account_id, account);
    
}

bool BSTree::RetrieveHelper(Node* node, const int& account_id,
                            Account*& account) const{
    if (node == nullptr){
        account = nullptr;
        return false;
    }
    else if ((*(node ->p_acct)).account_id() == account_id){
        account = node -> p_acct;
        return true;
    }
    else if((*(node ->p_acct)).account_id() > account_id){
        RetrieveHelper(node -> left, account_id, account);
    }
    else if((*(node ->p_acct)).account_id() < account_id){
        RetrieveHelper(node -> right, account_id, account);
    }
    return false;
}


// deletes the nodes and account from a given tree
void BSTree::DeleteTree(Node* node){
    if(node != nullptr){
        DeleteTree(node -> left);
        DeleteTree(node -> right);
        delete node -> p_acct;
        delete node;
    }

}
// I used algorithm from Corrano P. 498 and 499
// Wrapper function for removal. 
bool BSTree::Delete(const int& account_id){
    bool ret = false;
    root_ = RemoveValue(root_, account_id, ret);
    return ret;
}
// I used algorithm from Corrano P. 498 and 499 
// Does not do actual removal. Finds the node that needs to be 
// removed and add calls RemoveNode function to remove actual node
BSTree::Node* BSTree::RemoveValue(Node* node, const int& account_id, bool& status){
    if (node == nullptr){
        status = false;
    }else if((*(node -> p_acct)).account_id()== account_id){
        status = true;
        node= RemoveNode(root_);
    }else if((*(node -> p_acct)).account_id() > account_id){
        Node * temp = RemoveValue(node -> left, account_id, status);
        node -> left = temp;
    }else{
        Node * temp = RemoveValue(node -> left, account_id, status);
        node -> right = temp;
    }
    return node;
}
// I used algorithm from Corrano P. 498 and 499: Helper function
// It removes the node. 
BSTree::Node* BSTree::RemoveNode(Node* node){
    if ((node -> right == nullptr) && ((node -> left) == nullptr)){
        delete node -> p_acct;
        delete node;
        node = nullptr;
        return node;
    }else if((node -> right == nullptr) || ((node -> left) == nullptr)){
        Node* ret_node = nullptr;
        if ((node -> right != nullptr)){
            ret_node = node -> right;
        }else{
            ret_node =node -> left;
        }
        delete node -> p_acct;
        delete node;
        return ret_node;

    }else{
        Node* temp = node -> right;
        while (temp -> left != nullptr){
            temp = temp -> left;
        }
        delete node -> p_acct;
        node -> p_acct = new Account(*(temp -> p_acct));
        delete temp -> p_acct;
        delete temp;
        return node;
    }
    
}

int BSTree::Size() const{
    int size = 0;
    Node * temp = root_;
    SizeHelper(temp, size);
    return size;
}
void BSTree::SizeHelper(Node * node, int& size) const{
    if (node != nullptr){
        inorder_traverse(node -> left);
        size++;
        inorder_traverse(node -> right);
    }
}



/** Deallocated memory and deletes the tree*/
BSTree::~BSTree(){
   DeleteTree(root_);
}
