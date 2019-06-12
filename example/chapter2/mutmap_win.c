#include <Windows.h>
#include <WinBase.h>

int main()
{
    size_t size = sizeof(LPINT);
    HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0, size,
        NULL);

    LPINT add1 = (LPINT)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, size);
    LPINT add2 = (LPINT)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, size);

    *add1 = 0xdeafbeef;
    printf("Address of add1 is: %p, value of add1 is: 0x%x\n", add1, *add1);
    printf("Address of add2 is: %p, value of add2 is: 0x%x\n", add2, *add2);

    UnmapViewOfFile(add1);
    UnmapViewOfFile(add2);
    CloseHandle(hMapFile);
    return 0;
}