#pragma once
enum class MessageEvent {
  // KEYBOARD_KEYS
  UP_PRESSED,
  DOWN_PRESSED,
  LEFT_PRESSED,
  RIGHT_PRESSED,
  RETURN_PRESSED,
  ESCAPE_PRESSED,
  BACKSPACE_PRESSED,
  TAB_PRESSED,
  SPACE_PRESSED,
  EXCLAMATION_MARK_PRESSED,
  DOUBLE_QUOTES_PRESSED,
  HASH_PRESSED,
  DOLLAR_SIGN_PRESSED,
  PERCENTAGE_SIGN_PRESSED,
  AMPERSAND_PRESSED,
  SINGLE_QUOTE_PRESSED,
  LEFT_PARENTHESIS_PRESSED,
  RIGHT_PARENTHESIS_PRESSED,
  ASTERISK_PRESSED,
  PLUS_SIGN_PRESSED,
  COMA_PRESSED,
  MINUS_PRESSED,
  PERIOD_PRESSED,
  SLASH_PRESSED,
  KEY_0_PRESSED,
  KEY_1_PRESSED,
  KEY_2_PRESSED,
  KEY_3_PRESSED,
  KEY_4_PRESSED,
  KEY_5_PRESSED,
  KEY_6_PRESSED,
  KEY_7_PRESSED,
  KEY_8_PRESSED,
  KEY_9_PRESSED,
  COLON_PRESSED,
  SEMICOLON_PRESSED,
  LESS_THAN_SIGN_PRESSED,
  EQUALS_SIGN_PRESSED,
  MORE_THAN_SIGN_PRESSED,
  QUESTION_MARK_PRESSED,
  AT_PRESSED,
  LEFT_SQUARE_BRACKET_PRESSED,
  BACKSLASH_PRESSED,
  RIGHT_SQUARE_BRACKET_PRESSED,
  CIRCUMFLEX_PRESSED,
  UNDERSCORE_PRESSED,
  TICK_PRESSED,
  a_PRESSED,
  b_PRESSED,
  c_PRESSED,
  d_PRESSED,
  e_PRESSED,
  f_PRESSED,
  g_PRESSED,
  h_PRESSED,
  i_PRESSED,
  j_PRESSED,
  k_PRESSED,
  l_PRESSED,
  m_PRESSED,
  n_PRESSED,
  o_PRESSED,
  p_PRESSED,
  q_PRESSED,
  r_PRESSED,
  s_PRESSED,
  t_PRESSED,
  u_PRESSED,
  v_PRESSED,
  w_PRESSED,
  x_PRESSED,
  y_PRESSED,
  z_PRESSED,
  LEFT_BRACKET_PRESSED,
  PIPE_PRESSED,
  RIGHT_BRACKET_PRESSED,
  TILDE_PRESSED,
  DEL_PRESSED,
  // !KEYBOARD_KEYS
  LMB_PRESSED,
  RMB_PRESSED,

  // CONTACT
  ENTITY_CONTACT,
  // !CONTACT
  ENTITY_REMOVE,

  QUIT,
  NEXT_LEVEL
};
