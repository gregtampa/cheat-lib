//=============================================================================
// 2D rendering interfaces.
//=============================================================================
#pragma once
#include "Types.hpp"
#include <d3d11.h>

class FWindow;

// DirectX 11 2D render interface.
class FRender {
public:
	//=========================================================================
	// Utility functions.
	//=========================================================================

	// Returns a color in 32-bit unsigned RGBA format.
	static constexpr u32 RGBA(u32 r, u32 g, u32 b, u32 a) {
		return (((u32)((u8)(r))) | ((u32)((u8)(g)) << 8) | ((u32)((u8)(b)) << 16) | ((u32)((u8)(a)) << 24));
	}

	// Returns a hue in 32-bit RGBA format.
	static u32 HSVAtoRGBA(f32 h, f32 s, f32 v, f32 a);

	//=========================================================================
	// Interface functions.
	//=========================================================================

	// Creates the render interface.
	void Create(FWindow* window);

	// Destroys the render interface.
	void Destroy();

	// Begins a new frame.
	b32 FrameInit();

	// Finishes the frame.
	void FramePost();

	// Returns the size of the viewport.
	vec2 GetViewport();

	// Sets the drawing font. Warning: replaces the old font, so expensive.
	void SetFont(WCHAR const* face, i32 size);

	//=========================================================================
	// Drawing functions.
	//=========================================================================

	// Draws many lines composed of the given points.
	void DrawLines(vec2 const* points, u32 pointsCount, u32 color, b32 closed = false);

	// Draws a polygon.
	void DrawPolygon(vec2 const* points, u32 pointsCount, u32 color);

	// Draws teext.
	void DrawText(vec2 pos, u32 color, i8 const* fmt, ...);

	// Draws a stroked rect with the given size.
	void DrawRectFill(vec2 tl, vec2 br, u32 color);

	// Draws a stroked rectangle.
	void DrawRect(vec2 tl , vec2 br, u32 color);

	// Adds a triangle formed by points a, b, and c.
	void DrawTriangleFill(vec2 a, vec2 b, vec2 c, u32 color);

	//=========================================================================
	// Drawing utility.
	//=========================================================================

	// Returns the width of the given string of text.
	f32 CalcTextWidth(i8 const* text);

protected:
	//=========================================================================
	// Private constants.
	//=========================================================================

	// Maximum number of vertices to draw per frame.
	static constexpr u32 const VTX_LIMIT = 16384;

	// Maximum number of indices to draw per frame.
	static constexpr u32 const IDX_LIMIT = 32768;

	//=========================================================================
	// Private types.
	//=========================================================================

	// A drawing index.
	typedef u16 FIdx;

	// A drawing vertex.
	struct FVtx {
		vec2 Pos; // Position of the vertex in pixels relative to the top left corner of the overlay.
		vec2 Tex; // UV texture coordinates of the vertex.
		u32 Col; // Color of the vertex in 32-bit RGBA format.
	};

	// A font glyph.
	struct FGlyph {
		f32 Advance; // How far to advance the cursor.
		vec4 Tex; // The texture coordinates (TL, BR) of the glyph.
	};

	// Wrapper around a mapped D3D11 buffer.
	template <typename Type>
	struct FBuf {
		Type* Data; // Mapped buffer data.
		Type* Ptr; // Current write pointer.
		u32 Count; // Number of elements in the buffer.
		u32 Limit; // Maximum number of elements in the buffer.
	};

	// Drawing state.
	struct FState {
		FBuf<FVtx> Vtx; // Vertex data.
		FBuf<FIdx> Idx; // Index data.
	};

	//=========================================================================
	// Private functions.
	//=========================================================================

	// Recreates the render overlay.
	void Recreate();

	// Resets view dependent resources for the device.
	b32 Reset();

	// Allocates vertices and indices. State returned via pointer is *before* the allocation.
	b32 AllocPrimitives(u32 vtxNum, u32 idxNum, FState* prevState);

	//=========================================================================
	// D3D11 utility functions.
	//=========================================================================

	// Creates a D3D11 Buffer.
	HRESULT CreateBuffer(ID3D11Buffer** buffer, void const* src, UINT srcBytes, UINT bindFlags, BOOL write);

	// Maps a buffer for writing. Returns a pointer to the mapped data on success, 0 otherwise.
	void* MapBuffer(ID3D11Buffer* buffer);

	// Updates the data in a buffer.
	void UpdateBuffer(ID3D11Buffer* buffer, void const* src, UINT srcBytes);

	// Releases a COM pointer if it is not null.
	template <typename Type>
	static void ComRelease(Type** px) {
		Type* x = *px;
		if (x) {
			x->Release();
			*px = 0;
		}
	}

	//=========================================================================
	// Private state.
	//=========================================================================

	// D3D11 Resources.
	ID3D11Device* Device;
	ID3D11DeviceContext* Context;
	IDXGISwapChain* Swap;
	ID3D11RenderTargetView *RTV;
	ID3D11BlendState* AlphaBS;
	ID3D11DepthStencilState* DisabledDS;
	ID3D11RasterizerState* CullNoneRS;
	ID3D11SamplerState* LinearSS;
	ID3D11ShaderResourceView* FontResource;
	ID3D11VertexShader* VertexShader;
	ID3D11PixelShader* PixelShader;
	ID3D11InputLayout* InputLayout;
	ID3D11Buffer* ProjectionData;
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;

	FWindow* Window; // Handle to the window the render interface displays on.
	b32 IsInitialized; // True if the renderer is initialized.
	D3D11_VIEWPORT Viewport; // Current backbuffer viewport.

	FState State; // Drawing state.
	vec2 WhiteTexel; // Coordinate of the white texel in the font texture.
	f32 FontHeight; // Height in pixels of a line in the font.
	FGlyph FontGlyphs[256]; // Font glyph information.
};
