#include "mempool.h"

#define upAlign(a, b) (((a) + ((b) - 1)) & ~((b) - 1))

memPool::memPool(std::uint32_t type_bytesize_, std::uint32_t page_node_num_):
type_bytesize(type_bytesize_), page_node_num(page_node_num_), ptr_bytesize(sizeof(void*)),
page_node_num_magicnum(((std::uint64_t)1 << 32) / (std::uint64_t)page_node_num),
page_node_bytesize(upAlign(type_bytesize, (std::uint32_t)ptr_bytesize) + 2*ptr_bytesize),
page_node_offset1(page_node_bytesize - 2*ptr_bytesize),
page_node_offset2(page_node_bytesize - ptr_bytesize),
page_total_bytesize(sizeof(Page) + page_node_bytesize*page_node_num)
{
    empty_pagelist                      =   (Page*)malloc(sizeof(Page));
    empty_pagelist->L                   =   0;
    empty_pagelist->node_allocatednum   =   0;
    empty_pagelist->prev                =   NULL;
    empty_pagelist->next                =   NULL;
    full_pagelist                       =   (Page*)malloc(sizeof(Page));
    full_pagelist->L                    =   0;
    full_pagelist->node_allocatednum    =   0;
    full_pagelist->prev                 =   NULL;
    full_pagelist->next                 =   NULL;
    else_pagelist                       =   (Page*)malloc(sizeof(Page));
    else_pagelist->L                    =   0;
    else_pagelist->node_allocatednum    =   0;
    else_pagelist->prev                 =   NULL;
    else_pagelist->next                 =   NULL;
    node_maxnum                         =   0;
    node_allocatednum                   =   0;
}

memPool::~memPool(){
    Page *current, *next;

    current = empty_pagelist;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }

    current = full_pagelist;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }

    current = else_pagelist;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
}

Page* memPool::newPage(){
    Page* p = (Page*)malloc(page_total_bytesize);
    if(p == NULL)
        return NULL;
    
    p->prev = NULL; p->next = NULL;

    std::uint32_t i,j,k;
    uint_ptr p1, p2, *p3;
    
    p->L = (uint_ptr)(p->s);
    p->node_allocatednum = 0;

    p1 = (uint_ptr)p;
    for(i=0; i<page_node_bytesize*page_node_num-page_node_bytesize; i=j){
        j = i + page_node_bytesize;
        p2 = (uint_ptr)(&(p->s)[j]);

        k = j - ptr_bytesize;
        p3 = (uint_ptr*)(&(p->s)[k]);
        *p3 = p2;

        k -= ptr_bytesize;
        p3 = (uint_ptr*)(&(p->s)[k]);
        *p3 = p1;
    }
    p3 = (uint_ptr*)(&(p->s)[i+page_node_offset2]);
    *p3 = p1;
    p3 = (uint_ptr*)(&(p->s)[i+page_node_offset1]);
    *p3 = p1;

    return p;
}


