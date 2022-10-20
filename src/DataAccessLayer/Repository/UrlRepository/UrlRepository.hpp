#pragma once

#include "../IRepository/IRepository.hpp"
#include "../../Entities/Url.hpp"

class UrlRepository final : public IRepository<AliasUrlEntity,ComposedUrlsEntity>
{
    template<typename T>
    using Coro = drogon::Task<T>;

 public:
        UrlRepository(drogon::nosql::RedisClientPtr redis_ptr) : redis_client{redis_ptr} {}

        [[nodiscard]] Coro<ComposedUrlsEntity> GetBy(const AliasUrlEntity&) override;

        Coro<void> Create(const ComposedUrlsEntity&) override;
        
 private:
    drogon::nosql::RedisClientPtr redis_client;
};