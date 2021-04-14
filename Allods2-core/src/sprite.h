#pragma once
#include "graphics/renderable2d.h"


namespace Allods2 {namespace graphics {

	class Sprite : public Renderable2D {
	public:
		maths::vec3& position;
		maths::vec2& size;

	public:
		Sprite(Texture* texture);
		Sprite(float x, float y, Texture* texture);
		Sprite(float x, float y, float width, float height, unsigned int color);
		Sprite(float x, float y, float width, float height, maths::vec4 color);
		Sprite(float x, float y, float width, float height, Texture* texture);

		void setUV(std::vector<maths::vec2> uv);
	};

} }