#include <cpu.h>
#include <common.h>
#include <SDL2/SDL.h>

extern void send_key(uint8_t, bool);
void vga_update_screen();

#define TIMER_HZ 60

void device_update() {

  vga_update_screen();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                cpu.state = SIM_STOP;
            break;
            case SDL_KEYDOWN:
            case SDL_KEYUP: {
                uint8_t k = event.key.keysym.scancode;
                bool is_keydown = (event.key.type == SDL_KEYDOWN);
                send_key(k, is_keydown);
                break;
            }
            default: break;
        }
    }
    SDL_Delay(1000 / TIMER_HZ);
}

int thread_update(void* ptr) {
    while (cpu.state == SIM_RUNNING) {
        device_update();
    }
    return 0;
}

extern void init_serial();
extern void init_rtc();
extern void init_keyboard();
extern void init_vga();

void init_device() {
    init_serial();
    init_rtc();
    init_keyboard();
    init_vga();
    SDL_CreateThread(thread_update, "device_update", NULL);

}
