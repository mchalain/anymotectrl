#ifndef __KBDMAPING_H__
#define __KBDMAPING_H__
#define M_SHIFT (KEY_LEFTSHIFT << 8)

#ifdef BROADCOM
unsigned short ascii_keyboard[] =
{
	0, 0, 0, 0, 0, 0, 0, 0,
	KEY_BACKSPACE, KEY_TAB, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	KEY_SPACE, M_SHIFT|KEY_1, M_SHIFT|KEY_2, M_SHIFT|KEY_3,  M_SHIFT|KEY_4, M_SHIFT|KEY_5,  M_SHIFT|KEY_7, KEY_APOSTROPHE,
	M_SHIFT|KEY_9, M_SHIFT|KEY_0, M_SHIFT|KEY_8, M_SHIFT|KEY_EQUAL, KEY_COMMA, KEY_MINUS, KEY_DOT, KEY_SLASH,
	KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7,
	KEY_8, KEY_9, M_SHIFT|KEY_SEMICOLON, KEY_SEMICOLON, M_SHIFT|KEY_COMMA, KEY_EQUAL, M_SHIFT|KEY_DOT, M_SHIFT|KEY_SLASH,
	M_SHIFT|KEY_2, M_SHIFT|KEY_A, M_SHIFT|KEY_B, M_SHIFT|KEY_C, M_SHIFT|KEY_D, M_SHIFT|KEY_E, M_SHIFT|KEY_F, M_SHIFT|KEY_G, M_SHIFT|KEY_H,
	M_SHIFT|KEY_I, M_SHIFT|KEY_J, M_SHIFT|KEY_K, M_SHIFT|KEY_L, M_SHIFT|KEY_M, M_SHIFT|KEY_N, M_SHIFT|KEY_O, M_SHIFT|KEY_P,
	M_SHIFT|KEY_Q, M_SHIFT|KEY_R, M_SHIFT|KEY_S, M_SHIFT|KEY_T, M_SHIFT|KEY_U, M_SHIFT|KEY_V, M_SHIFT|KEY_W, M_SHIFT|KEY_X,
	M_SHIFT|KEY_Y, M_SHIFT|KEY_Z, 0, 0, 0, 0, M_SHIFT|KEY_MINUS,
	0, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H,
	KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P,
	KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X,
	KEY_Y, KEY_Z, 0, 0, M_SHIFT|KEY_BACKSLASH, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	
};
#elif defined(KEYBOARD_QWERTY)
unsigned short ascii_keyboard[] =
{
	0, 0, 0, 0, 0, 0, 0, 0,
	KEY_BACKSPACE, KEY_TAB, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	KEY_SPACE, M_SHIFT|KEY_1, M_SHIFT|KEY_2, KEY_BACKSLASH, M_SHIFT|KEY_4, M_SHIFT|KEY_5,  M_SHIFT|KEY_7, KEY_APOSTROPHE,
	M_SHIFT|KEY_9, M_SHIFT|KEY_0, M_SHIFT| KEY_8, M_SHIFT|KEY_EQUAL, KEY_COMMA, KEY_MINUS, KEY_DOT, KEY_SLASH,
	KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7,
	KEY_8, KEY_9, M_SHIFT|KEY_SEMICOLON, KEY_SEMICOLON, M_SHIFT|KEY_COMMA, KEY_EQUAL, M_SHIFT|KEY_DOT, M_SHIFT|KEY_SLASH,
	(M_SHIFT|KEY_APOSTROPHE), M_SHIFT|KEY_A, M_SHIFT|KEY_B, M_SHIFT|KEY_C, M_SHIFT|KEY_D, M_SHIFT|KEY_E, M_SHIFT|KEY_F, M_SHIFT|KEY_G, M_SHIFT|KEY_H,
	M_SHIFT|KEY_I, M_SHIFT|KEY_J, M_SHIFT|KEY_K, M_SHIFT|KEY_L, M_SHIFT|KEY_M, M_SHIFT|KEY_N, M_SHIFT|KEY_O, M_SHIFT|KEY_P,
	M_SHIFT|KEY_Q, M_SHIFT|KEY_R, M_SHIFT|KEY_S, M_SHIFT|KEY_T, M_SHIFT|KEY_U, M_SHIFT|KEY_V, M_SHIFT|KEY_W, M_SHIFT|KEY_X,
	M_SHIFT|KEY_Y, M_SHIFT|KEY_Z, 0, 0, 0, 0, M_SHIFT|KEY_MINUS,
	0, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H,
	KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P,
	KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X,
	KEY_Y, KEY_Z, 0, 0, M_SHIFT|KEY_BACKSLASH, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	
};
#elif defined(KEYBOARD_AZERTY)
unsigned short ascii_keyboard[] =
{
	0, 0, 0, 0, 0, 0, 0, 0,
	KEY_BACKSPACE, KEY_TAB, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	KEY_SPACE, KEY_SLASH, KEY_3, 0, KEY_RIGHTBRACE, M_SHIFT|KEY_APOSTROPHE, KEY_1, KEY_4,
	KEY_5, KEY_MINUS, KEY_GRAVE,M_SHIFT|KEY_EQUAL, KEY_M, KEY_6, M_SHIFT|KEY_COMMA, M_SHIFT|KEY_DOT,
	M_SHIFT|KEY_0, M_SHIFT|KEY_1, M_SHIFT|KEY_2, M_SHIFT|KEY_3, M_SHIFT|KEY_4, M_SHIFT|KEY_5,M_SHIFT|KEY_6, M_SHIFT|KEY_7,
	M_SHIFT|KEY_8, M_SHIFT|KEY_9,KEY_DOT, KEY_COMMA, M_SHIFT|KEY_COMMA, KEY_EQUAL, M_SHIFT|KEY_DOT, M_SHIFT|KEY_SLASH,
	(M_SHIFT|KEY_APOSTROPHE), M_SHIFT|KEY_Q, M_SHIFT|KEY_B, M_SHIFT|KEY_C, M_SHIFT|KEY_D, M_SHIFT|KEY_E, M_SHIFT|KEY_F, M_SHIFT|KEY_G, M_SHIFT|KEY_H,
	M_SHIFT|KEY_I, M_SHIFT|KEY_J, M_SHIFT|KEY_K, M_SHIFT|KEY_L, M_SHIFT|KEY_SEMICOLON, M_SHIFT|KEY_N, M_SHIFT|KEY_O, M_SHIFT|KEY_P,
	M_SHIFT|KEY_A , M_SHIFT|KEY_R, M_SHIFT|KEY_S, M_SHIFT|KEY_T, M_SHIFT|KEY_U, M_SHIFT|KEY_V, M_SHIFT|KEY_Z, M_SHIFT|KEY_X,
	M_SHIFT|KEY_Y, M_SHIFT|KEY_W, 0, 0, 0, 0, M_SHIFT|KEY_MINUS,
	0, KEY_Q, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H,
	KEY_I, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_N, KEY_O, KEY_P,
	KEY_A, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_Z, KEY_X,
	KEY_Y, KEY_W, 0, 0, M_SHIFT|KEY_BACKSLASH, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	
};
#endif
#endif
