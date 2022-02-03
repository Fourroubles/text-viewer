#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "menu.h"

///Модель текста
typedef struct text_t {
	char* str;                      // Tескст
	unsigned int* strStart;         // Указатель на начало строки
	unsigned int strCount;          // Кол-во строк
	unsigned int maxStrLenght;      // Максимальная длинна строки
	size_t size;                    // Размер буффера
}text_t;

///Модель представления
typedef struct view_t {
	int cxChar;                     // Усредненная ширина символа
	int cyChar;                     // Высота символа
	int cxCaps;                     // Ширина символа верхнего регистра

    int cxClient;                   // Размер рабочего окна по вертикали
    int cyClient;                   // Размер рабочего окна по горизонтали

    int iVscrollPos;                // Позиция вертикального колесика прокрутки
    int iVscrollMax;                // Максимальная позиция вертикального колесика прокрутки
    int iVscrollInc;                // Параметр инкрементирования

    int iHscrollPre;                // Предыдущая позиция вертикального колесика прокрутки
    int iHscrollMax;                // Позиция горизонтального колесика прокрутки
    int iHscrollPos;                // Максимальная позиция горизонтального колесика прокрутки
    int iHscrollInc;                // Параметр инкрементирования

    int maxStrCount;                // Максимальное кол-во строк для режима с версткой

    int mode;                       // Режим выводв данных с вертской иди без
    int indexStr;                   // Указатель на первый элемент строки соотвествующей положению скролла
}view_t;

///Файл
typedef struct fileName_t {
    OPENFILENAME of;               // Bнформация для инициализации диалогового окна
    char name[256];                // Максимальный путь к файлу
}fileName_t;

///Модель каретки
typedef struct caret_t{
    int caretY;                    // Позиция каретки по вертикали
    int caretX;                    // Позиция каретки по горизонтали
}caret_t;

#endif // HEADER_H_INCLUDED
