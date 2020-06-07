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

    // cr�e un contexte de p�riph�rique m�moire (dcImage) et y s�lectionne le bitmap
    CDC dcImage;
    dcImage.CreateCompatibleDC (pDC);
    CBitmap* pOldBitmapImage = dcImage.SelectObject (this);
    dcImage.SetMapMode (pDC->GetMapMode ());

    // cr�e un second contexte de p�riph�rique m�moire (dcAnd) et y cr�e un masque AND
    CDC dcAnd;
    dcAnd.CreateCompatibleDC (pDC);
    dcAnd.SetMapMode (pDC->GetMapMode ());

    CBitmap bitmapAnd;
    bitmapAnd.CreateBitmap (bm.bmWidth, bm.bmHeight, 1, 1, NULL);
    CBitmap* pOldBitmapAnd = dcAnd.SelectObject (&bitmapAnd);

    dcImage.SetBkColor (crColor);
    dcAnd.BitBlt (org.x, org.y, size.x, size.y, &dcImage, org.x, org.y,
        SRCCOPY);

    // cr�e un troisi�me contexte de p�riph�rique m�moire (dcXor) et y cr�e un masque XOR
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
    // contexte de p�riph�rique m�moire temporaire (dcTemp)
    CDC dcTemp;
    dcTemp.CreateCompatibleDC (pDC);
    dcTemp.SetMapMode (pDC->GetMapMode ());

    CBitmap bitmapTemp;
    bitmapTemp.CreateCompatibleBitmap (&dcImage, bm.bmWidth, bm.bmHeight);
    CBitmap* pOldBitmapTemp = dcTemp.SelectObject (&bitmapTemp);

    dcTemp.BitBlt (org.x, org.y, size.x, size.y, pDC, x, y, SRCCOPY);

    // g�n�re l'image finale en appliquant les masques AND et XOR �
    // l'image rang�e dans le contexte de p�riph�rique m�moire temporaire
    dcTemp.BitBlt (org.x, org.y, size.x, size.y, &dcAnd, org.x, org.y,
        SRCAND);

    dcTemp.BitBlt (org.x, org.y, size.x, size.y, &dcXor, org.x, org.y,
        SRCINVERT);

    // copie l'image r�sultante sur l'�cran
    pDC->BitBlt (x, y, size.x, size.y, &dcTemp, org.x, org.y, SRCCOPY);

    // restaure les bitmaps par d�faut
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
