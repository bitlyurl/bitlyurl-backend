#pragma once
#include <string>


class OriginalUrlDTO final
{
  public:
    OriginalUrlDTO()  = default;
    OriginalUrlDTO(std::string url) : url_ {std::move(url)} {}

    void SetUrl(std::string url) { url_ = std::move(url);}
    [[nodiscard]] std::string GetUrl() const  { return url_;}

    bool IsNull() const {return url_.empty();}
  private:
    std::string url_{};
};

class AliasUrlDTO final
{
  public:
    AliasUrlDTO() = default;
    AliasUrlDTO(std::string alias) : alias_{std::move(alias)} {}

    void SetAlias(std::string alias) { alias_ = std::move(alias);}
    [[nodiscard]] std::string GetAlias() const { return alias_;}

    bool IsNull() const {return alias_.empty();}
  private:
    std::string alias_{};
};

struct ComposedUrlsDTO
{
  AliasUrlDTO alias_url;
  OriginalUrlDTO original_url;
};