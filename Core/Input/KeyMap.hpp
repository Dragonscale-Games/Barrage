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

  const KEY KEY_UNKNOWN = -1;

  const KEY KEY_SPACE = 32;

  const KEY KEY_APOSTROPHE = 39;

  const KEY KEY_COMMA = 44;
  const KEY KEY_MINUS = 45;
  const KEY KEY_PERIOD = 46;
  const KEY KEY_FOWARD_SLASH = 47;

  const KEY KEY_0 = 48;
  const KEY KEY_1 = 49;
  const KEY KEY_2 = 50;
  const KEY KEY_3 = 51;
  const KEY KEY_4 = 52;
  const KEY KEY_5 = 53;
  const KEY KEY_6 = 54;
  const KEY KEY_7 = 55;
  const KEY KEY_8 = 56;
  const KEY KEY_9 = 57;

  const KEY KEY_SEMICOLON = 59;

  const KEY KEY_EQUAL = 61;

  const KEY KEY_A = 65;
  const KEY KEY_B = 66;
  const KEY KEY_C = 67;
  const KEY KEY_D = 68;
  const KEY KEY_E = 69;
  const KEY KEY_F = 70;
  const KEY KEY_G = 71;
  const KEY KEY_H = 72;
  const KEY KEY_I = 73;
  const KEY KEY_J = 74;
  const KEY KEY_K = 75;
  const KEY KEY_L = 76;
  const KEY KEY_M = 77;
  const KEY KEY_N = 78;
  const KEY KEY_O = 79;
  const KEY KEY_P = 80;
  const KEY KEY_Q = 81;
  const KEY KEY_R = 82;
  const KEY KEY_S = 83;
  const KEY KEY_T = 84;
  const KEY KEY_U = 85;
  const KEY KEY_V = 86;
  const KEY KEY_W = 87;
  const KEY KEY_X = 88;
  const KEY KEY_Y = 89;
  const KEY KEY_Z = 90;

  const KEY KEY_LEFT_BRACKET = 91;
  const KEY KEY_BACKSLASH = 92;
  const KEY KEY_RIGHT_BRACKET = 93;

  const KEY KEY_GRAVE = 96;

  const KEY KEY_WORLD_1 = 161;
  const KEY KEY_WORLD_2 = 162;

  const KEY KEY_ESCAPE = 256;
  const KEY KEY_ENTER = 257;
  const KEY KEY_TAB = 258;
  const KEY KEY_BACKSPACE = 259;
  const KEY KEY_INSERT = 260;
  const KEY KEY_DELETE = 261;

  const KEY KEY_RIGHT = 262;
  const KEY KEY_LEFT = 263;
  const KEY KEY_DOWN = 264;
  const KEY KEY_UP = 265;

  const KEY KEY_PAGE_UP = 266;
  const KEY KEY_PAGE_DOWN = 267;
  const KEY KEY_HOME = 268;
  const KEY KEY_END = 269;

  const KEY KEY_CAPS_LOCK = 280;
  const KEY KEY_SCROLL_LOCK = 281;
  const KEY KEY_NUM_LOCK = 282;

  const KEY KEY_PRINT_SCREEN = 283;
  const KEY KEY_PAUSE = 284;

  const KEY KEY_F1 = 290;
  const KEY KEY_F2 = 291;
  const KEY KEY_F3 = 292;
  const KEY KEY_F4 = 293;
  const KEY KEY_F5 = 294;
  const KEY KEY_F6 = 295;
  const KEY KEY_F7 = 296;
  const KEY KEY_F8 = 297;
  const KEY KEY_F9 = 298;
  const KEY KEY_F10 = 299;
  const KEY KEY_F11 = 300;
  const KEY KEY_F12 = 301;
  const KEY KEY_F13 = 302;
  const KEY KEY_F14 = 303;
  const KEY KEY_F15 = 304;
  const KEY KEY_F16 = 305;
  const KEY KEY_F17 = 306;
  const KEY KEY_F18 = 307;
  const KEY KEY_F19 = 308;
  const KEY KEY_F20 = 309;
  const KEY KEY_F21 = 310;
  const KEY KEY_F22 = 311;
  const KEY KEY_F23 = 312;
  const KEY KEY_F24 = 313;
  const KEY KEY_F25 = 314;

  const KEY KEY_0_NUMPAD = 320;
  const KEY KEY_1_NUMPAD = 321;
  const KEY KEY_2_NUMPAD = 322;
  const KEY KEY_3_NUMPAD = 323;
  const KEY KEY_4_NUMPAD = 324;
  const KEY KEY_5_NUMPAD = 325;
  const KEY KEY_6_NUMPAD = 326;
  const KEY KEY_7_NUMPAD = 327;
  const KEY KEY_8_NUMPAD = 328;
  const KEY KEY_9_NUMPAD = 329;

  const KEY KEY_PERIOD_NUMPAD = 330;
  const KEY KEY_FORWARD_SLASH_NUMPAD = 331;
  const KEY KEY_ASTERISK_NUMPAD = 332;
  const KEY KEY_MINUS_NUMPAD = 333;
  const KEY KEY_PLUS_NUMPAD = 334;
  const KEY KEY_ENTER_NUMPAD = 335;
  const KEY KEY_EQUAL_NUMPAD = 336;

  const KEY KEY_SHIFT_LEFT = 340;
  const KEY KEY_CTRL_LEFT = 341;
  const KEY KEY_ALT_LEFT = 342;
  const KEY KEY_SUPER_LEFT = 343;

  const KEY KEY_SHIFT_RIGHT = 344;
  const KEY KEY_CTRL_RIGHT = 345;
  const KEY KEY_ALT_RIGHT = 346;
  const KEY KEY_SUPER_RIGHT = 347;

  const KEY KEY_MENU = 348;
 
  const KEY MAX_KEY_VALUE = KEY_MENU;
}

////////////////////////////////////////////////////////////////////////////////
#endif // KeyMap_BARRAGE_H
////////////////////////////////////////////////////////////////////////////////