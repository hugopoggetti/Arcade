#ifndef __IGAME_MODULE__
    #define __IGAME_MODULE__

#include "../graphics/IDisplayModule.hpp"

#include <vector>

class Listener;

class IGameModule : public IModule {
    public:
        IGameModule() = default;
        virtual ~IGameModule() = default;
        virtual void init() = 0;
        virtual void run(IDisplayModule &dsp) = 0;   
        virtual std::pair<std::size_t, std::size_t> getGridSize() = 0;
        virtual std::map<Color::ColorID, Color::color_t> getColorPalette() = 0;
        virtual std::vector<Listener *> &getGameListeners() = 0;
        virtual int getScore() const = 0;
        virtual void setBestScore(int score) = 0;
};

#endif

