#pragma once
#include <string>

class OriginalUrlEntity final
{
 public:
    OriginalUrlEntity()  = default;
    OriginalUrlEntity(std::string url) : url_ {std::move(url)} {}

    void SetUrl(std::string url) { url_ = std::move(url);}
    [[nodiscard]] std::string GetUrl() const  { return url_;}

    bool IsNull() const { return url_.empty();}
  private:
    std::string url_{};
};


class AliasUrlEntity final
{
  public:
    AliasUrlEntity() = default;
    AliasUrlEntity(std::string alias) : alias_{std::move(alias)} {}

    void SetAlias(std::string alias) { alias_ = std::move(alias);}
    [[nodiscard]] std::string GetAlias() const { return alias_;}

    bool IsNull() const {return alias_.empty();}
  private:
    std::string alias_{};
};

struct ComposedUrlsEntity
{   
    AliasUrlEntity alias_url{};
    OriginalUrlEntity original_url{};
};