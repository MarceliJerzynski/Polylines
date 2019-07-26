//---------------------------------------------------------------------------
#ifndef SegmentH
#define SegmentH
#include "Classes.hpp"
#include <string>
#include <vcl.h>
#include <cmath>
#include "Unit1.h"

using namespace std;
//---------------------------------------------------------------------------
class Segment
{
public:
        Segment(int aX1, int aY1, string type);
        int __fastcall getX1();
        int __fastcall getX2();
        int __fastcall getY1();
        int __fastcall getY2();
        string __fastcall getType();
        float __fastcall getSx();
        float __fastcall getSy();
        bool __fastcall getToRight();

        void __fastcall setX1(int arg);
        void __fastcall setX2(int arg);
        void __fastcall setY1(int arg);
        void __fastcall setY2(int arg);
        void __fastcall setType(string arg);
        void __fastcall setA(float arg);
        void __fastcall setB(float arg);
        void __fastcall setLX1Y1t(int alastX1, int alastY1);
        void __fastcall draw(Graphics::TBitmap *bitMap, bool atoRight);

protected:


private:
        int X1, Y1;
        int X2, Y2;
        int lastX1, lastY1;
        float sx, sy;
        string type;

        float a_tangent;
        float b_tangent;
        bool toRight;
        void drawLine(Graphics::TBitmap *bitMap);
        void drawArc(Graphics::TBitmap *bitMap, bool atoRight);
        void drawingArc(Graphics::TBitmap *bitMap, bool atoRight,float r);
};

//---------------------------------------------------------------------------
#endif
