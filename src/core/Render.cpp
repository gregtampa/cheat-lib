#include "Render.hpp"
#include "Math.hpp"
#include "Utility.hpp"
#include "Vector.hpp"
#include "Window.hpp"
#include "Shaders/PS.h"
#include "Shaders/VS.h"
#include <stdio.h>

u32 FRender::HSVAtoRGBA(f32 h, f32 s, f32 v, f32 a) {
	vec3 col;
	col.x = Math::Saturate(fabsf(h * 6.0f - 3.0f) - 1.0f);
	col.y = Math::Saturate(2.0f - fabsf(h * 6.0f - 2.0f));
	col.z = Math::Saturate(2.0f - fabsf(h * 6.0f - 4.0f));

	vec3 res = ((col - 1.0f) * s + 1.0f) * v;
	return RGBA(res.x * 255, res.y * 255, res.z * 255, a * 255);
}

void FRender::Create(FWindow* window) {
	Window = window;

	DXGI_SWAP_CHAIN_DESC swapDesc = {};
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.BufferCount = 1;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.OutputWindow = window->Handle;
	swapDesc.Windowed = TRUE;

	if (FAILED(D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0, 0, D3D11_SDK_VERSION, &swapDesc, &Swap, &Device, 0, &Context))) {
		return;
	}

	IDXGIFactory *factory;
	if (SUCCEEDED(Swap->GetParent(IID_PPV_ARGS(&factory)))) {
		factory->MakeWindowAssociation(window->Handle, DXGI_MWA_NO_WINDOW_CHANGES | DXGI_MWA_NO_ALT_ENTER);
		factory->Release();
	}

	// Create the alpha blending state.
	D3D11_BLEND_DESC bd = {};
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	Device->CreateBlendState(&bd, &AlphaBS);

	// Create the depth-stencil state.
	D3D11_DEPTH_STENCIL_DESC dd = {};
	dd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dd.DepthFunc = D3D11_COMPARISON_ALWAYS;
	dd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
	dd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dd.BackFace = dd.FrontFace;

	Device->CreateDepthStencilState(&dd, &DisabledDS);

	// Create the sampler state.
	D3D11_SAMPLER_DESC sd = {};
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sd.MaxLOD = D3D11_FLOAT32_MAX;

	Device->CreateSamplerState(&sd, &LinearSS);

	// Create the rasterizer state.
	D3D11_RASTERIZER_DESC rd = {};
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_NONE;
	rd.DepthClipEnable = true;

	Device->CreateRasterizerState(&rd, &CullNoneRS);

	// Create the shader resources.
	Device->CreateVertexShader(VSData, sizeof(VSData), 0, &VertexShader);
	Device->CreatePixelShader(PSData, sizeof(PSData), 0, &PixelShader);

	D3D11_INPUT_ELEMENT_DESC ild[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT,   0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,   0, 8,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	Device->CreateInputLayout(ild, COUNT(ild), VSData, sizeof(VSData), &InputLayout);
	CreateBuffer(&ProjectionData, 0, sizeof(mat4), D3D11_BIND_CONSTANT_BUFFER, true);
	CreateBuffer(&VertexBuffer, 0, sizeof(FVtx) * VTX_LIMIT, D3D11_BIND_VERTEX_BUFFER, true);
	CreateBuffer(&IndexBuffer, 0, sizeof(FIdx) * IDX_LIMIT, D3D11_BIND_INDEX_BUFFER, true);

	IsInitialized = Reset();
}

void FRender::Destroy() {
	ComRelease(&IndexBuffer);
	ComRelease(&VertexBuffer);
	ComRelease(&ProjectionData);
	ComRelease(&PixelShader);
	ComRelease(&VertexShader);
	ComRelease(&FontResource);

	ComRelease(&LinearSS);
	ComRelease(&CullNoneRS);
	ComRelease(&DisabledDS);
	ComRelease(&AlphaBS);

	ComRelease(&RTV);
	ComRelease(&Swap);
	ComRelease(&Context);
	ComRelease(&Device);

	IsInitialized = false;
}

b32 FRender::FrameInit() {
	if (IsInitialized == false) {
		return false;
	}

	// Resize the backbuffer if needed.
	if (Window->Size.x != Viewport.Width || Window->Size.y != Viewport.Height) {
		if (Reset() == false) {
			Recreate();
			if (IsInitialized == false) {
				return false;
			}
		}
	}

	// Clear the backbuffer.
	f32 const color[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	Context->ClearRenderTargetView(RTV, color);

	// Upload the ortho projection matrix.
	auto ctx = Context;

	f32 l = 0.5f;
	f32 r = Viewport.Width;
	f32 t = 0.5f;
	f32 b = Viewport.Height;

	mat4 projection = {};
	projection._11 = 2.0f / (r - l);
	projection._22 = 2.0f / (t - b);
	projection._33 = 0.5f;

	projection._41 = (r + l) / (l - r);
	projection._42 = (t + b) / (b - t);
	projection._43 = 0.5f;
	projection._44 = 1.0f;

	D3D11_MAPPED_SUBRESOURCE ms = {};
	if (ProjectionData && SUCCEEDED(Context->Map(ProjectionData, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms))) {
		memcpy(ms.pData, &projection, sizeof(projection));
	}

	// Set context state for drawing 2D elements.
	ctx->PSSetShader(PixelShader, 0, 0);
	ctx->VSSetShader(VertexShader, 0, 0);

	f32 const blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	ctx->OMSetBlendState(AlphaBS, blendFactor, 0xffffffff);
	ctx->OMSetDepthStencilState(DisabledDS, 0);
	ctx->PSSetSamplers(0, 1, &LinearSS);
	ctx->PSSetShaderResources(0, 1, &FontResource);
	ctx->RSSetState(CullNoneRS);
	ctx->RSSetViewports(1, &Viewport);
	ctx->VSSetConstantBuffers(0, 1, &ProjectionData);

	UINT stride = sizeof(FVtx);
	UINT offset = 0;

	ctx->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	ctx->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
	ctx->IASetInputLayout(InputLayout);
	ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	ctx->OMSetRenderTargets(1, &RTV, 0);

	// Map vertex and index buffer data for writing.
	State.Vtx.Data = (FVtx*)MapBuffer(VertexBuffer);
	State.Vtx.Limit = State.Vtx.Data ? VTX_LIMIT : 0;

	State.Idx.Data = (FIdx*)MapBuffer(IndexBuffer);
	State.Idx.Limit = State.Idx.Data ? IDX_LIMIT : 0;

	return true;
}

void FRender::FramePost() {
	// Unmap vertex and index buffer data if they're open.
	if (State.Vtx.Data) {
		Context->Unmap(VertexBuffer, 0);
	}

	if (State.Idx.Data) {
		Context->Unmap(IndexBuffer, 0);
	}

	// Draw if applicable.
	if (State.Idx.Count > 0) {
		Context->DrawIndexed(State.Idx.Count, 0, 0);
	}

	// Reset drawing state.
	State = {};

	// Swap the backbuffer.
	HRESULT hr = Swap->Present(0, 0);
	if (FAILED(hr) && hr != DXGI_ERROR_WAS_STILL_DRAWING && hr != DXGI_STATUS_OCCLUDED) {
		Recreate();
	}
}

vec2 FRender::GetViewport() {
	return vec2{ Viewport.Width, Viewport.Height };
}

void FRender::SetFont(WCHAR const* face, i32 size) {
	if (Device == 0) {
		return;
	}

	// Create the drawing context.
	HDC dc = CreateCompatibleDC(0);
	if (dc == 0) {
		return;
	}

	// Create the font -> cleartype looks better than regular AA for small/med sizes
	SetMapMode(dc, MM_TEXT);
	HFONT font = CreateFontW(size, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, CLEARTYPE_QUALITY, 0, face);
	if (font == 0) {
		DeleteDC(dc);
		return;
	}

	// Use the font for calculations below.
	SelectObject(dc, font);

	// Calculate the line height.
	TEXTMETRICW tm = {};
	GetTextMetricsW(dc, &tm);

	i32 lineHeight = tm.tmHeight;
	FGlyph *glyphs = FontGlyphs;

	// Calculate glyph widths for unicode ranges.
	auto calcGlyphs = [&](WCHAR start, WCHAR end) {
		for (WCHAR c = start; c <= end; ++c) {
			SIZE size = {};
			GetTextExtentPoint32W(dc, &c, 1, &size);
			glyphs[c].Advance = size.cx;
		}
	};

	calcGlyphs(0x20, 0x7F);
	calcGlyphs(0xA0, 0xFF);

	// Determine the image size needed to fit all glpyhs.
	i32 sizeX = 128;
	i32 sizeY = 128;

	while (sizeX < 4096) {
		i32 endX = sizeX - 1;
		i32 x = 1;
		i32 y = 0;

		for (WCHAR c = 0; c < 256; ++c) {
			i32 gx = glyphs[c].Advance;
			if (x + gx >= endX) {
				x = 1;
				y += lineHeight;
			}

			x += gx + 2;
		}

		if (y + lineHeight < sizeY) {
			break;
		}

		if (sizeY < sizeX) {
			sizeY *= 2;
		} else {
			sizeX *= 2;
		}
	}

	// Create the image to render the font to.
	BITMAPINFO bmi = {};
	bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
	bmi.bmiHeader.biWidth = sizeX;
	bmi.bmiHeader.biHeight = -sizeY;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biSizeImage = sizeX * sizeY * 4;

	DWORD* data;
	HBITMAP bitmap = CreateDIBSection(dc, &bmi, DIB_RGB_COLORS, (void**)&data, 0, 0);
	if (bitmap == 0) {
		DeleteObject(font);
		DeleteDC(dc);
	}

	// Set drawing state.
	SelectObject(dc, bitmap);
	SelectObject(dc, font);

	SetTextAlign(dc, TA_TOP | TA_LEFT);
	SetTextColor(dc, RGB(255, 255, 255));
	SetBkColor(dc, RGB(0, 0, 0));

	// Draw glyphs to texture.
	i32 endX = sizeX - 1;
	i32 x = 1;
	i32 y = 0;

	auto setupGlyphs = [&](WCHAR start, WCHAR end) {
		for (WCHAR c = start; c < end; ++c) {
			i32 gx = glyphs[c].Advance;

			if (x + gx >= endX) {
				x = 1;
				y += lineHeight;
			}

			ExtTextOutW(dc, x, y, ETO_OPAQUE | ETO_IGNORELANGUAGE, 0, &c, 1, 0);

			glyphs[c].Tex.x = x / (f32)sizeX;
			glyphs[c].Tex.y = y / (f32)sizeY;
			glyphs[c].Tex.z = (x + glyphs[c].Advance) / (f32)sizeX;
			glyphs[c].Tex.w = (y + lineHeight) / (f32)sizeY;

			x += gx + 2;
		}
	};

	setupGlyphs(0x20, 0x7F);
	setupGlyphs(0xA0, 0xFF);

	// The drawn glyphs aren't actually on a transparent background. Cleartype works by assuming information about the
	// background color to derive its antialiasing. To make it work on transparent backgrounds we convert the image to
	// grayscale (via a colorimetric conversion to grayscale).
	u32 pixels = sizeX * sizeY;
	for (u32 i = 0; i < pixels; ++i) {
		DWORD p = data[i];
		p = (DWORD)(0.2126f * (p & 0xFF) + 0.7152f * ((p >> 8) & 0xFF) + 0.0722f * ((p >> 16) & 0xFF));
		data[i] = 0x00FFFFFF | (p << 24);
	}

	// Write out white texel pixels needed for drawing primitives.
	data[0] = 0xFFFFFFFF;
	data[1] = 0xFFFFFFFF;
	data[sizeX + 0] = 0xFFFFFFFF;
	data[sizeX + 1] = 0xFFFFFFFF;

	// Store font metadata.
	FontHeight = lineHeight;
	WhiteTexel = { 0.5f / sizeX, 0.5f / sizeY };

	// Create the texture.
	D3D11_TEXTURE2D_DESC texDesc = {};
	texDesc.Width = sizeX;
	texDesc.Height = sizeY;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	texDesc.SampleDesc.Count = 1;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA subDesc = {};
	subDesc.pSysMem = data;
	subDesc.SysMemPitch = sizeX * 4;

	ID3D11Texture2D* tex;
	if (SUCCEEDED(Device->CreateTexture2D(&texDesc, &subDesc, &tex))) {
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = texDesc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = texDesc.MipLevels;

		Device->CreateShaderResourceView(tex, &srvDesc, &FontResource);
		tex->Release();
	}

	DeleteObject(bitmap);
	DeleteObject(font);
	DeleteDC(dc);
}

void FRender::DrawLines(vec2 const * points, u32 pointsCount, u32 color, b32 closed) {
	if (pointsCount < 2) {
		return;
	}

	u32 count = closed ? pointsCount : pointsCount - 1;
	FState state;

	if (AllocPrimitives(count * 4, count * 6, &state) == false) {
		return;
	}

	FVtx* vtxPtr = state.Vtx.Ptr;
	FIdx* idxPtr = state.Idx.Ptr;
	u32 vtxNum = state.Vtx.Count;
	vec2 tex = WhiteTexel;

	for (u32 i1 = 0; i1 < count; ++i1) {
		u32 ip = (i1 + 1);
		u32 i2 = (ip == pointsCount ? 0 : ip);

		vec2 const& p1 = points[i1];
		vec2 const& p2 = points[i2];

		vec2 diff = p2 - p1;
		f32 ds = diff.x * diff.x + diff.y * diff.y;
		diff *= (ds > 0.0 ? (1.0f / sqrtf(ds)) : 1.0f);

		f32 dx = diff.x * 0.5f;
		f32 dy = diff.y * 0.5f;

		vtxPtr[0].Pos.x = p1.x + dy;
		vtxPtr[0].Pos.y = p1.y - dx;
		vtxPtr[0].Tex = tex; vtxPtr[0].Col = color;

		vtxPtr[1].Pos.x = p2.x + dy;
		vtxPtr[1].Pos.y = p2.y - dx;
		vtxPtr[1].Tex = tex;
		vtxPtr[1].Col = color;

		vtxPtr[2].Pos.x = p2.x - dy;
		vtxPtr[2].Pos.y = p2.y + dx;
		vtxPtr[2].Tex = tex;
		vtxPtr[2].Col = color;

		vtxPtr[3].Pos.x = p1.x - dy;
		vtxPtr[3].Pos.y = p1.y + dx;
		vtxPtr[3].Tex = tex;
		vtxPtr[3].Col = color;

		vtxPtr += 4;

		idxPtr[0] = (FIdx)(vtxNum + 0);
		idxPtr[1] = (FIdx)(vtxNum + 1);
		idxPtr[2] = (FIdx)(vtxNum + 2);

		idxPtr[3] = (FIdx)(vtxNum + 0);
		idxPtr[4] = (FIdx)(vtxNum + 2);
		idxPtr[5] = (FIdx)(vtxNum + 3);

		idxPtr += 6;
		vtxNum += 4;
	}
}

void FRender::DrawPolygon(vec2 const * points, u32 pointsCount, u32 color) {
	u32 idxCount = (pointsCount - 2) * 3;
	u32 vtxCount = pointsCount;
	FState state;

	if (AllocPrimitives(vtxCount, idxCount, &state) == false) {
		return;
	}

	FVtx* vtxPtr = state.Vtx.Ptr;
	FIdx* idxPtr = state.Idx.Ptr;
	u32 vtxNum = state.Vtx.Count;
	vec2 tex = WhiteTexel;

	for (u32 i = 0; i < vtxCount; ++i) {
		vtxPtr[0].Pos = points[i];
		vtxPtr[0].Tex = tex;
		vtxPtr[0].Col = color;
		vtxPtr++;
	}

	for (u32 i = 2; i < vtxCount; ++i) {
		idxPtr[0] = (FIdx)(vtxNum);
		idxPtr[1] = (FIdx)(vtxNum + i - 1);
		idxPtr[2] = (FIdx)(vtxNum + i);
		idxPtr += 3;
	}
}

void FRender::DrawText(vec2 pos, u32 color, i8 const * fmt, ...) {
	// Align the text on a full pixel instead of subpixel so it doesn't look terrible.
	pos.x = (f32)(i32)pos.x;
	pos.y = (f32)(i32)pos.y;

	// Format the string.
	va_list args;
	va_start(args, fmt);

	i8 buf[512];
	vsnprintf_s(buf, sizeof(buf), _TRUNCATE, fmt, args);
	va_end(args);

	// Draw glyphs.
	FGlyph* glyphs = FontGlyphs;
	f32 lineHeight = FontHeight;

	f32 x = pos.x;
	f32 y = pos.y;

	for (i32 i = 0; i < COUNT(buf); ++i) {
		// Assume space and tabs are empty glyphs.
		u8 c = (u8)buf[i];
		if (c == 0) {
			break;
		}

		FGlyph* glyph = glyphs + c;

		if (c == ' ' || c == '\t') {
			x += glyph->Advance;
			continue;
		}

		// Check for newlines.
		if (c == '\n') {
			x = pos.x;
			y += lineHeight;
			continue;
		}

		// Allocate space for the glyph.
		FState state;
		if (AllocPrimitives(4, 6, &state) == false) {
			return;
		}

		FVtx* vtxPtr = state.Vtx.Ptr;
		FIdx* idxPtr = state.Idx.Ptr;
		u32 vtxNum = state.Vtx.Count;

		// Calculate glyph position and size.
		f32 x1 = x;
		f32 y1 = y;
		f32 x2 = x + glyph->Advance;
		f32 y2 = y + lineHeight;
		x += glyph->Advance;

		// Calculate glyph uv coordinates.
		f32 u1 = glyph->Tex.x;
		f32 v1 = glyph->Tex.y;
		f32 u2 = glyph->Tex.z;
		f32 v2 = glyph->Tex.w;

		// Draw the glyph.
		idxPtr[0] = (FIdx)(vtxNum);
		idxPtr[1] = (FIdx)(vtxNum + 1);
		idxPtr[2] = (FIdx)(vtxNum + 2);
		idxPtr[3] = (FIdx)(vtxNum);
		idxPtr[4] = (FIdx)(vtxNum + 2);
		idxPtr[5] = (FIdx)(vtxNum + 3);

		vtxPtr[0].Pos.x = x1;
		vtxPtr[0].Pos.y = y1;
		vtxPtr[0].Tex.x = u1;
		vtxPtr[0].Tex.y = v1;
		vtxPtr[0].Col = color;

		vtxPtr[1].Pos.x = x2;
		vtxPtr[1].Pos.y = y1;
		vtxPtr[1].Tex.x = u2;
		vtxPtr[1].Tex.y = v1;
		vtxPtr[1].Col = color;

		vtxPtr[2].Pos.x = x2;
		vtxPtr[2].Pos.y = y2;
		vtxPtr[2].Tex.x = u2;
		vtxPtr[2].Tex.y = v2;
		vtxPtr[2].Col = color;

		vtxPtr[3].Pos.x = x1;
		vtxPtr[3].Pos.y = y2;
		vtxPtr[3].Tex.x = u1;
		vtxPtr[3].Tex.y = v2;
		vtxPtr[3].Col = color;
	}
}

void FRender::DrawRectFill(vec2 tl, vec2 br, u32 color) {
	vec2 tr = { br.x, tl.y };
	vec2 bl = { tl.x, br.y };
	vec2 uv = WhiteTexel;

	FState state;
	if (AllocPrimitives(4, 6, &state) == false) {
		return;
	}

	FVtx* vtxPtr = state.Vtx.Ptr;
	FIdx* idxPtr = state.Idx.Ptr;
	u32 vtxCount = state.Vtx.Count;

	// Add the rectangle vertices.
	idxPtr[0] = (vtxCount + 0);
	idxPtr[1] = (vtxCount + 1);
	idxPtr[2] = (vtxCount + 2);
	idxPtr[3] = (vtxCount + 0);
	idxPtr[4] = (vtxCount + 2);
	idxPtr[5] = (vtxCount + 3);

	vtxPtr[0].Pos = tl;
	vtxPtr[0].Tex = uv;
	vtxPtr[0].Col = color;

	vtxPtr[1].Pos = tr;
	vtxPtr[1].Tex = uv;
	vtxPtr[1].Col = color;

	vtxPtr[2].Pos = br;
	vtxPtr[2].Tex = uv;
	vtxPtr[2].Col = color;

	vtxPtr[3].Pos = bl;
	vtxPtr[3].Tex = uv;
	vtxPtr[3].Col = color;
}

void FRender::DrawRect(vec2 tl, vec2 br, u32 color) {
	f32 tlx1 = tl.x + 1.0f;
	f32 tly1 = tl.y + 1.0f;
	f32 brx1 = br.x - 1.0f;
	f32 bry1 = br.y - 1.0f;

	// Horizontal bars.
	DrawRectFill({ tl.x, tl.y }, { br.x, tly1 }, color);
	DrawRectFill({ tl.x, bry1 }, { br.x, br.y }, color);

	// Vertical bars.
	DrawRectFill({ tl.x, tly1 }, { tlx1, bry1 }, color);
	DrawRectFill({ brx1, tly1 }, { br.x, bry1 }, color);
}

void FRender::DrawTriangleFill(vec2 a, vec2 b, vec2 c, u32 color) {
	vec2 points[] = { a, b, c };
	DrawLines(points, COUNT(points), color, true);
}

f32 FRender::CalcTextWidth(i8 const* text) {
	FGlyph const* glyphs = FontGlyphs;
	f32 x = 0.0f;

	for (;;) {
		u8 c = *text++;
		if (c == 0) {
			break;
		}

		x += glyphs[c].Advance;
	}

	return x;
}

void FRender::Recreate() {
	FWindow* window = Window;

	Destroy();
	CLEAR(this);
	Create(window);
}

b32 FRender::Reset() {
	Context->ClearState();

	if (RTV) {
		ComRelease(&RTV);
		Swap->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
	}

	ID3D11Texture2D* tex;
	if (FAILED(Swap->GetBuffer(0, IID_PPV_ARGS(&tex)))) {
		return false;
	}

	D3D11_TEXTURE2D_DESC td = {};
	tex->GetDesc(&td);

	HRESULT hr = Device->CreateRenderTargetView(tex, 0, &RTV);
	tex->Release();

	if (FAILED(hr)) {
		return false;
	}

	Viewport.Width = (f32)td.Width;
	Viewport.Height = (f32)td.Height;
	Viewport.MaxDepth = 1.0f;

	return true;
}

b32 FRender::AllocPrimitives(u32 vtxNum, u32 idxNum, FState* prevState) {
	State.Vtx.Ptr = State.Vtx.Data + State.Vtx.Count;
	State.Idx.Ptr = State.Idx.Data + State.Idx.Count;

	*prevState = State;

	u32 newVtxCount = State.Vtx.Count + vtxNum;
	u32 newIdxCount = State.Idx.Count + idxNum;

	if (newVtxCount > State.Vtx.Limit || newIdxCount > State.Idx.Limit) {
		return false;
	}

	State.Vtx.Count = newVtxCount;
	State.Idx.Count = newIdxCount;

	return true;
}

HRESULT FRender::CreateBuffer(ID3D11Buffer ** buffer, void const * src, UINT srcBytes, UINT bindFlags, BOOL write) {
	D3D11_BUFFER_DESC desc;
	desc.BindFlags = bindFlags;
	desc.MiscFlags = 0;
	desc.ByteWidth = Math::RoundI32(srcBytes, 16);

	if (write) {
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		desc.Usage = D3D11_USAGE_DYNAMIC;
	} else {
		desc.CPUAccessFlags = 0;
		desc.Usage = D3D11_USAGE_IMMUTABLE;
	}

	D3D11_SUBRESOURCE_DATA initData = { 0 };
	initData.pSysMem = src;

	return Device->CreateBuffer(&desc, src ? &initData : 0, buffer);
}

void* FRender::MapBuffer(ID3D11Buffer * buffer) {
	D3D11_MAPPED_SUBRESOURCE ms;
	if (buffer && SUCCEEDED(Context->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms))) {
		return ms.pData;
	}

	return 0;
}

void FRender::UpdateBuffer(ID3D11Buffer* buffer, void const* src, UINT srcBytes) {
	D3D11_MAPPED_SUBRESOURCE ms;
	if (buffer && SUCCEEDED(Context->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms))) {
		memcpy(ms.pData, src, srcBytes);
		Context->Unmap(buffer, 0);
	}
}
