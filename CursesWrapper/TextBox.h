#ifndef SPACEINVADERS_TEXTBOX_H
#define SPACEINVADERS_TEXTBOX_H

#include "ScreenObject.h"
#include <string>

using namespace std;
class TextBox : public ScreenObject
{
private:
    string text;
    void drawInternal() override;
    void eraseInternal() override;
public:
    explicit TextBox(const string& str,const Vector2& pos);
    void moveTo(const Vector2 &nPos) override;
    void moveBy(const Vector2 &df) override;
    void erase() override;
    void draw() override;
};


#endif

