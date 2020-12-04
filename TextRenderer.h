#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include "Renderer.h"
#include <iostream>

/*!
 * \class TextRenderer
 * 
 * \brief TextRenderer abstract class
 * 
 * Az TextRenderer konsturkorának megtudjuk adni milyen kimenetre szeretnénk írni.
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

class TextRenderer : public Renderer{
protected:
    std::ostream& b_stream; ///< A kimenet típusa.
public:
    /// TextRenderer konstruktor
    TextRenderer(std::ostream& stream = std::cout/** [in] a kimenet típusa*/) : b_stream(stream){}
    /// Render függvény
    virtual void render(const Game&/**[in] a kiírandó Game*/) const = 0;
    /// Ez a függvény beállítja kimenetet.
    void setOutputStream(std::ostream& stream/** [in] a kimenet típusa*/){
        b_stream.copyfmt(stream);
    }
};

/*!
 * \class HeroTextRenderer
 * 
 * \brief HeroTextRenderer abstract class
 * 
 * Az HeroTextRenderer konsturkorának megtudjuk adni milyen kimenetre szeretnénk írni.
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

class HeroTextRenderer : public TextRenderer{
public:
    /// HeroTextRenderer konstruktor
    HeroTextRenderer(std::ostream& stream = std::cout/** [in] a kimenet típusa*/) : TextRenderer(stream){}
    void render(const Game&/**[in] a kiírandó Game*/) const override;
};  

/*!
 * \class ObserverTextRenderer
 * 
 * \brief ObserverTextRenderer abstract class
 * 
 * Az ObserverTextRenderer konsturkorának megtudjuk adni milyen kimenetre szeretnénk írni.
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

class ObserverTextRenderer : public TextRenderer{
public:
    /// TextRenderer konstruktor
    ObserverTextRenderer(std::ostream& stream = std::cout/** [in] a kimenet típusa*/) : TextRenderer(stream){}
    /// Render függvény
    void render(const Game&/**[in] a kiírandó Game*/) const override;
};


#endif