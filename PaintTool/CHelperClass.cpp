#include "CHelperClass.h"

// TODO remove redundancy

sf::String CHelperClass::SaveFile()
{
    ZeroMemory(&currFileName, sizeof(currFileName));
    currFileName.lStructSize = sizeof(currFileName);

    currFileName.hwndOwner = NULL;
    currFileName.lpstrFile = (LPWSTR)szFile;
    currFileName.lpstrFile[0] = '\0';
    currFileName.nMaxFile = sizeof(szFile);

    currFileName.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
    currFileName.nFilterIndex = 1;
    currFileName.lpstrFileTitle = NULL;
    currFileName.nMaxFileTitle = 0;
    currFileName.lpstrInitialDir = NULL;
    currFileName.Flags = OFN_FILEMUSTEXIST | OFN_FILEMUSTEXIST;

    GetSaveFileName(&currFileName);

    return currFileName.lpstrFile;
}

sf::String CHelperClass::LoadFile()
{
    ZeroMemory(&currFileName, sizeof(currFileName));
    currFileName.lStructSize = sizeof(currFileName);

    currFileName.hwndOwner = NULL;
    currFileName.lpstrFile = (LPWSTR)szFile;
    currFileName.lpstrFile[0] = '\0';
    currFileName.nMaxFile = sizeof(szFile);

    currFileName.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
    currFileName.nFilterIndex = 1;
    currFileName.lpstrFileTitle = NULL;
    currFileName.nMaxFileTitle = 0;
    currFileName.lpstrInitialDir = NULL;
    currFileName.Flags = OFN_FILEMUSTEXIST | OFN_FILEMUSTEXIST;

    GetOpenFileName(&currFileName);

    return currFileName.lpstrFile;
}
