#include "input_system.hpp"

#include <iostream>

void InputSystem::run()
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
        case SDL_QUIT:
            this->uiState.quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            mouse_button_down(event);
            break;
        case SDL_MOUSEBUTTONUP:
            mouse_button_up(event);
            break;
        case SDL_MOUSEMOTION:
            mouse_motion(event);
            break;
        case SDL_KEYDOWN:
            keydown(event);
            break;
        case SDL_KEYUP:
            keyup(event);
            break;
        }
    }

    if (this->uiState.click) {
        this->uiState.prevMouseDrag.x = this->uiState.mouseDrag.x;
        this->uiState.prevMouseDrag.y = this->uiState.mouseDrag.y;

        this->uiState.mouseDrag.x = this->uiState.mousePos.x;
        this->uiState.mouseDrag.y = this->uiState.mousePos.y;
    }
}

void InputSystem::mouse_button_down(SDL_Event& event)
{
    this->uiState.click = true;

    this->uiState.mouseDrag.x = this->uiState.mousePos.x;
    this->uiState.mouseDrag.y = this->uiState.mousePos.y;
}

void InputSystem::mouse_button_up(SDL_Event& event)
{
    this->uiState.click = false;
    this->uiState.cur_elt_id = "";
}

void InputSystem::mouse_motion(SDL_Event& event)
{
    this->uiState.mousePos.x = event.motion.x;
    this->uiState.mousePos.y = event.motion.y;
}

void InputSystem::keydown(SDL_Event& event)
{
    this->uiState.keydown_event = true;

    switch (event.key.keysym.sym) {
    case SDLK_a:
        this->uiState.a = true;
        break;
    case SDLK_b:
        this->uiState.b = true;
        break;
    case SDLK_c:
        this->uiState.c = true;
        break;
    case SDLK_d:
        this->uiState.d = true;
        break;
    case SDLK_e:
        this->uiState.e = true;
        break;
    case SDLK_f:
        this->uiState.f = true;
        break;
    case SDLK_g:
        this->uiState.g = true;
        break;
    case SDLK_h:
        this->uiState.h = true;
        break;
    case SDLK_i:
        this->uiState.i = true;
        break;
    case SDLK_j:
        this->uiState.j = true;
        break;
    case SDLK_k:
        this->uiState.k = true;
        break;
    case SDLK_l:
        this->uiState.l = true;
        break;
    case SDLK_m:
        this->uiState.m = true;
        break;
    case SDLK_n:
        this->uiState.n = true;
        break;
    case SDLK_o:
        this->uiState.o = true;
        break;
    case SDLK_p:
        this->uiState.p = true;
        break;
    case SDLK_q:
        this->uiState.q = true;
        break;
    case SDLK_r:
        this->uiState.r = true;
        break;
    case SDLK_s:
        this->uiState.s = true;
        break;
    case SDLK_t:
        this->uiState.t = true;
        break;
    case SDLK_u:
        this->uiState.u = true;
        break;
    case SDLK_v:
        this->uiState.v = true;
        break;
    case SDLK_w:
        this->uiState.w = true;
        break;
    case SDLK_x:
        this->uiState.x = true;
        break;
    case SDLK_y:
        this->uiState.y = true;
        break;
    case SDLK_z:
        this->uiState.z = true;
        break;

    case SDLK_UP:
        this->uiState.up = true;
        break;
    case SDLK_DOWN:
        this->uiState.down = true;
        break;
    case SDLK_LEFT:
        this->uiState.left = true;
        break;
    case SDLK_RIGHT:
        this->uiState.right = true;
        break;

    case SDLK_SPACE:
        this->uiState.space = true;
        break;
    case SDLK_LSHIFT:
        this->uiState.lshift = true;
        break;
    case SDLK_LCTRL:
        this->uiState.lctrl = true;
        break;
    case SDLK_LALT:
        this->uiState.lalt = true;
        break;
    case SDLK_TAB:
        this->uiState.tab = true;
        break;
    case SDLK_1:
        this->uiState.i1 = true;
        break;
    case SDLK_2:
        this->uiState.i2 = true;
        break;
    case SDLK_3:
        this->uiState.i3 = true;
        break;
    case SDLK_4:
        this->uiState.i4 = true;
        break;
    case SDLK_5:
        this->uiState.i5 = true;
        break;
    case SDLK_6:
        this->uiState.i6 = true;
        break;
    case SDLK_ESCAPE:
        this->uiState.esc = true;
        break;
    }
}

void InputSystem::keyup(SDL_Event& event)
{
    switch (event.key.keysym.sym) {
    case SDLK_a:
        this->uiState.a = false;
        break;
    case SDLK_b:
        this->uiState.b = false;
        break;
    case SDLK_c:
        this->uiState.c = false;
        break;
    case SDLK_d:
        this->uiState.d = false;
        break;
    case SDLK_e:
        this->uiState.e = false;
        break;
    case SDLK_f:
        this->uiState.f = false;
        break;
    case SDLK_g:
        this->uiState.g = false;
        break;
    case SDLK_h:
        this->uiState.h = false;
        break;
    case SDLK_i:
        this->uiState.i = false;
        break;
    case SDLK_j:
        this->uiState.j = false;
        break;
    case SDLK_k:
        this->uiState.k = false;
        break;
    case SDLK_l:
        this->uiState.l = false;
        break;
    case SDLK_m:
        this->uiState.m = false;
        break;
    case SDLK_n:
        this->uiState.n = false;
        break;
    case SDLK_o:
        this->uiState.o = false;
        break;
    case SDLK_p:
        this->uiState.p = false;
        break;
    case SDLK_q:
        this->uiState.q = false;
        break;
    case SDLK_r:
        this->uiState.r = false;
        break;
    case SDLK_s:
        this->uiState.s = false;
        break;
    case SDLK_t:
        this->uiState.t = false;
        break;
    case SDLK_u:
        this->uiState.u = false;
        break;
    case SDLK_v:
        this->uiState.v = false;
        break;
    case SDLK_w:
        this->uiState.w = false;
        break;
    case SDLK_x:
        this->uiState.x = false;
        break;
    case SDLK_y:
        this->uiState.y = false;
        break;
    case SDLK_z:
        this->uiState.z = false;
        break;

    case SDLK_UP:
        this->uiState.up = false;
        break;
    case SDLK_DOWN:
        this->uiState.down = false;
        break;
    case SDLK_LEFT:
        this->uiState.left = false;
        break;
    case SDLK_RIGHT:
        this->uiState.right = false;
        break;

    case SDLK_SPACE:
        this->uiState.space = false;
        break;
    case SDLK_LSHIFT:
        this->uiState.lshift = false;
        break;
    case SDLK_LCTRL:
        this->uiState.lctrl = false;
        break;
    case SDLK_LALT:
        this->uiState.lalt = false;
        break;
    case SDLK_TAB:
        this->uiState.tab = false;
        break;
    case SDLK_1:
        this->uiState.i1 = false;
        break;
    case SDLK_2:
        this->uiState.i2 = false;
        break;
    case SDLK_3:
        this->uiState.i3 = false;
        break;
    case SDLK_4:
        this->uiState.i4 = false;
        break;
    case SDLK_5:
        this->uiState.i5 = false;
        break;
    case SDLK_6:
        this->uiState.i6 = false;
        break;
    case SDLK_ESCAPE:
        this->uiState.esc = false;
        break;
    }
}

void InputSystem::nextState()
{
    this->prevUiState = this->uiState;
}
