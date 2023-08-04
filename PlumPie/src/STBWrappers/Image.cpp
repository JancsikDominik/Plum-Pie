#include "Image.hpp"

#include "Debugging/Debug.hpp"

namespace Plum
{
    Image::Image(const std::filesystem::path& filePath)
    {
        LoadImage(filePath);
        PLUM_ASSERT(m_data != nullptr);
    }

    bool Image::LoadImage(const std::filesystem::path& filePath)
    {
        const auto& Deleter = [](unsigned char* imageData) -> void {
            if (imageData != nullptr)
                stbi_image_free(imageData);
        };

        m_data = std::unique_ptr<unsigned char, std::function<void(unsigned char*)>>(
            stbi_load(filePath.string().c_str(), &m_width, &m_height, &m_channels, 4), Deleter
        );

        return m_data != nullptr;
    }

    void Image::InitRawData(size_t width, size_t height, size_t channels)
    {
        const auto& Deleter = [](unsigned char* ptr) -> void { 
            delete ptr; 
        };

        m_width = width;
        m_height = height;
        m_channels = channels;

        m_data = std::unique_ptr<unsigned char, std::function<void(unsigned char*)>>(new unsigned char[width * height * channels], Deleter);
    }

    void Image::SetColorAt(Color c, size_t i, size_t j)
    {
        if (m_data != nullptr && i < m_width && j < m_height)
        {
            size_t index = (j * m_width + i) * m_channels;
            m_data.get()[index] = m_channels >= 1 ? c.r * 255 : 0;
            m_data.get()[index + 1] = m_channels >= 2 ? c.g * 255 : 0;
            m_data.get()[index + 2] = m_channels >= 3 ? c.b * 255 : 0;
            m_data.get()[index + 2] = m_channels >= 4 ? c.a * 255 : 255;
        }
    }

    int Image::GetWidth() const
    {
        return m_width;
    }

    int Image::GetHeight() const
    {
        return m_height;
    }

    int Image::GetChannels() const
    {
        return m_channels;
    }

    unsigned char* Image::GetRawData() const
    {
        return m_data.get();
    }

    Color Image::GetColorAt(size_t i, size_t j) const
    {
        if (m_data != nullptr)
        {
            size_t index = (j * m_width + i) * m_channels;
            unsigned char r = m_channels >= 1 ? m_data.get()[0] : 0;
            unsigned char g = m_channels >= 2 ? m_data.get()[1] : 0;
            unsigned char b = m_channels >= 3 ? m_data.get()[2] : 0;
            unsigned char a = m_channels >= 4 ? m_data.get()[3] : 255;

            return Color(r / 255.f, g / 255.f, b / 255.f, a / 255.f);
        }
        else
        {
            return Color(0, 0, 0, 0);
        }
    }

}
