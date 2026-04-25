#include "skiplist.h"
#ifndef __skiplist_init__
#define __skiplist_init__

template <typename T, int maxheight>
skipList<T, maxheight>::skipList():pool_(sizeof(skipNode<T>), 100*maxheight), max_height(maxheight){
    if(!pool_.nodes_prepare(3)){
        throw "lack of heap memory.";
    }

    bottom = (skipNode<T>*)pool_.node_alloc();
    bottom->right = bottom;
    bottom->down = bottom;
    bottom->inf = false;
    bottom->data_ptr = nullptr;

    tail = (skipNode<T>*)pool_.node_alloc();
    tail->right = tail;
    tail->down = tail;
    tail->inf = true;
    tail->data_ptr = nullptr;

    L = (skipNode<T>*)pool_.node_alloc();
    L->inf = true;
    L->down = bottom;
    L->right = tail;
    L->data_ptr = nullptr;

    node_num = 0;
    height = 1;
    #ifdef __SKIP_LIST_TEST__
    new_times = 1;
    delete_times = 0;
    #endif
}

template <typename T, int maxheight>
skipList<T, maxheight>::~skipList(){
    skipNode<T>* title_list[maxheight+1];
    skipNode<T>* current = L;
    skipNode<T>* current_right;
    int i = 0;
    while(current != bottom){
        title_list[i++] = current;
        current = current->down;
    }

    for(i=0; i<height; i++){
        current = title_list[i];
        while(current != tail){
            current_right = current->right;
            pool_.node_free(current);
            current = current_right;
        }
    }

    pool_.node_free(tail);
    pool_.node_free(bottom);
}

#endif
