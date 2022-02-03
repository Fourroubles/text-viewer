#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include "header.h"
#include "Paint.h"
#include "Carret.h"
#include "Command.h"
#include "Scroll.h"

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    static char szAppName[] = "Text Viewer";
    char szMenu[]="MainMenu";
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX  wndclass;        /* Data structure for the windowclass */

    wndclass.cbSize = sizeof(wndclass);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WindowProcedure;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground =(HBRUSH) GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = szMenu;
    wndclass.lpszClassName = szAppName;
    wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&wndclass);

    hwnd = CreateWindow(
                        szAppName,
                        "Text Viewer",
                        WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        400,
                        500,
                        HWND_DESKTOP,
                        NULL,
                        hInstance,
                        szCmdLine
    );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, iCmdShow);
    UpdateWindow(hwnd);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    TEXTMETRIC tm;
    HMENU hmenu;
    SCROLLINFO si;
    static fileName_t fileName;
    static text_t text;
    static view_t view;
    static caret_t caret;

    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
        {
            hdc = GetDC(hwnd);
            SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
            GetTextMetrics(hdc, &tm);

            text.maxStrLenght = 0;
            text.strCount = 0;
            text.str = NULL;
            text.strStart = NULL;
            caret.caretX = caret.caretY = 0;
            view.cxClient = view.cyClient = view.iHscrollInc = view.iHscrollMax = view.iHscrollPos = view.iVscrollInc = view.iVscrollMax = view.iVscrollPos = 0;
            view.mode = IDM_WITHOUT_WRAP;
            view.cxChar = tm.tmAveCharWidth;
            view.cxCaps =(tm.tmPitchAndFamily & 1 ? 3 : 2) * view.cxChar / 2;
            view.cyChar = tm.tmHeight + tm.tmExternalLeading;

            hmenu = GetMenu(hwnd);
            EnableMenuItem(hmenu, IDM_WITH_WRAP, MF_GRAYED);
            EnableMenuItem(hmenu, IDM_WITHOUT_WRAP, MF_GRAYED);

            ReleaseDC(hwnd, hdc);
            return 0;
        }
        case WM_SIZE:
        {
            view.cxClient = LOWORD(lParam);
            view.cyClient = HIWORD(lParam);

            if(view.mode == IDM_WITHOUT_WRAP) {
                instalScrollWithoutWrap(hwnd, &text, &view);
            }
            else {
                if(view.mode == IDM_WITH_WRAP) {
                    instalScrollWithWrap(hwnd, &text, &view);
                }
            }

            InvalidateRect(hwnd, NULL, TRUE);
		    UpdateWindow(hwnd);

            return 0;
        }
        case WM_VSCROLL:
        {
            switch(LOWORD(wParam))
            {
                case SB_TOP:
                {
                    view.iVscrollInc = -view.iVscrollPos;
                    break;
                }
                case SB_BOTTOM:
                {
                    view.iVscrollInc = view.iVscrollMax - view.iVscrollPos;
                    break;
                }
                case SB_LINEUP:
                {
                    view.iVscrollInc = -1;
                    break;
                }
                case SB_LINEDOWN:
                {
                    view.iVscrollInc = 1;
                    break;
                }
                case SB_PAGEUP:
                {
                    view.iVscrollInc = min(-1, -view.cyClient/view.cyChar);
                    break;
                }
                case SB_PAGEDOWN:
                {
                    view.iVscrollInc = max(1, view.cyClient/view.cyChar);
                    break;
                }
                case SB_THUMBTRACK:
                {
                    ZeroMemory(&si, sizeof(si));
                    si.cbSize = sizeof(si);
                    si.fMask = SIF_TRACKPOS;

                    if (!GetScrollInfo(hwnd, SB_VERT, &si)){
                        break;
                    }

                    view.iVscrollInc = si.nTrackPos - view.iVscrollPos;

                    break;
                }
                default:
                {
                     view.iVscrollInc = 0;
                     break;
                }
            }

            view.iVscrollInc = max(-view.iVscrollPos, min(view.iVscrollInc, view.iVscrollMax - view.iVscrollPos));

            if (view.iVscrollInc != 0)
            {
                view.iVscrollPos += view.iVscrollInc;

                if(view.iVscrollInc > 0){
                    caret.caretY = --caret.caretY < 0 ? 0 : caret.caretY;
                    correctCarretV(hwnd, &caret, &text, &view);
                }
                else {
                    caret.caretY = ++caret.caretY > view.cyClient / view.cyChar - 1 ? view.cyClient / view.cyChar - 1 : caret.caretY;
                    correctCarretV(hwnd, &caret, &text, &view);
                }

                ScrollWindow(hwnd, 0, -view.cyChar * view.iVscrollInc, NULL, NULL);
                SetScrollPos(hwnd, SB_VERT, view.iVscrollPos, TRUE);
                SetCaretPos(caret.caretX * view.cxChar, caret.caretY * view.cyChar);
                view.indexStr = findStrIndex(&text, &view);
                InvalidateRect(hwnd, NULL, TRUE);
                UpdateWindow(hwnd);
            }

            return 0;
        }
        case WM_HSCROLL:
        {
            switch(LOWORD(wParam))
            {
                case SB_LINEUP:
                {
                    view.iHscrollInc = -1;
                    break;
                }
                case SB_LINEDOWN:
                {
                    view.iHscrollInc = 1;
                    break;
                }
                case SB_PAGEUP:
                {
                    view.iHscrollInc = -1;
                    break;
                }
                case SB_PAGEDOWN:
                {
                    view.iHscrollInc = 1;
                    break;
                }
                case SB_THUMBTRACK:
                {
                    ZeroMemory(&si, sizeof(si));
                    si.cbSize = sizeof(si);
                    si.fMask = SIF_TRACKPOS;

                    if (!GetScrollInfo(hwnd, SB_HORZ, &si)){
                        break;
                    }

                    view.iHscrollInc = si.nTrackPos - view.iHscrollPos;
                    break;
                }
                default:
                {
                     view.iHscrollInc = 0;
                     break;
                }
            }

            view.iHscrollInc = max(-view.iHscrollPos, min(view.iHscrollInc, view.iHscrollMax - view.iHscrollPos));

            if (view.iHscrollInc != 0)
            {
                view.iHscrollPos += view.iHscrollInc;
                ScrollWindow(hwnd, -view.cxChar * view.iHscrollInc, 0, NULL, NULL);
                SetScrollPos(hwnd, SB_HORZ, view.iHscrollPos, TRUE);
            }

            return 0;
        }
        case WM_KEYDOWN:
        {
            switch(wParam)
            {
                case VK_UP:
                {
                    view.iHscrollPos = view.iHscrollPre;
                    caretUp(hwnd, &caret, &text, &view);
                    break;
                }
                case VK_DOWN:
                {
                    view.iHscrollPos = view.iHscrollPre;
                    caretBottom(hwnd, &caret, &text, &view);
                    break;
                }
                case VK_LEFT:
                {
                    view.iHscrollPos = view.iHscrollPre;
                    caretLeft(hwnd, &caret, &text, &view);
                    break;
                }
                case VK_RIGHT:
                {
                    view.iHscrollPos = view.iHscrollPre;
                    caretRight(hwnd, &caret, &text, &view);
                    break;
                }
            }

            SetCaretPos(caret.caretX * view.cxChar, caret.caretY * view.cyChar);
            SetScrollPos(hwnd, SB_HORZ, view.iHscrollPos, TRUE);
            InvalidateRect(hwnd, NULL, TRUE);
            UpdateWindow(hwnd);
            view.iHscrollPre = view.iHscrollPos;
            return 0;
        }
        case WM_COMMAND:
        {
            hmenu = GetMenu(hwnd);

            switch(LOWORD(wParam))
            {
               case IDM_EXIT:
               {
                    DestroyWindow(hwnd);
                    break;
               }
               case IDM_OPEN:
               {
                   commandOpen(hwnd, hmenu, fileName, &text, &view, &caret);
                   InvalidateRect(hwnd, NULL, TRUE);
                   UpdateWindow(hwnd);
                   break;
               }
               case IDM_WITH_WRAP:
               {
                   commandEnableWrap(hwnd, hmenu, &caret, &text, &view, ps);
                   InvalidateRect(hwnd, NULL, TRUE);
                   UpdateWindow(hwnd);
                   break;
               }
               case IDM_WITHOUT_WRAP:
               {
                   commandDisableWpar(hwnd, hmenu, &caret, &text, &view);
                   InvalidateRect(hwnd, NULL, TRUE);
                   UpdateWindow(hwnd);
                   break;
               }
            }

        }
        case WM_SETFOCUS:
        {
            CreateCaret(hwnd, (HBITMAP)NULL, view.cxChar, view.cyChar);
            SetCaretPos(caret.caretX * view.cxChar, caret.caretY * view.cyChar);
            ShowCaret(hwnd);
            break;
        }
        case WM_PAINT:
        {
            hdc = BeginPaint(hwnd, &ps);
            SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
            textWithoutWrap(hdc, &text, &view, ps);
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_DESTROY:
        {
            freeText(&text);
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            return 0;
        }
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
