//---------------------------------------------------------------------------

#pragma hdrstop

#include "Segment.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

Segment::Segment(int aX1, int aY1, string atype)
{
        X1 = aX1;
        X2 = NULL;

        Y1 = aY1;
        Y2 = NULL;

        type = atype;

        a_tangent = NULL;
        b_tangent = NULL;
}
//---------------------------------------------------------------------------

int __fastcall Segment::getX1()
{
        return X1;
}
//---------------------------------------------------------------------------
int __fastcall Segment::getX2()
{
        return X2;
}
//---------------------------------------------------------------------------

int __fastcall Segment::getY1()
{
        return Y1;
}
//---------------------------------------------------------------------------
int __fastcall Segment::getY2()
{
        return Y2;
}
//---------------------------------------------------------------------------

string __fastcall Segment::getType()
{
        return type;
}
//---------------------------------------------------------------------------

float __fastcall Segment::getSx()
{
        return sx;
}
//---------------------------------------------------------------------------
float __fastcall Segment::getSy()
{
        return sy;
}
//---------------------------------------------------------------------------
bool __fastcall Segment::getToRight()
{
        return toRight;
}
//---------------------------------------------------------------------------

void __fastcall Segment::setX1(int arg)
{
         X1 = arg;
}
//---------------------------------------------------------------------------
void __fastcall Segment::setX2(int arg)
{
         X2 = arg;
}
//---------------------------------------------------------------------------
void __fastcall Segment::setY1(int arg)
{
         Y1 = arg;
}
//---------------------------------------------------------------------------
void __fastcall Segment::setY2(int arg)
{
         Y2 = arg;
}
//---------------------------------------------------------------------------
void __fastcall Segment::setType(string arg)
{
         type = arg;
}
//---------------------------------------------------------------------------
void __fastcall Segment::setA(float arg)
{
        a_tangent = arg;
}
//---------------------------------------------------------------------------
void __fastcall Segment::setB(float arg)
{
        b_tangent = arg;
}
//---------------------------------------------------------------------------
void __fastcall Segment::draw(Graphics::TBitmap *bitMap, bool atoRight)
{
        if (type == "Line")
        {
                drawLine(bitMap);
                if (X2 > X1 )
                {
                        toRight = true;
                }
                else
                {
                        toRight = false;
                }
        }
        if (type == "Arc")
        {
                drawArc(bitMap, atoRight);
        }

}
//---------------------------------------------------------------------------
void Segment::drawLine(Graphics::TBitmap *bitMap)
{
        bitMap->Canvas->MoveTo(X1, Y1 );
        bitMap->Canvas->LineTo(X2, Y2 );
}
//---------------------------------------------------------------------------
void Segment::drawArc(Graphics::TBitmap *bitMap, bool atoRight)
{
        float a,b,D,C,r;
        if (a_tangent == 0)
        {
           a_tangent = 0.001;
        }
        a = -1/a_tangent;       //wsp kierunkowy prostopadlej do stycznej
        b = Y1 - a*X1;          //wyraz wolny powyzszej
        C = a*X1;
        D = Y2 - b;
        toRight = atoRight;
        if ( abs(X2 + D*a - X1 - C*a) > 0.001)
        {
           sx = ( X2*X2 - X1*X1 - C*C + D*D )/(2*( X2 + D*a - X1 - C*a )); //x srodka okregu
           sy = a*sx + b;  //y srodka okregu

           //try
           //{
           float  r = sqrt( (X2-sx)*(X2-sx) + (Y2-sy)*(Y2-sy) ); //promien okregu
           drawingArc(bitMap, atoRight, r );
           //}
           //catch(...)
           //{
           //}
        }
        else
        {
          if ( lastX1 == X1 && lastY1 == Y1)    //double click
          {
             type = "Line";
          }
          bitMap->Canvas->MoveTo(X1, Y1 );
          bitMap->Canvas->LineTo(X2, Y2 );
        }
}
//---------------------------------------------------------------------------
void Segment::drawingArc(Graphics::TBitmap *bitMap, bool atoRight,float r)
{
        float max_y = sy + r;
        float min_y = sy - r;
        float max_x = sx + r;
        float min_x = sx - r;
        if ( atoRight == true) //jesli poprzedni luk/linia jest skierowany w prawo
        {
                if ( Y2 < a_tangent*X2 + b_tangent )    //pod styczn¹
                {
                        bitMap->Canvas->Arc(min_x, min_y, max_x, max_y, X1, Y1, X2, Y2);
                        if ( Y2 > sy )
                        {
                                toRight = true;
                        }
                        else
                        {
                                toRight = false;
                        }

                } else                                  //nad styczn¹
                {
                        bitMap->Canvas->Arc(min_x, min_y, max_x, max_y, X2, Y2, X1, Y1);
                        if ( Y2 < sy )
                        {
                                toRight = true;
                        }
                        else
                        {
                                toRight = false;
                        }
                }
        } else      //jesli poprzedni luk/linia jest skierowany w lewo
        {
                if ( Y2 < a_tangent*X2 + b_tangent )    //pod styczn¹
                {
                        bitMap->Canvas->Arc(min_x, min_y, max_x, max_y, X2, Y2, X1, Y1);
                        if ( Y2 < sy )
                        {
                                toRight = true;
                        }
                        else
                        {
                                toRight = false;
                        }

                } else                                  //nad styczn¹
                {
                        bitMap->Canvas->Arc(min_x, min_y, max_x, max_y, X1, Y1, X2, Y2);
                        if ( Y2 > sy )
                        {
                                toRight = true;
                        }
                        else
                        {
                                toRight = false;
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall Segment::setLX1Y1t(int alastX1, int alastY1)
{
        lastX1 = alastX1;
        lastY1 = alastY1;
}
