#pragma once
#include "layer.h"
#include "../batchrenderer2d.h"


namespace Allods2 {namespace graphics {

		class TileLayer : public Layer
		{
		public:
			TileLayer(Shader* shader);
			~TileLayer();
		};


} }