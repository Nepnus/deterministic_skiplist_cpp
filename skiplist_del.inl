#include "skiplist.h"
#ifndef __skiplist_del__
#define __skiplist_del__

template <typename T, int maxheight, bool iftypeok>
short skipList<T, maxheight, iftypeok>::del(const T& a){
    if(!pool_.nodes_prepare(height))
        return 2;
    
    short returnCode = 1;

    skipNode<T> item;
    item.inf        =   false;
    item.data_ptr   =   const_cast<T*> (&a);

    skipNode<T>* current    =   L;
    skipNode<T> *tmp1, *tmp2;
    downlist[0]             =   L;
    char flag;
    int i                   =   0;
    short count;

    tmp1 = L;
    while(1){
        flag = compare(&item, current);
        if(flag == 2){
            tmp1        =   current;
            current     =   current->right;
            downlist[i] =   current;
        }
        else{
            if(current->down == bottom){
                break;
            }
            else{
                if(current->right != tail && 
                    compare(current, current->down->right) == 1){
                    current->data_ptr       =   current->right->down->data_ptr;
                    current->inf            =   current->right->down->inf;
                    current->right->down    =   current->right->down->right;
                    if(compare(current->right, current->right->down) == 1){
                        current->data_ptr   =   current->right->data_ptr;
                        current->inf        =   current->right->inf;

                        tmp2                =   downlist[i-1]->right;
                        if(tmp2->down == current->right)
                            tmp2->down = nullptr;

                        tmp2                =   current->right->right;
                        pool_.node_free(current->right);
                        #ifdef __SKIP_LIST_TEST__
                        delete_times++;
                        #endif
                        current->right      =   tmp2;
                    }
                }

                tmp1            =   tmp1->down;
                if(tmp1 != current->down)
                    while(tmp1->right != current->down)
                        tmp1 = tmp1->right;
                current         =   current->down;
                downlist[++i]   =   current;
            }
        }
    }

    if(flag == 1){
        node_num--;

        if(downlist[i-1]->down == current)
            downlist[i-1]->down = current->right;
        
        tmp1->right = current->right;
        pool_.node_free(current);
        #ifdef __SKIP_LIST_TEST__
        delete_times++;
        #endif
        returnCode = 0;
    }
    
    for(--i; i>=1; --i){
        current = downlist[i];

        if(current->right->down == nullptr){
            count   =   0;
            tmp1    =   current->right->right;
            tmp2    =   current->down;
            while(tmp2->right != tmp1->down){
                tmp2 = tmp2->right;
                count++;
            }

            switch (count)
            {
                case 1:
                case 2:
                    if(downlist[i-1]->right->down == current->right)
                        downlist[i-1]->right->down = nullptr;
                    pool_.node_free(current->right);
                    #ifdef __SKIP_LIST_TEST__
                    delete_times++;
                    #endif
                    current->right = tmp1;
                    break;
                case 3:
                case 4:
                case 5:
                    current->right->down    =   current->down->right->right;
                    current->inf            =   current->down->right->inf;
                    current->data_ptr       =   current->down->right->data_ptr;
                    break;
                case 6:
                    current->right->down    =   current->down->right->right->right;
                    current->inf            =   current->down->right->right->inf;
                    current->data_ptr       =   current->down->right->right->data_ptr;
                    break;
            }
        }
        else if(current->inf && current->down->inf){
            tmp1        =   downlist[i-1]->down;
            while(tmp1->right != current)
                tmp1 = tmp1->right;
            tmp1->inf   =   true;
            tmp1->right =   tail;
            pool_.node_free(current);
            #ifdef __SKIP_LIST_TEST__
            delete_times++;
            #endif
            current     =   tmp1;

            if(!current->down->right->right->right->inf){
                tmp1                =   (skipNode<T>*)pool_.node_alloc();
                #ifdef __SKIP_LIST_TEST__
                new_times++;
                #endif
                tmp1->inf           =   true;
                tmp1->right         =   tail;
                tmp1->down          =   current->down->right->right;
                
                current->inf        =   false;
                current->data_ptr   =   current->down->right->data_ptr;
                current->right      =   tmp1;
            }
        }
        else if(!current->inf){
            tmp1 = current->down;

            while(tmp1->right != current->right->down)
                tmp1 = tmp1->right;
                
            current->data_ptr = tmp1->data_ptr;
        }
    }

    if(L->down->inf){
        tmp1 = L->down;
        pool_.node_free(L);
        #ifdef __SKIP_LIST_TEST__
        delete_times++;
        #endif
        L = tmp1;
        height--;
    }

    return returnCode;
}


#endif
