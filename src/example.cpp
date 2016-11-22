#include <stdio.h>
#include <stdlib.h>
#include <RemoxlyApi.h>

#if defined(_WIN32)
#  include <windows.h>
#  define sleep_millis(x) Sleep(x)
#elif defined(__APPLE__)
#  include <unistd.h>
#  define sleep_millis(x) usleep(x * 1000)
#endif

/* ------------------------------------- */

#define EL_ID_VIEW_OPTION 1
#define EL_ID_SAVE_BUTTON 2
#define EL_ID_SET_OBJECT_NAME 3

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

  /* Main section */
  bool draw_enabled = false;
  int num_particles = 0;
  int num_passes = 0;
  float max_force = 0.0f;
  float gravity = 9.8f;
  int max_lifetime = 100;
  const char* view_opts[] = { "Front view", "Side view", "Camera path", NULL };
  bool show_normals = false;
  bool show_edges = false;
  std::string filename;

  rx_add_section(rx, "Main");
  rx_add_group(rx, "Effects");
  rx_add_toggle(rx, "Enable drawing", draw_enabled);
  rx_add_slider_int(rx, "Number of particles", num_particles, 1, 1000000, 10);
  rx_add_slider_int(rx, "Number of render passes", num_passes, 1, 16, 1);
  rx_add_separator(rx);
  rx_add_slider_float(rx, "Max force", max_force, 0.001f, 10.0f, 0.01f);
  rx_add_slider_float(rx, "Gravity", gravity, 0.001f, 9.8f, 0.01f);
  rx_add_slider_int(rx, "Max life time", max_lifetime, 1, 240, 1);
  rx_add_separator(rx);
  rx_add_select(rx, "View", EL_ID_VIEW_OPTION, view_opts);
  rx_add_toggle(rx, "Show normals", show_normals);
  rx_add_toggle(rx, "Show edges", show_edges);
  rx_add_separator(rx);
  rx_add_input(rx, "Filename", filename);
  rx_add_button(rx, "Save properties", EL_ID_SAVE_BUTTON);

  /* Properties Section */
  bool show_name = false;
  bool show_axis = false;
  bool show_wire = false;
  bool show_bounds = false;
  int start_frame = 0;
  int end_frame = 100;
  std::string object_name;
  
  rx_add_section(rx, "Object");
  rx_add_group(rx, "Display");
  rx_add_toggle(rx, "Name", show_name);
  rx_add_toggle(rx, "Axis", show_axis);
  rx_add_toggle(rx, "Wire", show_wire);
  rx_add_toggle(rx, "Bounds", show_bounds);
  rx_add_separator(rx);
  rx_add_slider_int(rx, "Start frame", start_frame, 1, 1000, 1);
  rx_add_slider_int(rx, "End frame", end_frame, 1, 1000, 1);
  rx_add_separator(rx);
  rx_add_input(rx, "Object name", object_name);
  rx_add_button(rx, "Set object name", EL_ID_SET_OBJECT_NAME);
    
  while (true) {
    rx_update(rx);
    sleep_millis(16);
  }

  return 0;
}

/* ------------------------------------- */

static void on_gui_event(rx_context& rx, rx_element& el, void* user) {

  switch (rx_get_id(el)) {
    case EL_ID_VIEW_OPTION: {
      printf("View option changed.\n");
      break;
    }
    case EL_ID_SAVE_BUTTON: {
      printf("Save button pressed.\n");
      break;
    }
    case EL_ID_SET_OBJECT_NAME: {
      printf("Set object name.\n");
      break;
    }
    default: {
      printf("Error: unhandled remoxly element id.\n");
      break;
    }
  }
}

/* ------------------------------------- */
