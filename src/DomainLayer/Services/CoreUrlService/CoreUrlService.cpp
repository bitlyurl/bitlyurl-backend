#include "CoreUrlService.hpp"


CoreUrlService::Coro<ComposedUrlsBO> 
CoreUrlService::ProduceAliasAndGetBack(const OriginalUrlBO& original_url)
{
    try
    {   
        using namespace mutation;
        if(original_url.IsNull())
            throw std::runtime_error("KeyObject is null");
        
        std::string generated_alias = std::move(AliasGenerator::Generate(7)); // len of random alias
        AliasUrlBO alias_url(std::move(generated_alias));

        ComposedUrlsBO composed_urls{std::move(alias_url),std::move(original_url)};
        co_await repository->Create(PassBOAsEntity(std::move(composed_urls)));

        co_return composed_urls;
    }
    catch(const std::exception& e)
    {
        LOG_ERROR << e.what() <<'\n';
        co_return ComposedUrlsBO{{},{}};
    }
}


CoreUrlService::Coro<OriginalUrlBO> 
CoreUrlService::GetOriginalBy(const AliasUrlBO& alias_url)
{
    try
    {   
        using namespace mutation;
        if(alias_url.IsNull())
            throw std::runtime_error("KeyObject is null");
    
        ComposedUrlsBO composed_urls = PassEntityAsBO(co_await repository->GetBy(PassBOAsEntity(std::move(alias_url))));
        LOG_DEBUG <<"Got result : "<<composed_urls.original_url.GetUrl() <<'\n';
        
        co_return composed_urls.original_url;
    }
    catch(const std::exception& e)
    {
        LOG_ERROR << e.what() << '\n';
        co_return OriginalUrlBO{};
    }
}


