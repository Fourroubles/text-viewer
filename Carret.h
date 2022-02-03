#ifndef CARRET_H_INCLUDED
#define CARRET_H_INCLUDED

#include "header.h"

/** ���������� ������� �� 1 ������� ������
@Param[hwnd] - ��������� ����
@Param[caret] - ������ �������
@Param[text] - ������ �������������� ������
@Param[view] - ������ �������������� �����������
*/
void caretRight(HWND hwnd, caret_t *caret, text_t *text, view_t *view);

/** ���������� ������� �� 1 ������� �����
@Param[hwnd] - ��������� ����
@Param[caret] - ������ �������
@Param[text] - ������ �������������� ������
@Param[view] - ������ �������������� �����������
*/
void caretLeft(HWND hwnd, caret_t *caret, text_t *text, view_t *view);

/** ���������� ������� �� 1 ������� ����
@Param[hwnd] - ��������� ����
@Param[caret] - ������ �������
@Param[text] - ������ �������������� ������
@Param[view] - ������ �������������� �����������
*/
void caretBottom(HWND hwnd, caret_t *caret, text_t *text, view_t *view);

/** ���������� ������� �� 1 ������� �����
@Param[hwnd] - ��������� ����
@Param[caret] - ������ �������
@Param[text] - ������ �������������� ������
@Param[view] - ������ �������������� �����������
*/
void caretUp(HWND hwnd, caret_t *caret, text_t *text, view_t *view);

/** ����������� ��������� ������� ����� ������� ������� ������
@Param[hwnd] - ��������� ����
@Param[caret] - ������ �������
@Param[text] - ������ �������������� ������
@Param[view] - ������ �������������� �����������
*/
void correctCarretRH(HWND hwnd, caret_t *caret, text_t *text, view_t *view);

/** ����������� ��������� ������� ����� ������� ������� �����
@Param[hwnd] - ��������� ����
@Param[caret] - ������ �������
@Param[text] - ������ �������������� ������
@Param[view] - ������ �������������� �����������
*/
void correctCarretLH(HWND hwnd, caret_t *caret, text_t *text, view_t *view);

/** ����������� ��������� ������� �� ���������
@Param[hwnd] - ��������� ����
@Param[caret] - ������ �������
@Param[text] - ������ �������������� ������
@Param[view] - ������ �������������� �����������
*/
void correctCarretV(HWND hwnd, caret_t *caret, text_t *text, view_t *view);

#endif // CARRET_H_INCLUDED
