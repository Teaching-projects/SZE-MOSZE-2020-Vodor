#ifndef SVGRENDERER_H
#define SVGRENDERER_H

#include "Renderer.h"

class SVGRenderer : public Renderer{
protected:
    std::string b_out;
public:
    SVGRenderer(const std::string& out) : b_out(out){}
    virtual void render(const Game&) const = 0;
};

class CharacterSVGRenderer : public SVGRenderer{
public:
    CharacterSVGRenderer(const std::string& out) : SVGRenderer(out){}
    void render(const Game&) const override;
};

class ObserverSVGRenderer : public SVGRenderer{
public:
    ObserverSVGRenderer(const std::string& out) : SVGRenderer(out){}
    void render(const Game&) const override;
};

#endif