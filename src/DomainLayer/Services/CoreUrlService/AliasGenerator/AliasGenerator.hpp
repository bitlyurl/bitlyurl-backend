#pragma once
#include <string>
#include <random>

class AliasGenerator final
{
  public:

        AliasGenerator(const AliasGenerator&) =delete;
        AliasGenerator& operator=(const AliasGenerator&) = delete;

        AliasGenerator(AliasGenerator&&) noexcept = delete;
        AliasGenerator& operator=(AliasGenerator&&) noexcept = delete;

        
        static inline std::string Generate(std::size_t len)
        {
            return Instance().ProduceAlias(len);
        }


  private:
        static inline AliasGenerator& Instance()
        {
           static AliasGenerator generator;
           return generator;
        }

        std::string ProduceAlias(std::size_t);

        static constexpr std::string_view hex_chars{"0123456789abcdef"};
        AliasGenerator() = default;
        ~AliasGenerator() = default;
};


inline std::string AliasGenerator::ProduceAlias(std::size_t len)
{
    using Generator = std::mt19937;

    Generator gen{ std::random_device{}() };
    std::string alias;
    alias.reserve(len);

    while (alias.size() < len)
    {
        auto n = gen();
        for (auto i = Generator::max(); i & 0x8 && alias.size() < len; i >>= 4)
         {
            alias += hex_chars[n % hex_chars.size()];
            n >>= 4;
         }
    }
	return alias;
}