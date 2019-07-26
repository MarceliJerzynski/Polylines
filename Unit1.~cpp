//---------------------------------------------------------------------------
#include <vcl.h>

#pragma hdrstop

#include "Unit1.h"
#include "Segment.h"

#include <vector>
#include <windows.h>
using namespace std;
using namespace Graphics;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

int speedRendering = 25;

const int lineIndex = 0;
const int arcIndex = 1;
const int finishIndex = 3;
const int continueIndex = 4;
const int undoIndex = 6;
const int redoIndex = 7;

TForm1 *Form1;
vector <Segment> segment;
vector <Segment> segment_copy;
bool finish = false;
bool pause = false;
int mouseX = 100;
int mouseY = 100;
string currentType = "Line";
TMenuItem *Item;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void MenuItemEnable(int index, bool enable)
{
        Item = Form1->PopupMenu1->Items->Items[index];
        Item->Enabled = enable;
}

void Draw()
{
        Graphics::TBitmap *bitMap = new Graphics::TBitmap;
        bitMap->Width = Form1->Width;
        bitMap->Height = Form1->Height;

        if (pause == false)
        {
                TPoint p_rel_scr = Mouse->CursorPos;
                TPoint p_rel_frm = Form1->ScreenToClient( p_rel_scr );
                mouseX = (int) p_rel_frm.x;
                mouseY = (int) p_rel_frm.y;
        }
        bool toRight;
        if ( segment.size() != 0)
        {
                segment[ segment.size() -1 ].setX2(mouseX);
                segment[ segment.size() -1 ].setY2(mouseY);
        }
        for (unsigned int i = 0; i < segment.size(); i++)
        {
                if (i > 0)
                {
                        toRight = segment[i-1].getToRight();
                }
                segment[i].draw(bitMap, toRight);
        }
        Form1->Canvas->Draw(0, 0, bitMap);
        delete bitMap;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)            //Renderowanie linii
{
        Draw();
}

//---------------------------------------------------------------------------

void Undo()
{
        if (segment.size() != 0)
        {
                segment.pop_back();
        }
        MenuItemEnable(redoIndex, true);
        if (segment.size() == 0)
        {
                MenuItemEnable(undoIndex, false);
        }

}

void Redo()
{
        int original_size = segment.size();
        if (segment.size() != segment_copy.size() )
        {
                segment[original_size-1].setX2(segment_copy[original_size].getX1() );
                segment[original_size-1].setY2(segment_copy[original_size].getY1() );
                segment.push_back( segment_copy[original_size]);

                MenuItemEnable(undoIndex, true);
        }
}

void Finish()
{
        finish = true;
        MenuItemEnable(redoIndex, false);
        MenuItemEnable(undoIndex, false);
        MenuItemEnable(lineIndex, false);
        MenuItemEnable(arcIndex, false);
        MenuItemEnable(finishIndex, false);
        MenuItemEnable(continueIndex, true);

        Graphics::TBitmap *bitMap = new Graphics::TBitmap;
        bitMap->Width = Form1->Width;
        bitMap->Height = Form1->Height;

        bool toRight;
        if (segment.size() != 0)
        {
                for (unsigned int i = 0; i < segment.size()-1; i++)
                {
                if ( i > 0)
                {
                        toRight = segment[i-1].getToRight();
                }
                segment[i].draw(bitMap, toRight);
                }
        }
        Form1->Canvas->Draw(0, 0, bitMap);

        Form1->Timer1->Enabled = false;
}

void Continue()
{
        finish = false;
        MenuItemEnable(redoIndex, false);

        if (segment.size() != 0)
        {
                 MenuItemEnable(undoIndex, true);
        }
        else
        {
                 MenuItemEnable(undoIndex, false);
        }
         MenuItemEnable(continueIndex, false);
         MenuItemEnable(lineIndex, true);
         MenuItemEnable(arcIndex, true);
         MenuItemEnable(finishIndex, true);

        Form1->Timer1->Enabled = true;

}

float calculateATangent(Segment segment)
{
        float y2 =  segment.getY2();
        float y1 =  segment.getY1();
        float x2 =  segment.getX2();
        float x1 =  segment.getX1();
        if ( segment.getType() == "Line")
        {
                if (x2 == x1)   //jesli styczna jest pionowa
                {
                        if (y2 > y1)
                                return -2147483647;
                        else
                                return  2147483647;
                }
                else
                {
                        return  (y2 - y1) / (x2 - x1);
                }

        } else if (segment.getType() == "Arc")
        {
                return -(x2 - segment.getSx())/ ( y2 - segment.getSy() );
        }

        return NULL;
}

void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button,     //Nacisniecie przycisku
      TShiftState Shift, int X, int Y)
{
        if (Button == mbLeft)
        {
                if (finish == true)
                {
                        Continue();
                        segment.clear();
                        mouseX = X;
                        mouseY = Y;
                }

                Segment example(mouseX,mouseY, currentType);

                if (segment.size() != 0)
                {
                        Segment last = segment[segment.size()-1];
                        float a = calculateATangent(last);
                        example.setA( a );

                        float b;
                        b = last.getY2() - a*last.getX2();
                        example.setB(b);

                        example.setLX1Y1t(last.getX1(), last.getY1());

                }
                else
                {
                example.setType("Line");
                }
                segment.push_back(example);
                segment_copy = segment;

                MenuItemEnable(redoIndex, false);

                if (segment.size() != 0)
                {
                        MenuItemEnable(undoIndex, true);
                }
        }

}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormCreate(TObject *Sender)
{
        DoubleBuffered = true;
        Form1->PopupMenu = PopupMenu1;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,    //Ctrl + Z
      TShiftState Shift)
{
        if (finish == false)
        {

                Item = Form1 -> PopupMenu1->Items->Items[redoIndex];
                if (Key == 'Z' &&  Shift.Contains(ssCtrl) && Shift.Contains(ssShift))
                {
                        if (Item->Enabled == true)
                        {
                                Redo();
                        }
                } else
                if (Key == 'Z' &&  Shift.Contains(ssCtrl))
                {
                        Undo();
                }
                if (Key == VK_RETURN)
                {
                        Finish();
                }
        } else
        if (Key == VK_ESCAPE)
        {
                Continue();
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Undo1Click(TObject *Sender)
{
        Undo();
        pause = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Redo1Click(TObject *Sender)
{
        Redo();
        pause = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Finish1Click(TObject *Sender)
{
        Finish();
        pause = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Continue1Click(TObject *Sender)
{
        Continue();
        pause = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LineClick(TObject *Sender)
{
        if (segment.size()!=0)
        {
                segment[segment.size()-1].setType("Line");
        }
        currentType = "Line";
        Item = Form1->PopupMenu1->Items->Items[lineIndex];
        Item->Checked = true;
        pause = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ArcClick(TObject *Sender)
{       if (segment.size() != 1 && segment.size() != 0)
        {
                segment[segment.size()-1].setType("Arc");
        }
        currentType = "Arc";
        Item = Form1->PopupMenu1->Items->Items[arcIndex];
        Item->Checked = true;
        pause = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PopupMenu1Popup(TObject *Sender)
{
        pause = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Aprro1Click(TObject *Sender)
{
        pause = false;
}
//---------------------------------------------------------------------------

