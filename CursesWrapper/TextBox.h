#ifndef SPACEINVADERS_TEXTBOX_H
#define SPACEINVADERS_TEXTBOX_H

#include "ScreenObject.h"
#include <string>

using namespace std;
class TextBox : public ScreenObject
{
private:
    string text;
    short colorPair = 9;
    void drawInternal() override;
    void eraseInternal() override;
public:
    TextBox(const string& str,const Vector2& pos,short colorPair);
    TextBox();
    void moveTo(const Vector2 &nPos) override;
    void moveBy(const Vector2 &df) override;
    void erase() override;
    void draw() override;
    void changeText(const string& newText);
};


#endif

