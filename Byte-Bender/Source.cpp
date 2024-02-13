#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

int main() {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);             //gotta take a pic of all the process running 
    if (hProcessSnap == INVALID_HANDLE_VALUE) {  
        std::cerr << "CreateToolhelp32Snapshot failed." << std::endl;
        return EXIT_FAILURE;
    }


    pe32.dwSize = sizeof(PROCESSENTRY32); // Set  struc size

    // Retrieve information about the first process.
    if (!Process32First(hProcessSnap, &pe32)) {
        std::cerr << "Process32First failed." << std::endl;
        CloseHandle(hProcessSnap);
        return EXIT_FAILURE;
    }

    // Now  the pic of all processes  and for each process, display information.
    do {
        std::wcout << L"Process Name: " << pe32.szExeFile << L"\Process ID: " << pe32.th32ProcessID << std::endl;
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return EXIT_SUCCESS;
}