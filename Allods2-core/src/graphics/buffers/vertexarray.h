#pragma once
#include <glew.h>
#include <vector>
#include "buffer.h"
#include <cstddef>
#include <memory>



namespace Allods2 {namespace graphics {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	class VertexArray {
	private:
		GLuint m_ArrayID;
		std::vector<Buffer*> m_Buffer;
	public:
		VertexArray();
		~VertexArray();
		void addBuffer(Buffer* buffer, GLuint index);
		void bind() const;
		void unbind() const;
	};




} }