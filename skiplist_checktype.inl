#include "skiplist.h"
#ifndef __skiplist_checktype__
#define __skiplist_checktype__

template <typename T, typename U = std::void_t<> >
struct IFcanEqual : std::false_type {};

template <typename T>
struct IFcanEqual<T, std::void_t<decltype(std::declval<T>() == std::declval<T>())> > : std::true_type {};

template <typename T, typename U = std::void_t<> >
struct IFcanLess : std::false_type {};

template <typename T>
struct IFcanLess<T, std::void_t<decltype(std::declval<T>() < std::declval<T>())> > : std::true_type {};

template <typename T>
struct IFcanLessEqual {
    static constexpr bool value = (IFcanEqual<T>::value) && (IFcanLess<T>::value);
};

template <typename T>
using typecheck = struct IFcanLessEqual<T>;

#endif
