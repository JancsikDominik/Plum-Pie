#pragma once

#include <stb_image.h>
#include <filesystem>
#include <functional>

#include "Graphics/Vertex.hpp"

namespace Plum
{
	class Image
	{
    public:
        Image() = default;
        Image(const std::filesystem::path& filePath);

        virtual ~Image() = default;


        int GetWidth() const;
        int GetHeight() const;
        int GetChannels() const;
        unsigned char* GetRawData() const;
        Color GetColorAt(size_t i, size_t j) const;

        bool LoadImage(const std::filesystem::path& filePath);
        void InitRawData(int width, int height, int channels);
        void SetColorAt(Color c, size_t i, size_t j);
        
        // TODO: save image

	private:
		std::unique_ptr<unsigned char, std::function<void(unsigned char*)>> m_data = nullptr;
		int m_width = 0;
		int m_height = 0;
		int m_channels = 0;
	};
}


