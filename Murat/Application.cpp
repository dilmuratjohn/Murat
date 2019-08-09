#include "Murat.hpp"

int main(int argc, char *argv[]) {

    auto* app = new Murat::Application();
    app->run();
    delete app;
    return 0;
}

