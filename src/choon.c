#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define APP_NAME "choon"
#define MY_UUID { 0x5A, 0xE7, 0x98, 0x6D, 0x7D, 0x07, 0x4D, 0xCA, 0x85, 0x16, 0x5D, 0xC3, 0xD5, 0x00, 0x5A, 0x77 }
PBL_APP_INFO(MY_UUID,
             APP_NAME, "richo@psych0tik.net",
             0, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;


void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, APP_NAME);
  window_stack_push(&window, true /* Animated */);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init
  };
  app_event_loop(params, &handlers);
}
