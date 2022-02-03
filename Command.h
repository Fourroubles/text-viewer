#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

//#include "header.h"
#include "Scroll.h"

/** Открывает файл
@Param[text] - Модель предоставления текста
@Param[fileName] - путь к файлу
@Return - true: открытие файла произошло успешно, false: не получилось открыть файл
*/
BOOL fileRead(text_t *text, char *fileName);

/** Освобождает память из модели предоставления текста
@Param[text] - Модель предоставления текста
*/
void freeText(text_t *text);

/** Иницилизирует структуру предоставления файла и передает команду на открытие файла
@Param[hwnd] - Описатель окна
@Param[hmenu] - Дескриптор меню
@Param[fileName] - Струкутра файла
@Param[text] - Модель предоставления текста
@Param[view] - Модель предоставления отображения
@Param[caret] - Модель каретки
*/
void commandOpen(HWND hwnd, HMENU hmenu, fileName_t fileName, text_t *text, view_t *view, caret_t *caret);

/** Включает режим с версткой
@Param[hwnd] - Описатель окна
@Param[hmenu] - Дескриптор меню
@Param[caret] - Модель каретки
@Param[text] - Модель предоставления текста
@Param[view] - Модель предоставления отображения
@Param[ps] - Структура рисования
*/
void commandEnableWrap(HWND hwnd, HMENU hmenu, caret_t *caret, text_t *text, view_t *view, PAINTSTRUCT ps);

/** Включает режим без верстки
@Param[hwnd] - Описатель окна
@Param[hmenu] - Дескриптор меню
@Param[caret] - Модель каретки
@Param[text] - Модель предоставления текста
@Param[view] - Модель предоставления отображения
*/
void commandDisableWpar(HWND hwnd, HMENU hmenu, caret_t *caret, text_t *text, view_t *view);

#endif
