#include "App.h"
#include <wx/numdlg.h> 
#include "core\Dimacs.h"

MyApp::MyApp()
{
}

MyApp::~MyApp()
{
}

bool MyApp::OnInit()
{
	frame = new MyFrame("Chess Bishop Problem SAT Rules Generator Ultra", wxPoint(50, 50), wxSize(800, 900));
	frame->Show(true);
	return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	wxInitAllImageHandlers();

	panel = new wxPanel(this, wxID_ANY);
	panel->SetBackgroundColour(wxColour(50, 50, 50));

	strelec = wxImage(wxT("Assets/strelec.png"), wxBITMAP_TYPE_PNG);

	wxButton *button_run = new wxButton(panel, ID_Run, wxT("Run"), wxPoint(570, 655), wxSize(200, 30));
	Connect(ID_Run, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnRun));
	
	wxButton *button_in = new wxButton(panel, ID_Change, wxT("Change size of board"), wxPoint(340, 655), wxSize(200, 30));
	Connect(ID_Change, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::Change));
	
	debugText = new wxTextCtrl(panel, ID_Debug, wxT(""), wxPoint(10, 700), wxSize(765, 150), wxTE_READONLY | wxTE_RICH | wxTE_MULTILINE | wxBORDER_NONE);
	debugText->SetBackgroundColour(wxColour(35, 35, 35));

	debugText->SetDefaultStyle(wxTextAttr(wxColour(230, 230, 230), wxColour(35, 35, 35)));
	input = 1;
	/*gen = Generator(3);
	std::vector<std::string> o = gen.getRulesForm2();

	for (uint32_t i = 0; i < o.size(); ++i)
	{
		debugText->AppendText(o[i]);
		debugText->AppendText(wxT("\n"));
	}*/
}

void MyFrame::Change(wxCommandEvent& event)
{
	input = wxGetNumberFromUser(wxT("Insert size of the chess board."), wxT("Insert!"), wxT("Insert Size"), 8, 1, MAXLONG, this);
}

void MyFrame::OnRun(wxCommandEvent& event)
{
	//long in = wxGetNumberFromUser(wxT("Insert size of the chess board."), wxT("Insert!"), wxT("Insert Size"), 8, 1, MAXLONG, this);
	long in = input;
	wxClientDC dc(panel);
	int farba = 0;
	if (in != -1)
	{
		debugText->Clear();
		gen = Generator(in);
		std::vector<std::string> o = gen.getRulesForm1();
		for (uint32_t i = 0; i < o.size(); ++i)
		{
			debugText->AppendText(o[i]);
			debugText->AppendText(wxT("\n"));
		}
		Minisat::Solver solve;

		Fields f = gen.getVariables();
		std::vector<Minisat::Lit> vars = f.getVars();
		Minisat::vec<Minisat::Lit> v;
		for (uint32_t i = 0; i < vars.size(); ++i)
		{
			v.push(vars[i]);
			solve.newVar();
		}

		solve.addClause(v);
		std::vector<Rule> r = gen.getRules();

		for (uint32_t i = 1; i < r.size(); ++i)
		{
			solve.addClause(r[i].getA(), r[i].getB());
		}

		solve.solve();

		for (uint32_t i = 0; i < solve.model.size(); ++i)
		{
			Minisat::Lit l = Minisat::mkLit(i, true);
			int x = f.getX(l);
			int y = f.getY(l);
			if ((y % 2 != 0) && (x == 0)){
				dc.SetBrush(*wxWHITE_BRUSH);
				farba = 0;
			}
			else if ((y % 2 == 0) && (x == 0)){
				dc.SetBrush(*wxBLACK_BRUSH);
				farba = 1;
			}
				if (farba == 0){
					dc.SetBrush(*wxWHITE_BRUSH);
					farba = 1;
				}
				else if (farba == 1){
					dc.SetBrush(*wxBLACK_BRUSH);
					farba = 0;
				}
				
			dc.DrawRectangle(x*600/in + 90, y*600/in + 40, 600/in, 600/in);
			if (Minisat::toInt(solve.model[i]) == 1){
				dc.DrawBitmap(wxBitmap(strelec.Rescale(600 / in, 600 / in, wxIMAGE_QUALITY_HIGH)), x * 600 / in + 90, y * 600 / in + 40);
			}
			/*wxString t = wxString::Format(wxT("%i"), Minisat::toInt(solve.model[i]));
			t.Append(" x: ");
			t.Append(wxString::Format(wxT("%i"), x));
			t.Append(" y: ");
			t.Append(wxString::Format(wxT("%i"), y));
			debugText->AppendText(t);
			debugText->AppendText(wxT("\n"));
			*/
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
