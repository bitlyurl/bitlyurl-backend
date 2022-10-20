#define DROGON_TEST_MAIN
#include <drogon/drogon_test.h>

#include "../../src/DomainLayer/Services/CoreUrlService/CoreUrlService.hpp"

DROGON_TEST(CoreServiceTest)
{
    auto core_service_test1 = [TEST_CTX]() -> drogon::Task<void>
    {
        CO_REQUIRE(drogon::app().getRedisClient() != nullptr);

        std::unique_ptr<CoreUrlService> service =std::make_unique<CoreUrlService>();

        OriginalUrlBO orig("http://github.com");

        ComposedUrlsBO composed = co_await service->ProduceAliasAndGetBack(orig);

        CHECK((!composed.alias_url.IsNull() && !composed.original_url.IsNull()));

        LOG_INFO <<"Alias : "<< composed.alias_url.GetAlias() <<" URL : "<<composed.original_url.GetUrl() <<'\n';

        OriginalUrlBO found_orig = co_await service->GetOriginalBy(composed.alias_url);

        CO_REQUIRE(found_orig.GetUrl() == orig.GetUrl());
    };


    auto core_service_test2 = [TEST_CTX]() -> drogon::Task<void>
    {
        CO_REQUIRE(drogon::app().getRedisClient() != nullptr);

        std::unique_ptr<CoreUrlService> service =std::make_unique<CoreUrlService>();

        OriginalUrlBO orig("'''error");

        ComposedUrlsBO composed = co_await service->ProduceAliasAndGetBack(orig);

        CHECK((!composed.alias_url.IsNull() && !composed.original_url.IsNull()));

        LOG_INFO <<"Alias : "<< composed.alias_url.GetAlias() <<" URL : "<<composed.original_url.GetUrl() <<'\n';

        OriginalUrlBO found_orig = co_await service->GetOriginalBy(composed.alias_url);

        CO_REQUIRE(found_orig.GetUrl() == orig.GetUrl());
    };
    drogon::sync_wait(core_service_test1());
   // drogon::sync_wait(core_service_test2());
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