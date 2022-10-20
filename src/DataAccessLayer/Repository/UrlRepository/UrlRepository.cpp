#include "UrlRepository.hpp"


UrlRepository::Coro<ComposedUrlsEntity>
UrlRepository::GetBy(const AliasUrlEntity& alias_url)
{ 
    try
    {
        if(alias_url.IsNull())
            throw std::runtime_error("KeyObject is null");

        auto alias_key = std::move(alias_url.GetAlias());
        auto query_result = co_await redis_client->execCommandCoro("get %s",alias_key.c_str());
        
        if(query_result.isNil())
            throw std::runtime_error("Empty result with command: "+ alias_key );

        auto result_url = std::move(query_result.asString());
        co_return ComposedUrlsEntity{{std::move(alias_key)},{std::move(result_url)}};
    }
    catch(const std::exception& e)
    {
        LOG_ERROR << e.what() <<'\n';
        co_return ComposedUrlsEntity{{},{}};    
    } 
}

UrlRepository::Coro<void>
UrlRepository::Create(const ComposedUrlsEntity& composed_urls)
{
    try
    {
        auto alias = std::move(composed_urls.alias_url);
        auto original = std::move(composed_urls.original_url);

        if(alias.IsNull() || original.IsNull())
            throw std::runtime_error("ComposedObject is null");
        
        auto alias_key = std::move(alias.GetAlias());
        auto original_value = std::move(original.GetUrl());
     
        auto query_result = co_await redis_client->execCommandCoro("set %s %s",alias_key.c_str(),original_value.c_str());
        if(query_result.type() == drogon::nosql::RedisResultType::kError)
            throw std::runtime_error("Insertion failed");

        LOG_DEBUG <<"Insertion completed\n";
        co_return;
    }
    catch(const std::exception& e)
    {
        LOG_ERROR<< e.what() <<'\n';
        co_return;
    }
}