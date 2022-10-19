#pragma once
#include <drogon/HttpAppFramework.h>

#include "../../BuisnessObjects/Url.hpp"
#include "AliasGenerator/AliasGenerator.hpp"

#include "Repository/UrlRepository/UrlRepository.hpp"
class CoreUrlService final
{
    template <typename T>
    using Coro = drogon::Task<T>;

    public:
        Coro<ComposedUrlsBO> ProduceAliasAndGetBack(const OriginalUrlBO&);
        
        Coro<OriginalUrlBO>  GetOriginalBy(const AliasUrlBO&);
    private:
    /*smart-pointers tp gateways*/
};
