#include "skiplist.h"
#ifndef __skiplist_find__
#define __skiplist_find__

template <typename T, int maxheight>
char skipList<T, maxheight>::compare(const skipNode<T>* a, const skipNode<T>* b){
    if(a->inf && b->inf)
        return 1;
    else if(a->inf)
        return 2;
    else if(b->inf)
        return 0;
    else{
        if(*(a->data_ptr) < *(b->data_ptr))
            return 0;
        else if(*(a->data_ptr) == *(b->data_ptr))
            return 1;
        else
            return 2;
    }
}

template <typename T, int maxheight>
bool skipList<T, maxheight>::find(const T& a){
    skipNode<T> item;
    item.inf = false;
    item.data_ptr = const_cast<T*> (&a);

    skipNode<T>* current = L;
    bottom->data_ptr = const_cast<T*> (&a);
    char flag = compare(&item,  current);

    while(flag != 1){
        if(flag == 0)
            current = current->down;
        else
            current = current->right;
        flag = compare(&item, current);
    }

    if(current == bottom)
        return false;
    else
        return true;
}

#endif
