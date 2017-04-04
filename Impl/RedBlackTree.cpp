#include "../RedBlackTree.h"
namespace TinySTL
{

template<typename T>
RBTreeIterator<T>&
RBTreeIterator<T>::operator++()
{
    if(nodePtr_->right_ != nullptr)
    {
        nodePtr_ = nodePtr_->right_;
        while (nodePtr_->left_ != nullptr)
            nodePtr_ = nodePtr_->left_;
    }
    else
    {
        NodePtr pa = nodePtr_->parent_;
        while(nodePtr_ = pa->right_)
        {
            nodePtr_ = pa;
            pa = pa->parent_;
        }
        nodePtr_ = pa;
    }
}
template<typename K,typename V,typename KOV,typename CF,typename Alloc>
void RedBlackTree<K,V,KOV,CF,Alloc>::right_rotate(Node* pos,Node* &root)
{
    Node* pa = pos->parent_;
    Node* x = pos->left_;
    x->parent_ = pa; //1
    if(pos == root) //2
        pa->parent_ = x;
    else if(pos = pa->left_)
        pa->left_ = x;
    else
        pa->right_ = x; // end of 2
    pos->parent_ = x;//3
    pos->left_ = x->right_;//4
    if(x->right_ != nullptr)
        x->right_->parent_ = pos;//5
    x->right_ = pos; //6
}
template<typename K,typename V,typename KOV,typename CF,typename Alloc>
void RedBlackTree<K,V,KOV,CF,Alloc>::left_rotate(Node* pos,Node* &root)
{
    Node* pa = pos->parent_;
    Node* x = pos->right_;
    x->parent_ = pa; //1
    if(pos == root) //2
        pa->parent_ = x;
    else if(pos = pa->left_)
        pa->left_ = x;
    else
        pa->right_ = x; // end of 2
    pos->parent_ = x;//3
    pos->right_ = x->left_;//4
    if(x->left_ != nullptr)
        x->left_->parent_ = pos;//5
    x->left_ = pos; //6
}
template<typename K,typename V,typename KOV,typename CF,typename Alloc>
void RedBlackTree<K,V,KOV,CF,Alloc>::rebalance(Node* new_node,Node* &root)
{
    new_node->color_ = _red_color;//新加入的节点必为红色,其父节点也为红色，否则无需旋转

    while(new_node != root && new_node->color_ == _red_color &&
          new_node->parent_->color_ == _red_color)
    {
        if(new_node->parent_ == new_node->parent_->parent_->left_)//父节点为祖父节点左节点
        {
            Node* s = new_node->parent_->parent_->right_; //父节点的兄弟节点
            if(s != nullptr && s->color_ == _red_color)//gp节点有两个红子节点，无需旋转。直接将祖父节点改为红色，p,s改为黑色
            {
                new_node->parent_->color_ = _black_color;
                s->color_ = _black_color;
                new_node->parent_->parent_->color_ = _red_color;
                new_node = new_node->parent_->parent_;
            }
            else//父节点的兄弟节点为黑色
            {
                if(new_node = new_node->parent_->left_)//新节点是其父节点的左儿子
                {
                    new_node->parent_->color_ = _black_color;
                    new_node->parent_->parent_->color_ = _red_color;
                    right_rotate(new_node->parent_->parent_,root);
                }
                else //新节点是其父节点的左儿子
                {
                    left_rotate(new_node->parent_,root);
                    //经过旋转，new_node->parent_为原祖父节点,黑色。
                    new_node->color_ = _black_color;
                    new_node->parent_->color_ = _red_color;
                    right_rotate(new_node->parent_,root);
                }
                 //这个if else的另一种写法，代码更简洁，
                 //可以省掉while里面new_node->color == _red_color的判断
                 //if(new_node = new_node->parent_->right_)
                 //{
                 //    new_node = new_node->parent_;
                 //    left_rotate(new_node,root);
                 //}
                 //new_node->parent_->color_ = _black_color;
                 //new_node->parent_->parent_->color_ = _red_color;
                 //right_rotate(new_node->parent_->parent_,root);

            }
        }
        else //父节点为祖父节点右节点,与前面对称的处理
        {
            Node* s = new_node->parent_->parent_->left_; //父节点的兄弟节点
            if(s != nullptr && s->color_ == _red_color)//gp节点有两个红子节点，无需旋转。直接将祖父节点改为红色，p,s改为黑色
            {
                new_node->parent_->color_ = _black_color;
                s->color_ = _black_color;
                new_node->parent_->parent_->color_ = _red_color;
                new_node = new_node->parent_->parent_;
            }
            else//父节点的兄弟节点为黑色
            {
                if(new_node = new_node->parent_->right_)//新节点是其父节点的右儿子
                {
                    new_node->parent_->color_ = _black_color;
                    new_node->parent_->parent_->color_ = _red_color;
                    left_rotate(new_node->parent_->parent_,root);
                }
                else //新节点是其父节点的左儿子
                {
                    right_rotate(new_node->parent_,root);
                    //经过旋转，new_node->parent_为原祖父节点,黑色。
                    new_node->color_ = _black_color;
                    new_node->parent_->color_ = _red_color;
                    right_rotate(new_node->parent_,root);
                }
            }
        }
    }// end of while(...)
}

template<typename K,typename V,typename KOV,typename CF,typename Alloc>
typename RedBlackTree<K,V,KOV,CF,Alloc>::iterator
RedBlackTree<K,V,KOV,CF,Alloc>::find(const key_type& key)
{
    Node* y = header_;
    Node* cur = header_->parent_; //root
    while(cur != nullptr)
    {
        if(compareFunc_(key,getkey_(cur->data_)))
            cur = cur->left_;
        else if(compareFunc_(getkey_(cur->data_),key))
            cur = cur->right_;
        else
            return iterator(cur);
    }
    return end();
}
}
