//  **************************************
//  File:        renderingengine.h
//  ***************************************

#ifndef RenderingEngine_DEFINED
#define RenderingEngine_DEFINED

#include "NE_pubhead.h"
#include "REScalar.h"
#include "REPoint.h"
#include "RERect.h"
#include "REPath.h"
#include "RETypeface.h"
#include "REPaint.h"
#include "REMatrix.h"
#include "REColor.h"
#include "RERegion.h"
#include "RECanvas.h"
#include "REBitmap.h"
#include "ImageCoder.h"

namespace skia_surface
{


class IRESurface
{
public:
	// 
	virtual ~IRESurface() {};

	//surface
	virtual kn_bool Initialize(kn_dword width, kn_dword height, REBitmap::Config colorFormat) = 0;
	//surface
	virtual kn_bool Initialize(void* p, kn_dword width, kn_dword height, REBitmap::Config colorFormat) = 0;

	//surface
	virtual kn_bool InitializeFromFile(const kn_string& filename) = 0;

	//  surface
	virtual kn_bool InitializeThumbnailFromFile(const kn_string& filename, int width, int height, int scalemode, REColor bkgcolor) = 0;

	// surface
	virtual kn_bool InitializeFromPicBuffer(const kn_byte* pBuf, kn_int iBufLen) = 0;

	// 
	virtual void Release() = 0;

	// , , .
	virtual kn_bool IsInitialized() = 0;

	// BitmapBuffer
	virtual kn_byte* GetBitmapBuffer() const = 0;

	// BitmapBufferSize
	virtual size_t GetBitmapBufferSize() const = 0;

	// Bitmap
	virtual REBitmap* GetBitmap() const = 0;

	// Canvas
	virtual RECanvas* GetCanvas() const = 0;

	// BitmapBuffer
	virtual void LockBuffer() = 0;
	virtual void UnlockBuffer() = 0;

	// ,.
	virtual kn_dword GetWidth() const = 0;

	// ,
	virtual kn_dword GetHeight() const = 0;

	// 
	virtual kn_dword GetXPitch() const = 0;

	// 
	virtual kn_dword GetYPitch() const = 0;

	// 
	virtual REBitmap::Config GetColorFormat() const = 0;

	//  
	virtual void DrawColor(REColor color, SkXfermode::Mode mode = SkXfermode::ksrcOver_Mode) = 0;
	virtual void Clear(REColor ) = 0;
	// 
	virtual void DrawPoint(REScalar x, REScalar y, REColor color) = 0;
	virtual void DrawPoint(REScalar x, REScalar y, const REPaint& paint) = 0;
	
	// 
	virtual void DrawLine(REScalar x1, REScalar y1, REScalar x2, REScalar y2, const REPaint& paint) = 0;

	// 
	virtual void DrawLines(const REPoint* pPoint, size_t count, const REPaint& paint) = 0;

	// DashLine
	// : pPoint&count, pIntervals&interCount, phase
	// , , pIntervals = {20, 20}, 
	// dot dash line, pIntervals = {30, 20, 5, 20}, 30, 20, dot5, 20, 
	// phase, phase mod (pIntervals), pIntervals = {20, 20}, phase-5, 35, 75, 
	virtual void DrawDashLine(const REPoint* pPoint, size_t count, const REScalar* pIntervals, size_t interCount,  REScalar phase, const REPaint& paint) = 0;

	// 
	virtual void DrawRect(const RERect& rct, const REPaint& paint) = 0;

	// , framearea
	virtual void DrawPolygon(const REPoint* pPoint, size_t count, kn_bool bClose, const REPaint& paint ) = 0;

	// , , , frame
	virtual void DrawPonits(SkCanvas::PointMode mode, size_t count, const REPoint pts[], const REPaint& paint ) = 0;

	// 
	virtual void DrawCircle(REScalar x, REScalar y, REScalar radius, const REPaint& paint) = 0;
	virtual void DrawArc(RERect& oval, SkScalar startAngle, SkScalar sweepAngle, bool useCenter, SkPaint& paint) = 0;

	// , (left(), top())
	virtual kn_bool DrawBitmap(const IRESurface* pSourceRE, 
		REScalar left, 
		REScalar top, 
		const REPaint* pPaint = 0) = 0;

	// 
	virtual bool DrawBitmapMatrix(const IRESurface* pSourceRE, const REMatrix& m, const REPaint* pPaint = 0) = 0;

	virtual void drawBitmapNine(const IRESurface* bitmap, const RERect& center, const RERect& dst, const SkPaint* paint = NULL) = 0;
	
	// , srcRect(left(), top())
	virtual kn_bool DrawPartialBitmap(const IRESurface* pSourceRE, 
		RERect srcRect,
		REScalar destLeft, 
		REScalar destTop, 
		const REPaint* pPaint = 0) = 0;

	// , 
	virtual kn_bool DrawBitmapRectToRect(const IRESurface* pSourceRE, 
		const RERect* pSourceRect, 
		const RERect& destRect, 
		const REPaint* pPaint = 0) = 0;
	//
	virtual void DrawPaint(const REPaint& pPaint) = 0;
	// 
	virtual void DrawText(const void* text, size_t byteLength, REScalar x,
		REScalar y, const REPaint& paint) = 0;
		virtual void DrawText(const kn_string& text, REScalar x,
		REScalar y, const REPaint& paint) = 0;
	// 
	    /** Draw the text, with origin at (x,y), using the specified paint, along
        the specified path. The paint's Align setting determins where along the
        path to start the text.
        @param path         The path the text should follow for its baseline
        @param hOffset      The distance along the path to add to the text's
                            starting position
        @param vOffset      The distance above(-) or below(+) the path to
                            position the text
        @param paint        The paint used for the text
    */
    virtual void DrawTextOnPathHV(const kn_string& text,
                          const REPath& path, REScalar hOffset,
                          REScalar vOffset, const REPaint& paint) = 0;
	/** Draw the text, with origin at (x,y), using the specified paint, along
    the specified path. The paint's Align setting determins where along the
    path to start the text.
    @param path         The path the text should follow for its baseline
    @param matrix       (may be null) Applied to the text before it is
                        mapped onto the path
    @param paint        The paint used for the text
    */
    virtual void DrawTextOnPath(const kn_string& text, size_t byteLength,
                                const REPath& path, const REMatrix* matrix,
                                const REPaint& paint) = 0;

	// matrixclip
	virtual int Save() = 0;

	// savematrixclip
	virtual void Restore() = 0;

	// 
	virtual bool ClipRect(const RERect& rect,  RERegion::Op op = RERegion::kIntersect_Op, bool doAntiAlias = false) = 0;

	// surface, PNG, JPEG
	virtual bool WriteToFile(const kn_string& path, REImageEncoder::Type type = REImageEncoder::kPNG_Type, kn_int quality = 100) = 0;

	// 
	virtual void Flip(LSTRECT &lst_rect) = 0;

	// 
	virtual void DrawOval(const RERect& oval, const REPaint& paint) = 0;

	// 
	virtual void DrawRoundRect(const RERect& rect, REScalar rx, REScalar ry, const REPaint& paint) = 0;

	// 
	virtual void DrawPath(const REPath& path, const REPaint& paint) = 0;

	// 
	virtual bool Translate(REScalar dx, REScalar dy) = 0;

	// 
	virtual bool Scale(REScalar sx, REScalar sy) = 0;

	// 
	virtual bool Rotate(REScalar degrees) = 0;

	// 
	virtual bool Skew(REScalar sx, REScalar sy) = 0;

	// 
	virtual REMatrix GetTotalMatrix() = 0;

	// 
	virtual void SetMatrix(const REMatrix& m) = 0;

	// 
	virtual void Concat(const REMatrix& m) = 0;

	// 
	virtual void ResetMatrix() = 0;

	//screendraw
	virtual void preDraw() = 0;

	virtual REColor getColor(int x, int y) = 0;

};

// RESurface Factory, Skia2D
class RESurfaceFactory
{
public:
	// surface
	static IRESurface* CreateRESurface();

	// surface, , 
	static IRESurface* CreateRESurface(kn_int width, kn_int height, REBitmap::Config colorFormat);

	static IRESurface* CreateRESurface(void* p, kn_int width, kn_int height, REBitmap::Config colorFormat);

	// surface, , 
	static IRESurface* CreateRESurface(const kn_string& filePath);

#if defined(WIN32)
	// Win32surface
	static IRESurface* CreateDeviceReSurface(HDC,kn_int width, kn_int height, REBitmap::Config colorFormat);
	static IRESurface* CreateLayerDeviceReSurface(HWND wnd, HDC hdc,kn_int w, kn_int h, REBitmap::Config cf);
	static IRESurface* CreateDDrawReSurface(HWND,kn_int width, kn_int height, REBitmap::Config colorFormat);
	static IRESurface* CreateGLReSurface(HDC,kn_int width, kn_int height, REBitmap::Config colorFormat);
	static IRESurface* CreateSkiaGLReSurface(HWND wnd, kn_int w, kn_int h, REBitmap::Config cf);
	static IRESurface* CreateGLLayerDeviceReSurface(HWND wnd, HDC hdc,kn_int w, kn_int h, REBitmap::Config cf);

#elif ANDROID_NDK


	static IRESurface* CreateAndroidReSurface(char* buff, kn_int width, kn_int height, REBitmap::Config colorFormat);
    
#elif IOS_DEV
    
    static IRESurface* CreateIOSReSurface(void*& buff, kn_int width, kn_int height, REBitmap::Config colorFormat);
    

#elif QT_HMI

    static IRESurface* CreateQtSoftReSurface(void* p, kn_int width, kn_int height, REBitmap::Config colorFormat);

#endif

};

}
#endif
