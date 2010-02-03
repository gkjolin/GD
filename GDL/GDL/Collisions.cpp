/**
 *  Game Develop
 *      Player
 *
 *  Par Florian "4ian" Rival
 *
 */
/**
 *  Collisions.cpp
 *
 *  V�rifications des collisions
 */

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <time.h>
#include <SFML/Graphics.hpp>

#include "GDL/SpriteObject.h"
#include "GDL/Collisions.h"
#include "GDL/Log.h"

//Int�ressant
#ifndef PI
#define PI (3.14159265358979323846)
#endif
#define RADIANS_PER_DEGREE (PI/180.0)

sf::Vector2f GD_API RotatePoint( const sf::Vector2f& Point, float Angle )
{
    Angle = Angle * RADIANS_PER_DEGREE;
    sf::Vector2f RotatedPoint;
    RotatedPoint.x = Point.x * cos( Angle ) + Point.y * sin( Angle );
    RotatedPoint.y = -Point.x * sin( Angle ) + Point.y * cos( Angle );
    return RotatedPoint;
}

inline float MinValue( float a, float b, float c, float d )
{
    float min = a;

    min = ( b < min ? b : min );
    min = ( c < min ? c : min );
    min = ( d < min ? d : min );

    return min;
}

inline float MaxValue( float a, float b, float c, float d )
{
    float max = a;

    max = ( b > max ? b : max );
    max = ( c > max ? c : max );
    max = ( d > max ? d : max );

    return max;
}

sf::IntRect GetAABB( const sf::Sprite& Object )
{

    //Get the top left corner of the sprite regardless of the sprite's center
    //This is in Global Coordinates so we can put the rectangle back into the right place
    sf::Vector2f pos = Object.TransformToGlobal( sf::Vector2f( 0, 0 ) );

    //Store the size so we can calculate the other corners
    sf::Vector2f size = Object.GetSize();

    float Angle = Object.GetRotation();

    //Bail out early if the sprite isn't rotated
    if ( Angle == 0.0f )
    {
        return sf::IntRect( static_cast<int>( pos.x ),
                            static_cast<int>( pos.y ),
                            static_cast<int>( pos.x + size.x ),
                            static_cast<int>( pos.y + size.y ) );
    }

    //Calculate the other points as vectors from (0,0)
    //Imagine sf::Vector2f A(0,0); but its not necessary
    //as rotation is around this point.
    sf::Vector2f B( size.x, 0 );
    sf::Vector2f C( size.x, size.y );
    sf::Vector2f D( 0, size.y );

    //Rotate the points to match the sprite rotation
    B = RotatePoint( B, Angle );
    C = RotatePoint( C, Angle );
    D = RotatePoint( D, Angle );

    //Round off to int and set the four corners of our Rect
    int Left = static_cast<int>( MinValue( 0.0f, B.x, C.x, D.x ) );
    int Top = static_cast<int>( MinValue( 0.0f, B.y, C.y, D.y ) );
    int Right = static_cast<int>( MaxValue( 0.0f, B.x, C.x, D.x ) );
    int Bottom = static_cast<int>( MaxValue( 0.0f, B.y, C.y, D.y ) );

    //Create a Rect from out points and move it back to the correct position on the screen
    sf::IntRect AABB = sf::IntRect( Left, Top, Right, Bottom );
    AABB.Offset( static_cast<int>( pos.x ), static_cast<int>( pos.y ) );
    return AABB;
}



bool PixelPerfectTest( const sf::Sprite& Object1, const sf::Sprite& Object2, sf::Uint8 AlphaLimit )
{
    //Get AABBs of the two sprites
    sf::IntRect Object1AABB = GetAABB( Object1 );
    sf::IntRect Object2AABB = GetAABB( Object2 );

    sf::IntRect Intersection;

    if ( Object1AABB.Intersects( Object2AABB, Intersection ) )
    {

        //We've got an intersection we need to process the pixels
        //In that Rect.

        //Bail out now if AlphaLimit = 0
        if ( AlphaLimit == 0 ) return true;

        //There are a few hacks here, sometimes the TransformToLocal returns negative points
        //Or Points outside the image.  We need to check for these as they print to the error console
        //which is slow, and then return black which registers as a hit.

        sf::IntRect O1SubRect = Object1.GetSubRect();
        sf::IntRect O2SubRect = Object2.GetSubRect();

        sf::Vector2i O1SubRectSize( O1SubRect.GetSize().x, O1SubRect.GetSize().y );
        sf::Vector2i O2SubRectSize( O2SubRect.GetSize().x, O2SubRect.GetSize().y );

        sf::Vector2f o1v;
        sf::Vector2f o2v;
        //Loop through our pixels
        for ( int i = Intersection.Left; i < Intersection.Right; i++ )
        {
            for ( int j = Intersection.Top; j < Intersection.Bottom; j++ )
            {

                o1v = Object1.TransformToLocal( sf::Vector2f( i, j ) ); //Creating Objects each loop :(
                o2v = Object2.TransformToLocal( sf::Vector2f( i, j ) );

                //Hack to make sure pixels fall withint the Sprite's Image
                if ( o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
                        o1v.x < O1SubRectSize.x && o1v.y < O1SubRectSize.y &&
                        o2v.x < O2SubRectSize.x && o2v.y < O2SubRectSize.y )
                {

                    //If both sprites have opaque pixels at the same point we've got a hit
                    if (( Object1.GetPixel( static_cast<int>( o1v.x ), static_cast<int>( o1v.y ) ).a > AlphaLimit ) &&
                            ( Object2.GetPixel( static_cast<int>( o2v.x ), static_cast<int>( o2v.y ) ).a > AlphaLimit ) )
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    return false;
}

////////////////////////////////////////////////////////////
/// V�rifie une collision entre deux objets rapidement et sans pixel perfect
/// ( Bounding Box )
////////////////////////////////////////////////////////////
bool GD_API CheckCollisionNP( const boost::shared_ptr<const SpriteObject> objet1, const boost::shared_ptr<const SpriteObject> objet2 )
{
    //Get AABBs of the two sprites
    sf::IntRect Object1AABB = GetAABB( objet1->GetCurrentSprite() );
    sf::IntRect Object2AABB = GetAABB( objet2->GetCurrentSprite() );

    sf::IntRect Intersection;

    if ( Object1AABB.Intersects( Object2AABB, Intersection ) )
        return true;

    return false;
}

////////////////////////////////////////////////////////////
/// V�rifie une collision entre deux objets ( pixel perfect )
////////////////////////////////////////////////////////////
bool GD_API CheckCollision( const boost::shared_ptr<const SpriteObject> objet1, const boost::shared_ptr<const SpriteObject> objet2)
{
    return PixelPerfectTest( objet1->GetCurrentSprite(), objet2->GetCurrentSprite(), 1 );
}