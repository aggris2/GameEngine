#include "window.h"

namespace Allods2 {namespace graphics {

	
	void window_resize(GLFWwindow* window, int width, int height)
	{
		
		glViewport(0, 0, width, height);
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Width = width;
		win->m_Height = height;
	}

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_Keys[key] = action != GLFW_RELEASE;
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MouseButtons[button] = action != GLFW_RELEASE;
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Window* win = (Window*)glfwGetWindowUserPointer(window);
		win->m_MousePosition.x = (float)xpos;
		win->m_MousePosition.y = (float)ypos;
	}

	Window::Window(const char* title, int width, int height) {
		m_Title = title;
		m_Width = width;
		m_Height = height;

		if (!init()) {
			glfwTerminate();
		}

		FontManager::add(new Font("Arial", "arial.ttf", 32));

		sound::SoundManager::Init();

			for (int i = 0; i < MAX_KEYS; i++) {
				m_Keys[i] = false;
				m_KeyState[i] = false;
				m_KeyTyped[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++) {
				m_MouseButtons[i] = false;
				m_MouseState[i] = false;
				m_MouseClicked[i] = false;
			}

		
	}

	Window::~Window() {
		FontManager::clean();
		TextureManager::clean();
		sound::SoundManager::Clean();
		glfwTerminate();
	}

	bool Window::init() {

		if (!glfwInit()){
			std::cout << "Failed to initialize GLFW" << std::endl;
			return false;
		}
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, glfwGetPrimaryMonitor(), NULL);
		if (!m_Window) {
			std::cout << "Failed to create GLFW window!" << std::endl;
			return false;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetFramebufferSizeCallback(m_Window, window_resize);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetCursorPosCallback(m_Window, cursor_position_callback);
		glfwSwapInterval(0.0);


		if (glewInit() != GLEW_OK) {
			std::cout << "Could not initialize GLEW!" << std::endl;
			return false;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glfwSetKeyCallback(m_Window, key_callback);
		
		std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
		return true;

		
		}

	void Window::clear() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update() {

		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
			std::cout << "OpenGL Error: " << error << std::endl;

		glfwSwapBuffers(m_Window);
		glfwPollEvents();

		sound::SoundManager::Update();
	}

	void Window::updateInput()
	{
		for (int i = 0; i < MAX_KEYS; i++)
			m_KeyTyped[i] = m_Keys[i] && !m_KeyState[i];

		for (int i = 0; i < MAX_BUTTONS; i++)
			m_MouseClicked[i] = m_MouseButtons[i] && !m_MouseState[i];

		memcpy(m_KeyState, m_Keys, MAX_KEYS);
		memcpy(m_MouseState, m_MouseButtons, MAX_BUTTONS);
	}

	bool Window::closed() const {
		return glfwWindowShouldClose(m_Window) == 1;
	}

		bool Window::IsKeyPressed(unsigned int keycode) const {
			
			//TODO: LOG THIS!!!
			if (keycode >= MAX_KEYS)
				return false;

			return m_Keys[keycode];
		}

		bool Window::IsKeyTyped(unsigned int keycode) const {

			//TODO: LOG THIS!!!
			if (keycode >= MAX_KEYS)
				return false;

			return m_KeyTyped[keycode];
		}

		bool Window::IsMouseButtonPressed(unsigned int button) const {

			//TODO: LOG THIS!!!
			if (button >= MAX_BUTTONS)
				return false;

			return m_MouseButtons[button];
		}

		bool Window::IsMouseButtonClicked(unsigned int button) const {

			//TODO: LOG THIS!!!
			if (button >= MAX_BUTTONS)
				return false;

			return m_MouseClicked[button];
		}

		const maths::vec2& Window::GetMousePosition() const {
			return m_MousePosition;
		}

}  }
	