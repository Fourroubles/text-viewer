#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

//#include "header.h"
#include "Scroll.h"

/** ��������� ����
@Param[text] - ������ �������������� ������
@Param[fileName] - ���� � �����
@Return - true: �������� ����� ��������� �������, false: �� ���������� ������� ����
*/
BOOL fileRead(text_t *text, char *fileName);

/** ����������� ������ �� ������ �������������� ������
@Param[text] - ������ �������������� ������
*/
void freeText(text_t *text);

/** ������������� ��������� �������������� ����� � �������� ������� �� �������� �����
@Param[hwnd] - ��������� ����
@Param[hmenu] - ���������� ����
@Param[fileName] - ��������� �����
@Param[text] - ������ �������������� ������
@Param[view] - ������ �������������� �����������
@Param[caret] - ������ �������
*/
void commandOpen(HWND hwnd, HMENU hmenu, fileName_t fileName, text_t *text, view_t *view, caret_t *caret);

/** �������� ����� � ��������
@Param[hwnd] - ��������� ����
@Param[hmenu] - ���������� ����
@Param[caret] - ������ �������
@Param[text] - ������ �������������� ������
@Param[view] - ������ �������������� �����������
@Param[ps] - ��������� ���������
*/
void commandEnableWrap(HWND hwnd, HMENU hmenu, caret_t *caret, text_t *text, view_t *view, PAINTSTRUCT ps);

/** �������� ����� ��� �������
@Param[hwnd] - ��������� ����
@Param[hmenu] - ���������� ����
@Param[caret] - ������ �������
@Param[text] - ������ �������������� ������
@Param[view] - ������ �������������� �����������
*/
void commandDisableWpar(HWND hwnd, HMENU hmenu, caret_t *caret, text_t *text, view_t *view);

#endif
