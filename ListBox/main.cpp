#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include "resource.h"

CONST CHAR* string[] = { "This", "is", "my", "first", "List", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShoe)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hList = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(string) / sizeof(string[0]); i++)
		{
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)string[i]);
		}
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			CHAR sz_output_buffer[SIZE] = "�� ������� ������� � ";
			HWND hList = GetDlgItem(hwnd, IDC_LIST1);
			int i = SendMessage(hList, LB_GETCURSEL, 0, 0);
			SendMessage(hwnd, LB_GETTEXT, i, (LPARAM)sz_buffer);
			sprintf(sz_output_buffer, "�� ������� ������ � %i �� ��������� \"%s\".", i+1, sz_buffer);
			MessageBox(hwnd, sz_output_buffer, "Selected item", MB_OK | MB_ICONINFORMATION);
		}
		break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}