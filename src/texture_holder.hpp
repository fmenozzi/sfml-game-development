#ifndef SRC_TEXTURE_HOLDER_HPP_
#define SRC_TEXTURE_HOLDER_HPP_

#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

enum class TextureId {
    Landscape,
    Airplane,
    Missile,
};

class TextureHolder {
public:
    void load(TextureId id, const std::string& filename);

    sf::Texture& get(TextureId id);
    const sf::Texture& get(TextureId id) const;

private:
    std::map<TextureId, std::unique_ptr<sf::Texture>> mTextureMap;
};

#endif
