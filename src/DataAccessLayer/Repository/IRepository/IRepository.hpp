#pragma once
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

    virtual ~IRepository() = default;
};


