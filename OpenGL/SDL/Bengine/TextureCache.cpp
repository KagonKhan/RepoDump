#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>


GLTexture TextureCache::getTexture(std::string texturePath) {

    // look up the texture and see if its in the map
    std::map<std::string, GLTexture>::iterator mIt = _textureMap.find(texturePath); // or just use auto

    //check if its not in the map
    if (mIt == _textureMap.end()) {
        GLTexture newTexture = ImageLoader::loadPNG(texturePath);
        _textureMap.insert(std::make_pair(texturePath, newTexture));


        std::cout << "Loaded Texture!\n";

        return newTexture;

    }
    std::cout << "Used Cached Texture!\n";
    return mIt->second;

}
