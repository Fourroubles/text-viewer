#include "Command.h"

BOOL fileRead(text_t *text, char *fileName)
{
    unsigned int i;
    unsigned int strCount = 0;
    unsigned int strLenght = 0;

    FILE *file = fopen(fileName, "r");

    if(file != NULL){
            fseek(file, 0, SEEK_END);
            text->size = ftell(file);
            rewind(file);

            text->str = (char*)calloc((text->size + 1), sizeof(char));
            text->strStart = (unsigned int*)calloc((text->size + 1), sizeof(unsigned int));

            if(text->str == NULL || text->strStart == NULL)
            {
                fclose(file);
                return FALSE;
            }

            fread(text->str, sizeof(char), text->size, file);
            text->strStart[strCount] = 0;
            text->maxStrLenght = 0;

            for(i = 0; i < text->size; ++i){
                if(text->str[i] == '\n'){
                        strCount++;
                        text->strStart[strCount] = i + 1;
                        strLenght = text->strStart[strCount] - text->strStart[strCount - 1];
                        text->maxStrLenght = text->maxStrLenght > strLenght ? text->maxStrLenght : strLenght;
                        text->size--;
                }
            }

            text->strStart[strCount + 1] = i + 1;
            text->strCount = strCount + 1;
    }
    else
    {
        fclose(file);
        return FALSE;
    }

    fclose(file);

    return TRUE;
}

void freeText(text_t *text)
{
    free(text->str);
    free(text->strStart);
    text->strCount = 0;
    text->maxStrLenght = 0;
}

void commandOpen(HWND hwnd, HMENU hmenu, fileName_t fileName, text_t *text, view_t *view, caret_t *caret){
    fileName.of.lStructSize = sizeof(OPENFILENAME); //размер структуры
    fileName.of.hwndOwner = hwnd; //родительское окно
    fileName.of.lpstrFilter = "text(*.TXT)\0*.txt\0\0"; //фильтр
    fileName.of.lpstrFile = fileName.name; //текстовая строка, в которую будет записано имя открываемого файла
    fileName.of.nMaxFile = 256; //максимальный путь - константа
    fileName.of.lpstrFileTitle = NULL; //буфер для хранения выбранного файла
    fileName.of.lpstrInitialDir = NULL; //папка, с которой начинается обзор
    fileName.of.lpstrTitle = "Открытие файла"; //заголовок окна - его вы придумываете сами
    fileName.of.Flags = OFN_HIDEREADONLY; //флаги для открытия файла



    if(GetOpenFileName(&fileName.of))
    {
        freeText(text);
        if(!fileRead(text, fileName.name)){
            DestroyWindow(hwnd);
        }
    }

    view->mode = IDM_WITHOUT_WRAP;
    caret->caretX = 0;
    caret->caretY = 0;
    view->iHscrollPos = 0;
    view->iVscrollPos = 0;
    view->indexStr = 0;
    view->iHscrollPre = 0;

    instalScrollWithoutWrap(hwnd, text, view);

    EnableMenuItem(hmenu, IDM_WITH_WRAP, MF_ENABLED);
    EnableMenuItem(hmenu, IDM_WITHOUT_WRAP, MF_DISABLED);
}

void commandEnableWrap(HWND hwnd, HMENU hmenu, caret_t *caret, text_t *text, view_t *view, PAINTSTRUCT ps){
    view->mode = IDM_WITH_WRAP;
    instalScrollWithWrap(hwnd, text, view);
    caret->caretX = 0;
    caret->caretY = 0;
    view->iHscrollPos = 0;
    view->iVscrollPos = 0;
    SetCaretPos(caret->caretX * view->cxChar, caret->caretY * view->cyChar);
    SetScrollPos(hwnd, SB_VERT, view->iVscrollPos, TRUE);
    SetScrollPos(hwnd, SB_HORZ, view->iHscrollPos, TRUE);
    EnableMenuItem(hmenu, IDM_WITH_WRAP, MF_DISABLED);
    EnableMenuItem(hmenu, IDM_WITHOUT_WRAP, MF_ENABLED);
}

void commandDisableWpar(HWND hwnd, HMENU hmenu, caret_t *caret, text_t *text, view_t *view){
    view->mode = IDM_WITHOUT_WRAP;
    instalScrollWithoutWrap(hwnd, text, view);
    caret->caretX = 0;
    caret->caretY = 0;
    view->iVscrollPos = 0;
    SetCaretPos(caret->caretX * view->cxChar, caret->caretY * view->cyChar);
    SetScrollPos(hwnd, SB_VERT, view->iVscrollPos, TRUE);
    EnableMenuItem(hmenu, IDM_WITH_WRAP, MF_ENABLED);
    EnableMenuItem(hmenu, IDM_WITHOUT_WRAP, MF_DISABLED);
}
