#ifndef TINYSTL_REDBLACKTREE_H
#define TINYSTL_REDBLACKTREE_H
#include "Allocator.h"
#include "Iterator.h"
#include "Utility.h"
namespace TinySTL
{
typedef bool RBTreeColor;
const RBTreeColor _red_color = false;
const RBTreeColor _black_color = true;
template<typename T>
struct RBTreeNode
{
    RBTreeNode* parent_;
    RBTreeNode* left_;
    RBTreeNode* right_;
    RBTreeColor color_;
    T           data_;
};

template <typename T>
struct RBTreeIterator:public iterator<bidirectional_iterator_tag,T>
{
    //此处继承自TinySTL::iterator，原本不需要这些typedef
    //编译器问题，VS2013中不需要可编译,gcc需要
    typedef typename iterator<bidirectional_iterator_tag,T>::value_type value_type;
    typedef typename iterator<bidirectional_iterator_tag,T>::pointer pointer;
    typedef typename iterator<bidirectional_iterator_tag,T>::difference_type difference_type;
    typedef typename iterator<bidirectional_iterator_tag,T>::reference reference;
    typedef typename iterator<bidirectional_iterator_tag,T>::iterator_category iterator_category;
    typedef RBTreeNode<T>* NodePtr;
    //constructor ,destructor
    RBTreeIterator() = default;
    RBTreeIterator(const RBTreeIterator& iter):nodePtr_(iter.nodePtr_){}
    explicit RBTreeIterator(NodePtr ptr):nodePtr_(ptr){}
    ~RBTreeIterator()= default;
    //data member
    NodePtr nodePtr_;
    //operator
    RBTreeIterator& operator ++();
    RBTreeIterator operator ++(int);
    RBTreeIterator& operator --();
    RBTreeIterator operator--(int);
    reference operator*(){ return nodePtr_->data_;}
    pointer operator->(){ return &(operator *());}
};
template <typename Key,typename Value,typename KeyOfValue,
          typename CompareFunc,typename Alloc = alloc>
class RedBlackTree
{
public:
    typedef RBTreeNode<Value>            Node;
    typedef RBTreeIterator<Value>        iterator;
    typedef Value                        value_type;
    typedef Key                          key_type;
    typedef size_t                       size_type;
    typedef allocator<Node,Alloc>        NodeAllocator;
private:
    Node* header_;
    size_type elementNum_;
    CompareFunc compareFunc_;
    KeyOfValue getkey_;
    NodeAllocator allocator_;


public:
    RedBlackTree():elementNum_(0),allocator_(NodeAllocator())
    {
        initial();
    }
public:
    iterator begin(){ return iterator(header_->left_);}
    iterator end(){ return iterator(header_);}
    iterator find(const key_type& key);
    size_type size()const{ return elementNum_;}
    bool empty()const { return elementNum_ == 0;}

    Pair<iterator,bool> insert_unique(const value_type& val);
    Pair<iterator,bool> insert_equal(const value_type& val);
private:
    Node* get_node(){ return allocator_.allocate();}
    Node* create_node(const value_type& val)
    {
        Node* ptr = allocator_.allocate();
        allocator_.construct(ptr,val);
        return ptr;
    }
    void put_node(Node* ptr){ allocator_.deallocate(ptr);}
    void destroy_node(Node* ptr)
    {
        allocator_.destroy(ptr);
        allocator_.deallocate(ptr);
    }
    void initial()
    {
        header_ = get_node();
        header_->color_ = _red_color;
        header_->left_ = header_;
        header_->right_ = header_;
        header_->parent_ = nullptr;
    }
    Node* & root(){ return header_->parent_;}
    void insert_aux(Node* pos,Node* parent,const value_type& val);
    void rebalance(Node* pos, Node*& root);
    void left_rotate(Node* pos,Node*& root);
    void right_rotate(Node* pos,Node*& root);


};
}
#endif // REDBLACKTREE_H
