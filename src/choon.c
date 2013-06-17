#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "httppebble-watch/http.c"

#define APP_NAME "choon"
#define MY_UUID { 0x5A, 0xE7, 0x98, 0x6D, 0x7D, 0x07, 0x4D, 0xCA, 0x85, 0x16, 0x5D, 0xC3, 0xD5, 0x00, 0x5A, 0x77 }
PBL_APP_INFO(HTTP_UUID,
             APP_NAME, "richo@psych0tik.net",
             0, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;
TextLayer text;
DictionaryIterator *body;

void fire_track_request(char req) {
    static int ret;
    static char *url = "http://app.choon.io:4949/XXXXXXXXXXXX/_";
    /*                    XXX use choon.io */

    url[strlen(url) - 1] = req;
    if ((ret = http_out_get(url, 293847856, &body)) == HTTP_OK) {
        if (http_out_send() == HTTP_OK) {
            vibes_short_pulse();
        }
    }
}

void prev_track(ClickRecognizerRef recognizer, Window *window) {
    fire_track_request('p');
}

void next_track(ClickRecognizerRef recognizer, Window *window) {
    fire_track_request('n');
}

void toggle_play(ClickRecognizerRef recognizer, Window *window) {
    fire_track_request('t');
}

void click_config_provider(ClickConfig **config, Window *window) {
    config[BUTTON_ID_SELECT]->click.handler = (ClickHandler) toggle_play;
    config[BUTTON_ID_SELECT]->click.repeat_interval_ms = 100;

    config[BUTTON_ID_UP]->click.handler = (ClickHandler) prev_track;
    config[BUTTON_ID_UP]->click.repeat_interval_ms = 100;

    config[BUTTON_ID_DOWN]->click.handler = (ClickHandler) next_track;
    config[BUTTON_ID_DOWN]->click.repeat_interval_ms = 100;
}

void http_success_callback(int32_t cookie, int http_status, DictionaryIterator* response, void* context) {
    // Do nothing.
}

void handle_init(AppContextRef ctx) {
  (void)ctx;

  window_init(&window, APP_NAME);
  window_stack_push(&window, true /* Animated */);

  window_set_click_config_provider(&window, (ClickConfigProvider) click_config_provider);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .messaging_info = {
        .buffer_sizes = {
            .inbound = 124,
            .outbound = 124,
        }
    }
  };
  app_event_loop(params, &handlers);
}
