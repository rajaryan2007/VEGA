#pragma once

#include "VEGA/Core.h"

#include <string>


namespace VEGA {
	class Texture {
	public:
		virtual ~Texture() = default;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual void Bind(unsigned int slot = 0) const = 0;
		virtual void SetData(void* data, uint32_t size) = 0;

		/*static Texture* Create(const std::string& path);
		static Texture* Create(unsigned int width, unsigned int height);*/
	};

	class Texture2D : public Texture {
	 public:
		 static Ref<Texture2D> Create(const std::string& path);
		 static Ref<Texture2D> Create(unsigned int width, unsigned int height);
	};

}