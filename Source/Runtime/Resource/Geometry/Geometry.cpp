#include "Geometry.h"

namespace Flax
{
    Geometry::Geometry(u32 vertexLength, u32 indexLength) : m_vertexData(vertexLength), m_indexData(indexLength)
	{
	}

	Geometry::~Geometry()
	{
        m_vertexData.clear();
        m_indexData.clear();
	}

    void Geometry::AddPosition(Math::Vec3f position, u32 index)
    {
        if (index >= m_vertexData.size())
            m_vertexData.resize(index + 1);

        m_vertexData[index].position = position;
    }

    void Geometry::AddNormal(Math::Vec3f normal, u32 index)
    {
        if (index >= m_vertexData.size())
            m_vertexData.resize(index + 1);

        m_vertexData[index].normal = normal;
    }

    void Geometry::AddTangent(Math::Vec3f tangent, u32 index)
    {
        if (index >= m_vertexData.size())
            m_vertexData.resize(index + 1);

        m_vertexData[index].tangent = tangent;
    }

    void Geometry::AddBinormal(Math::Vec3f binormal, u32 index)
    {
        if (index >= m_vertexData.size())
            m_vertexData.resize(index + 1);

        m_vertexData[index].binormal = binormal;
    }

    void Geometry::AddColor(Math::Vec4f color, u32 index)
    {
        if (index >= m_vertexData.size())
            m_vertexData.resize(index + 1);

        m_vertexData[index].color = color;
    }

    void Geometry::AddTexCoord(Math::Vec2f uv, u32 index)
    {
        if (index >= m_vertexData.size())
            m_vertexData.resize(index + 1);

        m_vertexData[index].uv = uv;
    }

    void Geometry::AddIndex(u32 indexVal, u32 vecIndex)
    {
        if (vecIndex >= m_vertexData.size())
            m_indexData.resize(vecIndex + 1);

        m_indexData[vecIndex] = indexVal;
    }

    void Geometry::AddIndex(const Vector<u32>& indices)
    {
        for (auto index : indices)
            m_indexData.emplace_back(index);
    }

    ReadArray<u8> Geometry::GenerateRawVertex(VertexRawDataFlags flags) const
	{
        if (flags == VertexRawDataFlags::None)
            return ReadArray<u8>();

        usize vertexStride = 0;
        if (HasFlag(flags, VertexRawDataFlags::Position))
            vertexStride += sizeof(Math::Vec3f);
        if (HasFlag(flags, VertexRawDataFlags::Normal))
            vertexStride += sizeof(Math::Vec3f);
        if (HasFlag(flags, VertexRawDataFlags::Tangent))
            vertexStride += sizeof(Math::Vec3f);
        if (HasFlag(flags, VertexRawDataFlags::Binormal))
            vertexStride += sizeof(Math::Vec3f);
        if (HasFlag(flags, VertexRawDataFlags::Color))
            vertexStride += sizeof(Math::Vec4f);
        if (HasFlag(flags, VertexRawDataFlags::UV))
            vertexStride += sizeof(Math::Vec2f);

        usize totalSize = vertexStride * m_vertexData.size();

        u8* rawData = new u8[totalSize];
        u8* writePtr = rawData;

        for (const auto& vertex : m_vertexData)
        {
            if (HasFlag(flags, VertexRawDataFlags::Position))
            {
                const u8* positionBytes = reinterpret_cast<const u8*>(&vertex.position);
                std::memcpy(writePtr, positionBytes, sizeof(Math::Vec3f));
                writePtr += sizeof(Math::Vec3f);
            }
            if (HasFlag(flags, VertexRawDataFlags::Normal))
            {
                const u8* normalBytes = reinterpret_cast<const u8*>(&vertex.normal);
                std::memcpy(writePtr, normalBytes, sizeof(Math::Vec3f));
                writePtr += sizeof(Math::Vec3f);
            }
            if (HasFlag(flags, VertexRawDataFlags::Tangent))
            {
                const u8* tangentBytes = reinterpret_cast<const u8*>(&vertex.tangent);
                std::memcpy(writePtr, tangentBytes, sizeof(Math::Vec3f));
                writePtr += sizeof(Math::Vec3f);
            }
            if (HasFlag(flags, VertexRawDataFlags::Binormal))
            {
                const u8* binormalBytes = reinterpret_cast<const u8*>(&vertex.binormal);
                std::memcpy(writePtr, binormalBytes, sizeof(Math::Vec3f));
                writePtr += sizeof(Math::Vec3f);
            }
            if (HasFlag(flags, VertexRawDataFlags::Color))
            {
                const u8* colorBytes = reinterpret_cast<const u8*>(&vertex.color);
                std::memcpy(writePtr, colorBytes, sizeof(Math::Vec4f));
                writePtr += sizeof(Math::Vec4f);
            }
            if (HasFlag(flags, VertexRawDataFlags::UV))
            {
                const u8* uvBytes = reinterpret_cast<const u8*>(&vertex.uv);
                std::memcpy(writePtr, uvBytes, sizeof(Math::Vec2f));
                writePtr += sizeof(Math::Vec2f);
            }
        }

        ReadArray<u8> returnData(rawData, totalSize);
        delete[] rawData;
        return returnData;
	}

    ReadArray<u8> Geometry::GenerateRawIndex() const
    {
        usize totalSize = sizeof(u32) * m_indexData.size();
        u8* rawData = new u8[totalSize];
        std::memcpy(rawData, m_indexData.data(), totalSize);
        ReadArray<u8> returnData(rawData, totalSize);
        delete[] rawData;
        return returnData;
    }
}