#define DROGON_TEST_MAIN
#include <drogon/drogon_test.h>

#include "../../src/DataAccessLayer/Repository/UrlRepository/UrlRepository.hpp"

DROGON_TEST(UrlRepositoryTest)
{
    auto url_repo_test1 = [TEST_CTX]() -> drogon::Task<void>
    {
       auto redis_client = drogon::app().getRedisClient();
       CO_REQUIRE(redis_client != nullptr);

       UrlRepository repo(redis_client);

       AliasUrlEntity alias("alias");
       OriginalUrlEntity original("http://localhost");

       ComposedUrlsEntity composed{alias,original};

       co_await repo.Create(composed);
       auto  result = co_await repo.GetBy(alias);
       
       CHECK((!result.alias_url.IsNull() && !result.original_url.IsNull()));
       CHECK(result.original_url.GetUrl() == original.GetUrl());
    };

    auto url_repo_test2 = [TEST_CTX]() -> drogon::Task<void>
    {
       auto redis_client = drogon::app().getRedisClient();
       CO_REQUIRE(redis_client != nullptr);

       UrlRepository repo(redis_client);

       AliasUrlEntity alias("new_alias");
       OriginalUrlEntity original("http://google.com");

       ComposedUrlsEntity composed{alias,original};

       co_await repo.Create(composed);
       auto  result = co_await repo.GetBy(alias);
       
       CHECK((!result.alias_url.IsNull() && !result.original_url.IsNull()));
       CHECK(result.original_url.GetUrl() == original.GetUrl());
    };
    drogon::sync_wait(url_repo_test1());
    drogon::sync_wait(url_repo_test2());
}

int main(int argc,char** argv)
{   
   using namespace drogon;
    std::promise<void> p1;
    std::future<void> f1 = p1.get_future();

    // Start the main loop on another thread
    std::thread thr([&]() {
        // Queues the promise to be fulfilled after starting the loop
        app().getLoop()->queueInLoop([&p1]() { p1.set_value(); });

        app().createRedisClient("127.0.0.1",6379);

        app().run();
    });

    // The future is only satisfied after the event loop started
    f1.get();
    int status = test::run(argc, argv);

    // Ask the event loop to shutdown and wait
    app().getLoop()->queueInLoop([]() { app().quit(); });
    thr.join();
    return status;
    
}