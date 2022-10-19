#pragma once
#include <concepts>

#include <drogon/HttpAppFramework.h>


/*TODO : Implement CacheRepository for Users */

template <typename KeyType,typename ValueType>
class IRepository
{   
    template<typename T>
    using Coro = drogon::Task<T>;

 public:

    [[nodiscard ]] virtual Coro<ValueType> GetBy(const KeyType&) = 0;

    virtual Coro<void> Create(const ValueType&) = 0;

    /* Method As() allows to expand functionality of base class by derived's clases methods */
    template<std::derived_from<IRepository> DerivedType>
    DerivedType* As() { return dynamic_cast<DerivedType*>(this);}

    virtual ~IRepository() = default;
};