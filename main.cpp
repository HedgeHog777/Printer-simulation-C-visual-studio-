#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <cstdio>

#include "Printer.h"

int main()
{
    // оголошення об'єкта класу
    Printer Canon;

    Canon.Reset();

    // безкінечний цикл обробки команд з клавіатури
    do
    {
        // вивід запрошення
        system("cls");

        printf("--------Object - oriented printer model-------- \n");
        printf("---------------------------------------------\n");
        printf("----Select one of these options[e - exit]-----\n");
        printf("[0 - Turn off] [1 - Turn on] [2 - Load paper]\n");
        printf("[3 - Unload paper] [4 - Load ink] [5 - Print]\n");
        printf("---------------------------------------------\n");

        // вивід стану принтера
        printf("State of printer:\n");
        printf("Power: %d State: %s ",
            Canon.GetPower(),
            Canon.GetStateName());

        printf("Paper: %d Ink: %d",
            Canon.GetPaper(),
            Canon.GetInk());

        // прийом команди з клавіатури
        int key = _getch();

        switch (key)
        {
        case '0':
            Canon.TurnOff();
            break;

        case '1':
            Canon.TurnOn();
            break;

        case '2':
        {
            int Sheets;

            printf("Input the number of sheets to load: ");
            scanf_s("%d", &Sheets);

            Canon.LoadPaper(Sheets);
            break;
        }

        case '3':
        {
            int Sheets;

            printf("Input the number of sheets to unload: ");
            scanf_s("%d", &Sheets);

            Canon.UnloadPaper(Sheets);
            break;
        }

        case '4':
        {
            int Drops;

            printf("Input the volume of ink to load: ");
            scanf_s("%d", &Drops);

            Canon.LoadInk(Drops);
            break;
        }

        case '5':
        {
            int Sheets;
            int Fill;

            printf("Input the number of sheets and fill: ");
            scanf_s("%d%d", &Sheets, &Fill);

            Canon.Print(Sheets, Fill);
            break;
        }

        case 'e':
            return 0;

        default:
            printf("Invalid option! Press any key to continue...");
            _getch();
            break;
        }

    } while (true);

    return 0;
}
