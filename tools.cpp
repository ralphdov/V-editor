#include <afxwin.h>
#include <afxcmn.h>
#include "tools.h"


void CMaskedBitmap::DrawTransparent (CDC* pDC, int x, int y,
    COLORREF crColor)
{
    BITMAP bm;
    GetObject (sizeof (BITMAP), &bm);
    CPoint size (bm.bmWidth, bm.bmHeight);
    pDC->DPtoLP (&size);

    CPoint org (0, 0);
    pDC->DPtoLP (&org);

    // crée un contexte de périphérique mémoire (dcImage) et y sélectionne le bitmap
    CDC dcImage;
    dcImage.CreateCompatibleDC (pDC);
    CBitmap* pOldBitmapImage = dcImage.SelectObject (this);
    dcImage.SetMapMode (pDC->GetMapMode ());

    // crée un second contexte de périphérique mémoire (dcAnd) et y crée un masque AND
    CDC dcAnd;
    dcAnd.CreateCompatibleDC (pDC);
    dcAnd.SetMapMode (pDC->GetMapMode ());

    CBitmap bitmapAnd;
    bitmapAnd.CreateBitmap (bm.bmWidth, bm.bmHeight, 1, 1, NULL);
    CBitmap* pOldBitmapAnd = dcAnd.SelectObject (&bitmapAnd);

    dcImage.SetBkColor (crColor);
    dcAnd.BitBlt (org.x, org.y, size.x, size.y, &dcImage, org.x, org.y,
        SRCCOPY);

    // crée un troisième contexte de périphérique mémoire (dcXor) et y crée un masque XOR
    CDC dcXor;
    dcXor.CreateCompatibleDC (pDC);
    dcXor.SetMapMode (pDC->GetMapMode ());

    CBitmap bitmapXor;
    bitmapXor.CreateCompatibleBitmap (&dcImage, bm.bmWidth, bm.bmHeight);
    CBitmap* pOldBitmapXor = dcXor.SelectObject (&bitmapXor);

    dcXor.BitBlt (org.x, org.y, size.x, size.y, &dcImage, org.x, org.y,
        SRCCOPY);

    dcXor.BitBlt (org.x, org.y, size.x, size.y, &dcAnd, org.x, org.y,
        0x220326);

    // copie les pixels du rectangle cible vers un
    // contexte de périphérique mémoire temporaire (dcTemp)
    CDC dcTemp;
    dcTemp.CreateCompatibleDC (pDC);
    dcTemp.SetMapMode (pDC->GetMapMode ());

    CBitmap bitmapTemp;
    bitmapTemp.CreateCompatibleBitmap (&dcImage, bm.bmWidth, bm.bmHeight);
    CBitmap* pOldBitmapTemp = dcTemp.SelectObject (&bitmapTemp);

    dcTemp.BitBlt (org.x, org.y, size.x, size.y, pDC, x, y, SRCCOPY);

    // génère l'image finale en appliquant les masques AND et XOR à
    // l'image rangée dans le contexte de périphérique mémoire temporaire
    dcTemp.BitBlt (org.x, org.y, size.x, size.y, &dcAnd, org.x, org.y,
        SRCAND);

    dcTemp.BitBlt (org.x, org.y, size.x, size.y, &dcXor, org.x, org.y,
        SRCINVERT);

    // copie l'image résultante sur l'écran
    pDC->BitBlt (x, y, size.x, size.y, &dcTemp, org.x, org.y, SRCCOPY);

    // restaure les bitmaps par défaut
    dcTemp.SelectObject (pOldBitmapTemp);
    dcXor.SelectObject (pOldBitmapXor);
    dcAnd.SelectObject (pOldBitmapAnd);
    dcImage.SelectObject (pOldBitmapImage);
}




void CMaskedBitmap::Draw (CDC* pDC, int x, int y)
{
 	BITMAP bm;
	CDC dcMem;
	CBitmap* pOldBitmap;

	dcMem.CreateCompatibleDC (pDC);
    GetObject (sizeof (BITMAP), &bm);
    /*CPoint size (bm.bmWidth, bm.bmHeight);
    pDC->DPtoLP (&size);

    CPoint org (0, 0);
    pDC->DPtoLP (&org);*/

    pOldBitmap = dcMem.SelectObject (this);
	dcMem.SetMapMode (pDC->GetMapMode ());

    //pDC->BitBlt (x, y, size.x, size.y, &dcMem, org.x, org.y, SRCCOPY);
	pDC->BitBlt (x, y, bm.bmWidth, bm.bmHeight, &dcMem, 0, 0, SRCCOPY);

    dcMem.SelectObject (pOldBitmap);
}
