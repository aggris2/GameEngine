#pragma once

#include <cstddef>
#include "buffers/indexbuffer.h"
#include "renderer2d.h"
#include "renderable2d.h"

namespace Allods2 {namespace graphics {

#define RENDERER_MAX_SPRITES     60000
#define RENDERER_VERTEX_SIZE     sizeof(VertexData)
#define RENDERER_SPRITE_SIZE     RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE     RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE    RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES    16

#define SHADER_VERTEX_INDEX     0
#define SHADER_UV_INDEX         1
#define SHADER_TID_INDEX        2
#define SHADER_COLOR_INDEX      3
	
		
	class BatchRenderer2D : public Renderer2D {
	private:
		GLuint m_VAO;
		GLuint m_VBO;
		IndexBuffer* m_IBO;
		GLsizei m_IndexCount;
		VertexData* m_Buffer;

		std::vector<GLuint> m_TextureSlots;
		
		
	public:
		BatchRenderer2D();
		~BatchRenderer2D();

		

		void begin() override;
		void submit(const Renderable2D* renderable) override;
		static void subTexture(const glm::mat4& transform, const Ref<Texture>& texture, float tilingFactor, const glm::vec4& tintColor);
		void drawString(const std::string& text, const maths::vec3& position, const Font& font, unsigned int color) override;
		void end() override;
		void flush() override;
	private:
		void init();
		};
	
	
	
} }
