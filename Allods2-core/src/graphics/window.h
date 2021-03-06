#pragma once
#include <iostream>
#include <glew.h>
#include <GLFW3.h>
#include "font_manager.h"
#include "../audio/sound_manager.h"
#include "texture_manager.h"
#include "../maths/vec2.h"

namespace Allods2 { namespace graphics {

#define MAX_KEYS	1024
#define MAX_BUTTONS 32

	class Window {
	
	private:
		
		const char* m_Title;
		int m_Width, m_Height;
		GLFWwindow* m_Window;
		bool m_Closed;

		bool m_Keys[MAX_KEYS];
		bool m_KeyState[MAX_KEYS];
		bool m_KeyTyped[MAX_KEYS];
		bool m_MouseButtons[MAX_BUTTONS];
		bool m_MouseState[MAX_BUTTONS];
		bool m_MouseClicked[MAX_BUTTONS];
		maths::vec2 m_MousePosition;

	public:
		Window(const char *name, int width, int height);
		~Window();
		void clear() const;
		void update();
		void updateInput();
		bool closed() const;

		inline int getWidth() const { return m_Width; }
		inline int getHeight() const { return m_Height; }
		
		

		bool IsKeyPressed(unsigned int keycode) const;
		bool IsKeyTyped(unsigned int keycode) const;
		bool IsMouseButtonPressed(unsigned int button) const;
		bool IsMouseButtonClicked(unsigned int button) const;
		const maths::vec2& GetMousePosition() const;
		

	private:
		bool init();
		friend static void window_resize(GLFWwindow* window, int width, int height);
		friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		
	};

	}

}