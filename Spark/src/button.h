#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"

namespace spark_luchelli
{

    struct Button
    {
        Rectangle rect;
        const char* text;
        Color color;
    };

    Button createButton(Vector2 position, Vector2 size, const char* text);
    void drawButton(Button& button);
    bool isButtonClicked(Button& button);

}

#endif // BUTTON_H



