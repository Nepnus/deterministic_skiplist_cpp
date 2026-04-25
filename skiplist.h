
// #define __SKIP_LIST_TEST__
#ifndef __SKIP_LIST__
#define __SKIP_LIST__
#include "mempool.h"

template <typename T>
struct SkipNode{
    struct SkipNode* right;
    struct SkipNode* down;
    T* data_ptr;
    bool inf;
};

template <typename T>
using skipNode = struct SkipNode<T>;

template <typename T, int maxheight = 60>
class skipList{
    private:
        memPool pool_;
        const int max_height;
        int node_num;
        int height;
        #ifdef __SKIP_LIST_TEST__
        unsigned long long int new_times;
        unsigned long long int delete_times;
        #endif
        skipNode<T>* tail;
        skipNode<T>* bottom;
        skipNode<T>* L;
        skipNode<T>* downlist[maxheight+1];
        char compare(const skipNode<T>*, const skipNode<T>*);
        skipList(const skipList&);
    public:
        skipList();
        ~skipList();
        bool find(const T&);
        short insert(const T&);
        short del(const T&);
        void free_memory(){
            pool_.free_emptypage();
        }
        #ifdef __SKIP_LIST_TEST__
        void printlist();
        bool check();
        #endif
};

#include "skiplist_init.inl"
#include "skiplist_find.inl"
#include "skiplist_insert.inl"
#include "skiplist_del.inl"
#ifdef __SKIP_LIST_TEST__
#include "skiplist_print.inl"
#endif


#endif



