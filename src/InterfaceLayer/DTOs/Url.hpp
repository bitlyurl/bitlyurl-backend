#pragma once
#include <string>

class OriginalUrl final
{
  public:
    OriginalUrl()  = default;
    OriginalUrl(std::string url) : url_ {std::move(url)} {}

    void SetUrl(std::string url) { url_ = std::move(url);}
    [[nodiscard]] std::string GetUrl() const  { return url_;}

  private:
    std::string url_{};
};

class ShortUrl final
{
  public:
    ShortUrl() = default;
    ShortUrl(std::string url) : url_{std::move(url)} {}

    void SetUrl(std::string url) { url_ = std::move(url);}
    [[nodiscard]] std::string GetUrl() const { return url_;}

  private:
  std::string url_{};
};


