#include "skiplist.h"
#ifndef __skiplist_insert__
#define __skiplist_insert__

template <typename T, int maxheight>
short skipList<T, maxheight>::insert(const T& a){
    if(height >= max_height)
        return 1;

    if(!pool_.nodes_prepare(height+1))
        return 2;

    skipNode<T> item;
    item.inf = false;
    item.data_ptr = const_cast<T*> (&a);

    skipNode<T>* current = L;
    skipNode<T>* newNode;
    bottom->data_ptr = const_cast<T*> (&a);

    char flag = 0;
    int node_num_old = node_num;
    while(current != bottom){
        flag = compare(&item, current);
        while(flag == 2){
            current = current->right;
            flag = compare(&item, current);
        }

        flag = compare(current, current->down->right->right);
        if(flag == 2){
            newNode = (skipNode<T>*)pool_.node_alloc();
            #ifdef __SKIP_LIST_TEST__
            new_times++;
            #endif
            newNode->inf = current->inf;
            newNode->data_ptr = current->data_ptr;
            newNode->right = current->right;
            newNode->down = current->down->right->right;

            current->right = newNode;
            current->data_ptr = current->down->right->data_ptr;
            current->inf = current->down->right->inf;

            if(current->down == bottom)
                node_num++;
        }
        else
            current = current->down;
    }

    if(L->right != tail){
        newNode = (skipNode<T>*)pool_.node_alloc();
        #ifdef __SKIP_LIST_TEST__
        new_times++;
        #endif
        newNode->inf = true;
        newNode->right = tail;
        newNode->down = L;
        L = newNode;

        height++;
    }

    if(node_num_old == node_num)
        return 3;
    else
        return 0;
}

#endif
