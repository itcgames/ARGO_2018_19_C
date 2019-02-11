#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <map>
#include <memory>

class assets {
public:
	~assets();
	static assets& instance();
	SDL_Texture* load_texture(const std::string& path, SDL_Renderer* ren);
private:
	std::map<std::string, SDL_Texture*> textures;
	assets();
};
