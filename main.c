#include <windows.h>
#include "users.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    login();

    menuUsers();

    return 0;
}