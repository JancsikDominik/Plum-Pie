#include "GLTexture.hpp"
#include "Debugging/Debug.hpp"

namespace Plum
{
    bool GLTexture::Bind(size_t textureSlot)
    {
        constexpr GLenum openglTextureSlot0 = GL_TEXTURE0;
        if (textureSlot > GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1)
            return false;

        GL_CALL(glBindTexture(GetOpenGLTextureTarget(), m_textureID));
        GL_CALL(glActiveTexture(openglTextureSlot0 + textureSlot));
        return true;
    }

    GLTexture::GLTexture(TextureTarget t)
        : Texture(t)
    {
        CreateTexture();
    }

    GLTexture::GLTexture()
    {
        CreateTexture();
    }

    GLTexture::~GLTexture()
    {
        ReleaseTexture();
    }

    void GLTexture::SetData(unsigned char* data, int width, int height)
    {
    }

    void GLTexture::SetMinFilter(TextureFilter filter)
    {
        switch (filter)
        {
        case TextureFilter::NearestMipMapNearest:
            GL_CALL(glTexParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));
            break;
        case TextureFilter::LinearMipMapNearest:
            GL_CALL(glTexParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST));
            break;
        case TextureFilter::NearestMipMapLinear:
            GL_CALL(glTexParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR));
            break;
        case TextureFilter::LinearMipMapLinear:
            GL_CALL(glTexParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
            break;
        case TextureFilter::Nearest:
            GL_CALL(glTexParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
            break;
        case TextureFilter::Linear:
            GL_CALL(glTexParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
            break;
        default:
            Debug::Console::LogError("Unsupported texture filter type for min filter: %d", filter);
        }
    }

    void GLTexture::SetMagFilter(TextureFilter filter)
    {
        switch (filter)
        {
        case TextureFilter::Nearest:
            GL_CALL(glTexParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
            break;
        case TextureFilter::Linear:
            GL_CALL(glTexParameteri(m_textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
            break;
        default:
            Debug::Console::LogError("Unsupported texture filter type for mag filter: %d", filter);
        }
    }

    void GLTexture::SetWrapS(TextureWrapping tw)
    {
        switch (tw)
        {
        case TextureWrapping::Repeat:
            GL_CALL(glTexParameteri(GetOpenGLTextureTarget(), GL_TEXTURE_WRAP_S, GL_REPEAT));
            break;
        case TextureWrapping::MirroredRepeat:
            GL_CALL(glTexParameteri(GetOpenGLTextureTarget(), GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT));
            break;
        case TextureWrapping::ClampToEdge:
            GL_CALL(glTexParameteri(GetOpenGLTextureTarget(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
            break;
        case TextureWrapping::ClampToBorder:
            GL_CALL(glTexParameteri(GetOpenGLTextureTarget(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
            break;
        }
    }

    void GLTexture::SetWrapT(TextureWrapping tw)
    {
        switch (tw)
        {
        case TextureWrapping::Repeat:
            GL_CALL(glTexParameteri(GetOpenGLTextureTarget(), GL_TEXTURE_WRAP_T, GL_REPEAT));
            break;
        case TextureWrapping::MirroredRepeat:
            GL_CALL(glTexParameteri(GetOpenGLTextureTarget(), GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT));
            break;
        case TextureWrapping::ClampToEdge:
            GL_CALL(glTexParameteri(GetOpenGLTextureTarget(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
            break;
        case TextureWrapping::ClampToBorder:
            GL_CALL(glTexParameteri(GetOpenGLTextureTarget(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
            break;
        }
    }

    void GLTexture::GenerateMipMaps()
    {
        GL_CALL(glGenerateTextureMipmap(m_textureID));
    }

    size_t GLTexture::GetWidth() const
    {
        // TODO: when done with set data stuff
        return size_t();
    }

    size_t GLTexture::GetHeight() const
    {
        // TODO: when done with set data stuff
        return size_t();
    }

    TextureFormat GLTexture::GetFormat() const
    {
        return m_format;
    }

    void GLTexture::SetFormat(TextureFormat format)
    {
        m_format = format;
    }

    Color GLTexture::GetTexelColor(uint32_t u, uint32_t v) const
    {
        // TODO: when done with set data stuff
        return Color();
    }

    GLenum GLTexture::GetOpenGLTextureTarget()
    {
        switch (m_textureTarget)
        {
        case TextureTarget::Tex1D:
            return GL_TEXTURE_1D;
        case TextureTarget::Tex2D:
            return GL_TEXTURE_2D;
        case TextureTarget::Tex3D:
            return GL_TEXTURE_3D;
        case TextureTarget::Tex1DArray:
            return GL_TEXTURE_1D_ARRAY;
        case TextureTarget::Tex2DArray:
            return GL_TEXTURE_2D_ARRAY;
        case TextureTarget::Rectangle:
            return GL_TEXTURE_RECTANGLE;
        case TextureTarget::CubeMap:
            return GL_TEXTURE_CUBE_MAP;
        case TextureTarget::CubeMapArray:
            return GL_TEXTURE_CUBE_MAP_ARRAY;
        case TextureTarget::Buffer:
            return GL_TEXTURE_BUFFER;
        case TextureTarget::Tex2DMultisample:
            return GL_TEXTURE_2D_MULTISAMPLE;
        case TextureTarget::Tex2DMultisampleArray:
            return GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
        default:
            return 0;
        }
    }

    GLenum GLTexture::GetOpenGLTextureFormat()
    {
        switch (m_format)
        {
        case TextureFormat::RGBA:
            return GL_RGBA;
        case TextureFormat::RGB:
            return GL_RGB;
        case TextureFormat::RG:
            return GL_RG;
        case TextureFormat::RED:
            return GL_RED;
        case TextureFormat::Undefined:
        default:
            return 0;
        }
    }

    void GLTexture::CreateTexture()
    {
        GL_CALL(glGenTextures(1, &m_textureID));
    }

    void GLTexture::ReleaseTexture()
    {
        GL_CALL(glBindTexture(m_textureID, 0));
        GL_CALL(glDeleteTextures(1, &m_textureID));
    }
}
