
#include "Controllers/UrlController/UrlController.hpp"

int main()
{
    LOG_INFO <<"Loading configuraton file...\n\n";
    
    drogon::app().loadConfigFile("backend.json");

    drogon::app().run();
    return 0;
}