#include "App.h"
#include <wx/numdlg.h> 

MyApp::MyApp()
{
}

MyApp::~MyApp()
{
}

bool MyApp::OnInit()
{
	frame = new MyFrame("Chess Bishop Problem SAT Rules Generator Ultra", wxPoint(50, 50), wxSize(800, 600));
	frame->Show(true);
	return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	panel = new wxPanel(this, wxID_ANY);
	panel->SetBackgroundColour(wxColour(53, 53, 53));

	wxButton *button_run = new wxButton(panel, ID_Run, wxT("Run"), wxPoint(230, 300), wxSize(205, 30));
	Connect(ID_Run, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnRun));

	debugText = new wxTextCtrl(panel, ID_Debug, wxT(""), wxPoint(10, 340), wxSize(425, 215), wxTE_READONLY | wxTE_RICH | wxTE_MULTILINE | wxBORDER_NONE);
	debugText->SetBackgroundColour(wxColour(35, 35, 35));

	debugText->SetDefaultStyle(wxTextAttr(wxColour(230, 230, 230), wxColour(35, 35, 35)));
	gen = Generator(3);
	std::vector<std::string> o = gen.getRulesForm2();

	for (uint32_t i = 0; i < o.size(); ++i)
	{
		debugText->AppendText(o[i]);
		debugText->AppendText(wxT("\n"));
	}
}

void MyFrame::OnRun(wxCommandEvent& event)
{
	long in = wxGetNumberFromUser(wxT("Insert size of the chess board."), wxT("Insert!"), wxT("Insert Size"), 8, 1, MAXLONG, this);
	if (in != -1)
	{
		debugText->Clear();
		gen = Generator(in);
		std::vector<std::string> o = gen.getRulesForm2();

		for (uint32_t i = 0; i < o.size(); ++i)
		{
			debugText->AppendText(o[i]);
			debugText->AppendText(wxT("\n"));
		}
	}
}

void MyFrame::OnPaint(wxPaintEvent& event)
{
}

void MyFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void MyFrame::OnClose(wxCloseEvent& event)
{
	Destroy();
}
