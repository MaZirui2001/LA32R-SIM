#include <cpu.h>
#include <common.h>
#include <SDL2/SDL.h>

extern void send_key(uint8_t, bool);
extern uint64_t get_time();
// void vga_update_screen();

#define TIMER_HZ 60

void device_update() {
  static uint64_t last = 0;
  uint64_t now = get_time();
  if (now - last < 100000 / TIMER_HZ) {
    return;
  }
  last = now;

//   vga_update_screen();

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        cpu.state = SIM_END;
        break;
      //If a key was pressed
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
}

extern void init_serial();
extern void init_rtc();
extern void init_keyboard();

void init_device() {
  init_serial();
  init_rtc();
  init_keyboard();
}
