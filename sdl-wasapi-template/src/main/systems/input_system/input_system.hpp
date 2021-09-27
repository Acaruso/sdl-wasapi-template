#pragma once

#include <string>

#include <SDL.h>

#include "../../store/coord.hpp"

struct UiState
{
	bool click{false};

    Coord mousePos{0, 0};
    Coord mouseDrag{0, 0};
    Coord prevMouseDrag{0, 0};

    std::string cur_elt_id{""};

    bool a{false};
    bool b{false};
    bool c{false};
    bool d{false};
    bool e{false};
    bool f{false};
    bool g{false};
    bool h{false};
    bool i{false};
    bool j{false};
    bool k{false};
    bool l{false};
    bool m{false};
    bool n{false};
    bool o{false};
    bool p{false};
    bool q{false};
    bool r{false};
    bool s{false};
    bool t{false};
    bool u{false};
    bool v{false};
    bool w{false};
    bool x{false};
    bool y{false};
    bool z{false};

    bool up{false};
	bool down{false};
	bool left{false};
	bool right{false};

    bool space{false};
    bool lshift{false};
    bool lctrl{false};
    bool lalt{false};
    bool tab{false};
	bool quit{false};
    bool esc{false};

    bool i1{false};
    bool i2{false};
    bool i3{false};
    bool i4{false};
    bool i5{false};
    bool i6{false};

    bool keydown_event{false};
};

struct InputSystem
{
    UiState uiState;
    UiState prevUiState;

    void run();

    void mouse_button_down(SDL_Event& event);
    void mouse_button_up(SDL_Event& event);
    void mouse_motion(SDL_Event& event);
    void keydown(SDL_Event& event);
    void keyup(SDL_Event& event);

    void nextState();
};
