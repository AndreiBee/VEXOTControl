#include "cApp.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{
}

bool cApp::OnInit()
{
	::wxInitAllImageHandlers();
	m_cMainFrame = new cMain(wxT("VEXOTControl"));
	//m_cMainFrame->Show();
	return true;
}

cApp::~cApp()
{

}
