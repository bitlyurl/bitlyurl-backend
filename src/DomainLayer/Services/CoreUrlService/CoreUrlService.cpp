#include "CoreUrlService.hpp"


CoreUrlService::Coro<ComposedUrlsBO> 
CoreUrlService::ProduceAliasAndGetBack(const OriginalUrlBO& original_url)
{
    try
    {
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}


CoreUrlService::Coro<OriginalUrlBO> 
CoreUrlService::GetOriginalBy(const AliasUrlBO& alias_url)
{
    try
    {
        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}


