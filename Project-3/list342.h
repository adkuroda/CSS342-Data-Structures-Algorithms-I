#include <iostream>
#include <fstream>
using namespace std;
/** This template class creates dynamically allocates and 
 *  by creating new object in singly linked list. 
*/

template <class T>
class List342{
public:
    /** Constructors and Destructor */
    List342();
    List342(const T& obj);
    List342(const List342<T>& list);
    ~List342();
    
    /** Member Functions */
    int Size() const;
    bool Insert(T* obj);
    bool Remove(T target, T& result);
    bool Peek(T target, T& result) const;
    void DeleteList();
    bool Merge(List342& rhs);
    bool BuildList(string file_name);

    /** Operator Overloads */
    List342<T>& operator =(const List342<T>& list);
    List342<T>& operator +=(const List342<T>& rhs);
    List342<T> operator +(const List342<T>& rhs) const;
    bool operator ==(const List342<T>& rhs) const;
    bool operator !=(const List342<T>& rhs) const;
    
    
private:
    struct Node{
        T *data = nullptr;
        Node *next = nullptr;
    };
    Node* head_;
    
    /** Output stream operator overload  */
    template<class U>
    friend ostream& operator<<(ostream& os, const List342<U>& rhs);

    template<class U>
    friend istream& operator<<(istream& is, List342<U>& rhs);

};
/** Default Constructor */
template <class T>
List342<T>::List342(): head_(nullptr){}

/** Default Constructor */
template <class T>
List342<T>::List342(const T& obj){
    if (obj == nullptr){
        head_ = nullptr;
    }else{
        head_ = new Node();
        head_ -> data = new T(*obj);
        head_-> next = nullptr;
    }
}
/** Assignment constructor utilized = operator */
template <class T>
List342<T>::List342(const List342<T>& list){
    head_ = nullptr;
    *this = list;
}

/** Determines the size of the List by iterating through 
 *  the entire list and counts each node. */
template <class T>
int List342<T>::Size() const{
    Node* current = head_;
    int ret = 0;
    while (current != nullptr){
        ret++;
        current = current -> next;
    }
    return ret;
}
/** If the object does not exisit in given list, this function  
 *  insert an object while maintaining sorter order and limiting 
 *  duplicate objects  */
template <class T>
bool List342<T>::Insert(T* obj){
    if (obj == nullptr){
        return false;
    }
    if (head_ == nullptr){
        head_ = new Node();
        head_-> data  = new T(*obj);
        return true;
    }
    if (*(head_ -> data) > *obj){
        Node* ins_node = new Node();
        ins_node-> data = new T(*obj);
        ins_node->next = head_;
        head_ = ins_node;
        return true;
    }
    if (*(head_ -> data) == *obj){
        return false;
    }
    Node* p_node = head_;
    while ((p_node->next != nullptr) && (*(p_node->next->data) < *obj)){
        p_node = p_node->next;
    }
    if ((p_node->next != nullptr) && (*(p_node->next->data) == *obj)){
        return false;
    }
    Node* ins_node = new Node();
    ins_node-> data = new T(*obj);
    ins_node->next = p_node->next;
    p_node->next = ins_node;
    return true;
}

/**Removes element if exist in the list returns true. Otherwise 
 * false. User of this function should ensure to check this function 
 * returns true before utilizing the result value in parameter 
 */
template <class T>
bool List342<T>::Remove(T target, T& result){
    if (head_ == nullptr){
        return false;
    }
    if (*(head_ -> data) == target){
        Node* temp = head_;
        head_ = head_->next;
        result = *(temp -> data);
        delete temp -> data;
        delete temp;
        return true;
    }
    Node* p_node = head_;
    while ((p_node->next != nullptr) && (*(p_node->next->data) < target)){
        p_node = p_node->next;
    }
    if (p_node->next == nullptr){
        return false;
    }
    if (p_node->next != nullptr && *(p_node->next->data) == target){
        Node* temp = p_node->next;
        p_node->next = p_node->next->next;
        result = *(temp -> data);
        delete temp -> data;
        delete temp;
        return true;
    }
    return false;
}
/** Based on file, this member function reads the file 
 * and passes the value to an object to create a new object. 
 * Newly created object will be inserted into the list 
*/
template <class T>
bool List342<T>::BuildList(string file_name){
    if(file_name.size() <= 0){
        return false;
    }
    ifstream in_file;
    in_file.open(file_name);
    if (!in_file.is_open()){
        return false;
    }
    T temp;
    while (!in_file.eof()){
        in_file >> temp;
        Insert(&temp);
    }
    return true;
    
}

/** Assignment operator. It deletes the existing the list and 
 * assigns right hand side to the list. Ensures there is not memory leak 
*/
template <class T>
List342<T>& List342<T>::operator =(const List342<T>& list){
    if (this == &list){
        return *this;
    }
    DeleteList();
    if (list.head_ == nullptr){
        head_ = nullptr;
        return *this;
    }
    Node * s_node = list.head_;
    Node * d_node = new Node();
    d_node -> data = new T(*(s_node -> data));
    head_ = d_node;
    s_node = s_node -> next;
    while (s_node != nullptr){
        d_node -> next = new Node();
        d_node = d_node -> next;
        d_node -> data = new T(*(s_node -> data));
        s_node = s_node -> next;
    }
    return *this;
}

/** Itilized the list += operator to implement this function*/
template<class T>
List342<T> List342<T>::operator +(const List342<T>& rhs) const{
    List342<T> ret = *this;
    ret += rhs;
    return ret;
}
/** This function adds list on right hand side to object in 
 *  linear time. Ensures no duplicate is added and list retains  
*/
template <class T>
List342<T>& List342<T>::operator +=(const List342<T>& rhs){
    if ((this == &rhs) || (rhs.head_ == nullptr)){
        return *this;
    }
    if (head_ == nullptr){
        Node* s_node = rhs.head_;
        Node* d_node = new Node();
        head_ = d_node;
        d_node -> data = new T(*(s_node -> data));
        s_node = s_node -> next;
        while(s_node != nullptr){
            d_node -> next = new Node();
            d_node = d_node -> next;
            d_node -> data = new T(*(s_node -> data));
            s_node = s_node -> next;
        }
        return *this;
    }
    Node* s_node = rhs.head_;
    Node* d_node = head_;
    if (*(d_node -> data) > *(s_node -> data)){
        head_= new Node();
        head_ -> data = new T(*(s_node -> data));
        head_ -> next = d_node;
        d_node  = head_;
        s_node = s_node -> next;
    }
    while ((d_node -> next != nullptr) && (s_node != nullptr)){
        if (*(d_node -> next -> data) == *(s_node -> data)){
            s_node  = s_node -> next;
        }else if (*(d_node -> next -> data) > *(s_node -> data)){
            Node* temp = new Node();
            temp -> data = new T(*(s_node -> data));
            temp -> next = d_node -> next;
            d_node -> next  = temp;
            d_node = temp;
            s_node = s_node -> next;
        }else{
            d_node = d_node -> next;
        }
    }
    if (s_node != nullptr){
        while(s_node != nullptr){
            d_node -> next = new Node();
            d_node = d_node -> next;
            d_node -> data = new T(*(s_node -> data));
            s_node = s_node -> next;
        }
    }
    return *this;
}

/** 
 * Checks if two List342 holds same objects. Returns false if their 
 *  size does not match or they contain different values 
*/
template<class T>
bool List342<T>::operator ==(const List342<T>& rhs) const{
    if (Size() != rhs.Size()){
        return false;
    }
    Node* cur_this = head_;
    Node* cur_rhs = rhs.head_;
    while (cur_this != nullptr && cur_rhs != nullptr){
        if (*(cur_this -> data) != *(cur_rhs -> data)){
            return false;
        }
        cur_this = cur_this -> next;
        cur_rhs = cur_rhs -> next;
    }
    return true;
}
/**
 *  This utilizes == operator to implement the function
*/
template<class T>
bool List342<T>::operator !=(const List342<T>& rhs) const{
    return !(*this == rhs);
}
/** Output stream operator overload */
template <typename T>
ostream& operator<<(ostream& os, const List342<T>& rhs){
    typename List342<T>::Node* current = rhs.head_;
    while (current != nullptr){
        os << *(current -> data);
        current = current -> next;
    }
    return os;
}
/** operator overload. Assumes other object operator >> are implemented*/
template <typename T>
istream& operator >> (istream& is, List342<T>& rhs){
    T temp;
    is >> temp;
    rhs.Insert(&temp);
    return is;
}

/** Merges two object in Linear time without creating an new object*/
template<class T>
bool List342<T>::Merge(List342& rhs){
    if (this == &rhs || rhs.head_ == nullptr){ 
        return false;
    }
    if (head_ == nullptr){
        Node* current = rhs.head_;
        head_ = current;
        Node* previous = head_;
        current = current -> next;
        while(current!= nullptr){
            previous -> next = current;
            previous = current;
            current = current -> next;
        }
        rhs.head_ = current;
        return true;
    }
    Node* cur_list = rhs.head_;
    Node* cur_this = head_;
    Node* previous = nullptr;
    
    while (cur_list != nullptr && cur_this != nullptr){
        if (*(cur_list -> data) == *(cur_this -> data)){
            previous = cur_this;
            cur_this = cur_this -> next;
            Node* temp = cur_list;
            cur_list = cur_list -> next;
            // if there is value then I dont need add so I guess I need to
            // delete it so it wont be dangling
            rhs.head_ = cur_list;
            delete temp -> data;
            delete temp;
            continue;
        }
        if (*(cur_list -> data) < *(cur_this -> data)){
            if (previous != nullptr){
                Node* temp = cur_list;
                cur_list = cur_list -> next;
                previous -> next = temp;
                previous = temp;
                temp -> next = cur_this;
            }else{
                Node* temp = cur_list;
                cur_list = cur_list -> next;
                head_ = temp;
                previous = temp;
                temp -> next = cur_this;
            }
        }else{
            previous = cur_this;
            cur_this = cur_this -> next;
        }
    }
    while (cur_list != nullptr){
        previous -> next = cur_list;
        previous = cur_list;
        cur_list = cur_list -> next;
   
    }
    rhs.head_ = cur_list;
    return true;
}
/** This deletes entire list */
template <class T>
void List342<T>::DeleteList(){
    while(head_!= nullptr){
        Node* temp = head_;
        head_ = head_ -> next;
        delete temp -> data;
        delete temp;  
    }
}
/** This function checks if the item exist in the list */
template <class T>
bool List342<T>::Peek(T target, T& result) const{
    if (head_ == nullptr){
        return false;
    }
    Node* current = head_;
    while(current != nullptr){
        if (current -> data != nullptr && *(current -> data) == target){
            result = *(current -> data);
            return true;
        }
        current = current -> next;
    }
    return false;
}
/** Destructor: Ensures this there is no leak*/
template<class T>
List342<T>::~List342(){
    DeleteList();
}