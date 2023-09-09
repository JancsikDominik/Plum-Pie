#pragma once

#include <glew.h>

#include "Core/Texture.hpp"
#include "STBWrappers/Image.hpp"

namespace Plum
{

	class GLTexture final : public Texture
	{
	public:
        using Ref = std::shared_ptr<GLTexture>;

        GLTexture() = delete;
        GLTexture(TextureTarget t);
        GLTexture(Image image, TextureTarget t, TextureFormat format);
        GLTexture(const std::filesystem::path& pathToTexture, TextureTarget t, TextureFormat format);

        ~GLTexture();


        void szopjle()
        {
            const Image img("./texture.png", 4);

            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.GetWidth(), img.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.GetRawData());
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        void Bind() override;
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

