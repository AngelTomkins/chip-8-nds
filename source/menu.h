#ifndef MENU_H
#define MENU_H

#include <nds.h>

typedef struct {
  PrintConsole console; 
  int keyboard_id;
  int config_page;
} ConfigMenu;

void init_config_console(int bg_id, int keyboard_id);
void open_menu();


#endif
