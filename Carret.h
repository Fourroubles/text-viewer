#ifndef CARRET_H_INCLUDED
#define CARRET_H_INCLUDED

#include "header.h"

/** Перемещает каретку на 1 позоцию вправо
@Param[hwnd] - Описатель окна
@Param[caret] - Модель каретки
@Param[text] - Модель предоставления текста
@Param[view] - Модель предоставления отображения
*/
void caretRight(HWND hwnd, caret_t *caret, text_t *text, view_t *view);

/** Перемещает каретку на 1 позоцию влево
@Param[hwnd] - Описатель окна
@Param[caret] - Модель каретки
@Param[text] - Модель предоставления текста
@Param[view] - Модель предоставления отображения
*/
void caretLeft(HWND hwnd, caret_t *caret, text_t *text, view_t *view);

/** Перемещает каретку на 1 позоцию вниз
@Param[hwnd] - Описатель окна
@Param[caret] - Модель каретки
@Param[text] - Модель предоставления текста
@Param[view] - Модель предоставления отображения
*/
void caretBottom(HWND hwnd, caret_t *caret, text_t *text, view_t *view);

/** Перемещает каретку на 1 позоцию вверх
@Param[hwnd] - Описатель окна
@Param[caret] - Модель каретки
@Param[text] - Модель предоставления текста
@Param[view] - Модель предоставления отображения
*/
void caretUp(HWND hwnd, caret_t *caret, text_t *text, view_t *view);

/** Коректирует положение картеки после нажатия клавиши вправо
@Param[hwnd] - Описатель окна
@Param[caret] - Модель каретки
@Param[text] - Модель предоставления текста
@Param[view] - Модель предоставления отображения
*/
void correctCarretRH(HWND hwnd, caret_t *caret, text_t *text, view_t *view);

/** Коректирует положение картеки после нажатия клавиши влево
@Param[hwnd] - Описатель окна
@Param[caret] - Модель каретки
@Param[text] - Модель предоставления текста
@Param[view] - Модель предоставления отображения
*/
void correctCarretLH(HWND hwnd, caret_t *caret, text_t *text, view_t *view);

/** Коректирует положение картеки по вертикали
@Param[hwnd] - Описатель окна
@Param[caret] - Модель каретки
@Param[text] - Модель предоставления текста
@Param[view] - Модель предоставления отображения
*/
void correctCarretV(HWND hwnd, caret_t *caret, text_t *text, view_t *view);

#endif // CARRET_H_INCLUDED
