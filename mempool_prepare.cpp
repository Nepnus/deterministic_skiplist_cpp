#include "mempool.h"

bool memPool::nodes_prepare(std::uint32_t node_num){
    std::uint32_t free_node_num = node_maxnum - node_allocatednum;
    if(free_node_num >= node_num)
        return true;
    
    std::uint32_t node_needtoalloc = node_num - free_node_num;
    std::uint32_t page_needtoalloc = (std::uint32_t)((std::uint64_t)node_needtoalloc*page_node_num_magicnum >> 32) + 1;

    Page* p;
    for(int i=0; i<page_needtoalloc; i++){
        p = newPage();
        if(p == NULL)
            return false;
        p->prev = empty_pagelist;
        p->next = empty_pagelist->next;
        if(empty_pagelist->next != NULL)
            empty_pagelist->next->prev = p;
        empty_pagelist->next = p;
        node_maxnum += page_node_num;
    }

    return true;
}

void memPool::free_emptypage(){
    Page *current, *next;

    current = empty_pagelist->next;
    while(current != NULL){
        next = current->next;
        current->L = 0;
        free(current);
        current = next;
        node_maxnum -= page_node_num;
    }
}


