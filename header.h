#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "menu.h"

///������ ������
typedef struct text_t {
	char* str;                      // T�����
	unsigned int* strStart;         // ��������� �� ������ ������
	unsigned int strCount;          // ���-�� �����
	unsigned int maxStrLenght;      // ������������ ������ ������
	size_t size;                    // ������ �������
}text_t;

///������ �������������
typedef struct view_t {
	int cxChar;                     // ����������� ������ �������
	int cyChar;                     // ������ �������
	int cxCaps;                     // ������ ������� �������� ��������

    int cxClient;                   // ������ �������� ���� �� ���������
    int cyClient;                   // ������ �������� ���� �� �����������

    int iVscrollPos;                // ������� ������������� �������� ���������
    int iVscrollMax;                // ������������ ������� ������������� �������� ���������
    int iVscrollInc;                // �������� �����������������

    int iHscrollPre;                // ���������� ������� ������������� �������� ���������
    int iHscrollMax;                // ������� ��������������� �������� ���������
    int iHscrollPos;                // ������������ ������� ��������������� �������� ���������
    int iHscrollInc;                // �������� �����������������

    int maxStrCount;                // ������������ ���-�� ����� ��� ������ � ��������

    int mode;                       // ����� ������ ������ � �������� ��� ���
    int indexStr;                   // ��������� �� ������ ������� ������ �������������� ��������� �������
}view_t;

///����
typedef struct fileName_t {
    OPENFILENAME of;               // B��������� ��� ������������� ����������� ����
    char name[256];                // ������������ ���� � �����
}fileName_t;

///������ �������
typedef struct caret_t{
    int caretY;                    // ������� ������� �� ���������
    int caretX;                    // ������� ������� �� �����������
}caret_t;

#endif // HEADER_H_INCLUDED
