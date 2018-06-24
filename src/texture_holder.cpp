#include "texture_holder.hpp"

#include <utility>

void TextureHolder::load(TextureId id, const std::string& filename) {
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    texture->loadFromFile(filename);

    mTextureMap.insert(std::make_pair(id, std::move(texture)));
}

sf::Texture& TextureHolder::get(TextureId id) {
    return *mTextureMap.find(id)->second;
}

const sf::Texture& TextureHolder::get(TextureId id) const {
    return get(id);
}
