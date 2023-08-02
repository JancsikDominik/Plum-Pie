#pragma once

#include <glew.h>

#include "Core/Texture.hpp"

namespace Plum
{

	class GLTexture final : public Texture
	{
	public:
        GLTexture();
        GLTexture(TextureTarget t);
        // TODO: GLTexture(const std::filesystem::path& pathToTexture, TextureTarget t, TextureFormat format);

        ~GLTexture();

        
        bool Bind(size_t textureSlot) override;
        void SetData(unsigned char* data, int width, int height) override;

        void SetMinFilter(TextureFilter filter) override;
        void SetMagFilter(TextureFilter filter) override;

        void SetWrapS(TextureWrapping tw) override;
        void SetWrapT(TextureWrapping tw) override;

        void GenerateMipMaps() override;

        size_t GetWidth() const override;
        size_t GetHeight() const override;

        TextureFormat GetFormat() const override;
        void SetFormat(TextureFormat format) override;

        Color GetTexelColor(uint32_t u, uint32_t v) const override;

    private:
        GLenum GetOpenGLTextureTarget();
        GLenum GetOpenGLTextureFormat();

        void CreateTexture();
        void ReleaseTexture();

        GLuint m_textureID = 0;
        TextureFormat m_format = TextureFormat::Undefined;
	};
}

