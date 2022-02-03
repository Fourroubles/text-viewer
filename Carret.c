#include "Carret.h"

void correctCarretRH(HWND hwnd, caret_t *caret, text_t *text, view_t *view) {
    int strLenght = text->strStart[caret->caretY + view->iVscrollPos  + 1] - text->strStart[caret->caretY + view->iVscrollPos];
    strLenght = strLenght == 0 ? 1 : strLenght;

    if(caret->caretX + view->iHscrollPos == strLenght && caret->caretY + view->iVscrollPos != view->iVscrollMax + view->cyClient / view->cyChar - 1){
        if(caret->caretY == view->cyClient / view->cyChar - 1){
            view->iVscrollPos++;
        }
        else {
            caret->caretY++;
        }

        caret->caretX = 0;
        view->iHscrollPos = 0;
    }

    if(caret->caretY + view->iVscrollPos == view->iVscrollMax + view->cyClient / view->cyChar - 1 && caret->caretX == strLenght - view->iHscrollPos) {
        caret->caretX = strLenght - view->iHscrollPos - 1;
    }
}

void correctCarretLH(HWND hwnd, caret_t *caret, text_t *text, view_t *view) {

    if(caret->caretX == 0 && caret->caretY == 0 && view->iHscrollPos == 0 && view->iVscrollPos != 0){
       view->iVscrollPos--;
       caret->caretY++;
    }
    if(caret->caretX == 0 && view->iHscrollPos == 0 && caret->caretY != 0){
        caret->caretY--;
        caret->caretX = view->cxClient / view->cxChar;
        int strLenght = text->strStart[caret->caretY + view->iVscrollPos  + 1] - text->strStart[caret->caretY + view->iVscrollPos];
        view->iHscrollPos = strLenght - view->cxClient / view->cxChar;


        if(strLenght <= view->cxClient / view->cxChar){
            view->iHscrollPos = 0;
            caret->caretX = strLenght - 1 < 0 ? 0 : strLenght - 1;
        }
    }
}

void correctCarretV(HWND hwnd, caret_t *caret, text_t *text, view_t *view) {
    int strLenght = text->strStart[caret->caretY + view->iVscrollPos  + 1] - text->strStart[caret->caretY + view->iVscrollPos] - 1;

    if(caret->caretX + view->iHscrollPos >= strLenght){
        if(strLenght > view->iHscrollPos && strLenght < view->iHscrollPos + view->cxClient / view->cxChar){
            caret->caretX = strLenght - view->iHscrollPos - 1;
        }
        else{
            view->iHscrollPos = strLenght - view->cxClient / view->cxChar + 1;
            caret->caretX = strLenght - view->iHscrollPos;
        }

        view->iHscrollPos = view->iHscrollPos < 0 ? 0 : view->iHscrollPos;
        caret->caretX = strLenght < 1 ? 0 : strLenght - view->iHscrollPos;
    }
}

void caretRight(HWND hwnd, caret_t *caret, text_t *text, view_t *view)
{
    if((caret->caretX + 1 )* view->cxChar > view->cxClient && caret->caretX + view->iHscrollPos != view->iHscrollMax + view->cxClient / view->cxChar) {
        SendMessage(hwnd, WM_HSCROLL, SB_PAGEDOWN, 0L);

    }
    else {
        if(view->cxClient / view->cxChar + view->iHscrollMax != caret->caretX){
            caret->caretX++;
        }
    }

    correctCarretRH(hwnd, caret, text, view);
}

void caretLeft(HWND hwnd, caret_t *caret, text_t *text, view_t *view)
{
    if(caret->caretX == 0) {
        correctCarretLH(hwnd, caret, text, view);
        SendMessage(hwnd, WM_HSCROLL, SB_PAGEUP, 0L);
    }
    else{
        caret->caretX--;
    }
}

void caretBottom(HWND hwnd, caret_t *caret, text_t *text, view_t *view)
{
    if(caret->caretY * view->cyChar >= view->cyClient - 2 * view->cyChar) {
        SendMessage(hwnd, WM_VSCROLL, SB_LINEDOWN, 0L);
        caret->caretY = ++caret->caretY > view->cyClient / view->cyChar - 1 ? view->cyClient / view->cyChar - 1 : caret->caretY;
    }
    else{
        if(view->cyClient / view->cyChar + view->iVscrollMax != caret->caretY){
            caret->caretY++;
        }
    }

    correctCarretV(hwnd, caret, text, view);
}

void caretUp(HWND hwnd, caret_t *caret, text_t *text, view_t *view)
{
    if(caret->caretY == 0) {
        SendMessage(hwnd, WM_VSCROLL, SB_LINEUP, 0L);
        caret->caretY = --caret->caretY < 0 ? 0 : caret->caretY;
    }
    else{
        caret->caretY--;
    }

    correctCarretV(hwnd, caret, text, view);
}
