#pragma once
#include <Graphics/Vertex.hpp>

namespace Plum
{
    enum class TextureFilter
    {
        NearestMipMapNearest,
        LinearMipMapNearest,
        NearestMipMapLinear,
        LinearMipMapLinear,
        Nearest,
        Linear
    };

    enum class TextureWrapping
    {
        Repeat,
        MirroredRepeat,
        ClampToEdge,
        ClampToBorder
    };

    enum class TextureFormat
    {
        Undefined,
        RGB,
        RGBA,
        RG, 
        RED
        // TODO: R8, R16 ... (Sized Internal Format)
    };

    enum class TextureTarget
    {
        Tex1D,
        Tex2D,
        Tex3D,
        Tex1DArray,
        Tex2DArray,
        Rectangle,
        CubeMap,
        CubeMapArray,
        Buffer,
        Tex2DMultisample,
        Tex2DMultisampleArray
    };

    class Texture 
    {
    public:
        Texture() = default;
        Texture(TextureTarget t)
        {
            SetTextureTarget(t);
        }

        virtual ~Texture() = default;
        virtual bool Bind(size_t textureSlot) = 0;
        virtual void SetData(unsigned char* data, int width, int height) = 0;
       
        virtual void SetMinFilter(TextureFilter filter) = 0;
        virtual void SetMagFilter(TextureFilter filter) = 0;

        virtual void SetWrapS(TextureWrapping tw) = 0;
        virtual void SetWrapT(TextureWrapping tw) = 0;

        virtual void GenerateMipMaps() = 0;

        virtual size_t GetWidth() const = 0;
        virtual size_t GetHeight() const = 0;

        virtual TextureFormat GetFormat() const = 0;
        virtual void SetFormat(TextureFormat format) = 0;

        virtual Color GetTexelColor(uint32_t u, uint32_t v) const = 0;

        void SetTextureTarget(TextureTarget t)
        {
            m_textureTarget = t;
        }

    protected:
        TextureTarget m_textureTarget;
    };
}