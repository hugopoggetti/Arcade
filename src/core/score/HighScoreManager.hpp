#pragma once

#include "../../plugin/Plugin.hpp"

class HighScoreManager {
    public:
        HighScoreManager(const std::string name, int score);
        ~HighScoreManager() = default;
        void encryptScore();
        int getBestScore();
    private:
        const std::string decryptScore();
        const std::string getUsername();
        bool isSaved();
        const std::string updateSave();
        const std::string _name;
        int _score;
};
