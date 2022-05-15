#ifndef LCD_H_
#define LCD_H_

void LCD_vInit(void);
static void SendPulse(void);
void LCD_vSend_CMD(char cmd);
void LCD_vSend_Char(char character);
void LCD_vSend_String(char *data);
void LCD_ClearScreen(void);
void LCD_MoveCursor(char row, char column);
void LCD_ClearRow(char row);


#endif
