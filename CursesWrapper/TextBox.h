#ifndef SPACEINVADERS_TEXTBOX_H
#define SPACEINVADERS_TEXTBOX_H

#include "ScreenObject.h"
#include <string>
#include <vector>

using namespace std;
class TextBox : public ScreenObject
{
private:
    vector<string> lines;
    short colorPair = 9;
    void drawInternal() override;
    void eraseInternal() override;
    int largerString();
public:
    TextBox(const string& str,const Vector2& pos,short colorPair);
    TextBox();
    void erase() override;
    void draw() override;
    void changeText(const string& newText);
    void addLine(const string& newLine);

};


#endif

