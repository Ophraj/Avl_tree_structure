//
// Created by ophra on 20/04/2022.
//

#ifndef EMPLOYEE1_AVL_TREE_H
#define EMPLOYEE1_AVL_TREE_H
//
// Created by ophra on 29/11/2021.
//

#include "CompaniesManager.h"
#include <iostream>

typedef enum {
    AVL_SUCCESS,
    AVL_NODE_ALREADY_EXISTS,
    AVL_NODE_NO_EXIST,
    AVL_NULL_ARGUMENT,
    AVL_NO_ALLOCATION,
} AVLResults;


template <class T>
class Node {
    int key;
    T element;
    int height;
    Node* father;
    Node* left_son;
    Node* right_son;
public:
    Node(int key = -1, T element = nullptr, int height = 0, Node* father = nullptr, Node* left_son = nullptr,
         Node* right_son = nullptr);
    ~Node();
    void SetKey(int key);
    int GetKey() const;
    void SetKey(Node<T>* node);
    void SetElement(Node<T>* node);
    T& GetElement();
    void SetHeight(int new_height);
    int GetHeight();
    void SetNodeLeft(Node* left_son);
    Node* GetNodeLeft();
    void SetNodeRight(Node* right_son);
    Node* GetNodeRight();
    void SetFatherNode(Node* father);
    Node* GetFatherNode();
    int GetBF();
    //int getHeight();
    Node* Get_Following_node();
    int SetNewHeight();
    Node* BuildAvlSubtree(int height_needed);
    Node<T>* GetPreviousNode();
};

template <class T>
class Avl_tree {
private:
    Node<T>* root;
    //Node<T>* CopyNodes(Node<T>* node);

public:
    Avl_tree();

    Avl_tree(Node<T>* root);

    ~Avl_tree();

    void AuxDistructorTree(Node<T>* node);

    Node<T>* GetRoot();

    void SetRoot( Node<T>* new_root);

    Node<T>* FindNode(Node<T>* root, int key) const;

    Node<T>* FindNode(Node<T>* root, int key, int player_id);

    int InorderVisit(Node<T>* node, int* array, int i);

    int CountNodesOfTree(Node<T>* root);

    AVLResults InsertNode(int key, T& element, Node<T>* node_added);

    AVLResults InsertNode(Node<T>* node);

    AVLResults InsertNode(int key, T& element, int PlayerID, Node<T>* added_node);

    void Fix_BF_after_insert(Node<T>* check);

    AVLResults RemoveNode(int key);

    AVLResults RemoveNode(int key, int PlayerID);

    AVLResults Remove_Node_Leaf(Node<T>* node);

    AVLResults Remove_Node_With_Only_Child (Node<T>* node);

    void Swap(Node<T>* node_1, Node<T>* node_2);

    AVLResults RotateLL(Node<T>* node);

    AVLResults RotateLR(Node<T>* node);

    AVLResults RotateRL(Node<T>* node);

    AVLResults RotateRR(Node<T>* node);

    Node<T>* Get_smallest_node();

    void ReverseInorder(Node<T>* node, int* i);

    void Inorder(Node<T>* node, Node<T>** array, int size);

    Node<T>* ReplaceNodeByAnother(Node<T>* last, Node<T>* new_node);
};


template <class T>
Node<T>::Node(int key, T element, int height, Node* father, Node* left_son, Node* right_son) :
        key(key), element(element), height(height), father(father), left_son(left_son), right_son(right_son) {}

template <class T>
Node<T>::~Node()
{
    delete element;
}

template <class T>
void Node<T>::SetKey(int key)
{
    this->key = key;
}

template <class T>
int Node<T>::GetKey() const
{
    return key;
}

template <class T>
T& Node<T>::GetElement()
{
    return element;
}

template <class T>
void Node<T>::SetHeight(int new_height)
{
    this->height = new_height;
}

template <class T>
int Node<T>::GetHeight()
{
    return this->height;
}
template <class T>
void Node<T>::SetKey(Node<T>* node)
{
    this->key = node->GetKey();
}

template <class T>
void Node<T>::SetElement(Node<T>* node)
{
    this->element = node->GetElement();
}

template <class T>
void Node<T>::SetNodeLeft(Node* left_son_to_set)
{
    this->left_son = left_son_to_set;
}

template <class T>
Node<T>* Node<T>::GetNodeLeft()
{
    return left_son;
}

template <class T>
void Node<T>::SetNodeRight(Node* right_son_to_set)
{
    this->right_son = right_son_to_set;
}

template <class T>
Node<T>* Node<T>::GetNodeRight()
{
    return right_son;
}

template <class T>
void Node<T>::SetFatherNode(Node* father_to_set)
{
    this->father = father_to_set;
}

template <class T>
Node<T>* Node<T>::GetFatherNode()
{
    return father;
}

template <class T>
int Node<T>::GetBF() {

    int height_left=-1;  //if there's no left son
    if (this->left_son != nullptr)
        height_left= this->left_son->GetHeight();

    int height_right=-1;  //if there's no right son
    if (this->right_son!= nullptr)
        height_right= this->right_son->GetHeight();

    return (height_left-height_right);
}

template <class T>
Node<T>* Node<T>::BuildAvlSubtree(int height_needed)
{
    if (height_needed <= 0)
        return nullptr;
    Node<T>* node = new Node<T>();
    node->left_son = BuildAvlSubtree(height_needed-1);
    node->right_son = BuildAvlSubtree(height_needed-1);
    return node;
}

/*template <class T>
int Node<T>::getHeight() { //n

    if(this->left_son == nullptr && this->right_son == nullptr)
    {
        return 1;
    }
    if(this->left_son == nullptr)
    {
        return this->right_son->getHeight() + 1;
    }
    if(this->right_son == nullptr)
    {
        return this->left_son->getHeight() + 1;
    }

    return std::max(this->left_son->getHeight(), this->right_son->getHeight()) + 1;
}*/

template <class T>
Node<T>* Node<T>::Get_Following_node()
{
    Node<T> *following;
    if (this->father == nullptr) {
        if (this->right_son == nullptr) //there's no bigger after him and there's no father
        {
            return nullptr;
        }

        following = this->right_son; //biggest

        while (true) {
            if (following->left_son == nullptr) //smallest after him
                break;
            following = following->left_son;
        }
        return following;
    }
    else  //there's a father
    {
        if (this->right_son != nullptr) //there's a right son
        {
            following = this->right_son;

            while (true) {
                if (following->left_son == nullptr) //smallest after him
                    break;
                following = following->left_son;
            }
            return following;
        }

        //There's no right son but there's a father
        Node<T>* father = this->father;
        if (this->right_son == nullptr) {
            if (father->left_son == this) //node if a left son
            {
                return father;
            }
            else if (father->right_son == this) //rightson
            {
                Node<T> *grandfather = father->father;

                while (true) {
                    if (grandfather == nullptr) {
                        return nullptr;
                    }

                    if (grandfather->left_son == father) {
                        return grandfather;
                    }

                    if (grandfather->left_son != father) {
                        grandfather = grandfather->father;
                        father= father->father;
                    }
                }
            }
        }
    }
    return nullptr;
}


template <class T>
int Node<T>::SetNewHeight()
{
    if (this == nullptr)
        return -1;

    int previous_height = this->GetHeight();

    int height_right=-1;
    int height_left=-1;
    if(this->GetNodeRight()!=nullptr)
        height_right=this->GetNodeRight()->GetHeight();
    if(this->GetNodeLeft()!=nullptr)
        height_left=this->GetNodeLeft()->GetHeight();

    int height= std::max(height_right, height_left)+1;
    this->SetHeight(height);

    if(previous_height == this->GetHeight()) //if there wasnt any change
        return 0;
    return 1; //we changed it
}
//****************************************TREE*********************************

template <class T>
Avl_tree<T>::Avl_tree(): root(nullptr) {}

template <class T>
Avl_tree<T>::Avl_tree(Node<T>* root) : root(root) {}

template <class T>
Avl_tree<T>::~Avl_tree() {}


template <class T>
void Avl_tree<T>::SetRoot( Node<T>* new_root)
{
    this->root = new_root;
}

template <class T>
void Avl_tree<T>::AuxDistructorTree(Node<T>* node)
{
    if(node == nullptr) {
        return;
    }
    AuxDistructorTree(node->GetNodeLeft());
    AuxDistructorTree(node->GetNodeRight());
    delete node;
}

template <class T>
void Avl_tree<T>::ReverseInorder(Node<T> *node, int* i)
{
    if(node == nullptr || *i<=0)
        return;

    ReverseInorder(node->GetNodeRight() , i);
    Node<T>* father = node->GetFatherNode();
    Node<T>* left_node = node->GetNodeLeft();
    if(*i > 0 && node->GetNodeRight() == nullptr && node->GetNodeLeft() == nullptr )
    {
        if (father!= nullptr)
        {
            if (father->GetNodeRight()==node)
                father->SetNodeRight(nullptr);
            else
                father->SetNodeLeft(nullptr);
        }
        delete node;
        *i = *i - 1;
    }

    ReverseInorder(left_node, i);
}


template <class T>
void Avl_tree<T>::Inorder(Node<T>* node, Node<T>** array, int size)
{
    if(node == nullptr)
        return;

    for (int i = 0; i < size && node != nullptr; ++i)
    {
        if(node->GetFatherNode() == nullptr)
        {
            this->root = array[i];
        }
        node = ReplaceNodeByAnother(node, array[i]);
        node = node->Get_Following_node();
    }
}

template<class T>
Node<T>* Avl_tree<T>::ReplaceNodeByAnother(Node<T>* last, Node<T>* new_node)
{
    //take the pointers all around the last_node
    Node<T>* left_last= last->GetNodeLeft();
    Node<T>* right_last= last->GetNodeRight();
    Node<T>* father_last= last->GetFatherNode();

    //Place them into the new Node
    new_node->SetFatherNode(father_last);
    new_node->SetNodeLeft(left_last);
    new_node->SetNodeRight(right_last);

    //Make the father point to the new node
    if(father_last!= nullptr)
    {
        if(father_last->GetNodeLeft()==last)
            father_last->SetNodeLeft(new_node);
        else
            father_last->SetNodeRight(new_node);
    }

    //Make the children point to the new node
    if(right_last!= nullptr)
    {
        right_last->SetFatherNode(new_node);
    }

    if(left_last!= nullptr)
    {
        left_last->SetFatherNode(new_node);
    }
    delete last;
    return new_node;
}

/*
Avl_tree::Avl_tree(const Avl_tree& tree) : compare_fct(tree.compare_fct), free_fct(tree.free_fct), cpy_fct(tree.cpy_fct)
{
    this->root = CopyNodes(tree.root);
}

Node* Avl_tree::CopyNodes(Node* node)
{
    if(node != nullptr)
    {
        Node* left = CopyNodes(node->GetNodeLeft());
        Node* right = CopyNodes(node->GetNodeRight());
        Node* father = CopyNodes(node->GetFatherNode());

        return new Node(this->compare_fct, this->free_fct, this->cpy_fct, node->GetKey(), node->GetElement(), node->GetFatherNode(), left, right);
    }
    else
    {
        return nullptr;
    }
}
*/

template <class T>
Node<T>* Avl_tree<T>::GetRoot()
{
    return this->root;
}


template <class T>
Node<T>* Avl_tree<T>::FindNode(Node<T>* root, int key) const
{
    if (this->root == nullptr)
    {
        return nullptr;
    }
    if(root == nullptr)
    {
        return nullptr;
    }

    if (root->GetKey() == key)
    {
        return root;
    }
    else if (root->GetKey() > key)
    {
        return Avl_tree::FindNode(root->GetNodeLeft(), key);
    }
    else if (root->GetKey() < key)
    {
        return Avl_tree::FindNode(root->GetNodeRight(), key);
    }

    return nullptr;
}

template <class T>
Node<T>* Avl_tree<T>::FindNode(Node<T>* root, int key, int player_id)
{
    if (this->root == nullptr)
    {
        return nullptr;
    }

    if(root == nullptr)
    {
        return nullptr;
    }

    if (root->GetKey() == key)
    {
        if(GetPlayerID(root->GetElement()) < player_id)
        {
            return Avl_tree::FindNode(root->GetNodeLeft(), key, player_id);
        }
        if(GetPlayerID(root->GetElement()) > player_id)
        {
            return Avl_tree::FindNode(root->GetNodeRight(), key, player_id);
        }
        if(GetPlayerID(root->GetElement()) == player_id)
        {
            return root;
        }
    }
    else if (root->GetKey() > key)
    {
        return FindNode(root->GetNodeLeft(), key, player_id);
    }
    else if (root->GetKey() < key)
    {
        return Avl_tree::FindNode(root->GetNodeRight(), key, player_id);
    }

    return nullptr;
}

template<class T>
Node<T>* Node<T>::GetPreviousNode()
{
    Node<T> *following;
    if (this->father == nullptr) {
        if (this->left_son == nullptr) //there's no smallest after him and there's no father
        {
            return nullptr;
        }

        following = this->left_son; //smallest

        while (true) {
            if (following->right_son == nullptr) //smallest after him
                break;
            following = following->right_son;
        }
        return following;
    }

    else  //there's a father
    {
        if (this->left_son != nullptr) //there's a left son
        {
            following = this->left_son;

            while (true) {
                if (following->right_son == nullptr) //smallest after him
                    break;
                following = following->right_son;
            }
            return following;
        }

        //There's no left son but there's a father
        Node<T>* father = this->father;
        if (this->left_son == nullptr) {
            if (father->right_son == this) //node is a right son
            {
                return father;
            }
            else if (father->left_son == this) //left son
            {
                Node<T> *grandfather = father->father;

                while (true) {
                    if (grandfather == nullptr)
                        return nullptr;

                    if (grandfather->right_son == father) {
                        return grandfather;
                    }

                    if (grandfather->right_son != father) {
                        grandfather = grandfather->father;
                        father = father->father;
                    }
                }
            }
        }
    }
    return nullptr;
}


template <class T>
int Avl_tree<T>::   InorderVisit(Node<T>* node, int* array, int i)
{
    if(node == nullptr)
    {
        return i;
    }

    else
    {
        int i_2 = InorderVisit(node->GetNodeLeft(), array, i);
        array[i_2] = GetPlayerID(node->GetElement());
        int i_3 = InorderVisit(node->GetNodeRight(), array, i_2 + 1);
        return i_3;
    }
}


template <class T>
int Avl_tree<T>::CountNodesOfTree(Node<T>* root)
{
    if(root == nullptr)
    {
        return 0;
    }

    //recursive call to left child and right child and add the result of these with 1 ( 1 for counting the root)
    return 1 + CountNodesOfTree(root->GetNodeLeft()) + CountNodesOfTree(root->GetNodeRight());
}

template <class T>
AVLResults Avl_tree<T>::InsertNode(Node<T>* node)
{
    if (node == nullptr)
    {
        return AVL_NULL_ARGUMENT;
    }

    if (FindNode(this->root, node->GetKey()) != nullptr)
    {
        return AVL_NODE_ALREADY_EXISTS;
    }

    Node<T>* check = this->root;
    if (check == nullptr) {
        node->SetHeight(0);
        node->SetFatherNode(check);
        node->SetNodeRight(nullptr);
        node->SetNodeLeft(nullptr);
        this->root = node;
        return AVL_SUCCESS;
    }

    for (; check!= nullptr;) {
        if (check->GetKey() < node->GetKey()) {
            if (check->GetNodeRight() == nullptr)
                break;

            check = check->GetNodeRight();
            continue;
        }

        if (check->GetKey() > node->GetKey()) {
            if (check->GetNodeLeft() == nullptr)
                break;

            check = check->GetNodeLeft();
            continue;
        }
    }

    if (node->GetKey()>check->GetKey()){
        check->SetNodeRight(node);
    }
    if (node->GetKey() < check->GetKey()){
        check->SetNodeLeft(node);
    }

    node->SetFatherNode(check);
    node->SetHeight(0);
    node->SetNodeRight(nullptr);
    node->SetNodeLeft(nullptr);

    //Now that the Node is properly added, we want to check BF and fix it if wrong.
    Node<T>* temp = node;
    while (temp->GetFatherNode() != nullptr)
    {
        temp->GetFatherNode()->SetNewHeight();
        temp = temp->GetFatherNode();
    }


    Node<T>* node_to_fix= check->GetFatherNode();
    int BF=0;

    while (node_to_fix!= nullptr)
    {
        BF=node_to_fix->GetBF();

        if (BF==2 || BF==-2) //The balance factor needs to be fixed with rotation.
        {
            Fix_BF_after_insert(check);
            break;
        }

        node_to_fix=node_to_fix->GetFatherNode();
        check= check->GetFatherNode();
    }

    temp = node;
    while (temp->GetFatherNode() != nullptr)
    {
        temp->GetFatherNode()->SetNewHeight();
        temp = temp->GetFatherNode();
    }

    return AVL_SUCCESS;              //The node is added and the tree is fixed.
}


template <class T>
AVLResults Avl_tree<T>::InsertNode(int key, T &element, Node<T>* node_added) {
    if (key <= 0 || element == nullptr)
        return AVL_NULL_ARGUMENT; //**************

    if (FindNode(this->root, key) != nullptr)
        return AVL_NODE_ALREADY_EXISTS;

    Node<T> *node = new Node<T>(key, element, 0);
    if (node == nullptr)
        return AVL_NO_ALLOCATION;

    //check if it's the first Node to be added and if so update the root.
    Node<T> *check = this->root;
    if (check == nullptr) {
        node->SetHeight(0);
        node->SetFatherNode(check);
        node->SetNodeRight(nullptr);
        node->SetNodeLeft(nullptr);
        this->root = node;
        return AVL_SUCCESS;
    }
    for (; check != nullptr;) {
        if (check->GetKey() < node->GetKey()) {
            if (check->GetNodeRight() == nullptr)
                break;

            check = check->GetNodeRight();
            continue;
        }

        if (check->GetKey() > node->GetKey()) {
            if (check->GetNodeLeft() == nullptr)
                break;

            check = check->GetNodeLeft();
            continue;
        }
    }

    if (node->GetKey() > check->GetKey()) {
        check->SetNodeRight(node);
    }
    if (node->GetKey() < check->GetKey()) {
        check->SetNodeLeft(node);
    }

    node->SetHeight(0);
    node->SetFatherNode(check);
    node->SetNodeRight(nullptr);
    node->SetNodeLeft(nullptr);

    //Now that the Node is properly added, we want to check BF and fix it if wrong.

    //Fix the heights log n
    Node<T>* temp = node;
    while (temp->GetFatherNode() != nullptr)
    {
        temp->GetFatherNode()->SetNewHeight();
        temp = temp->GetFatherNode();
    }

    Node<T>* node_to_fix= check->GetFatherNode();
    int BF=0;

    while (node_to_fix!= nullptr)
    {
        BF=node_to_fix->GetBF();

        if (BF==2 || BF==-2) //The balance factor needs to be fixed with rotation.
        {
            Fix_BF_after_insert(check);
            break;
        }

        node_to_fix=node_to_fix->GetFatherNode();
        check= check->GetFatherNode();
    }

    if(node_added != nullptr)
    {
        node_added = node;
    }

    temp = node;
    while (temp->GetFatherNode() != nullptr)
    {
        temp->GetFatherNode()->SetNewHeight();
        temp = temp->GetFatherNode();
    }

    return AVL_SUCCESS;              //The node is added and the tree is fixed.
}


template <class T>
AVLResults Avl_tree<T>::InsertNode(int key, T& element, int PlayerID, Node<T>* added_node)
{
    if (key < 0 || element== nullptr)
        return AVL_NULL_ARGUMENT;

    if (FindNode(this->root, key, PlayerID) != nullptr)
        return AVL_NODE_ALREADY_EXISTS;

    Node<T>* node = new Node<T>(key, element, 0);
    if (node== nullptr)
        return AVL_NO_ALLOCATION;

    Node<T>* check=this->root;
    if (check == nullptr) {
        node->SetHeight(0);
        node->SetFatherNode(check);
        node->SetNodeRight(nullptr);
        node->SetNodeLeft(nullptr);
        this->root = node;
        return AVL_SUCCESS;
    }

    for (;check!= nullptr;) {

        if (check->GetKey() == node->GetKey()) {
            if (GetPlayerID(node->GetElement()) < GetPlayerID(check->GetElement())) {
                if (check->GetNodeRight() == nullptr)
                    break;

                check = check->GetNodeRight();
            } else {
                if (check->GetNodeLeft() == nullptr)
                    break;
                check = check->GetNodeLeft();
            }

            continue;
        }

        if (check->GetKey() < node->GetKey()) {
            if (check->GetNodeRight() == nullptr)
                break;

            check = check->GetNodeRight();
            continue;
        }

        if (check->GetKey() > node->GetKey()) {
            if (check->GetNodeLeft() == nullptr)
                break;

            check = check->GetNodeLeft();
            continue;
        }
    }

    if (node->GetKey()>check->GetKey())
        check->SetNodeRight(node);
    if(node->GetKey()<check->GetKey())
        check->SetNodeLeft(node);
    if (node->GetKey()==check->GetKey()) {
        if (GetPlayerID(node->GetElement()) < GetPlayerID(check->GetElement()))
            check->SetNodeRight(node);
        else
            check->SetNodeLeft(node);
    }

    node->SetHeight(0);
    node->SetFatherNode(check);
    node->SetNodeRight(nullptr);
    node->SetNodeLeft(nullptr);

    //******************************
    //Now that the Node is properly added, we want to check BF and fix it if wrong.

    Node<T>* temp = node;
    while (temp->GetFatherNode() != nullptr)
    {
        temp->GetFatherNode()->SetNewHeight();
        temp = temp->GetFatherNode();
    }

    Node<T>* node_to_fix= check->GetFatherNode();
    int BF=0;

    while (node_to_fix!= nullptr)
    {
        BF=node_to_fix->GetBF();

        if (BF==2 || BF==-2) //The balance factor needs to be fixed with rotation.
        {
            Fix_BF_after_insert(check);
            break;
        }

        node_to_fix=node_to_fix->GetFatherNode();
        check= check->GetFatherNode();
    }
    //The node is added and the tree is fixed.
    //fix the height log n
    temp = node;
    while (temp->GetFatherNode() != nullptr)
    {
        temp->GetFatherNode()->SetNewHeight();
        temp = temp->GetFatherNode();
    }
    return AVL_SUCCESS;
}


template <class T>
void Avl_tree<T>::Fix_BF_after_insert(Node<T>* check)
{
    if(check == nullptr)
    {
        return;
    }
    Node<T>* node_to_fix= check->GetFatherNode();
    if(node_to_fix == nullptr)
    {
        return;
    }
    int BF=node_to_fix->GetBF();

    if (BF==2 && check->GetBF()>=0)
        RotateLL(node_to_fix);

    else if (BF==2 && check->GetBF()<=-1)
        RotateLR(node_to_fix);

    else if (BF==-2 && check->GetBF()<=0)
        RotateRR(node_to_fix);

    else if (BF==-2 && check->GetBF()>=1)
        RotateRL(node_to_fix);
}

template <class T>
AVLResults Avl_tree<T>::RemoveNode(int key , int EmployeeID){
    if (key<0 || EmployeeID<=0)
        return AVL_NULL_ARGUMENT;

    Node<T>* node_to_remove= FindNode(this->root, key, EmployeeID);
    if (node_to_remove== nullptr)
        return AVL_NODE_NO_EXIST;

    if (node_to_remove->GetNodeRight()== nullptr && node_to_remove->GetNodeLeft()== nullptr)
        return this->Remove_Node_Leaf(node_to_remove);

    else if (node_to_remove->GetNodeRight()== nullptr || node_to_remove->GetNodeLeft()== nullptr)
        return this->Remove_Node_With_Only_Child(node_to_remove);

    //The node has 2 children, we look for the "following" node and we swap them
    //then we delete the node to remove
    Node<T>* following_node= node_to_remove->Get_Following_node();
    /*there's a following node because if there's not it means the node_to_remove is the biggest
    node and that means it's the leaf at the right of the tree */
    Swap(node_to_remove, following_node);
    if(node_to_remove->GetFatherNode()== nullptr)
    {
        this->root=following_node;
        following_node->SetFatherNode(nullptr);
    }

    else if(node_to_remove->GetFatherNode()!= nullptr)
    {
        if(node_to_remove->GetNodeRight()== nullptr) {
            if (node_to_remove->GetFatherNode()->GetNodeRight() == node_to_remove)
                node_to_remove->GetFatherNode()->SetNodeRight(nullptr);
            else if (node_to_remove->GetFatherNode()->GetNodeLeft() == node_to_remove)
                node_to_remove->GetFatherNode()->SetNodeLeft(nullptr);
        }

        else if(node_to_remove->GetNodeRight() != nullptr)
        {
            node_to_remove->GetNodeRight()->SetFatherNode(node_to_remove->GetFatherNode());
            if (node_to_remove->GetFatherNode()->GetNodeRight() == node_to_remove)
                node_to_remove->GetFatherNode()->SetNodeRight(node_to_remove->GetNodeRight());
            else if (node_to_remove->GetFatherNode()->GetNodeLeft() == node_to_remove)
                node_to_remove->GetFatherNode()->SetNodeLeft(node_to_remove->GetNodeRight());
        }
    }

    //fix the heights of the fathers
    Node<T>* father = node_to_remove->GetFatherNode();
    Node<T>* temp =father;
    while(temp!= nullptr)
    {
        if(temp->SetNewHeight()==0)
            break;
        temp= temp->GetFatherNode();
    }

    //We now check the BF of all the nodes from here to the root
    if(father == nullptr)
    {
        return AVL_SUCCESS;
    }
    int BF = father->GetBF();

    while (true)
    {
        if (BF==2){
            if(father->GetNodeLeft() != nullptr) {

                if ((father->GetNodeLeft())->GetBF() == -1)
                    RotateLR(father);
                else if ((father->GetNodeLeft())->GetBF() >= 0)
                    RotateLL(father);
            }
        }

        if (BF==-2){
            if(father->GetNodeRight() != nullptr) {
                if ((father->GetNodeRight())->GetBF() == 1)
                    RotateRL(father);
                else if ((father->GetNodeRight())->GetBF() <= 0)
                    RotateRR(father);
            }
        }

        if (father->GetFatherNode()== nullptr)
            break;
        father=father->GetFatherNode();
        BF = father->GetBF();
    }

    delete node_to_remove;
    return AVL_SUCCESS;
}

template <class T>
AVLResults Avl_tree<T>::RemoveNode(int key){
    if (key<0)
        return AVL_NULL_ARGUMENT;

    Node<T>* node_to_remove= FindNode(this->root, key);
    if (node_to_remove== nullptr)
        return AVL_NODE_NO_EXIST;

    if (node_to_remove->GetNodeRight()== nullptr && node_to_remove->GetNodeLeft()== nullptr)
        return this->Remove_Node_Leaf(node_to_remove);

    else if (node_to_remove->GetNodeRight()== nullptr || node_to_remove->GetNodeLeft()== nullptr)
        return this->Remove_Node_With_Only_Child(node_to_remove);

    //The node has 2 children, we look for the "following" node and we swap them
    //then we delete the node to remove
    Node<T>* following_node= node_to_remove->Get_Following_node();
    /*there's a following node because if there's not it means the node_to_remove is the biggest
    node and that means it's the leaf at the right of the tree */
    Swap(node_to_remove, following_node);
    if(node_to_remove->GetFatherNode()== nullptr)
    {
        this->root=following_node;
        following_node->SetFatherNode(nullptr);
    }

    else if(node_to_remove->GetFatherNode()!= nullptr)
    {
        if(node_to_remove->GetNodeRight()== nullptr) {
            if (node_to_remove->GetFatherNode()->GetNodeRight() == node_to_remove)
                node_to_remove->GetFatherNode()->SetNodeRight(nullptr);
            else if (node_to_remove->GetFatherNode()->GetNodeLeft() == node_to_remove)
                node_to_remove->GetFatherNode()->SetNodeLeft(nullptr);
        }

        else if(node_to_remove->GetNodeRight() != nullptr)
        {
            node_to_remove->GetNodeRight()->SetFatherNode(node_to_remove->GetFatherNode());
            if (node_to_remove->GetFatherNode()->GetNodeRight() == node_to_remove)
                node_to_remove->GetFatherNode()->SetNodeRight(node_to_remove->GetNodeRight());
            else if (node_to_remove->GetFatherNode()->GetNodeLeft() == node_to_remove)
                node_to_remove->GetFatherNode()->SetNodeLeft(node_to_remove->GetNodeRight());
        }
    }

    //fix the heights of the fathers
    Node<T>* father = node_to_remove->GetFatherNode();
    Node<T>* temp =father;
    while(temp!= nullptr)
    {
        if(temp->SetNewHeight()==0)
            break;
        temp= temp->GetFatherNode();
    }

    //We now check the BF of all the nodes from here to the root
    if(father == nullptr)
    {
        return AVL_SUCCESS;
    }
    int BF = father->GetBF();

    while (true)
    {
        if (BF==2){
            if(father->GetNodeLeft() != nullptr) {

                if ((father->GetNodeLeft())->GetBF() == -1)
                    RotateLR(father);
                else if ((father->GetNodeLeft())->GetBF() >= 0)
                    RotateLL(father);
            }
        }

        if (BF==-2){
            if(father->GetNodeRight() != nullptr) {
                if ((father->GetNodeRight())->GetBF() == 1)
                    RotateRL(father);
                else if ((father->GetNodeRight())->GetBF() <= 0)
                    RotateRR(father);
            }
        }

        if (father->GetFatherNode()== nullptr)
            break;
        father=father->GetFatherNode();
        BF = father->GetBF();
    }

    delete node_to_remove;
    return AVL_SUCCESS;
}

//if it's a leaf, remove it and then check the BF of every node before and fix it.
template <class T>
AVLResults Avl_tree<T>::Remove_Node_Leaf(Node<T>* node) {
    if (node == nullptr)
        return AVL_NULL_ARGUMENT;

    //Remove the node
    Node<T>* father = node->GetFatherNode();

    if(father== nullptr) //the node is the root and has no son
    {
        this->root = nullptr;
        delete node;
        return AVL_SUCCESS;
    }

    //the node is a left leaf
    if (father->GetNodeLeft()==node) {
        father->SetNodeLeft(nullptr);
        if(father->GetNodeRight()== nullptr) {
            father->SetHeight(0);
            Node<T>* temp= father;
            while(temp->GetFatherNode()!= nullptr)
            {
                //if the node didnt change the height, we stop checking further
                if (temp->GetFatherNode()->SetNewHeight()==0)
                    break;
                temp= temp->GetFatherNode();
            }
        }
    }

    //the node is a right leaf
    if (father->GetNodeRight()==node) {
        father->SetNodeRight(nullptr);

        if (father->GetNodeLeft() == nullptr) { //change the height
            father->SetHeight(0);
            Node<T> *temp = father;
            while (temp->GetFatherNode() != nullptr) {
                //if the node didnt change the height, we stop checking further
                if (temp->GetFatherNode()->SetNewHeight() == 0)
                    break;
                temp = temp->GetFatherNode();
            }
        }
    }

    delete node;

    //then check the BF of every node from father to the root.
    int BF = father->GetBF();

    while (true)
    {
        if (BF==2){
            if(father->GetNodeLeft() != nullptr) {
                if ((father->GetNodeLeft()->GetBF() == -1))
                    RotateLR(father);
                else if ((father->GetNodeLeft())->GetBF() >= 0)
                    RotateLL(father);
            }
        }

        if (BF==-2){
            if(father->GetNodeRight() != nullptr) {
                if ((father->GetNodeRight())->GetBF() == 1)
                    RotateRL(father);
                else if ((father->GetNodeRight())->GetBF() <= 0)
                    RotateRR(father);
            }
        }

        if (father->GetFatherNode()== nullptr)
            break;
        father=father->GetFatherNode();
        BF = father->GetBF();
    }

    return AVL_SUCCESS;
}

//if there's one son, remove it and replace it in the "father" node with his son
// and then check the BF of every node before and fix it.
//if there's one son, remove it and replace it in the "father" node with his son
// and then check the BF of every node before and fix it.
template <class T>
AVLResults Avl_tree<T>::Remove_Node_With_Only_Child(Node<T>* node) {
    if (node== nullptr)
        return AVL_NULL_ARGUMENT;

    Node<T>* father = node->GetFatherNode();
    if(father == nullptr) //node is root and has only one son
    {
        if (node->GetNodeRight() == nullptr)
        {
            this->root = node->GetNodeLeft();
            node->GetNodeLeft()->SetFatherNode(nullptr);
            delete node;
            return AVL_SUCCESS;
        }

        if (node->GetNodeLeft() == nullptr)
        {
            this->root = node->GetNodeRight();
            node->GetNodeRight()->SetFatherNode(nullptr);
            delete node;
            return AVL_SUCCESS;
        }
    }

    //first remove the node and replace it with his son.
    if(father->GetNodeLeft()==node) {
        if (node->GetNodeRight() == nullptr) {
            father->SetNodeLeft(node->GetNodeLeft());
            node->GetNodeLeft()->SetFatherNode(father);
        }
        else {
            father->SetNodeLeft(node->GetNodeRight());
            node->GetNodeRight()->SetFatherNode(father);
        }
    }

    else {
        if (node->GetNodeRight() == nullptr) {
            father->SetNodeRight(node->GetNodeLeft());
            node->GetNodeLeft()->SetFatherNode(father);
        }
        else {
            father->SetNodeRight(node->GetNodeRight());
            node->GetNodeRight()->SetFatherNode(father);
        }
    }

    //fix the heights of the fathers
    Node<T>* temp =father;
    while(temp!= nullptr)
    {
        if(temp->SetNewHeight()==0)
            break;
        temp= temp->GetFatherNode();
    }

    delete node;

    //then check the BF and fix it from father up to the root
    if(father == nullptr)
    {
        return AVL_SUCCESS;
    }
    int BF = father->GetBF();

    while (true)
    {
        if (BF==2){
            if(father->GetNodeLeft() != nullptr) {

                if ((father->GetNodeLeft())->GetBF() == -1)
                    RotateLR(father);
                else if ((father->GetNodeLeft())->GetBF() >= 0)
                    RotateLL(father);
            }
        }

        if (BF==-2){
            if(father->GetNodeRight() != nullptr) {

                if ((father->GetNodeRight())->GetBF() == 1)
                    RotateRL(father);
                else if ((father->GetNodeRight())->GetBF() <= 0)
                    RotateRR(father);
            }
        }

        if (father->GetFatherNode()== nullptr)
            break;
        father=father->GetFatherNode();
        BF = father->GetBF();
    }

    return AVL_SUCCESS;
}

template <class T>
void Avl_tree<T>::Swap(Node<T>* node_1, Node<T>* node_2) {

    bool node2_is_left_son= (node_1->GetNodeLeft()==node_2);
    bool node2_is_right_son= (node_1->GetNodeRight()==node_2);
    bool node1_is_left_son= (node_2->GetNodeLeft()==node_1);
    bool node1_is_right_son= (node_2->GetNodeRight()==node_1);

    //keep the pointers in the Node
    Node<T>* father_1= node_1->GetFatherNode();
    Node<T>* son_right_1= node_1->GetNodeRight();
    Node<T>* son_left_1= node_1->GetNodeLeft();

    Node<T>* father_2=node_2->GetFatherNode();
    Node<T>* son_right_2= node_2->GetNodeRight();
    Node<T>* son_left_2= node_2->GetNodeLeft();

    //swap the pointers
    if(node2_is_left_son) {
        node_1->SetFatherNode(node_2);
        node_2->SetNodeLeft(node_1);
        node_1->SetNodeLeft(son_left_2);
        node_1->SetNodeRight(son_right_2);
        node_2->SetFatherNode(father_1);
        node_2->SetNodeRight(son_right_1);

        if(node_1->GetNodeLeft() != nullptr)
        {
            node_1->GetNodeLeft()->SetFatherNode(node_1);
        }
        if(node_1->GetNodeRight() != nullptr)
        {
            node_1->GetNodeRight()->SetFatherNode(node_1);
        }
        if(node_2->GetNodeRight() != nullptr)
        {
            node_2->GetNodeRight()->SetFatherNode(node_2);
        }

        if(node_2->GetFatherNode() != nullptr)
        {
            if(node_2->GetFatherNode()->GetNodeLeft() == node_1)
            {
                node_2->GetFatherNode()->SetNodeLeft(node_2);
            }
            else if(node_2->GetFatherNode()->GetNodeRight() == node_1)
            {
                node_2->GetFatherNode()->SetNodeRight(node_2);
            }
        }
        if(node_2->GetFatherNode() == nullptr)
        {
            this->root = node_2;
        }
    }

    else if(node2_is_right_son)
    {
        node_1->SetFatherNode(node_2);
        node_2->SetNodeRight(node_1);
        node_1->SetNodeLeft(son_left_2);
        node_1->SetNodeRight(son_right_2);
        node_2->SetFatherNode(father_1);
        node_2->SetNodeLeft(son_left_1);

        if(node_1->GetNodeLeft() != nullptr)
        {
            node_1->GetNodeLeft()->SetFatherNode(node_1);
        }
        if(node_1->GetNodeRight() != nullptr)
        {
            node_1->GetNodeRight()->SetFatherNode(node_1);
        }
        if(node_2->GetNodeLeft() != nullptr)
        {
            node_2->GetNodeLeft()->SetFatherNode(node_2);
        }

        if(node_2->GetFatherNode() != nullptr)
        {
            if(node_2->GetFatherNode()->GetNodeLeft() == node_1)
            {
                node_2->GetFatherNode()->SetNodeLeft(node_2);
            }
            else if(node_2->GetFatherNode()->GetNodeRight() == node_1)
            {
                node_2->GetFatherNode()->SetNodeRight(node_2);
            }
        }
        if(node_2->GetFatherNode() == nullptr)
        {
            this->root = node_2;
        }
    }

    else if(node1_is_left_son)
    {
        node_2->SetFatherNode(node_1);
        node_1->SetNodeLeft(node_2);
        node_2->SetNodeLeft(son_left_1);
        node_2->SetNodeRight(son_right_1);
        node_1->SetFatherNode(father_2);
        node_1->SetNodeRight(son_right_2);

        if(node_2->GetNodeLeft() != nullptr)
        {
            node_2->GetNodeLeft()->SetFatherNode(node_2);
        }
        if(node_2->GetNodeRight() != nullptr)
        {
            node_2->GetNodeRight()->SetFatherNode(node_2);
        }
        if(node_1->GetNodeRight() != nullptr)
        {
            node_1->GetNodeRight()->SetFatherNode(node_1);
        }

        if(node_1->GetFatherNode() != nullptr)
        {
            if(node_1->GetFatherNode()->GetNodeLeft() == node_2)
            {
                node_1->GetFatherNode()->SetNodeLeft(node_1);
            }
            else if(node_1->GetFatherNode()->GetNodeRight() == node_2)
            {
                node_1->GetFatherNode()->SetNodeRight(node_1);
            }
        }
        if(node_1->GetFatherNode() == nullptr)
        {
            this->root = node_1;
        }
    }

    else if(node1_is_right_son)
    {
        node_2->SetFatherNode(node_1);
        node_1->SetNodeRight(node_2);
        node_2->SetNodeLeft(son_left_1);
        node_2->SetNodeRight(son_right_1);
        node_1->SetFatherNode(father_2);
        node_1->SetNodeLeft(son_left_2);

        if(node_2->GetNodeLeft() != nullptr)
        {
            node_2->GetNodeLeft()->SetFatherNode(node_2);
        }
        if(node_2->GetNodeRight() != nullptr)
        {
            node_2->GetNodeRight()->SetFatherNode(node_2);
        }
        if(node_1->GetNodeLeft() != nullptr)
        {
            node_1->GetNodeLeft()->SetFatherNode(node_1);
        }

        if(node_1->GetFatherNode() != nullptr)
        {
            if(node_1->GetFatherNode()->GetNodeLeft() == node_2)
            {
                node_1->GetFatherNode()->SetNodeLeft(node_1);
            }
            else if(node_1->GetFatherNode()->GetNodeRight() == node_2)
            {
                node_1->GetFatherNode()->SetNodeRight(node_1);
            }
        }
        if(node_1->GetFatherNode() == nullptr)
        {
            this->root = node_1;
        }
    }

    else {
        node_1->SetFatherNode(father_2);
        node_1->SetNodeLeft(son_left_2);
        node_1->SetNodeRight(son_right_2);


        node_2->SetFatherNode(father_1);
        node_2->SetNodeLeft(son_left_1);
        node_2->SetNodeRight(son_right_1);

        //*******update the pointers of the sons to them******
        //the left son of node2
        if(son_left_2!= nullptr && son_left_2!=node_1){ //there's a left son to node2 and it's not node1
            node_1->GetNodeLeft()->SetFatherNode(node_1);
        }
        else if (node_1->GetNodeLeft()==node_1) //node1 is the left son of node2, we swap
        {
            node_1->SetNodeLeft(node_2);
            node_2->SetFatherNode(node_1);
        }

        //the right son of node2
        if(son_right_2!= nullptr && son_right_2!=node_1) { //there's a right son to node2 and it's not node1
            node_1->GetNodeRight()->SetFatherNode(node_1);
        }
        else if (node_1->GetNodeRight()==node_1) //node1 is the right son of node2, we swap
        {
            node_1->SetNodeRight(node_2);
            node_2->SetFatherNode(node_1);
        }

        //the left son of node1
        if(son_left_1!= nullptr && son_left_1!=node_2) { //there's a left son to node1 and it's not node2
            node_2->GetNodeLeft()->SetFatherNode(node_2);
        }
        else if(node_2->GetNodeLeft()==node_2){  //node2 is the left son of node1, we swap
            node_2->SetNodeLeft(node_1);
            node_1->SetFatherNode(node_2);
        }

        //the right son of node1
        if(son_right_1!= nullptr && son_right_1!=node_2) { //there's a right son to node1 and it's not node2
            node_2->GetNodeRight()->SetFatherNode(node_2);
        }
        else if(node_2->GetNodeRight()==node_2){   //node2 is the right son of node1
            node_2->SetNodeLeft(node_1);
            node_1->SetFatherNode(node_2);
        }


        //*******Update the pointers of the fathers to them********
        int father_swapped=0;
        if(node_1->GetFatherNode()==node_2->GetFatherNode()){
            if (node_1->GetFatherNode()->GetNodeLeft() == node_1) {
                node_1->GetFatherNode()->SetNodeLeft(node_2);
                node_1->GetFatherNode()->SetNodeRight(node_1);
            }
            else {
                node_1->GetFatherNode()->SetNodeRight(node_2);
                node_1->GetFatherNode()->SetNodeLeft(node_1);
            }
            father_swapped=1;
        }

        bool node1_was_root=false;
        if(this->root == node_1)                        //node1 had no father
        {
            this->root = node_2; //updating node2 as the root
            node1_was_root = true;
        }

        else if (father_swapped==0)  {                   //node1 had a father
            if(node_2->GetFatherNode()->GetNodeLeft()==node_1){       //node1 was a left son
                node_2->GetFatherNode()->SetNodeLeft(node_2);        // so now node2 becomes the left son
            }
            if(node_2->GetFatherNode()->GetNodeRight()==node_1){      //node1 was a right son
                node_2->GetFatherNode()->SetNodeRight(node_2);       // so now node2 becomes the right son
            }
        }

        if(node1_was_root==false && this->root == node_2)                        //node2 had no father
        {
            this->root = node_1;
        }

        else if (father_swapped==0){                    //node2 had a father
            if(node_1->GetFatherNode()->GetNodeLeft()==node_2){       //node2 was a left son
                node_1->GetFatherNode()->SetNodeLeft(node_1);        //now node1 becomes the left son
            }
            if(node_1->GetFatherNode()->GetNodeRight()==node_2){      //node2 was a right son
                node_1->GetFatherNode()->SetNodeRight(node_1);       //so now node1 becomes the right son
            }
        }

        //Here the nodes are swapped and all the pointers point around point to the right Node
    }

    node_1->SetNewHeight();
    node_2->SetNewHeight();
    node_1->SetNewHeight(); //in case the first time node2 was his son and wasnt updated
}

template <class T>
AVLResults Avl_tree<T>::RotateLL(Node<T>* node){

    if (node== nullptr)
        return AVL_NULL_ARGUMENT;

    Node<T>* father= node->GetFatherNode();
    Node<T>* left= node->GetNodeLeft();
    Node<T>* left_right=left->GetNodeRight();

    //Rotate
    if(this->root == node)
    {
        this->root = left;
        left->SetFatherNode(nullptr);
    }

    else {
        left->SetFatherNode(father);
        if(father->GetNodeLeft()==node)
            father->SetNodeLeft(left);
        else
            father->SetNodeRight(left);
    }

    node->SetNodeLeft(left_right);
    if(left_right != nullptr)
    {
        left_right->SetFatherNode(node);
    }
    left->SetNodeRight(node);
    node->SetFatherNode(left);

    node->SetNewHeight();
    left->SetNewHeight();

    return AVL_SUCCESS;
}


template <class T>
AVLResults Avl_tree<T>::RotateRR(Node<T>* node){

    if (node== nullptr)
        return AVL_NULL_ARGUMENT;


    Node<T>* father= node->GetFatherNode();
    Node<T>* right= node->GetNodeRight();
    Node<T>* right_left= right->GetNodeLeft();

    //Rotate
    if(this->root == node)
    {
        this->root = right;
        right->SetFatherNode(nullptr);
    }

    else {
        right->SetFatherNode(father);
        if(father->GetNodeLeft()==node)
            father->SetNodeLeft(right);
        else
            father->SetNodeRight(right);
    }

    node->SetNodeRight(right_left);
    if(right_left != nullptr)
    {
        right_left->SetFatherNode(node);

    }
    right->SetNodeLeft(node);
    node->SetFatherNode(right);

    node->SetNewHeight();
    right->SetNewHeight();

    return AVL_SUCCESS;
}

template <class T>
AVLResults Avl_tree<T>::RotateLR(Node<T>* node)
{
    AVLResults res1 = RotateRR(node->GetNodeLeft());
    AVLResults res2 = RotateLL(node);
    if (res1 == AVL_SUCCESS && res2 == AVL_SUCCESS )
    {
        return AVL_SUCCESS;
    }
    else
    {
        return AVL_NULL_ARGUMENT;
    }
}

template <class T>
AVLResults Avl_tree<T>::RotateRL(Node<T>* node)
{
    AVLResults res1 = RotateLL(node->GetNodeRight());
    AVLResults res2 = RotateRR(node);
    if (res1 == AVL_SUCCESS && res2 == AVL_SUCCESS)
    {
        return AVL_SUCCESS;
    }

    return AVL_NULL_ARGUMENT;
}

template <class T>
Node<T>* Avl_tree<T>::Get_smallest_node()
{
    if (this == nullptr)
        return nullptr;

    Node<T>* root= this->GetRoot();
    Node<T>* smallest= root->GetNodeLeft();

    if (smallest== nullptr)
        return root;

    for (; smallest!= nullptr;)
    {
        if(smallest->GetNodeLeft()== nullptr)
            break;

        smallest=smallest->GetNodeLeft();
    }

    return smallest;
}


#endif //EMPLOYEE1_AVL_TREE_H
