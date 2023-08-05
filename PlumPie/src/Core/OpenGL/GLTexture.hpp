#pragma once

#include <glew.h>

#include "Core/Texture.hpp"
#include "STBWrappers/Image.hpp"

namespace Plum
{

	class GLTexture final : public Texture
	{
	public:
        GLTexture();
        GLTexture(TextureTarget t);
        GLTexture(Image image, TextureTarget t, TextureFormat format);
        GLTexture(const std::filesystem::path& pathToTexture, TextureTarget t, TextureFormat format);

        ~GLTexture();

        
        bool Bind() override;
        void Unbind();
        void Use(size_t textureSlot);

        void SetData(const Image& img) override;

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

        bool Activate(size_t textureSlot);

        GLuint m_textureID = 0;
        TextureFormat m_format = TextureFormat::Undefined;
	};
}

