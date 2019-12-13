#include <world/text.h>

#include <engine/engine.h>

// texture should not be pointer it should be stack allocated
Character::Character(Text &text, float x, float y, float size, Texture texture)
    : Thing({ text.engine, {  x, y, Text::width * size, Text::height * size}}) {
    this->texture = texture;

    save();
}

Texture Text::getTextureForChar(char a) {
    uint32_t index = 0;

    if (a >= 'a' && a <= 'z') {
        index = a - 'a';
    } else if (a >= 'A' && a <= 'Z') {
        index = a - 'A';
    } else if (a >= '0' && a <= '9') {
        index = a - '0' + 26;
    } else if (a == ' ') {
        index = 26 + 10;
    } else if (a == '.') {
        index = 26 + 10 + 1;
    } else if (a == ',') {
        index = 26 + 10 + 2;
    } else if (a == '-') {
        index = 26 + 10 + 3;
    } else {
        assert(false);
    }

    return textures[index];
}

void Text::freeCharacters() {
    for (auto &character : characters) {
        character->remove();
    }

    characters.clear();
}

void Text::show(bool value) {
    for (auto &character : characters) {
        character->isVisible = value;
    }
}

void Text::modify(const std::string &text) {
    freeCharacters();

    for (size_t a = 0; a < text.size(); a++) {
        char currentChar = text[a];

        characters.push_back(new Character(*this,
            x + a * fontSize * (Text::width + Text::padding), y, fontSize, getTextureForChar(currentChar)));
    }
}

Text::Text(Engine *engine, float x, float y) : engine(engine), x(x), y(y) {
    texture = engine->loadTexture("/Users/desgroup/Desktop/font.png");
    textures = texture.split(charsPerRow, charsPerRow);
}

Text::~Text() {
    freeCharacters();
}