
#include "Controllers/UrlController/UrlController.hpp"

int main(int argc,char** argv)
{
    LOG_INFO <<"Loading configuraton file...\n\n";
    
    drogon::app().loadConfigFile(argv[1]);

    drogon::app().run();
    return 0;
}