//  **************************************
//  File:        KTextMultiLineDrawable.h
//  ***************************************
#ifndef K_TEXTMULTILINE_DRAWABLE_H
#define K_TEXTMULTILINE_DRAWABLE_H

#include "KTextDrawable.h"
#include "DataSync.h"

#define ALIGN_TOP 0
#define ALIGN_CENTER 1
#define ALIGN_BOTTOM 2

class API KTextMultiLineDrawable : public KTextDrawable
{
public:
	KTextMultiLineDrawable( REColor color,  kn_int iFontSize, REPaint::Align align);
	virtual void Draw(IRESurface* pDstSurface, const REMatrix* pMatrix = 0, int iDstX = 0, int iDstY = 0);

	int GetTextLine(std::vector<kn_string>& vStr);

	virtual void SetText(const kn_char* szText);
	virtual void SetText(const kn_string& szText);

	void setAlignType(int type){m_aligntype = type;};
	int getAlignType(){return m_aligntype;};

	// 
	void autoMLine();

	//
//	void getTextWH(int &w, int& h);

	//
	int getLine();
	int getMaxWidth();
	void setRowInterval(int);
	void setMaxLine(int);
	bool isOverroad(); //
protected:
	//string
    boost::shared_mutex    m_draw_string_mutex;
	std::vector<kn_string> m_v_draw_string;
	int m_aligntype;

	//
	int m_txt_row_interval;
	//
	//int m_txt_line;
	int m_multi_line_w;
	int m_max_line;
	kn_bool m_b_overroad;	//
};

typedef boost::shared_ptr<KTextMultiLineDrawable> KTextMultiLineDrawable_PTR;

#endif
