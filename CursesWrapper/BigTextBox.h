#ifndef SPACEINVADERS_BIGTEXTBOX_H
#define SPACEINVADERS_BIGTEXTBOX_H

#include "ScreenObject.h"
#include "Sprite.h"
#include <vector>

class BigTextBox : public ScreenObject
{
private:
    vector<vector<Sprite>> text;
    int getLargestLine();
    static int getLineSize(vector<Sprite>& line);
    void relocateLines();
    void eraseInternal() override;
    void drawInternal() override;
    void changeTextInternal(const string& _text);
public:
    BigTextBox(const string& _text,const Vector2& position);
    void moveTo(const Vector2 &nPos) override;
    void moveBy(const Vector2 &df) override;
    void erase() override;
    void draw() override;
    void editText(const string& text);
};

#endif
