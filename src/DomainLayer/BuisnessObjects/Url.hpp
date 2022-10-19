#pragma  once
#include <string>

class OriginalUrlBO final
{
  public:
    OriginalUrlBO() =default;
    OriginalUrlBO(std::string url) : url_{std::move(url)} {}

    void SetUrl(std::string url) { url_ = std::move(url);}
    [[nodiscard]] std::string GetUrl() const  { return url_; }

    bool IsNull() const {return url_.empty();}
  private:
    std::string url_{};
};

class AliasUrlBO final
{
  public:
    AliasUrlBO() = default;
    AliasUrlBO(std::string url) : url_{std::move(url)} {}

    void SetUrl(std::string url) { url_ = std::move(url);}
    [[nodiscard]] std::string GetUrl() const { return url_;}

    bool IsNull() const {return url_.empty();}
  private:
    std::string url_{};
};

struct ComposedUrlsBO
{
    AliasUrlBO alias_url;
    OriginalUrlBO original_url;
};
