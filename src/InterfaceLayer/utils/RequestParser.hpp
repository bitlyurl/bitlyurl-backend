#pragma once
#include "../DTOs/Url.hpp"
#include <drogon/HttpAppFramework.h>



namespace utils
{
    class RequestParser
    {
     public:
        template <typename ParseIntoType>
        static inline ParseIntoType ParseInto(const drogon::HttpRequestPtr request)
        {
            if constexpr (std::is_same_v<ParseIntoType,AliasUrlDTO>)
            {
                return ParseIntoAliasUrl(request);
            }
            else if constexpr (std::is_same_v<ParseIntoType,OriginalUrlDTO>) 
            {
                return ParseIntoOrigUrl(request);
            }
        }
     private:

        static  AliasUrlDTO ParseIntoAliasUrl(const drogon::HttpRequestPtr);
        static  OriginalUrlDTO ParseIntoOrigUrl(const drogon::HttpRequestPtr);
    };

    inline AliasUrlDTO RequestParser::ParseIntoAliasUrl(const drogon::HttpRequestPtr request)
    {       
           AliasUrlDTO short_url;
           const auto json = *request->getJsonObject();
           std::string url_payload = json["alias_url"].as<std::string>(); 

           /*validation*/
           if(!url_payload.empty())
            short_url.SetAlias(std::move(url_payload));
           else
             throw std::runtime_error("Invalid payload for AliasUrlDTO object");

           return short_url;
    }   

   inline  OriginalUrlDTO RequestParser::ParseIntoOrigUrl(const drogon::HttpRequestPtr request)
    {
           OriginalUrlDTO orig_url;
           const auto json = *request->getJsonObject();
           std::string url_payload = json["original_url"].as<std::string>(); 
           LOG_DEBUG<< "Got url : "<< url_payload <<'\n';
           /*validation*/
           if(!url_payload.empty())
            orig_url.SetUrl(std::move(url_payload));
           else
            throw std::runtime_error("Invalid payload for OriginalUrlDTO object");
            
           return orig_url;
    }
}