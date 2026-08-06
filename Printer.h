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

    bool GetPower() { return Power; }

    int LoadPaper(int);
    int UnloadPaper(int);

    int GetPaper() { return Paper; }

    int LoadInk(int);

    int GetInk() { return Ink; }

    int Print(int, int);

    int GetState();

    const char* const GetStateName()
    {
        return PrinterStateName[State];
    }
};
