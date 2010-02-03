
/**
 *  Game Develop
 *      Player
 *
 *  Par Florian "4ian" Rival
 *
 */
/**
 *
 *  Contient une ou plusieurs actions
 */

#include <vector>
#include <string>
#include "GDL/Object.h"
#include <SFML/System.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "GDL/aCamera.h"
#include "GDL/Event.h"
#include <iostream>
#include <sstream>
#include "GDL/Chercher.h"
#include "GDL/algo.h"
#include "GDL/Force.h"
#include <iostream>
#include "GDL/Access.h"
#include "GDL/RuntimeScene.h"
#include "GDL/ObjectsConcerned.h"



////////////////////////////////////////////////////////////
/// Fixe la cam�ra sur un objet, sans d�passer un cadre
///
/// Type : FixCamera
/// Param�tre 1 : Objet
/// Param�tre 2 : Xmin
/// Param�tre 3 : Ymin
/// Param�tre 4 : Xmax
/// Param�tre 5 : Ymax
/// Param�tre 6 : Calque
////////////////////////////////////////////////////////////
bool ActFixCamera( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    ObjList list = objectsConcerned.Pick(action.GetParameter( 0 ).GetPlainString(), action.IsGlobal());

    if ( list.empty() ) return false;

    sf::View * view = NULL;

    //Compatibilit� Game Develop < 1.1.5429 :
    if ( action.GetParameters().size() >= 6 )
        view = &scene->ModLayer(action.GetParameter(5).GetPlainString()).ModView();
    else
        view = &scene->ModLayer("").ModView();

    float decalementX = 0;
    float decalementY = 0;

    //Prise en compte des d�placements de l'objet
    if ( action.GetParameters().size() < 6 )
    {
        decalementX = ( list[0]->TotalForceX() * scene->GetElapsedTime() );
        decalementY = ( list[0]->TotalForceY() * scene->GetElapsedTime() );
    }
    else if ( action.GetParameter(5).GetPlainString() != "no" && action.GetParameter(5).GetPlainString() != "non")
    {
        decalementX = ( list[0]->TotalForceX() * scene->GetElapsedTime() );
        decalementY = ( list[0]->TotalForceY() * scene->GetElapsedTime() );
    }

    //Si on est dans le cadre
    if ( list[0]->GetX() > eval.EvalExp(action.GetParameter( 1 ))
        && list[0]->GetX() < eval.EvalExp(action.GetParameter( 3 ))
        && list[0]->GetY() > eval.EvalExp(action.GetParameter( 2 ))
        && list[0]->GetY() < eval.EvalExp(action.GetParameter( 4 ))
        )
    {
        view->SetCenter(list[0]->GetX() + decalementX, list[0]->GetY() + decalementY);
    }

    //Si on n'est pas dedans.
    if ( ( list[0]->GetX() < eval.EvalExp(action.GetParameter( 1 ))
        || list[0]->GetX() > eval.EvalExp(action.GetParameter( 3 )) )
        && list[0]->GetY() > eval.EvalExp(action.GetParameter( 2 ))
        && list[0]->GetY() < eval.EvalExp(action.GetParameter( 4 )) )

    {
        view->SetCenter(view->GetCenter().x, list[0]->GetY() + decalementY);
    }
    if ( ( list[0]->GetY() < eval.EvalExp(action.GetParameter( 2 ))
        || list[0]->GetY() > eval.EvalExp(action.GetParameter( 4 )) )
        && list[0]->GetX() > eval.EvalExp(action.GetParameter( 1 ))
        && list[0]->GetX() < eval.EvalExp(action.GetParameter( 3 )))
    {
        view->SetCenter(list[0]->GetX() + decalementX, view->GetCenter().y);
    }

    return true;
}


////////////////////////////////////////////////////////////
/// Fixe la cam�ra sur un objet
///
/// Type : FixCamera
/// Param�tre 1 : Objet
/// Param�tre 2 : Prise en compte du d�placement ( Oui/Non )
/// Param�tre 3 : Calque
////////////////////////////////////////////////////////////
bool ActCentreCamera( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    ObjList list = objectsConcerned.Pick(action.GetParameter( 0 ).GetPlainString(), action.IsGlobal());

    if ( list.empty() ) return false;

    float decalementX = 0;
    float decalementY = 0;

    sf::View * view = NULL;

    //Compatibilit� Game Develop < 1.1.5429 :
    if ( action.GetParameters().size() >= 3 )
        view = &scene->ModLayer(action.GetParameter(2).GetPlainString()).ModView();
    else
        view = &scene->ModLayer("").ModView();

    //Prise en compte des d�placements de l'objet
    if ( action.GetParameters().size() < 2 )
    {
        decalementX = ( list[0]->TotalForceX() * scene->GetElapsedTime() );
        decalementY = ( list[0]->TotalForceY() * scene->GetElapsedTime() );
    }
    else if ( action.GetParameter(1).GetPlainString() != "no" && action.GetParameter(1).GetPlainString() != "non")
    {
        decalementX = ( list[0]->TotalForceX() * scene->GetElapsedTime() );
        decalementY = ( list[0]->TotalForceY() * scene->GetElapsedTime() );
    }

    view->SetCenter(list[0]->GetX() + decalementX,
                    list[0]->GetY() + decalementY);

    return true;
}

////////////////////////////////////////////////////////////
/// Zoomer / D�zoomer
///
/// Type : ZoomCamera
/// Param�tre 1 : Nouvelle valeur
/// Param�tre 2 : Calque
////////////////////////////////////////////////////////////
bool ActZoomCamera( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    sf::View * view = NULL;

    //Compatibilit� Game Develop < 1.1.5429 :
    if ( action.GetParameters().size() >= 2 )
        view = &scene->ModLayer(action.GetParameter(1).GetPlainString()).ModView();
    else
        view = &scene->ModLayer("").ModView();

    float newZoom = eval.EvalExp( action.GetParameter( 0 ) );
    if ( newZoom == 0 ) return false;
#ifndef SFMLTEST
    view->SetSize((scene->game->windowWidth/newZoom), (scene->game->windowHeight/newZoom));
#endif
    return true;
}

////////////////////////////////////////////////////////////
/// Faire tourner la cam�ra
///
/// Type : RotateCamera
/// Param�tre 1 : Nouvelle valeur
/// Param�tre 2 : Signe de la modification
/// Param�tre 3 : Calque
////////////////////////////////////////////////////////////
bool ActRotateCamera( RuntimeScene * scene, ObjectsConcerned & objectsConcerned, const Instruction & action, const Evaluateur & eval )
{
    sf::View * view = NULL;

    //Compatibilit� Game Develop < 1.1.5429 :
    if ( action.GetParameters().size() >= 3 )
        view = &scene->ModLayer(action.GetParameter(2).GetPlainString()).ModView();
    else
        view = &scene->ModLayer("").ModView();

    float value = eval.EvalExp( action.GetParameter( 0 ) );
    if ( action.GetParameter( 1 ).GetPlainString().empty() || action.GetParameter( 1 ).GetAsModOperator() == GDExpression::Set ) view->SetRotation(value);
    else if ( action.GetParameter( 1 ).GetAsModOperator() == GDExpression::Add ) view->SetRotation(view->GetRotation()+value);
    else if ( action.GetParameter( 1 ).GetAsModOperator() == GDExpression::Substract ) view->SetRotation(view->GetRotation()-value);
    else if ( action.GetParameter( 1 ).GetAsModOperator() == GDExpression::Multiply ) view->SetRotation(view->GetRotation()*value);
    else if ( action.GetParameter( 1 ).GetAsModOperator() == GDExpression::Divide ) view->SetRotation(view->GetRotation()/value);

    return true;
}

#undef PARAM