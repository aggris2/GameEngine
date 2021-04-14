
#if 0

#include "src/graphics/window.h"
#include <glew.h>
#include "src/graphics/shader.h"
#include "src/maths/maths.h"
#include "src/utils/timer.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/IndexBuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/renderer2D.h"
#include "src/graphics/batchrenderer2d.h"

#include "src/sprite.h"

#include "src/graphics/layers/group.h"
#include "src/graphics/label.h"
#include "src/graphics/layers/tilelayer.h"
#include "src/graphics/texture.h"
#include "src/utils/imageload.h"

#include <gorilla/ga.h>
#include "src/graphics/font_manager.h"
#include "src/audio/sound_manager.h"


int main() {

	using namespace Allods2;
	using namespace graphics;
	using namespace maths;
	using namespace sound;

	Window window("Allods2", 960, 540);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	
	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	shader.enable();
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
	
	TileLayer layer(&shader);
	Texture* textures[] = {
		new Texture("test.png"),
		new Texture("MyChar_a.png")
	};
	for (float y = -9.0f; y < 9.0f; y++) {
		for (float x = -16.0; x < 16.0f; x++) {
			//layer.add(new Sprite(x, y, 0.9f, 0.9f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			int r = rand() % 256;
			int col = 0xffff00 << 8 | r;
			if(rand() % 4 == 0)
				layer.add(new Sprite(x, y, 0.9f, 0.9f, col));
			else
			layer.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 2]));
		}
	}
	
	FontManager::add(new Font("Roboto", "roboto.ttf", 32));
	Group* g = new Group(maths::mat4::translation(maths::vec3(-15.8f, 7.2f, 0.0f)));
	Label* fps = new Label("",  0.4f, 0.4f, "Roboto", 0xffffffff);
	g->add(new Sprite(0, 0, 5, 1.5f, 0x505050DD));
	g->add(fps);

	layer.add(g);

	
	shader.enable();
	shader.setUniformMat4("pr_matrix", maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
	
	SoundManager::Add(new Sound("credit", "test.ogg"));
	SoundManager::Add(new Sound("Steam", "steam.wav"));
	
	

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	float t = 0.0f;
	float gain = 0.5f;
	SoundManager::Get("credit")->Play();
	SoundManager::Get("credit")->SetGain(gain);

	

	while (!window.closed()) {
		t += 0.01f;
		window.clear();
		double x, y;
		
	    shader.enable();
		//maths::vec2 mouse = window->GetMousePosition();
		//shader.setUniform2f("light_pos", vec2((float)(mouse.x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));
		layer.render();
		
		const std::vector<Renderable2D*>& rs = layer.getRenderables();
		for (int i = 0; i < rs.size(); i++) {
			float c = sin(t) / 2 + 0.5f;
			rs[i]->setColor(maths::vec4(c, 0, 1, 1));
		}
		
		if (window.IsKeyTyped(GLFW_KEY_P))
			SoundManager::Get("credit")->Play();

		if (window.IsKeyTyped(GLFW_KEY_L))
			SoundManager::Get("credit")->Loop();

		if (window.IsKeyTyped(GLFW_KEY_Z))
			SoundManager::Get("credit")->Pause();

		if (window.IsKeyTyped(GLFW_KEY_R))
			SoundManager::Get("credit")->Resume();

		if (window.IsKeyTyped(GLFW_KEY_S))
			SoundManager::Get("credit")->Stop();
		

		if (window.IsKeyTyped(GLFW_KEY_UP)) {
			gain += 0.05f;
			SoundManager::Get("credit")->SetGain(gain);
		}
		
		if (window.IsKeyTyped(GLFW_KEY_DOWN)) {
			gain -= 0.05f;
			SoundManager::Get("credit")->SetGain(gain);
		}

		
		window.update();
		frames++;
		if (time.elapsed() - timer > 1.0f) {
			timer += 1.0f;
			fps->text = std::to_string(frames) + " fps";
			printf("%d fps\n", frames);
			frames = 0;
		}
		
	}
	for(int i = 0; i < 2; i++)
		delete textures[i];
	
	return 0;
}

#endif