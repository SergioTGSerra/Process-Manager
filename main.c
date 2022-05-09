#include <windows.h>
#include "users.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);

    ELEM_USER *iniListU=NULL;
    readUsers(&iniListU);

    login(iniListU);
    menuUsers(&iniListU);

    return 0;
}