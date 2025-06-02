#ifndef FONT_MGR_H
#define FONT_MGR_H

#include <SDL_ttf.h>

class FontMgr
{
public:
    static FontMgr &getInstance() {
        static FontMgr instance;
        return instance;
    }
    ~FontMgr() = default;

    void init();

    //
    TTF_Font *getTitleFontPtr() {
        return titleFont;
    }
    TTF_Font *getTextFontPtr() {
        return textFont;
    }

private:
    FontMgr() = default;

    // 删除拷贝与赋值构造函数
    FontMgr(const FontMgr &) = delete;
    FontMgr &operator=(const FontMgr &) = delete;

    //
    TTF_Font *titleFont;
    TTF_Font *textFont;
};

#endif // FONT_MGR_H