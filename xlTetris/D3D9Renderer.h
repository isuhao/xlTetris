//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   D3D9Renderer.h
//    Author:      Streamlet
//    Create Time: 2015-03-23
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __D3D9RENDERER_H_0A2D3A08_EA39_4B3B_90D8_9E15CC145A07_INCLUDED__
#define __D3D9RENDERER_H_0A2D3A08_EA39_4B3B_90D8_9E15CC145A07_INCLUDED__


#include <xl/Windows/Memory/xlSafeSmartPtr.h>
#include "Renderer.h"
#include <d3d9.h>
#include <d3dx9core.h>


class D3D9Renderer;
class D3D9RenderContext : public RenderContext
{
public:
    D3D9RenderContext(HWND hWnd, D3D9Renderer *pRenderer);
    ~D3D9RenderContext();

public:
    // RenderMethods methods
    void FillSolidRect(LPCRECT lpRect, const RGBQUAD &color) override;
    void DrawText(LPCTSTR lpszText, int cchText, LPCRECT lplpRectrc, UINT uFormat, const RGBQUAD &color) override;
    void DrawImage(HBITMAP hBitmap, LPCRECT lprcDest, LPCRECT lprcSource, BYTE byAlpha) override;
    void DrawImageGaussianBlur(HBITMAP hBitmap, LPCRECT lprcDest, LPCRECT lprcSource, BYTE byAlpha, BYTE byRadius) override;

public:
    // RenderContext Methods
    bool Initialize() override;
    void Uninitialize() override;
    void BeginDraw() override;
    void EndDraw() override;

private:
    bool CreateDeviceRelatedResources();
    void DestroyDeviceRelatedResources();
    IDirect3DTexture9 *BitmapToTexture(HBITMAP hBitmap, SIZE *pSize);
    void DrawImage(IDirect3DTexture9 *pTexture, SIZE sz, LPCRECT lprcDest, LPCRECT lprcSource, BYTE byAlpha, IDirect3DVertexShader9 *pVS, IDirect3DPixelShader9 *pPS);
    DWORD GetResource(LPVOID *pBuffer, LPCTSTR lpszResType, UINT nResID);

private:
    HWND m_hWnd;
    D3D9Renderer *m_pRenderer;
    D3DPRESENT_PARAMETERS m_Params;
    IDirect3DDevice9 *m_pD3DDevice;
    IDirect3DVertexBuffer9 *m_pVertex;
    IDirect3DIndexBuffer9 *m_pIndex;
    IDirect3DPixelShader9 *m_pPSGaussianBlur;
    HFONT m_hFont;
};

class D3D9Renderer : public Renderer
{
public:
    D3D9Renderer();
    ~D3D9Renderer();

public:
    // Render methods
    LPCTSTR GetName() override;
    bool Initialize() override;
    void Uninitialize() override;
    RenderContext *CreateContext(HWND hWnd) override;
    void ReleaseContext(RenderContext *pContext) override;

private:
    friend D3D9RenderContext;
    IDirect3D9 *m_pD3D;
};

#endif // #ifndef __D3D9RENDERER_H_0A2D3A08_EA39_4B3B_90D8_9E15CC145A07_INCLUDED__
