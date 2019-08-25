#include "ExampleLayer.hpp"

int main(int argc, char *argv[]) {
    auto *app = new Murat::Application();
    Sandbox::ExampleLayer layer = Sandbox::ExampleLayer();
    app->pushLayer(&layer);
    app->run();
    return 0;
}
