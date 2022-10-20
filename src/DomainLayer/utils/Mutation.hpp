#pragma once
#include <type_traits>

#include "../../DataAccessLayer/Entities/Url.hpp"
#include "../BuisnessObjects/Url.hpp"

namespace mutation
{
    template<typename CurrentLayerType>
    auto PassBOAsEntity(const CurrentLayerType& bo)
    {
        if constexpr(std::is_same_v<CurrentLayerType,AliasUrlBO>)
        {
            AliasUrlEntity entity;
            entity.SetAlias(bo.GetAlias());
            return entity;
        }
        else if constexpr (std::is_same_v<CurrentLayerType,OriginalUrlBO>)
        {
            OriginalUrlEntity entity;
            entity.SetUrl(bo.GetUrl());
            return entity;
        }
        else if constexpr (std::is_same_v<CurrentLayerType,ComposedUrlsBO>)
        {
           ComposedUrlsEntity entity;
           entity.alias_url.SetAlias(bo.alias_url.GetAlias());
           entity.original_url.SetUrl(bo.original_url.GetUrl());
           return entity;
        }
    }

    template<typename CurrentLayerType>
    auto PassEntityAsBO(const CurrentLayerType& entity)
    {
        if constexpr(std::is_same_v<CurrentLayerType,AliasUrlEntity>)
        {
            AliasUrlBO bo;
            bo.SetAlias(entity.GetAlias());
            return bo;
        }
        else if constexpr (std::is_same_v<CurrentLayerType,OriginalUrlEntity>)
        {
            OriginalUrlBO bo;
            bo.SetUrl(entity.GetUrl());
            return bo;
        }
        else if constexpr (std::is_same_v<CurrentLayerType,ComposedUrlsEntity>)
        {
           ComposedUrlsBO bo;
           bo.alias_url.SetAlias(entity.alias_url.GetAlias());
           bo.original_url.SetUrl(entity.original_url.GetUrl());
           return bo;
        }
    }
} // namespace mutation