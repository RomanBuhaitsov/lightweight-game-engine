#include <unordered_map>

#include "../message_bus/message.h"
#include <SDL2/SDL.h>

const std::unordered_map<int, MessageEvent> KEY_EVENT_MAP = {
    {SDLK_UP, MessageEvent::UP_PRESSED},
    {SDLK_DOWN, MessageEvent::DOWN_PRESSED},
    {SDLK_LEFT, MessageEvent::LEFT_PRESSED},
    {SDLK_RIGHT, MessageEvent::RIGHT_PRESSED},
    {SDLK_RETURN, MessageEvent::RETURN_PRESSED},
    {SDLK_ESCAPE, MessageEvent::ESCAPE_PRESSED},
    {SDLK_BACKSPACE, MessageEvent::BACKSPACE_PRESSED},
    {SDLK_TAB, MessageEvent::TAB_PRESSED},
    {SDLK_SPACE, MessageEvent::SPACE_PRESSED},
    {SDLK_EXCLAIM, MessageEvent::EXCLAMATION_MARK_PRESSED},
    {SDLK_QUOTEDBL, MessageEvent::DOUBLE_QUOTES_PRESSED},
    {SDLK_HASH, MessageEvent::HASH_PRESSED},
    {SDLK_PERCENT, MessageEvent::PERCENTAGE_SIGN_PRESSED},
    {SDLK_DOLLAR, MessageEvent::DOLLAR_SIGN_PRESSED},
    {SDLK_AMPERSAND, MessageEvent::AMPERSAND_PRESSED},
    {SDLK_QUOTE, MessageEvent::SINGLE_QUOTE_PRESSED},
    {SDLK_LEFTPAREN, MessageEvent::LEFT_PARENTHESIS_PRESSED},
    {SDLK_RIGHTPAREN, MessageEvent::RIGHT_PARENTHESIS_PRESSED},
    {SDLK_ASTERISK, MessageEvent::ASTERISK_PRESSED},
    {SDLK_PLUS, MessageEvent::PLUS_SIGN_PRESSED},
    {SDLK_COMMA, MessageEvent::COMA_PRESSED},
    {SDLK_MINUS, MessageEvent::MINUS_PRESSED},
    {SDLK_PERIOD, MessageEvent::PERIOD_PRESSED},
    {SDLK_SLASH, MessageEvent::SLASH_PRESSED},
    {SDLK_0, MessageEvent::KEY_0_PRESSED},
    {SDLK_1, MessageEvent::KEY_1_PRESSED},
    {SDLK_2, MessageEvent::KEY_2_PRESSED},
    {SDLK_3, MessageEvent::KEY_3_PRESSED},
    {SDLK_4, MessageEvent::KEY_4_PRESSED},
    {SDLK_5, MessageEvent::KEY_5_PRESSED},
    {SDLK_6, MessageEvent::KEY_6_PRESSED},
    {SDLK_7, MessageEvent::KEY_7_PRESSED},
    {SDLK_8, MessageEvent::KEY_8_PRESSED},
    {SDLK_9, MessageEvent::KEY_9_PRESSED},
    {SDLK_COLON, MessageEvent::COLON_PRESSED},
    {SDLK_SEMICOLON, MessageEvent::SEMICOLON_PRESSED},
    {SDLK_LESS, MessageEvent::LESS_THAN_SIGN_PRESSED},
    {SDLK_EQUALS, MessageEvent::EQUALS_SIGN_PRESSED},
    {SDLK_GREATER, MessageEvent::MORE_THAN_SIGN_PRESSED},
    {SDLK_QUESTION, MessageEvent::QUESTION_MARK_PRESSED},
    {SDLK_AT, MessageEvent::AT_PRESSED},
    {SDLK_LEFTBRACKET, MessageEvent::LEFT_SQUARE_BRACKET_PRESSED},
    {SDLK_BACKSLASH, MessageEvent::BACKSLASH_PRESSED},
    {SDLK_RIGHTBRACKET, MessageEvent::RIGHT_SQUARE_BRACKET_PRESSED},
    {SDLK_CARET, MessageEvent::CIRCUMFLEX_PRESSED},
    {SDLK_UNDERSCORE, MessageEvent::UNDERSCORE_PRESSED},
    {SDLK_BACKQUOTE, MessageEvent::TICK_PRESSED},
    {SDLK_a, MessageEvent::a_PRESSED},
    {SDLK_b, MessageEvent::b_PRESSED},
    {SDLK_c, MessageEvent::c_PRESSED},
    {SDLK_d, MessageEvent::d_PRESSED},
    {SDLK_e, MessageEvent::e_PRESSED},
    {SDLK_f, MessageEvent::f_PRESSED},
    {SDLK_g, MessageEvent::g_PRESSED},
    {SDLK_h, MessageEvent::h_PRESSED},
    {SDLK_i, MessageEvent::i_PRESSED},
    {SDLK_j, MessageEvent::j_PRESSED},
    {SDLK_k, MessageEvent::k_PRESSED},
    {SDLK_l, MessageEvent::l_PRESSED},
    {SDLK_m, MessageEvent::m_PRESSED},
    {SDLK_n, MessageEvent::n_PRESSED},
    {SDLK_o, MessageEvent::o_PRESSED},
    {SDLK_p, MessageEvent::p_PRESSED},
    {SDLK_q, MessageEvent::q_PRESSED},
    {SDLK_r, MessageEvent::r_PRESSED},
    {SDLK_s, MessageEvent::s_PRESSED},
    {SDLK_t, MessageEvent::t_PRESSED},
    {SDLK_u, MessageEvent::u_PRESSED},
    {SDLK_v, MessageEvent::v_PRESSED},
    {SDLK_w, MessageEvent::w_PRESSED},
    {SDLK_x, MessageEvent::x_PRESSED},
    {SDLK_y, MessageEvent::y_PRESSED},
    {SDLK_z, MessageEvent::z_PRESSED},
    {SDL_BUTTON_LEFT, MessageEvent::LMB_PRESSED},
    {SDL_BUTTON_RIGHT, MessageEvent::RMB_PRESSED},
};
