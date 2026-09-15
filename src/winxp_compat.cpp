#include <windows.h>
#include <stdio.h>

// Forzar la versión mínima de Windows soportada a Windows XP (0x0501)
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501

// Parche de compatibilidad para evitar llamadas a funciones no disponibles en WinXP (como GetThreadId)
extern "C" {
    // Si algún runtime antiguo intenta resolver GetThreadId, proveemos un fallback dummy
    __declspec(dllexport) DWORD WINAPI GetThreadId_Fallback(HANDLE /*Thread*/) {
        return GetCurrentThreadId();
    }
}
