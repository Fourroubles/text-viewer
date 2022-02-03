#ifndef SCROLL_H_INCLUDED
#define SCROLL_H_INCLUDED

#include "header.h"

/** ������ �������� � ��������� ������ ����� ��������� ������� �������. � ������ ��� ��������.
@Param[hwnd] - ��������� ����
@Param[text] - ������ �������������� ������
@Param[view] - ������ �������������� �����������
*/
void instalScrollWithoutWrap(HWND hwnd, text_t *text, view_t *view);

/** ������ �������� � ��������� ������ ����� ��������� ������� �������. � ������ �� ��������.
@Param[hwnd] - ��������� ����
@Param[text] - ������ �������������� ������
@Param[view] - ������ �������������� �����������
*/
void instalScrollWithWrap(HWND hwnd, text_t *text, view_t *view);

/** ������� ����� ������� ������ � ������ ������� �����
@Param[text] - ������ �������������� ������
@Param[view] - ������ �������������� �����������
*/
int strCountLines(text_t *text, view_t *view);

/** ������� ������ �������� �������������� ������� �������� ������ � ������ ������� �������
@Param[text] - ������ �������������� ������
@Param[view] - ������ �������������� �����������
*/
int findStrIndex(text_t* text, view_t *view);

/** ��������� ���������� �����
@Param[text] - ������ �������������� ������
@Param[view] - ������ �������������� �����������
*/
void updateStrCount(text_t *text, view_t *view);

/** ��������� ������ ������ �����
@Param[text] - ������ �������������� ������
@Param[view] - ������ �������������� �����������
*/
void updateStrStart(text_t *text,  view_t *view);

#endif // SCROLL_H_INCLUDED
