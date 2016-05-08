#include "Generator.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class MyFrame;

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
	void OnPaint(wxPaintEvent& event);

private:
	void OnRun(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
	void Change(wxCommandEvent& event);

	long input;

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
	ID_Change = 5
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(wxID_EXIT, MyFrame::OnExit)
	EVT_CLOSE(MyFrame::OnClose)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);