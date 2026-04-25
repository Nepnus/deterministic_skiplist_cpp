
#ifndef __MEM_POOL__
#define __MEM_POOL__
#include <stdlib.h>
#include <cstdint>
#include <new>

template <unsigned N>
struct ptr_size {};

template <>
struct ptr_size<4> {
    using type = std::uint32_t;
};

template <>
struct ptr_size<8> {
    using type = std::uint64_t;
};

using uint_ptr = typename ptr_size<sizeof(void*)>::type;

typedef struct Page{
    Page* prev;
    Page* next;
    uint_ptr L;
    std::uint32_t node_allocatednum;
    unsigned char s[];
}Page;

class memPool {
    private:
        Page* empty_pagelist;
        Page* full_pagelist;
        Page* else_pagelist;

        unsigned long long node_maxnum;
        unsigned long long node_allocatednum;

        const std::uint8_t  ptr_bytesize;
        const std::uint32_t page_node_num;
        const std::uint64_t page_node_num_magicnum;
        const std::uint32_t type_bytesize;
        
        const std::uint32_t page_node_bytesize;
        const std::uint32_t page_node_offset1;
        const std::uint32_t page_node_offset2;
        const std::uint32_t page_total_bytesize;

        Page* newPage();
        memPool();
        memPool(const memPool&);
    public:
        memPool(std::uint32_t type_bytesize_, std::uint32_t page_node_num_);
        ~memPool();
        void* node_alloc();
        void node_free(const void*);
        bool nodes_prepare(std::uint32_t node_num);
        void free_emptypage();
        template <typename T1, typename...T2>
        T1* node_new(T2...args){
            void* p = node_alloc();
            if(p == NULL)
                return nullptr;
            T1* p2 = new(p) T1(args...);
            return p2;
        }
};


#endif
