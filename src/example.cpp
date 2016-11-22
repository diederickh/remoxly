#include <stdio.h>
#include <stdlib.h>
#include <RemoxlyApi.h>

#if defined(_WIN32)
#  include <windows.h>
#endif

/* ------------------------------------- */

static void on_gui_event(rx_context& rx, rx_element& el, void* user);

/* ------------------------------------- */

int main() {
  
  printf("\n\nRemoxly Example\n\n");

  rx_context* rx = rx_create(on_gui_event, NULL);
  if (NULL == rx) {
    printf("Error: failed to create the remoxly context.\n");
    exit(EXIT_FAILURE);
  }

  bool draw_enabled = false;
  
  rx_add_section(rx, "Main Section");
  rx_add_group(rx, "Group 1");
  rx_add_toggle(rx, "Enable drawing", draw_enabled);
  
  while (true) {
    rx_update(rx);
    Sleep(16);
  }

  return 0;
}

/* ------------------------------------- */

static void on_gui_event(rx_context& rx, rx_element& el, void* user) {
  printf("Got gui event.\n");
}

/* ------------------------------------- */
