//  **************************************
//  File:        SkiaRESurface.h
//  ***************************************

#ifndef RESurface_DEFINED
#define RESurface_DEFINED

#include "renderingengine.h"

using namespace skia_surface;
class API RESurface: public IRESurface
{
public:
	RESurface();

	virtual ~RESurface();

	virtual kn_bool Initialize(kn_dword width, kn_dword height, REBitmap::Config colorFormat);
	
	virtual kn_bool Initialize(void* p, kn_dword width, kn_dword height, REBitmap::Config colorFormat);

	virtual kn_bool InitializeFromFile(const kn_string& filename);

	virtual kn_bool InitializeThumbnailFromFile(const kn_string& filename, int width, int height, int scalemode, REColor bkgcolor);

	virtual kn_bool InitializeFromPicBuffer(const kn_byte* pBuf, kn_int iBufLen);

	virtual void Release();

	virtual kn_bool IsInitialized();

	virtual kn_byte* GetBitmapBuffer() const;

	virtual size_t GetBitmapBufferSize() const;

	virtual REBitmap* GetBitmap() const;

	virtual RECanvas* GetCanvas() const;

	virtual void LockBuffer();
	virtual void UnlockBuffer();

	virtual kn_dword GetWidth() const;

	virtual kn_dword GetHeight() const;

	virtual kn_dword GetXPitch() const;

	virtual kn_dword GetYPitch() const;

	virtual REBitmap::Config GetColorFormat() const;

	virtual void DrawColor(REColor color, SkXfermode::Mode mode = SkXfermode::ksrcOver_Mode);

	virtual void Clear(REColor );
	virtual void DrawPoint(REScalar x, REScalar y, REColor color);
	virtual void DrawPoint(REScalar x, REScalar y, const REPaint& paint);

	virtual void DrawLine(REScalar x1, REScalar y1, REScalar x2, REScalar y2, const REPaint& paint);

	virtual void DrawLines(const REPoint* pPoint, size_t count, const REPaint& paint);

	virtual void DrawDashLine(const REPoint* pPoint, size_t count, const REScalar* pIntervals, size_t interCount,  REScalar phase, const REPaint& paint);

	virtual void DrawRect(const RERect& rct, const REPaint& paint);

	virtual void DrawPolygon(const REPoint* pPoint, size_t count, kn_bool bClose, const REPaint& paint );

	virtual void DrawPonits(SkCanvas::PointMode mode, size_t count, const REPoint pts[], const REPaint& paint );

	virtual void DrawCircle(REScalar x, REScalar y, REScalar radius, const REPaint& paint);

	virtual void DrawArc(RERect& oval, SkScalar startAngle, SkScalar sweepAngle, bool useCenter, SkPaint& paint);

	virtual kn_bool DrawBitmap(const IRESurface* pSourceRE, 
		REScalar left, 
		REScalar top, 
		const REPaint* pPaint);

	virtual bool DrawBitmapMatrix(const IRESurface* pSourceRE, const REMatrix& m, const REPaint* pPaint);

	virtual kn_bool DrawPartialBitmap(const IRESurface* pSourceRE, 
		RERect srcRect,
		REScalar destLeft, 
		REScalar destTop, 
		const REPaint* pPaint);

	virtual void drawBitmapNine(const IRESurface* bitmap, const RERect& center, const RERect& dst, const SkPaint* paint = NULL);

	virtual kn_bool DrawBitmapRectToRect(const IRESurface* pSourceRE, 
		const RERect* pSourceRect, 
		const RERect& destRect, 
		const REPaint* pPaint);
	virtual void DrawPaint(const REPaint& pPaint);
	virtual void DrawText(const void* text, size_t byteLength, REScalar x,
		REScalar y, const REPaint& paint);
	virtual void DrawText(const kn_string& text, REScalar x,
		REScalar y, const REPaint& paint);
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
                          REScalar vOffset, const REPaint& paint);
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
                                const REPaint& paint);

	virtual int Save();

	virtual void Restore();

	virtual bool ClipRect(const RERect& rect, RERegion::Op op = RERegion::kIntersect_Op, bool doAntiAlias = false);

	virtual void Flip(LSTRECT &lst_rect){};

	virtual bool WriteToFile(const kn_string& path, REImageEncoder::Type type = REImageEncoder::kPNG_Type, kn_int quality = 100);

	virtual void DrawOval(const RERect& oval, const REPaint& paint);

	virtual void DrawRoundRect(const RERect& rect, REScalar rx, REScalar ry, const REPaint& paint);

	virtual void DrawPath(const REPath& path, const REPaint& paint);

	virtual bool Translate(REScalar dx, REScalar dy);

	virtual bool Scale(REScalar sx, REScalar sy);

	virtual bool Rotate(REScalar degrees);

	virtual bool Skew(REScalar sx, REScalar sy);

	virtual REMatrix GetTotalMatrix();

	virtual void SetMatrix(const REMatrix& m);

	virtual void Concat(const REMatrix& m);

	virtual void ResetMatrix();

	virtual void preDraw();

	virtual REColor getColor(int x, int y);
protected:
	RECanvas* m_pCanvas;
	REBitmap* m_pBitmap;
};

#endif