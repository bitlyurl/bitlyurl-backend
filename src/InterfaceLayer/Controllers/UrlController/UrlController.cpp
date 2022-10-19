#include "UrlController.hpp"
UrlHttpController::Coro<UrlHttpController::ResponseType> 
UrlHttpController::CreateAliasUrl(const drogon::HttpRequestPtr request)
{   
    try
    {   using namespace utils;
        OriginalUrlDTO OrigUrl = RequestParser::ParseInto<OriginalUrlDTO>(request);
        
        


    }
    catch(const std::exception& e)
    {
       LOG_ERROR << e.what() <<'\n';

       Json::Value InternalError;
       InternalError["code"] = 500;
       InternalError["reason"]= "Internal Server Error";
       InternalError["original_url"] = "null";
       InternalError["alias_url"] = "null";

       co_return drogon::HttpResponse::newHttpJsonResponse(InternalError);;
    }
}


UrlHttpController::Coro<UrlHttpController::ResponseType> 
UrlHttpController::GetOriginalUrlBy(const drogon::HttpRequestPtr request,std::string&& alias)
{   
    try
    {
        AliasUrlDTO short_url;
        short_url.SetUrl(alias);

    }
    catch(const std::exception& e)
    {
       LOG_ERROR << e.what() <<'\n';
    
       co_return drogon::HttpResponse::newNotFoundResponse();;
    }
}