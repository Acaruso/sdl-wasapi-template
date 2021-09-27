#include "../audio/audio_entrypoint.hpp"
#include "app/app.hpp"
#include "callback/callback.hpp"

int main(int argc, char* args[])
{
    App app(setup, callback);
    app.run();
    return 0;
}
