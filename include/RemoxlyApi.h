#ifndef POLY_REMOXLY_API_H
#define POLY_REMOXLY_API_H

#include <string>

struct rx_context;
struct rx_element;

typedef void(*rx_callback)(rx_context& ctx, rx_element& el, void* user);

rx_context* rx_create(rx_callback cb, void* user);
void rx_destroy(rx_context* ctx);
void rx_update(rx_context* ctx);
void rx_shutdown(rx_context* ctx);
void rx_save(rx_context* ctx);
void rx_load(rx_context* ctx);

void rx_add_section(rx_context* ctx, const char* title);
void rx_add_group(rx_context* ctx, const char* title);
void rx_add_slider_int(rx_context* ctx, const char* title, int& val, int minv, int maxv, int step);
void rx_add_slider_float(rx_context* ctx, const char* title, float& val, float minv, float maxv, float step, int ndecimals = 2);
void rx_add_button(rx_context* ctx, const char* title, int id);
void rx_add_toggle(rx_context* ctx, const char* title, bool& value);
void rx_add_select(rx_context* ctx, const char* title, int id, const char* opts[]);
void rx_add_input(rx_context* ctx, const std::string& title, std::string& value);
void rx_add_separator(rx_context* ctx);

int rx_get_id(rx_element& el);
int rx_get_selected_index(rx_element& el); /* Get selected value from a select. */

bool rx_is_button(rx_element& el);
bool rx_is_select(rx_element& el);

#endif
