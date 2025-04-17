#include "HighScoreManager.hpp"
#include <cstddef>
#include <cstdio>
#include <dirent.h>
#include <string>
#include <sys/stat.h>
#include <cstdlib>
#include <filesystem>

HighScoreManager::HighScoreManager(const std::string name, int score)
    : _name(name), _score(score)
{
    std::filesystem::create_directory("./saves");
}

int HighScoreManager::getBestScore()
{
    std::string save = decryptScore();
    std::istringstream iss(save);
    std::string line;

    while (std::getline(iss, line)) {
        size_t delimiter = line.find(':');
        if (delimiter != std::string::npos) {
            std::string name = line.substr(0, delimiter);
            int value = std::stoi(line.substr(delimiter + 1));
            if (name == _name){
                return value;
            }
        }
    }
    return 0;
}

const std::string HighScoreManager::updateSave()
{
    std::string save;
    bool found = false;

    if (isSaved()) {
        save = decryptScore();
        std::istringstream iss(save);
        std::ostringstream oss;
        std::string line;

        while (std::getline(iss, line)) {
            size_t delimiter = line.find(':');
            if (delimiter != std::string::npos) {
                std::string name = line.substr(0, delimiter);
                if (name == _name) {
                    oss << name << ":" << _score << "\n";
                    found = true;
                } else {
                    oss << line << "\n";
                }
            }
        }
        if (!found) {
            oss << _name << ":" << _score << "\n";
        }
        save = oss.str();
    } else {
        save = _name + ":" + std::to_string(_score) + "\n";
    }
    return save;

}

void HighScoreManager::encryptScore()
{
    std::string save = updateSave(); 
    const std::string u_out = "./saves/" + getUsername() + ".out";
    const std::string u_key = "./saves/" + getUsername() + ".key";

    FILE *encrypted_file = fopen(u_out.c_str(), "w");
    FILE *key_file = fopen(u_key.c_str(), "w");

    for (std::size_t i = 0; i < save.size(); i++) {
        int key = rand();
        int encrypted_char = save[i] ^ key;

        fputc(key, key_file);
        fputc(encrypted_char, encrypted_file);
    }
    fclose(encrypted_file);
    fclose(key_file);
}

const std::string HighScoreManager::decryptScore()
{
    const std::string u_out = "./saves/" + getUsername() + ".out";
    const std::string u_key = "./saves/" + getUsername() + ".key";

    FILE *encrypted_file = fopen(u_out.c_str(), "r");
    FILE *key_file = fopen(u_key.c_str(), "r");
    
    if (!encrypted_file || !key_file) {
        if (encrypted_file) fclose(encrypted_file);
        if (key_file) fclose(key_file);
        return "";
    }

    std::string decrypted;

    int encrypted_char = 0;
    int key_char = 0;
    while ((encrypted_char = fgetc(encrypted_file)) != EOF && (key_char = fgetc(key_file)) != EOF) {
        int decrypted_char = encrypted_char ^ key_char;
        decrypted += static_cast<char>(decrypted_char);
    }
    fclose(encrypted_file);
    fclose(key_file);
    return decrypted;
}

const std::string HighScoreManager::getUsername()
{
    const std::string userName(getenv("USER"));
    return userName;
}

bool HighScoreManager::isSaved()
{
    const std::string out_path = "./saves/" + getUsername() + ".out";
    const std::string key_path = "./saves/" + getUsername() + ".key";

    struct stat out_stat, key_stat;

    return (stat(out_path.c_str(), &out_stat) == 0 && S_ISREG(out_stat.st_mode) &&
            stat(key_path.c_str(), &key_stat) == 0 && S_ISREG(key_stat.st_mode));
}

