#ifndef PAINT_H_INCLUDED
#define PAINT_H_INCLUDED

#include "header.h"

/** ����������� ������
@Param[hdc] - ��������� ��������� ����������
@Param[text] - ������ �������������� ������
@Param[view] - ������ �������������� �����������
@Param[ps] - ��������� ���������
*/
void textWithoutWrap(HDC hdc, text_t* text, view_t *view, PAINTSTRUCT ps);
#endif // PAINT_H_INCLUDED
