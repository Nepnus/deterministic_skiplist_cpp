#include "skiplist.h"
#ifdef __SKIP_LIST_TEST__
#ifndef __skiplist_print__
#define __skiplist_print__
#include <iostream>

template <typename T, int maxheight, bool iftypeok>
void skipList<T, maxheight, iftypeok>::printlist(){
    skipNode<T>* title_list[maxheight+1];
    skipNode<T>* current = L;
    int i = 0;
    while(current != bottom){
        title_list[i++] = current;
        current = current->down;
    }

    for(i=0; i<height; i++){
        current = title_list[i];
        while(current != tail){
            if(current->inf)
                std::cout << "inf(";
            else
                std::cout << *(current->data_ptr) << "(";
            if(current->down == bottom)
                std::cout << "b)";
            else if(current->down->data_ptr != nullptr)
                std::cout << *(current->down->data_ptr) << ")";
            std::cout << " -> ";
            current = current->right;
        }
        std::cout << "tail" << std::endl;
    }
}

template <typename T, int maxheight, bool iftypeok>
bool skipList<T, maxheight, iftypeok>::check(){
    skipNode<T>* title_list[maxheight+1];
    skipNode<T>* current = L;
    skipNode<T>* tmp;
    int i = 0;
    while(current != bottom){
        title_list[i++] = current;
        current = current->down;
    }

    char flag;
    for(i=0; i<height-2; i++){
        current = title_list[i];
        while(!current->inf){
            tmp = current->down;
            flag = compare(tmp->right, current->right->down);
            while(flag == 0){
                tmp = tmp->right;
                flag = compare(tmp->right, current->right->down);
            }
            if(tmp == current->down)
                return false;
            flag = compare(tmp, current);
            if(flag != 1)
                return false;
            current = current->right;
        }
        if(current->down->inf)
            return false;
        if(!current->down->right->right->right->inf)
            return false;
    }

    current = title_list[i];
    while(!current->inf){
        flag = compare(current, current->right);
        if(flag == 2)
            return false;
        current = current->right;
    }

    return true;
}

#endif
#endif
