#include "Paint.h"

void textWithoutWrap(HDC hdc, text_t* text, view_t *view, PAINTSTRUCT ps){
    unsigned long i;
    char *textForPrint = NULL;
    unsigned int x = 0, y = 0;
    unsigned int strLenght = 0;
    unsigned int paintBeg = max(0, view->iVscrollPos + ps.rcPaint.top / view->cyChar - 1);
    unsigned int paintEND = min(text->strCount, view->iVscrollPos + ps.rcPaint.bottom / view->cyChar);

    for(i = paintBeg; i < paintEND; ++i){
        x = view->cxChar * (- view->iHscrollPos);
        y = view->cyChar * (- view->iVscrollPos + i);
        textForPrint = (char*)text->str + text->strStart[i];
        strLenght = text->strStart[i + 1] - text->strStart[i];
        TextOut(hdc, x, y, textForPrint, strLenght);
    }
}
