#include <AzCore/PlatformIncl.h>
#include <AzCore/Console/IConsole.h>

namespace WindowPosition
{
    void SetWindowXY(const AZ::ConsoleCommandContainer& args)
    {
        if (args.size() != 2)
        {
            return;
        }

        // Grab first argument.
        AZ::CVarFixedString argX{ args.front() };
        const int x = atoi(argX.c_str());

        // Grab second argument.
        AZ::CVarFixedString argY{ *(args.begin() + 1) };
        const int y = atoi(argY.c_str());

        HWND handle = GetActiveWindow();
        if (!handle)
        {
            // Try the console window.
            handle = GetConsoleWindow();
        }

        if (handle)
        {
            SetWindowPos(handle, nullptr,
                x, y,
                0, 0, SWP_NOOWNERZORDER | SWP_NOSIZE);
        }
    }

    AZ_CONSOLEFREEFUNC(SetWindowXY, AZ::ConsoleFunctorFlags::Null,
        "Moves the window to x,y coordinates");
} // namespace MyGem
