#include "UrlController.hpp"
UrlHttpController::Coro<UrlHttpController::ResponseType> 
UrlHttpController::CreateAliasUrl(const drogon::HttpRequestPtr request)
{   
    try
    {   using namespace utils;
        using namespace mutation;
        OriginalUrlDTO orig_url = RequestParser::ParseInto<OriginalUrlDTO>(request);
        
        ComposedUrlsDTO composed = PassBOAsDTO(co_await core_service->ProduceAliasAndGetBack(PassDTOAsBo(orig_url)));

        if(composed.alias_url.IsNull() || composed.original_url.IsNull())
            throw std::runtime_error("Null-object from response");
        
        Json::Value json_response;
        json_response["original_url"] = composed.original_url.GetUrl();
        json_response["alias_url"] = composed.alias_url.GetAlias();

        co_return drogon::HttpResponse::newHttpJsonResponse(json_response);
    }
    catch(const std::exception& e)
    {
       LOG_ERROR << e.what() <<'\n';

       Json::Value internal_error;
       internal_error["error"]= "Internal Server Error";
       internal_error["original_url"] = "null";
       internal_error["alias_url"] = "null";

       co_return drogon::HttpResponse::newHttpJsonResponse(internal_error);
    }
}


UrlHttpController::Coro<UrlHttpController::ResponseType> 
UrlHttpController::GetOriginalUrlBy(const drogon::HttpRequestPtr request,std::string&& alias)
{   
    try
    {      
        using namespace mutation;
        if(alias.empty())
            throw std::runtime_error("Invalid request argument");

        AliasUrlDTO short_url;
        short_url.SetAlias(alias);

        OriginalUrlDTO orig_url = PassBOAsDTO(co_await core_service->GetOriginalBy(PassDTOAsBo(short_url)));

        if(orig_url.IsNull())
            throw std::runtime_error("Null-object from response");
        
        LOG_DEBUG <<"Original URL : "<<orig_url.GetUrl() <<'\n';
        co_return drogon::HttpResponse::newRedirectionResponse(orig_url.GetUrl());
    }
    catch(const std::exception& e)
    {
       LOG_ERROR << e.what() <<'\n';
       co_return drogon::HttpResponse::newNotFoundResponse();;
    }
}