#include "Generator.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyFrame;

class DrawPanel : public wxPanel
{
public:
	DrawPanel(wxFrame *parent);

	void OnPaint(wxPaintEvent& evt);

	DECLARE_EVENT_TABLE();
};

BEGIN_EVENT_TABLE(DrawPanel, wxPanel)
	EVT_PAINT(DrawPanel::OnPaint)
END_EVENT_TABLE()

class MyApp : public wxApp
{
public:
	MyApp();
	~MyApp();
	virtual bool OnInit();

private:
	MyFrame *frame;
};


class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
	void OnRun(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
	void Change(wxCommandEvent& event);
	void Rule1(wxCommandEvent& event);
	void Rule2(wxCommandEvent& event);

	long input;
	int rule;

	wxImage strelec;

	wxTextCtrl *debugText;
	wxPanel *panel;

	Generator gen;
	wxBitmap bgImage;

	wxDECLARE_EVENT_TABLE();
};

enum
{
	ID_Run = 2,
	ID_Debug = 3,
	ID_Output = 4,
	ID_Change = 5,
	ID_Rule1 = 6,
	ID_Rule2 = 7
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(wxID_EXIT, MyFrame::OnExit)
	EVT_CLOSE(MyFrame::OnClose)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);