#pragma once

constexpr int MAX_PAPER = 100;
constexpr int MAX_INK = 50;
constexpr float ERROR_PROBABILITY = 0.05f;

enum PrinterState
{
    OFF,
    READY,
    NOINK,
    NOPAPER,
    ERROR
};

// Масив назв станів визначається в Printer.cpp
extern const char PrinterStateName[5][10];

class Printer
{
private:
    bool Power;
    int State;
    int Paper;
    float Ink;

    void SetState(int);

public:
    void Reset();

    void TurnOn();
    void TurnOff();

    bool GetPower()
    {
        return Power;
    }

    int LoadPaper(int Sheets);
    int UnloadPaper(int Sheets);

    int GetPaper()
    {
        return Paper;
    }

    int LoadInk(int Drops);

    int GetInk()
    {
        return Ink;
    }

    int Print(int Sheets, int Fill);

    int GetState();

    const char* GetStateName()
    {
        return PrinterStateName[State];
    }
};
