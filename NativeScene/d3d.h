#pragma once

#pragma comment(lib,"D3D11.lib")
#pragma comment(lib,"D3dcompiler.lib") // for shader compile

#include <d3d11.h>

extern ID3D11Device           *d3d_device;
extern ID3D11DeviceContext    *d3d_context;
extern IDXGISwapChain         *d3d_swapchain;
extern ID3D11RenderTargetView *d3d_rendertarget;

extern int                     d3d_screen_width;
extern int                     d3d_screen_height;

void d3d_init         (HWND hwnd);
void d3d_shutdown     ();
void d3d_render_begin ();
void d3d_render_end   ();
void d3d_resize_screen(int width, int height);