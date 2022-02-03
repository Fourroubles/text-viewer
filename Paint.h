#ifndef PAINT_H_INCLUDED
#define PAINT_H_INCLUDED

#include "header.h"

/** Отображение текста
@Param[hdc] - Описатель контекста устройства
@Param[text] - Модель предоставления текста
@Param[view] - Модель предоставления отображения
@Param[ps] - Структура рисования
*/
void textWithoutWrap(HDC hdc, text_t* text, view_t *view, PAINTSTRUCT ps);
#endif // PAINT_H_INCLUDED
