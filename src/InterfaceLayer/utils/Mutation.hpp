#pragma once
#include <type_traits>

#include "../DTOs/Url.hpp"
#include "../../DomainLayer/BuisnessObjects/Url.hpp"
namespace mutation
{
    template<typename CurrentLayerType>
    decltype(auto) PassDTOAsBo(const CurrentLayerType& dto)
    {
        if constexpr(std::is_same_v<CurrentLayerType,AliasUrlDTO>)
        {
            AliasUrlBO bo;
            bo.SetAlias(dto.GetAlias());
            return bo;
        }
        else if constexpr (std::is_same_v<CurrentLayerType,OriginalUrlDTO>)
        {
            OriginalUrlBO bo;
            bo.SetUrl(dto.GetUrl());
            return bo;
        }
        else if constexpr (std::is_same_v<CurrentLayerType,ComposedUrlsDTO>)
        {
           ComposedUrlsBO bo;
           bo.alias_url.SetAlias(dto.alias_url.GetAlias());
           bo.original_url.SetUrl(dto.original_url.GetUrl());
           return bo;
        }
    }


    template<typename CurrentLayerType>
    decltype(auto) PassBOAsDTO(const CurrentLayerType& bo)
    {
        if constexpr(std::is_same_v<CurrentLayerType,AliasUrlBO>)
        {
            AliasUrlDTO dto;
            dto.SetAlias(bo.GetAlias());
            return dto;
        }
        else if constexpr (std::is_same_v<CurrentLayerType,OriginalUrlBO>)
        {
            OriginalUrlDTO dto;
            dto.SetUrl(bo.GetUrl());
            return dto;
        }
        else if constexpr (std::is_same_v<CurrentLayerType,ComposedUrlsBO>)
        {
           ComposedUrlsDTO dto;
           dto.alias_url.SetAlias(bo.alias_url.GetAlias());
           dto.original_url.SetUrl(bo.original_url.GetUrl());
           return dto;
        }
    }
} // namespace mutation
