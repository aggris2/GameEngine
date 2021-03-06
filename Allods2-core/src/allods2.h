#pragma once
#include "graphics/window.h"
#include "../src/graphics/window.h"
#include "../src/graphics/layers/layer.h"
#include "../src/graphics/layers/group.h"
#include "graphics/batchrenderer2d.h"
#include "graphics/renderer2d.h"
#include "sprite.h"
#include "graphics/label.h"
#include "audio/sound.h"
#include "audio/sound_manager.h"
#include "graphics/texture_manager.h"


#include "maths/maths.h"
#include "utils/timer.h"

namespace Allods2 {

	class A2 {
	private:
		graphics::Window* m_Window;
		Timer* m_Timer;
		int m_FramesPerSecond, m_UpdatesPerSecond;
	protected:
		A2() : m_FramesPerSecond(0), m_UpdatesPerSecond(0) {

		}

		virtual ~A2() {
			delete m_Window;
			delete m_Timer;
		}

		graphics::Window* createWindow(const char* name, int width, int height) {
			m_Window = new graphics::Window(name, width, height);
			return m_Window;
		}

	public:
		void start() {
			init();
			run();
		}
	protected:
		//Runs once upon initialization
		virtual void init() = 0;
		//Runs once per second
		virtual void tick() {}
		//Runs once 60 times per second
		virtual void update() {}
		//Runs as fast as possible (unless vsync is enabled)
		virtual void render() = 0;

		const unsigned int getFPS() const {return m_FramesPerSecond;}
		const unsigned int getUPS() const { return m_UpdatesPerSecond; }
		


	private:
		void run() {

			m_Timer = new Timer();
			float timer = 0.0f;
			float updateTick = 1.0f / 60.0f;
			float updateTimer = 0.0f;
			m_Timer = new Timer();
			unsigned int frames = 0;
			unsigned int updates = 0;
			while (!m_Window->closed()) {

				m_Window->clear();
				if (m_Timer->elapsed() - updateTimer > updateTick) {
					m_Window->updateInput();
					update();
					updates++;
					updateTimer += updateTick;
				}


				frames++;
				render();
				m_Window->update();
				if (m_Timer->elapsed() - timer > 1.0f) {
					timer += 1.0f;
					m_FramesPerSecond = frames;
					m_UpdatesPerSecond = updates;
					frames = 0;
					updates = 0;
					tick();
				}





			}
		}

	};

}