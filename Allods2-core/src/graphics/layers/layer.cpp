#include "layer.h"

namespace Allods2 {namespace graphics {

	Layer::Layer(Renderer2D* renderer, Shader* shader, maths::mat4 projectionMatrix) 
	: m_Renderer(renderer), m_Shader(shader), m_ProjectionMatrix(projectionMatrix){
		
		m_Shader->enable();
		m_Shader->setUniformMat4("pr_matrix", m_ProjectionMatrix);

		GLint texIDs[]{
		0, 1, 2, 3, 4, 5, 6, 7, 8,
		9, 10, 11, 12, 13, 14, 15
		};

		m_Shader->setUniform1iv("textures", texIDs, 16);
		m_Shader->disable();
	}

	Layer::~Layer() {
		delete m_Shader;
		delete m_Renderer;

		for (unsigned int i = 0; i < m_Renderables.size(); i++)
			delete m_Renderables[i];
	}

	void Layer::add(Renderable2D* renderable) {
		m_Renderables.push_back(renderable);
	}

	void Layer::render() {
		m_Shader->enable();
		m_Renderer->begin();
		
		for (const Renderable2D* renderable : m_Renderables) { 
			renderable->submit(m_Renderer);
		}

		//m_Renderer->drawString("", maths::vec3(0, 0, 0), *m_Font, 0xffffffff);
		
		m_Renderer->end();

		m_Renderer->flush();
	
	}

} }