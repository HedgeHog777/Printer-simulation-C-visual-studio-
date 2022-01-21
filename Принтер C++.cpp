#include <cstdlib>
#include <iostream>
#include <conio.h> 
#include <stdio.h>


const int MAXPAPER = 100; const int MAXINK = 50;

// ймовірність виникнення помилки друку (5 %) 
const float ERRORPROB = 0.05;

// перелічення можливих станів принтера

enum PrinterState { OFF, READY, NOINK, NOPAPER, ERROR }; // масив констант з назвами станів

const char PrinterStateName[5][10] = { "OFF", "READY", "NOINK", "NOPAPER", "ERROR" };
class Printer {
	bool Power; int State; int Paper; float Ink;

	//приватний метод, що встановлює заданий стан

	//метод призначено для внутрішнього використання іншими методами

	//(користувач не може самовільно змінити стан принтера:

	//для цього необхідно використовувати доступні методи)

	void SetState(int);
public:
	//ініціалізація змінних класу початковими значеннями 
	void Reset(void);

	//управління живленням

	void TurnOn(void); void TurnOff(void);


	//inline-реалізація простого метода 
	bool GetPower(void) { return Power; }

	//управління папером

	int LoadPaper(int); int UnloadPaper(int);

	int GetPaper(void) { return Paper; }

	//управління чорнилами 
	int LoadInk(int);

	int GetInk(void) { return Ink; }

	//друк

	int Print(int, int);

	// визначення коду і назви стану 
	int GetState(void);

	const char* const GetStateName() { return PrinterStateName[State]; }
};


//реалізація класу принтера

void Printer::Reset(void)

{

	Power = false; SetState(OFF); Paper = 0;

	Ink = 50;

}

void Printer::TurnOn(void)

{


	if (!Power)

	{

		Power = true; SetState(READY);

	}

	// для імітації подальшого випадкового виникнення помилок при друку 
	srand(1);

}

void Printer::TurnOff(void)

{

	if (Power)

	{

		Power = false; SetState(OFF);

	}

}

int Printer::LoadPaper(int Sheets)

{

	if (Sheets < 0) return 0;

	int NewPaper = Paper + Sheets;

	// перевірка, чи не перевищує кількість паперу найбільшу можливу 
	if (NewPaper > MAXPAPER)

	{

		Paper = MAXPAPER;

		return MAXPAPER - Sheets;

	}

	Paper = NewPaper; return Sheets;

}

int Printer::UnloadPaper(int Sheets)

{

	if (Sheets < 0) return 0; int OldPaper = Paper;



	int NewPaper = Paper - Sheets;

	// перевірка, чи не перевищує кількість аркушів наявну 
	if (NewPaper < 0)

	{

		Paper = 0; return OldPaper;

	}

	Paper = NewPaper; return Sheets;

}

int Printer::LoadInk(int Drops)

{

	if (Power) return 0;

	if (Drops < 0) return 0; int NewInk = Ink + Drops;

	// перевірка, чи не перевищує кількість чорнил найбільшу можливу 
	if (NewInk > MAXINK)

	{

		Ink = MAXINK;

		return MAXINK - Drops;

	}

	Ink = NewInk; return Drops;

}

void Printer::SetState(int NewState)

{

	State = NewState;

}

int Printer::Print(int Sheets, int Fill)

{

	//перевірка працездатності принтера та коректності заданих параметрів 
	if (!Power || State != READY) return 0;

	if (Sheets < 0 || Fill < 0 || Fill > 100) return 0; int LuckSheets;

	//імітація виникнення випадкової помилки із заданою ймовірністю

	if (rand() % 100 < ERRORPROB * 100) LuckSheets = rand() % Sheets; else LuckSheets = Sheets;

	//обчислення кількості сторінок, на друк яких вистачить наявних чорнил 
	int PosSheetsByInk = Ink * 50 / Fill, PosPaper;

	//не вистачить чорнил

	if (PosSheetsByInk < LuckSheets)

	{

		PosPaper = PosSheetsByInk; SetState(NOINK);

	}

	// не вистачить паперу

	else if (Paper < LuckSheets)

	{

		PosPaper = Paper; SetState(NOPAPER);

	}

	// вистачить всього 
	else

	{

		PosPaper = LuckSheets; SetState(READY);

	}

	//зменшення кількості чорнил і паперу:

	//обнулення “Ink = 0” потрібне для усунення похибки, яка

	//може виникати при обчисленні потрібної кількості чорнил 
	if (State == NOINK) Ink = 0;

	else Ink -= PosPaper * Fill / 50;

	UnloadPaper(PosPaper);

	if (LuckSheets < Sheets) SetState(ERROR); return PosPaper;

}

int Printer::GetState(void)

{

	return State;

}
void main()

{

	//оголошення об‟єкта класу 
	Printer Canon;

	Canon.Reset();

	//бескінечний цикл обробки команд з клавіатури

	do
	{
		// вивід запрошення

		system("cls");

		printf("--------Object - oriented printer model-------- \n");

		printf("---------------------------------------------\n");

		printf("----Select one of these options[e - exit]-- -\n");

		printf("[0 - Turn off] [1 - Turn on] [2- Load paper]\n");

		printf("[3 - Unload paper] [4 - Load ink] [5 - Print]\n");

		printf("--------------------------------------------- \n");

		//вивід стану принтера 





		printf("State of printer:\n");

		printf("Power: %d State: %s ", Canon.GetPower(), Canon.GetStateName()); printf_s("Paper: %d Ink: %d", Canon.GetPaper(), Canon.GetInk());

		//прийом команди з клавіатури

		int key = _getch(); switch (key)

		{

		case '0': Canon.TurnOff(); break; case '1': Canon.TurnOn(); break; case '2':

		{

			int Sheets;

			printf("Input the number of sheets to load: ");
			scanf_s("%d", &Sheets);

			Canon.LoadPaper(Sheets); break;

		}

		case '3':

		{

			int Sheets;

			printf("Input the number of sheets to unload: ");
			scanf_s("%d", &Sheets);

			Canon.UnloadPaper(Sheets); break;

		}

		case '4':

		{

			int Drops;

			printf("Input the volume of ink to load: ");

			scanf_s("%d", &Drops); Canon.LoadInk(Drops); break;

		}

		case '5':

		{

			int Sheets, Fill;

			printf("Input the number of sheets and fill: ");
			scanf_s("%d%d", &Sheets, &Fill);

			Canon.Print(Sheets, Fill); break;

		}

		case 'e':

		{

			return;

		}

		default:

			printf("Invalid option! Press any key to continue..."); _getch();

		}

	} while (true);

}