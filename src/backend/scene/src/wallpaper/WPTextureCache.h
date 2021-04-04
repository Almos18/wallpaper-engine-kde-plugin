#pragma once
#include "GLWrapper.h"
#include "SceneTexture.h"
#include <memory>

#include "GraphicManager.h"
#include "SpriteAnimation.h"

namespace wallpaper {
namespace gl {

class Texture {
public:
	Texture(GLWrapper* glWrapper, const std::string& name);
	Texture(GLWrapper* glWrapper, GLTexture* texture):m_glWrapper(glWrapper),texture(texture) {};
	~Texture();

	void Bind();
	GLTexture* texture;
	TextureFormat Format() {return m_format;};
	std::vector<int> GetResolution();
	int Count() const {return m_textures.size();};
	bool IsSprite() const {return m_isSprite;};
	const SpriteFrame* NextSpriteFrame(int time); 
	const SpriteFrame* NextSpriteFrame(); 
	void SwitchTex(int index);
private:
	std::string m_name;
	TextureFormat m_format;
	int m_resolution[4] = {0};
	GLWrapper* m_glWrapper;
	std::vector<GLTexture*> m_textures;
	bool m_isSprite;
	int m_spriteIter = -1;
	int m_frametime = 0;
	std::vector<SpriteFrame> m_spriteFrames;
};

class WPTextureCache {
public:
	WPTextureCache(GLWrapper* glWrapper):m_glWrapper(glWrapper) {};
	Texture* LoadTexture(const std::string& name);
	Texture* LoadTextureHeader(const std::string& name);
	Texture* GetTexture(const std::string& name);
	void Clear();
private:
	GLWrapper* m_glWrapper;
	typedef std::unordered_map<std::string, std::unique_ptr<Texture>> TextureCache;
	TextureCache m_texCache;
};

}
}
