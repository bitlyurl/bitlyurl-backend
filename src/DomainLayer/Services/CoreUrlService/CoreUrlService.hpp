#pragma once

#include "../../BuisnessObjects/Url.hpp"
#include "AliasGenerator/AliasGenerator.hpp"

#include "Repository/UrlRepository/UrlRepository.hpp"
#include "../../utils/Mutation.hpp"

class CoreUrlService final
{
    template <typename T>
    using Coro = drogon::Task<T>;

    public:

        CoreUrlService() : repository{std::make_unique<UrlRepository>(drogon::app().getRedisClient())}
        {}
        
        Coro<ComposedUrlsBO> ProduceAliasAndGetBack(const OriginalUrlBO&);

        Coro<OriginalUrlBO>  GetOriginalBy(const AliasUrlBO&);
    private:
    std::unique_ptr<UrlRepository> repository;
};
