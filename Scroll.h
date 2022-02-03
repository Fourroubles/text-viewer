#ifndef SCROLL_H_INCLUDED
#define SCROLL_H_INCLUDED

#include "header.h"

/** Задает интервал и положение скрола после изменения раюочей области. В режиме без смещения.
@Param[hwnd] - Описатель окна
@Param[text] - Модель предоставления текста
@Param[view] - Модель предоставления отображения
*/
void instalScrollWithoutWrap(HWND hwnd, text_t *text, view_t *view);

/** Задает интервал и положение скрола после изменения раюочей области. В режиме со смещения.
@Param[hwnd] - Описатель окна
@Param[text] - Модель предоставления текста
@Param[view] - Модель предоставления отображения
*/
void instalScrollWithWrap(HWND hwnd, text_t *text, view_t *view);

/** Находит номер текущей строки с учетом дробных строк
@Param[text] - Модель предоставления текста
@Param[view] - Модель предоставления отображения
*/
int strCountLines(text_t *text, view_t *view);

/** Находит индекс элемента соотвествующий первому элементу строки в начале рабочей области
@Param[text] - Модель предоставления текста
@Param[view] - Модель предоставления отображения
*/
int findStrIndex(text_t* text, view_t *view);

/** Обновляет количество строк
@Param[text] - Модель предоставления текста
@Param[view] - Модель предоставления отображения
*/
void updateStrCount(text_t *text, view_t *view);

/** Обновляет массив начала строк
@Param[text] - Модель предоставления текста
@Param[view] - Модель предоставления отображения
*/
void updateStrStart(text_t *text,  view_t *view);

#endif // SCROLL_H_INCLUDED
