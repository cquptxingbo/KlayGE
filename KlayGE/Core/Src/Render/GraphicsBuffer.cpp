// VertexBuffer.cpp
// KlayGE 顶点缓冲区类 实现文件
// Ver 3.2.0
// 版权所有(C) 龚敏敏, 2003-2006
// Homepage: http://klayge.sourceforge.net
//
// 3.2.0
// 支持32位的IndexStream (2006.1.4)
//
// 3.1.0
// 分离了实例和几何流 (2005.10.31)
//
// 3.0.0
// 支持instancing (2005.10.22)
//
// 2.4.0
// 改名为VertexBuffer (2005.3.7)
//
// 修改记录
/////////////////////////////////////////////////////////////////////////////////

#include <KlayGE/KlayGE.hpp>
#include <KlayGE/Context.hpp>
#include <KlayGE/RenderFactory.hpp>
#include <KlayGE/RenderView.hpp>
#include <KlayGE/MapVector.hpp>

#include <boost/bind.hpp>

#include <KlayGE/GraphicsBuffer.hpp>

namespace KlayGE
{
	class NullGraphicsBuffer : public GraphicsBuffer
	{
	public:
		NullGraphicsBuffer()
			: GraphicsBuffer(BU_Static)
		{
		}

		void* Map(BufferAccess /*ba*/)
		{
			return NULL;
		}

		void Unmap()
		{
		}

		void DoResize()
		{
		}

		RenderViewPtr CreateRenderView(uint32_t /*width*/, uint32_t /*height*/)
		{
			return RenderView::NullObject();
		}
	};

	GraphicsBuffer::GraphicsBuffer(BufferUsage usage)
			: usage_(usage), size_in_byte_(0)
	{
	}

	GraphicsBuffer::~GraphicsBuffer()
	{
	}

	GraphicsBufferPtr GraphicsBuffer::NullObject()
	{
		static GraphicsBufferPtr obj(new NullGraphicsBuffer);
		return obj;
	}

	void GraphicsBuffer::Resize(uint32_t size_in_byte)
	{
		size_in_byte_ = size_in_byte;
		this->DoResize();
	}

	void GraphicsBuffer::CopyToBuffer(GraphicsBuffer& rhs)
	{
		GraphicsBuffer::Mapper lhs_mapper(*this, BA_Read_Only);
		GraphicsBuffer::Mapper rhs_mapper(rhs, BA_Write_Only);
		std::copy(lhs_mapper.Pointer<uint8_t>(), lhs_mapper.Pointer<uint8_t>() + size_in_byte_,
			rhs_mapper.Pointer<uint8_t>());
	}
}
