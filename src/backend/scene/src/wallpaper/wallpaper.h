#pragma once
#include <memory>
#include <vector>
#include <cstdint>
#include "pkg.h"
#include "object.h"
#include "WPRender.h"
#include "GLVertice.h"
#include "FpsCounter.h"

namespace wallpaper
{
class WallpaperGL
{
public:
    static const fs::file_node& GetPkgfs(){
        return m_pkgfs;
    }
    WallpaperGL():m_fboTrans(1.0f),m_mousePos({0,0}) {};
    ~WallpaperGL() {m_vertices.Delete();};
	bool Init(void *get_proc_address(const char *));
    void Load(const std::string& pkg_path);
    void Render(uint fbo, int width, int height);
    void Clear();
	void SetAssets(const std::string& path);
    void SetObjEffNum(int obj, int eff);
	void SetFlip(bool value) {m_flip = value;};
	void SetKeepAspect(bool value) {m_keepAspect = value;};
	void SetMousePos(float x, float y) {m_mousePos = std::vector<float>({x,y});};
    static int ObjNum() {return m_objnum;};
    static int EffNum() {return m_effnum;};

	bool Loaded() const {return m_loaded;};

private:
    static fs::file_node m_pkgfs;
	std::string m_pkgPath;
    std::vector<std::unique_ptr<RenderObject>> m_objects;
	WPRender m_wpRender;
	glm::mat4 m_fboTrans;

	bool m_inited = false;
	bool m_loaded = false;
	int m_framecount = 0;
	bool m_flip = false;
	bool m_keepAspect = false;
	std::vector<float> m_mousePos;

	gl::VerticeArray m_vertices;
	gl::Shadervalues m_shadervalues;

	FpsCounter fpsCounter;

    // for debug
    static int m_objnum;
    static int m_effnum;
};

}
