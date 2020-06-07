#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <afxwin.h>
#include <afxcmn.h>


class CMaskedBitmap : public CBitmap
{
public:
    virtual void Draw (CDC*, int, int);
    virtual void DrawTransparent (CDC*, int, int, COLORREF);
};


#endif