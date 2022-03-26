#include "CHelperClass.h"

sf::String CHelperClass::SaveFile()
{
    Setup();
    GetSaveFileName(&currFileName);
    return currFileName.lpstrFile;
}

sf::String CHelperClass::LoadFile()
{
    Setup();
    GetOpenFileName(&currFileName);
    return currFileName.lpstrFile;
}

void CHelperClass::Setup()
{
    ZeroMemory(&currFileName, sizeof(currFileName));
    currFileName.lStructSize = sizeof(currFileName);

    currFileName.hwndOwner = NULL;
    currFileName.lpstrFile = (LPWSTR)szFile;
    currFileName.lpstrFile[0] = '\0';
    currFileName.nMaxFile = sizeof(szFile);

    currFileName.lpstrFilter = L"png\0*.png\0jpg\0*.jpg\0All\0*.*\0";
    currFileName.nFilterIndex = 1;
    currFileName.lpstrFileTitle = NULL;
    currFileName.nMaxFileTitle = 0;
    currFileName.lpstrInitialDir = NULL;
    currFileName.Flags = OFN_FILEMUSTEXIST | OFN_FILEMUSTEXIST;
}
