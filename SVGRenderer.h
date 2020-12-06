#ifndef SVGRENDERER_H
#define SVGRENDERER_H

#include "Renderer.h"
#include <string>

/*!
 * \class SVGRenderer
 * 
 * \brief SVGRenderer abstract class
 * 
 * Az SVGRenderer konsturkora vár egy kimeneti fájlt, az SVG kimenet ebbe a fájlba fog íródni.
 * 
 * 
 * \author  Borbély Roland, Vitéz Marcell, Voznek Péter
 * 
 * \version 5.0
 * 
 * \date 2020/12/03 21:37
 * 
 * Created on 2020/12/03 21:37
 */

class SVGRenderer : public Renderer{
protected:
    std::string b_out; ///< a kimeneti fájl elérési útja
public:
    /// SVGRenderer konstruktor
    SVGRenderer(const std::string& out/** [in] a kimeneti fájl elérési útja*/) : b_out(out){}
    /// render függvény
    virtual void render(const Game&/**[in] a kiírandó Game*/) const = 0;
};

/*!
 * \class CharacterSVGRenderer
 * 
 * \brief CharacterSVGRenderer class
 * 
 * A CharacterSVGRenderer konsturkora vár egy kimeneti fájlt, az SVG kimenet ebbe a fájlba fog íródni.
 * 
 * 
 * \author  Borbély Roland, Vitéz Marcell, Voznek Péter
 * 
 * \version 5.0
 * 
 * \date 2020/12/03 21:37
 * 
 * Created on 2020/12/03 21:37
 */

class CharacterSVGRenderer : public SVGRenderer{
public:
    /// CharacterSVGRenderer konstruktor
    CharacterSVGRenderer(const std::string& out/** [in] a kimeneti fájl elérési útja*/) : SVGRenderer(out){}
    /// render függvény
    virtual void render(const Game&/**[in] a kiírandó Game*/) const;
};
/*!
 * \class ObserverSVGRenderer
 * 
 * \brief ObserverSVGRenderer class
 * 
 * Az ObserverSVGRenderer konsturkora vár egy kimeneti fájlt, az SVG kimenet ebbe a fájlba fog íródni.
 * 
 * 
 * \author  Borbély Roland, Vitéz Marcell, Voznek Péter
 * 
 * \version 5.0
 * 
 * \date 2020/12/03 21:37
 * 
 * Created on 2020/12/03 21:37
 */

class ObserverSVGRenderer : public SVGRenderer{
public:
    /// ObserverSVGRenderer konstruktor
    ObserverSVGRenderer(const std::string& out/** [in] a kimeneti fájl elérési útja*/) : SVGRenderer(out){}
    /// render függvény
    virtual void render(const Game&/**[in] a kiírandó Game*/) const;
};

#endif