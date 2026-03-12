#pragma once

namespace VEGA {

	using KeyCode = uint16_t;

	namespace Key
	{
		enum : KeyCode
		{
			/* Printable keys */
			Space = 32,
			Apostrophe = 39, /* ' */
			Comma = 44, /* , */
			Minus = 45, /* - */
			Period = 46, /* . */
			Slash = 47,

			D0 = 48,
			D1 = 49,
			D2 = 50,
			D3 = 51,
			D4 = 52,
			D5 = 53,
			D6 = 54,
			D7 = 55,
			D8 = 56,
			D9 = 57,

			Semicolon = 59, /* ; */
			Equal = 61, /* = */

			A = 65,
			B = 66,
			C = 67,
			D = 68,
			E = 69,
			F = 70,
			G = 71,
			H = 72,
			I = 73,
			J = 74,
			K = 75,
			L = 76,
			M = 77,
			N = 78,
			O = 79,
			P = 80,
			Q = 81,
			R = 82,
			S = 83,
			T = 84,
			U = 85,
			V = 86,
			W = 87,
			X = 88,
			Y = 89,
			Z = 90,

			LeftBracket = 91,  /* [ */
			Backslash = 92,  /* \ */
			RightBracket = 93,  /* ] */
			GraveAccent = 96,  /* ` */

			/* Function keys */

			Escape = 256,
			Enter = 257,
			Tab = 258,
			Backspace = 259,
			Insert = 260,
			Delete = 261,
			Right = 262,
			Left = 263,
			Down = 264,
			Up = 265,
			PageUp = 266,
			PageDown = 267,
			Home = 268,
			End = 269,
			CapsLock = 280,
			ScrollLock = 281,
			NumLock = 282,
			PrintScreen = 283,
			Pause = 284,

			F1 = 290,
			F2 = 291,
			F3 = 292,
			F4 = 293,
			F5 = 294,
			F6 = 295,
			F7 = 296,
			F8 = 297,
			F9 = 298,
			F10 = 299,
			F11 = 300,
			F12 = 301,
			F13 = 302,
			F14 = 303,
			F15 = 304,
			F16 = 305,
			F17 = 306,
			F18 = 307,
			F19 = 308,
			F20 = 309,
			F21 = 310,
			F22 = 311,
			F23 = 312,
			F24 = 313,
			F25 = 314,

			/* Keypad */

			KP0 = 320,
			KP1 = 321,
			KP2 = 322,
			KP3 = 323,
			KP4 = 324,
			KP5 = 325,
			KP6 = 326,
			KP7 = 327,
			KP8 = 328,
			KP9 = 329,
			KPDecimal = 330,
			KPDivide = 331,
			KPMultiply = 332,
			KPSubtract = 333,
			KPAdd = 334,
			KPEnter = 335,
			KPEqual = 336,

			/* Modifiers */

			LeftShift = 340,
			LeftControl = 341,
			LeftAlt = 342,
			LeftSuper = 343,
			RightShift = 344,
			RightControl = 345,
			RightAlt = 346,
			RightSuper = 347,
			Menu = 348
		};
	}
}

/* Macro helpers */

#define VG_KEY_SPACE           ::VEGA::Key::Space
#define VG_KEY_APOSTROPHE      ::VEGA::Key::Apostrophe
#define VG_KEY_COMMA           ::VEGA::Key::Comma
#define VG_KEY_MINUS           ::VEGA::Key::Minus
#define VG_KEY_PERIOD          ::VEGA::Key::Period
#define VG_KEY_SLASH           ::VEGA::Key::Slash
#define VG_KEY_0               ::VEGA::Key::D0
#define VG_KEY_1               ::VEGA::Key::D1
#define VG_KEY_2               ::VEGA::Key::D2
#define VG_KEY_3               ::VEGA::Key::D3
#define VG_KEY_4               ::VEGA::Key::D4
#define VG_KEY_5               ::VEGA::Key::D5
#define VG_KEY_6               ::VEGA::Key::D6
#define VG_KEY_7               ::VEGA::Key::D7
#define VG_KEY_8               ::VEGA::Key::D8
#define VG_KEY_9               ::VEGA::Key::D9

#define VG_KEY_A               ::VEGA::Key::A
#define VG_KEY_B               ::VEGA::Key::B
#define VG_KEY_C               ::VEGA::Key::C
#define VG_KEY_D               ::VEGA::Key::D
#define VG_KEY_E               ::VEGA::Key::E
#define VG_KEY_F               ::VEGA::Key::F
#define VG_KEY_G               ::VEGA::Key::G
#define VG_KEY_H               ::VEGA::Key::H
#define VG_KEY_I               ::VEGA::Key::I
#define VG_KEY_J               ::VEGA::Key::J
#define VG_KEY_K               ::VEGA::Key::K
#define VG_KEY_L               ::VEGA::Key::L
#define VG_KEY_M               ::VEGA::Key::M
#define VG_KEY_N               ::VEGA::Key::N
#define VG_KEY_O               ::VEGA::Key::O
#define VG_KEY_P               ::VEGA::Key::P
#define VG_KEY_Q               ::VEGA::Key::Q
#define VG_KEY_R               ::VEGA::Key::R
#define VG_KEY_S               ::VEGA::Key::S
#define VG_KEY_T               ::VEGA::Key::T
#define VG_KEY_U               ::VEGA::Key::U
#define VG_KEY_V               ::VEGA::Key::V
#define VG_KEY_W               ::VEGA::Key::W
#define VG_KEY_X               ::VEGA::Key::X
#define VG_KEY_Y               ::VEGA::Key::Y
#define VG_KEY_Z               ::VEGA::Key::Z

#define VG_KEY_ESCAPE          ::VEGA::Key::Escape
#define VG_KEY_ENTER           ::VEGA::Key::Enter
#define VG_KEY_TAB             ::VEGA::Key::Tab
#define VG_KEY_BACKSPACE       ::VEGA::Key::Backspace
#define VG_KEY_INSERT          ::VEGA::Key::Insert
#define VG_KEY_DELETE          ::VEGA::Key::Delete

#define VG_KEY_RIGHT           ::VEGA::Key::Right
#define VG_KEY_LEFT            ::VEGA::Key::Left
#define VG_KEY_DOWN            ::VEGA::Key::Down
#define VG_KEY_UP              ::VEGA::Key::Up

#define VG_KEY_LEFT_SHIFT      ::VEGA::Key::LeftShift
#define VG_KEY_LEFT_CONTROL    ::VEGA::Key::LeftControl
#define VG_KEY_LEFT_ALT        ::VEGA::Key::LeftAlt
#define VG_KEY_LEFT_SUPER      ::VEGA::Key::LeftSuper
#define VG_KEY_RIGHT_SHIFT     ::VEGA::Key::RightShift
#define VG_KEY_RIGHT_CONTROL   ::VEGA::Key::RightControl
#define VG_KEY_RIGHT_ALT       ::VEGA::Key::RightAlt
#define VG_KEY_RIGHT_SUPER     ::VEGA::Key::RightSuper