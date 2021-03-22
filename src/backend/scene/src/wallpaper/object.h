#pragma once
#include <memory>
#include <vector>
#include <string>
#include "common.h"
#include "material.h"
#include "effect.h"
#include "WPRender.h"
#include "GLVertice.h"
#include "WPJson.h"

namespace wallpaper
{
namespace RenderableType
{
	enum Type {
		Image,
		Particle
	};
};

class RenderObject : public Renderable
{
public:
    RenderObject():m_name(""),m_angles({0.0f,0.0f,0.0f}),
							m_origin(3),
							m_scale({1.0f,1.0f,1.0f}),
							m_parallaxDepth({1.0f,1.0f}),
							m_visible(true) {};
	
    virtual ~RenderObject() {
        m_vertices.Delete();
    }
    virtual void Load(WPRender&) = 0;
    virtual void Render(WPRender&) = 0;
    virtual bool From_json(const nlohmann::json&);
	virtual RenderableType::Type Type() const = 0;


	const std::string& Name() const {return m_name;};
    const auto& Origin() const {return m_origin;};
    const auto& Angles() const {return m_angles;};
    const auto& Scale() const {return m_scale;};
    const auto& ParallaxDepth() const {return m_parallaxDepth;};
    bool Visible() const {return m_visible;};

    auto& Vertices() {return m_vertices;};
protected:
    auto& Origin() {return m_origin;};

private:
    std::string m_name;
    std::vector<float> m_angles;
    std::vector<float> m_origin;
    std::vector<float> m_scale;
	std::vector<float> m_parallaxDepth;
    bool m_visible;
    gl::VerticeArray m_vertices;
};

class ImageObject : public RenderObject
{
public:
    ImageObject():m_material(*this),m_size(2),m_materialEffePass(*this) {};
    bool From_json(const nlohmann::json&);
    ~ImageObject();
    void Load(WPRender&);
    void Render(WPRender&);
	RenderableType::Type Type() const {return RenderableType::Image;};
	bool IsCompose() const;
	const gl::Combos BaseCombos() const {return m_basecombos;};

	gl::GLFramebuffer* CurFbo();
	gl::GLFramebuffer* TargetFbo();
	void SwitchFbo();

	const std::vector<int>& Size() const {return m_size;}

private:
	void GenBaseCombos();

	Material m_material;
	Material m_materialEffePass;
	std::vector<Effect> m_effects;

	gl::Combos m_basecombos;
	gl::Shadervalues shadervalues_;
	gl::VerticeArray m_verticesDefault;

	gl::GLFramebuffer* m_curFbo;
	std::unique_ptr<gl::GLFramebuffer> m_fbo1;
	std::unique_ptr<gl::GLFramebuffer> m_fbo2;
	glm::mat4 m_fboTrans;
	std::string m_shader;

	std::vector<int> m_size;
	bool m_autosize = false;
	bool m_copybackground = false;
	bool m_compose = false;
	bool m_fullscreen = false;
	float m_alpha = 1.0f;
	float m_brightness  = 1.0f;
	int m_blendmode = -1;
	std::vector<float> m_color = {1.0f,1.0f,1.0f};
};

class ParticleObject : public RenderObject
{
public:
    ParticleObject();
    bool From_json(const nlohmann::json&);
    ~ParticleObject() {};
    void Load(WPRender&);
    void Render(WPRender&) {};
	RenderableType::Type Type() const {return RenderableType::Particle;};
};


std::unique_ptr<RenderObject> CreateObject(const nlohmann::json&);
}


