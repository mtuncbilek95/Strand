#include "ImagePixel.h"

#include <stb_image.h>

namespace Flax
{
	void ImagePixel::ImportPixelData(const String& path)
	{
        i32 w, h, channels;
        stbi_uc* pixelData = stbi_load(path.c_str(), &w, &h, &channels, 0);
        if (!pixelData)
        {
            Log::Critical(LogType::Resource, "Could not import the image data via stb!");
            Log::Info(LogType::Resource, "Failed Path: {}", path); 
            m_data = {};
            m_size = { 0, 0 };
            m_channels = 0;
            return;
        }

        usize totalSize = static_cast<usize>(w * h * channels);
        m_data = ReadArray<c8>(totalSize);

        std::memcpy(m_data.Data(), pixelData, totalSize);

        m_size = Math::Vec2u(static_cast<u32>(w), static_cast<u32>(h));
        m_channels = static_cast<u32>(channels);

        stbi_image_free(pixelData);
	}

	Span<c8> ImagePixel::Data() const { return m_data.ToSpan(); }
	const Math::Vec2u& ImagePixel::Size() const { return m_size; }
	u32 ImagePixel::Channels() const { return m_channels; }
}
