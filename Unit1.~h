//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        TPopupMenu *PopupMenu1;
        TMenuItem *Line;
        TMenuItem *Arc;
        TMenuItem *N1;
        TMenuItem *Finish1;
        TMenuItem *Continue1;
        TMenuItem *N3;
        TMenuItem *Undo1;
        TMenuItem *Redo1;
        void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Undo1Click(TObject *Sender);
        void __fastcall Redo1Click(TObject *Sender);
        void __fastcall Finish1Click(TObject *Sender);
        void __fastcall Continue1Click(TObject *Sender);
        void __fastcall LineClick(TObject *Sender);
        void __fastcall ArcClick(TObject *Sender);
        void __fastcall PopupMenu1Popup(TObject *Sender);
        void __fastcall Aprro1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

