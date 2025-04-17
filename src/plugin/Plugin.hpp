#ifndef __PLUGIN__
    #define __PLUGIN__

#include "../loader/Loader.hpp"

#include <string>

class Plugin {
public:
    /**
     * Default constructor
     */
    Plugin() = default;
    
    /**
     * Base constructor, used to create a @{Plugin} using a name, a version, an author, and an icon
     */
    Plugin(const std::string &name, const std::string &version, const std::string &author, const std::string &icon);
    
    /**
     * Default deconstructor
     */
    ~Plugin() = default;
    
    /**
     * Get @{Plugin} name
     * @return name
     */
    const std::string &getName() const;
    
    /**
     * Get @{Plugin} version
     * @return name
     */
    const std::string &getVersion() const;
    
    /**
     * Get @{Plugin} author
     * @return name
     */
    const std::string &getAuthor() const;
    
    /**
     * Get @{Plugin} icon
     * @return name
     */
    const std::string &getIcon() const;
private:
    std::string _name;
    std::string _version;
    std::string _author;
    std::string _icon;
};
#endif
