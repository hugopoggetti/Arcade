#include "Plugin.hpp"

Plugin::Plugin(const std::string &name, const std::string &version,
    const std::string &author, const std::string &icon) :
    _name(name), _version(version), _author(author), _icon(icon)
{
    return;
}

const std::string &Plugin::getName() const
{
    return this->_name;
}

const std::string &Plugin::getVersion() const
{
    return this->_version;
}

const std::string &Plugin::getAuthor() const
{
    return this->_author;
}

const std::string &Plugin::getIcon() const
{
    return this->_icon;
}
