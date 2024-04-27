#ifndef _MENU_H_
#define _MENU_H_

#include "headfile.h"

extern int display_codename; // 显示页面代号

extern int waring_on;
extern float threshold_temp, threshold_smog_vol;


void Cursor(void);
void Menu_Next_Back(void);
int Have_Sub_Menu(int menu_id); // 查看是否存在子菜单

void HandleKeystroke(int keystroke_label);
void Keystroke_Special_Value(int *parameter);
void Keystroke_int(int *parameter, int change_unit_MIN);
void Keystroke_float(float *parameter, float change_unit_MIN);

void Keystroke_Menu(void);
void Keystroke_Menu_HOME(void);

void Menu_ONE_Display(uint8 control_line);
void Keystroke_Menu_ONE(void);

// void Menu_TWO_Display(uint8 control_line);
// void Keystroke_Menu_TWO(void);

#endif