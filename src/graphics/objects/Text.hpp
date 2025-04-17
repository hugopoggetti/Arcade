#ifndef __TEXT__
    #define __TEXT__

#include "../transform/Transform.hpp"
#include "../color/Color.hpp"

#include <string>
#include <optional>

class Text {
    public:
        Text() = default;
        Text(const std::string &text, const std::string &fontPath,
            Color::ColorID color = Color::ColorID::WHITE);
        Text(const Text &other);
        ~Text() = default;
        void setText(const std::string &text);
        const std::string &getText() const;
        void setFontPath(const std::string &fontPath);
        const std::string &getFontPath() const;
        Transform &getTransform();
        const Transform &getTransform() const;
        void setColor(Color::ColorID color);
        Color::ColorID getColor() const;
        void operator=(const Text &other);
    private:
        std::string _text;
        std::string _fontPath;
        Transform _transform;
        Color::ColorID _colorID;
};

#endif
