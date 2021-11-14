#include "DecoderAnimation.h"



void DecoderAnimation::setPathDirectory(const std::string& pathDirectory)
{
	this->pathDirectory = pathDirectory;
    std::cout << pathDirectory << std::endl;
	WIN32_FIND_DATAA wfd;
	HANDLE  hFile = FindFirstFileA(pathDirectory.c_str(), &wfd);
	size_t numberFileSize = -2;
	if (INVALID_HANDLE_VALUE != hFile)
	{
		do
		{
			numberFileSize++;

		} while (NULL != FindNextFileA(hFile, &wfd));
		FindClose(hFile);
	}
	std::cout << "numberFileSize:\n" << numberFileSize << std::endl;
	pathFile.resize(numberFileSize);
    vectorHBitmap.resize(numberFileSize);
}

void DecoderAnimation::searchFile()
{
	WIN32_FIND_DATAA wfd;
	HANDLE  hFile = FindFirstFileA(pathDirectory.c_str(), &wfd);

//	vecFile.resize(numberFileSize);
	setlocale(LC_ALL, "rus");
    pathDirectory.resize(pathDirectory.size() - 1);
    
    //supportPath.resize(supportPath.size() - 1);
  //  size_t size = supportPath.size() - 1;
	if (INVALID_HANDLE_VALUE != hFile)
	{
		int i = -2;
		do
		{

			if (i >= 0)

			{
			//	std::cout << wfd.cFileName /*& FILE_ATTRIBUTE_DIRECTORY ? "�������: " : "����: "*/ << std::endl;
              
             
                pathFile[i] = pathDirectory + wfd.cFileName;
			}

			i++;
		} while (NULL != FindNextFileA(hFile, &wfd));

		FindClose(hFile);
	}
}

void DecoderAnimation::initialize(int pos_x, int pos_y)
{
    for ( int i = 0; i < vectorHBitmap.size(); i++)
    {
        vectorHBitmap[i] = (HBITMAP)LoadImageA(GetModuleHandle(nullptr), pathFile[i].c_str(), IMAGE_BITMAP, pos_x, pos_y, LR_LOADFROMFILE);
    }
}

void DecoderAnimation::DrawBitmap(HDC hDC, int x, int y, HBITMAP hBitmap)
{
    HBITMAP hbm, hOldbm;
    HDC hMemDC;
    BITMAP bm;
    POINT ptSize, ptOrg;

    // ������� �������� ������, �����������
    // � ���������� �����������
    hMemDC = CreateCompatibleDC(hDC);

    // �������� ����������� bitmap � �������� ������
    hOldbm = (HBITMAP)SelectObject(hMemDC, hBitmap);

    // ���� �� ���� ������, ���������� ������
    if (hOldbm)
    {
        // ��� ��������� ������ ������������� ��� ��
        // ����� �����������, ��� ������������ �
        // ��������� �����������
        SetMapMode(hMemDC, GetMapMode(hDC));

        // ���������� ������� �����������
        GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);

        ptSize.x = bm.bmWidth;  // ������
        ptSize.y = bm.bmHeight; // ������

        // ����������� ���������� ���������� � ����������
        // ��� ���������� ������
        DPtoLP(hDC, &ptSize, 1);

        ptOrg.x = 0;
        ptOrg.y = 0;

        // ����������� ���������� ���������� � ����������
        // ��� ��������� ������
        DPtoLP(hMemDC, &ptOrg, 1);

        // ������ ����������� bitmap
        BitBlt(hDC, x, y, ptSize.x, ptSize.y,
            hMemDC, ptOrg.x, ptOrg.y, SRCCOPY);

        // ��������������� �������� ������
        SelectObject(hMemDC, hOldbm);
    }

    // ������� �������� ������
    DeleteDC(hMemDC);
}

void DecoderAnimation::animation(int t, HDC& hDC, HWND& hWnd, PAINTSTRUCT& ps, int pos_x, int pos_y)
{
    hDC = BeginPaint(hWnd, &ps);
    DrawBitmap(hDC, pos_x, pos_y, vectorHBitmap[t]);
    EndPaint(hWnd, &ps);
    SwapBuffers(hDC);
}

