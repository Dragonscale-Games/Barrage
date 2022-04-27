/* ======================================================================== */
/*!
 * \file            KeyMap.hpp
 * \par             Barrage Engine
 * \author          David Cruse
 * \par             david.n.cruse\@gmail.com

 * \brief
   All keyboard keys defined as ints (for use with the InputManager's key 
   functions).
 */
/* ======================================================================== */

////////////////////////////////////////////////////////////////////////////////
#ifndef KeyMap_BARRAGE_H
#define KeyMap_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////

namespace Barrage
{
  typedef int KEY;

  const int KEY_UNKNOWN = -1;

  const int KEY_SPACE = 32;

  const int KEY_APOSTROPHE = 39;

  const int KEY_COMMA = 44;
  const int KEY_MINUS = 45;
  const int KEY_PERIOD = 46;
  const int KEY_FOWARD_SLASH = 47;

  const int KEY_0 = 48;
  const int KEY_1 = 49;
  const int KEY_2 = 50;
  const int KEY_3 = 51;
  const int KEY_4 = 52;
  const int KEY_5 = 53;
  const int KEY_6 = 54;
  const int KEY_7 = 55;
  const int KEY_8 = 56;
  const int KEY_9 = 57;

  const int KEY_SEMICOLON = 59;

  const int KEY_EQUAL = 61;

  const int KEY_A = 65;
  const int KEY_B = 66;
  const int KEY_C = 67;
  const int KEY_D = 68;
  const int KEY_E = 69;
  const int KEY_F = 70;
  const int KEY_G = 71;
  const int KEY_H = 72;
  const int KEY_I = 73;
  const int KEY_J = 74;
  const int KEY_K = 75;
  const int KEY_L = 76;
  const int KEY_M = 77;
  const int KEY_N = 78;
  const int KEY_O = 79;
  const int KEY_P = 80;
  const int KEY_Q = 81;
  const int KEY_R = 82;
  const int KEY_S = 83;
  const int KEY_T = 84;
  const int KEY_U = 85;
  const int KEY_V = 86;
  const int KEY_W = 87;
  const int KEY_X = 88;
  const int KEY_Y = 89;
  const int KEY_Z = 90;

  const int KEY_LEFT_BRACKET = 91;
  const int KEY_BACKSLASH = 92;
  const int KEY_RIGHT_BRACKET = 93;

  const int KEY_GRAVE = 96;

  const int KEY_WORLD_1 = 161;
  const int KEY_WORLD_2 = 162;

  const int KEY_ESCAPE = 256;
  const int KEY_ENTER = 257;
  const int KEY_TAB = 258;
  const int KEY_BACKSPACE = 259;
  const int KEY_INSERT = 260;
  const int KEY_DELETE = 261;

  const int KEY_RIGHT = 262;
  const int KEY_LEFT = 263;
  const int KEY_DOWN = 264;
  const int KEY_UP = 265;

  const int KEY_PAGE_UP = 266;
  const int KEY_PAGE_DOWN = 267;
  const int KEY_HOME = 268;
  const int KEY_END = 269;

  const int KEY_CAPS_LOCK = 280;
  const int KEY_SCROLL_LOCK = 281;
  const int KEY_NUM_LOCK = 282;

  const int KEY_PRINT_SCREEN = 283;
  const int KEY_PAUSE = 284;

  const int KEY_F1 = 290;
  const int KEY_F2 = 291;
  const int KEY_F3 = 292;
  const int KEY_F4 = 293;
  const int KEY_F5 = 294;
  const int KEY_F6 = 295;
  const int KEY_F7 = 296;
  const int KEY_F8 = 297;
  const int KEY_F9 = 298;
  const int KEY_F10 = 299;
  const int KEY_F11 = 300;
  const int KEY_F12 = 301;
  const int KEY_F13 = 302;
  const int KEY_F14 = 303;
  const int KEY_F15 = 304;
  const int KEY_F16 = 305;
  const int KEY_F17 = 306;
  const int KEY_F18 = 307;
  const int KEY_F19 = 308;
  const int KEY_F20 = 309;
  const int KEY_F21 = 310;
  const int KEY_F22 = 311;
  const int KEY_F23 = 312;
  const int KEY_F24 = 313;
  const int KEY_F25 = 314;

  const int KEY_0_NUMPAD = 320;
  const int KEY_1_NUMPAD = 321;
  const int KEY_2_NUMPAD = 322;
  const int KEY_3_NUMPAD = 323;
  const int KEY_4_NUMPAD = 324;
  const int KEY_5_NUMPAD = 325;
  const int KEY_6_NUMPAD = 326;
  const int KEY_7_NUMPAD = 327;
  const int KEY_8_NUMPAD = 328;
  const int KEY_9_NUMPAD = 329;

  const int KEY_PERIOD_NUMPAD = 330;
  const int KEY_FORWARD_SLASH_NUMPAD = 331;
  const int KEY_ASTERISK_NUMPAD = 332;
  const int KEY_MINUS_NUMPAD = 333;
  const int KEY_PLUS_NUMPAD = 334;
  const int KEY_ENTER_NUMPAD = 335;
  const int KEY_EQUAL_NUMPAD = 336;

  const int KEY_SHIFT_LEFT = 340;
  const int KEY_CTRL_LEFT = 341;
  const int KEY_ALT_LEFT = 342;
  const int KEY_SUPER_LEFT = 343;

  const int KEY_SHIFT_RIGHT = 344;
  const int KEY_CTRL_RIGHT = 345;
  const int KEY_ALT_RIGHT = 346;
  const int KEY_SUPER_RIGHT = 347;

  const int KEY_MENU = 348;
 
  const int MAX_KEY_VALUE = KEY_MENU;
}

////////////////////////////////////////////////////////////////////////////////
#endif // KeyMap_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////