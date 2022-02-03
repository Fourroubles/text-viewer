#include "Carret.h"

void updateStrCount(text_t *text, view_t *view){
    unsigned int i;
    unsigned int strLenght = 0;
    int sizeWindow = view->cxClient/view->cxChar;

    text->strCount = 0;

    for(i = 0; i < text->size; ++i){
        strLenght++;
        if(text->str[i] == '\n' || (view->mode == IDM_WITH_WRAP && strLenght == sizeWindow)){
            text->strCount++;
            strLenght = 0;
        }
    }

    text->strCount = text->strCount + 1;
}

void updateStrStart(text_t *text,  view_t *view){
    unsigned int i;
    unsigned int strLenght = 0;
    unsigned int strCount = 0;
    int sizeWindow = view->cxClient/view->cxChar;

    free(text->strStart);
    text->strStart = (unsigned int*)calloc((text->strCount + 1), sizeof(unsigned int));
    text->strStart[strCount] = 0;

    for(i = 0; i < text->size; ++i){
        strLenght++;
        if(text->str[i] == '\n' || (view->mode == IDM_WITH_WRAP && strLenght == sizeWindow)){
            strCount++;
            text->strStart[strCount] = i + 1;
            strLenght = 0;
        }
    }

    text->strStart[strCount + 1] = i + 1;
}

unsigned int findStrIndex(text_t* text, view_t *view) {
    unsigned int countLines = 0;
    unsigned int i = 0;
    unsigned int stringLenght = 0;
    int windowLenght = view->cxClient / view->cxChar - 1;

    for(i = 0; i < view->iVscrollPos; ++i) {
        stringLenght = 0;
        while(text->str[countLines] != '\n'){
            if(stringLenght == windowLenght){
                break;
            }

            countLines++;
            stringLenght++;
        }

        countLines++;
    }

    return countLines;
}

int strCountLines(text_t* text, view_t *view) {
    unsigned int countLines = 0;
    unsigned int i = 0;
    unsigned int stringLenght = 0;
    int windowLenght = view->cxClient/view->cxChar - 1;

    for(i = 0; i < view->indexStr; ++i) {
        stringLenght = 0;
        while(text->str[i] != '\n'){
            if(stringLenght == windowLenght){
                break;
            }

            if(i >= view->indexStr){
                return countLines;
            }

            i++;
            stringLenght++;
        }

        countLines++;
    }

    return countLines;
}


void instalScrollWithoutWrap(HWND hwnd, text_t *text, view_t *view){
    updateStrCount(text, view);
    updateStrStart(text, view);

    view->iVscrollMax = max(0, (int)((int)text->strCount - view->cyClient / view->cyChar));
    view->iVscrollPos = min(view->iVscrollPos, view->iVscrollMax);
    SetScrollRange(hwnd, SB_VERT, 0, view->iVscrollMax, FALSE);
    SetScrollPos(hwnd, SB_VERT, view->iVscrollPos, TRUE);
    view->iHscrollMax = max(0, (int)(((int)text->maxStrLenght  * (int)view->cxChar  - (int)view->cxClient) / (int)view->cxChar));

    view->iHscrollPos = min(view->iHscrollPos, view->iHscrollMax);
    SetScrollRange(hwnd, SB_HORZ, 0, view->iHscrollMax, FALSE);
    SetScrollPos(hwnd, SB_HORZ, view->iHscrollPos, TRUE);
}

void instalScrollWithWrap(HWND hwnd, text_t *text, view_t *view){
    updateStrCount(text, view);
    updateStrStart(text, view);

    view->iVscrollMax = max(0, (int)((int)text->strCount - view->cyClient / view->cyChar));

    while(text->str[view->indexStr - 1] != '\n' && view->indexStr != 0){
        view->indexStr--;
    }

    view->iVscrollPos = strCountLines(text, view);
    view->iVscrollPos = min(view->iVscrollPos, view->iVscrollMax);
    SetScrollRange(hwnd, SB_VERT, 0, view->iVscrollMax, FALSE);
    SetScrollPos(hwnd, SB_VERT, view->iVscrollPos, TRUE);

    view->iHscrollPos = 0;
    SetScrollRange(hwnd, SB_HORZ, 0, 0, FALSE);
    SetScrollPos(hwnd, SB_HORZ, view->iHscrollPos, TRUE);
}
