#pragma once

#include "UrlController.hpp"


UrlHttpController::Coro<UrlHttpController::ResponseType> UrlHttpController::CreateShortUrl(const drogon::HttpRequestPtr request)
{

}


UrlHttpController::Coro<UrlHttpController::ResponseType> UrlHttpController::GetOriginalUrlBy(const drogon::HttpRequestPtr request,std::string&& ShortUrl)
{
    
}