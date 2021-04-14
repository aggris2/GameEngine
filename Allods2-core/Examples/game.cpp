#include "../src/allods2.h"

using namespace Allods2;
using namespace graphics;
using namespace sound;

class Game : public A2 {
private:
	Window* window;
	Layer* layer;
	Label* fps;
	Sprite* sprite;
	Shader* shader;
	Ref<Texture*> tiletexture;
public:
	Game() {

	}
	~Game() {
		delete layer;
	}
	
	void init() override {
		window = createWindow("Test Game", 1366, 760);
		int ww = window->getWidth();
		int wh = window->getHeight();
		float ortow1 = (ww / 2) - ww;
		float ortow2 = (ww / 2);
		float ortoh1 = (wh / 2) - wh;
		float ortoh2 = (wh / 2);

		
		Texture* textures[] = {
			new Texture("tiles.png"),
			//new Texture("MyChar_a.png") 
		};
		
		FontManager::get()->setScale(window->getWidth() / 800.0f, window->getHeight() / 450.0f);
		shader = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
		layer = new Layer(new BatchRenderer2D(), shader, maths::mat4::orthographic(ortow1, ortow2, ortoh1, ortoh2, -1.0f, 1.0f));

		
		

		layer->add(new Sprite(ortow1, ortoh1, textures[0]));
		
		sprite = new Sprite(0, 0, new Texture("MyChar_a.png"));
		layer->add(sprite);
		sprite = new Sprite(0, 0, new Texture("MyChar_a.png"));
		layer->add(sprite);
		

		fps = new Label("", ortow1 + 10, ortoh2 - 30, 0xffffffff);
		layer->add(fps);

		SoundManager::Add(new Sound("Testsound", "test.ogg"));
		SoundManager::Add(new Sound("Steam", "steam.wav"));
		SoundManager::Add(new Sound("credit", "credit.wav"));
	}

	void tick() override {
		fps->text = std::to_string(getFPS()) + " fps";
		std::cout << getUPS() << " ups, " << getFPS() << " fps" << std::endl;
	}
	
	void update() override {
		float speed = 4.0f;
		if (window->IsKeyPressed(GLFW_KEY_UP))
			sprite->position.y += speed;
		else if (window->IsKeyPressed(GLFW_KEY_DOWN))
		 	sprite->position.y -= speed;
		if (window->IsKeyPressed(GLFW_KEY_LEFT))
		 	sprite->position.x -= speed;
		else if (window->IsKeyPressed(GLFW_KEY_RIGHT))
			sprite->position.x += speed;



		double x, y;
		maths::vec2 mouse = window->GetMousePosition();
		shader->setUniform2f("light_pos", maths::vec2((float)(mouse.x * 32.0f / window->getWidth() - 16.0f), (float)(9.0f - mouse.y * 18.0f / window->getHeight())));

	}

	void render() override {		
		layer->render();
	}
	
	};


int main() {

	Game game;
	game.start();

	return 0;
}