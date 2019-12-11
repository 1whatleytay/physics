#pragma once

#include <engine/thing.h>

#include <string>

class Text;

class Character : public Thing {
    Character(Text &text, float x, float y, float size, Texture texture);

    friend class Text;
};

class Text {
    static constexpr uint32_t width = 5;
    static constexpr uint32_t height = 7;
    static constexpr uint32_t padding = 2;
    static constexpr uint32_t charsPerRow = 13;

    Engine *engine;
    Texture texture;
    std::vector<Texture> textures;
    std::vector<Character *> characters;

    Texture getTextureForChar(char a);
    void freeCharacters();

    friend class Character;
public:
    float x = 0, y = 0;
    float fontSize = 4;

    void show(bool value);
    void modify(const std::string &text);

    explicit Text(Engine *engine, float x, float y);
    ~Text();
};