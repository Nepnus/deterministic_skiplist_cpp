#include "mempool.h"

void* memPool::node_alloc(){
    Page *p;
    void *q;
    uint_ptr a1;

    if(else_pagelist->next != NULL){
        p = else_pagelist->next;
        q = (void*)(p->L);

        a1 = p->L + page_node_offset2;
        p->L = *((uint_ptr*)a1);

        p->node_allocatednum ++;
        node_allocatednum ++;
        if(p->node_allocatednum == page_node_num){
            else_pagelist->next = p->next;
            if(else_pagelist->next != NULL)
                else_pagelist->next->prev = else_pagelist;
            p->prev = full_pagelist;
            p->next = full_pagelist->next;
            if(full_pagelist->next != NULL)
                full_pagelist->next->prev = p;
            full_pagelist->next = p;
        }
    }
    else if(empty_pagelist->next != NULL){
        p = empty_pagelist->next;
        q = (void*)(p->L);

        a1 = p->L + page_node_offset2;
        p->L = *((uint_ptr*)a1);

        p->node_allocatednum ++;
        node_allocatednum ++;
        empty_pagelist->next = p->next;
        if(empty_pagelist->next != NULL)
            empty_pagelist->next->prev = empty_pagelist;
        p->prev = else_pagelist;
        p->next = else_pagelist->next;
        if(else_pagelist->next != NULL)
            else_pagelist->next->prev = p;
        else_pagelist->next = p;
    }
    else{
        p = newPage();
        if(p == NULL)
            return NULL;
        q = (void*)(p->L);

        a1 = p->L + page_node_offset2;
        p->L = *((uint_ptr*)a1);

        p->node_allocatednum ++;
        node_allocatednum ++;
        node_maxnum += page_node_num;
        p->prev = else_pagelist;
        p->next = else_pagelist->next;
        if(else_pagelist->next != NULL)
            else_pagelist->next->prev = p;
        else_pagelist->next = p;
    }

    return q;
};

void memPool::node_free(const void* ptr){
    Page *p;
    uint_ptr a1, *a2, ptr_value = (uint_ptr)ptr;

    if(ptr == NULL || ptr == nullptr)
        return;

    a1 = ptr_value + page_node_offset1;
    a1 = *((uint_ptr*)a1);
    p = (Page*)a1;

    if(p->node_allocatednum == 0 || p->L == 0)
        return;

    a1 = ptr_value + page_node_offset2;
    a2 = (uint_ptr*) a1;
    *a2 = p->L;
    p->L = ptr_value;

    if(p->node_allocatednum == page_node_num){
        p->prev->next = p->next;
        if(p->next != NULL)
            p->next->prev = p->prev;

        p->prev = else_pagelist;
        p->next = else_pagelist->next;
        if(else_pagelist->next != NULL)
            else_pagelist->next->prev = p;
        else_pagelist->next = p;
    }

    if(p->node_allocatednum == 1){
        p->prev->next = p->next;
        if(p->next != NULL)
            p->next->prev = p->prev;

        p->prev = empty_pagelist;
        p->next = empty_pagelist->next;
        if(empty_pagelist->next != NULL)
            empty_pagelist->next->prev = p;
        empty_pagelist->next = p;
    }

    p->node_allocatednum --;
    node_allocatednum --;
}



