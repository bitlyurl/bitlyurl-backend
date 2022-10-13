#pragma once

#include <drogon/HttpController.h>
#include <drogon/HttpAppFramework.h>

class UrlHttpController final : public drogon::HttpController<UrlHttpController>
{
    using ResponseType = drogon::HttpResponsePtr;

    template <typename T>
    using Coro = drogon::Task<T>;

    public:
    
    METHOD_LIST_BEGIN
    
        ADD_METHOD_TO(UrlHttpController::CreateShortUrl,  "/app",           {drogon::Post});
        ADD_METHOD_TO(UrlHttpController::GetOriginalUrlBy,"/app/{shortUrl}",{drogon::Get });

    METHOD_LIST_END

    
    /*Call of this method will produce the alias to the original URL.
    The result must be in json format like:
    200 OK
    {
        "original_url" : "https://google.com"
        "alias_url"    :  "https://bitlyurl.com/agSh4dh"
    }
    500 Internal server error
    {
        "original_url" : null
        "alias_url"    : null
    }*/
    Coro<ResponseType> CreateShortUrl  (const drogon::HttpRequestPtr);

    /* Call of this method will return original URL by linked alias.
    The result is HttpRedirectionResponse.*/
    Coro<ResponseType> GetOriginalUrlBy(const drogon::HttpRequestPtr,std::string&&);
    
    private:
    /*smapr-pointers to services */
};