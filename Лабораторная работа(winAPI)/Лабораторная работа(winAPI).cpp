﻿#include <Windows.h>
#include "resource.h"

CONST CHAR gsz_LOGIN_INVITATION[] = "Enter username";
CONST CHAR gsz_PASSWORD_INVITATION[] = "Enter password";

//#define MSG_BOX

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), (LPSTR)IDI_ICON1);
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);

		SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)gsz_LOGIN_INVITATION);
		SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)gsz_PASSWORD_INVITATION);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			if (HIWORD(wParam) == EN_SETFOCUS)
			{
				if(strcmp(sz_buffer, gsz_LOGIN_INVITATION) == 0)
				SendMessage(hEditLogin, WM_SETTEXT, 0, (LPARAM)"");
			}
			if (HIWORD(wParam) == EN_KILLFOCUS)
			{
				SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
				if (strlen(sz_buffer) == 0)
					SendMessage(hEditLogin, WM_SETTEXT, SIZE, (LPARAM)gsz_LOGIN_INVITATION);
			}
		}
		break;
		case IDC_BUTTON_COPY:
		{
			CONST INT SIZE = 256;
			CHAR buffer[SIZE] = {};
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)buffer);
		}
		break;
		case IDOK:MessageBox(NULL, "Была нажата кнопка ОК", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL:EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShoe)
{
	#ifdef MSG_BOX
	MessageBox(NULL, "Привет! Это наше первое сообщение", "Заголовок окна сообщения!", MB_YESNOCANCEL | MB_ICONWARNING | MB_DEFBUTTON2);

	#endif // MSG_BOX

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);

	return 0;
}
