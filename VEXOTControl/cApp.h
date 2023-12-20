#pragma once
#ifndef CAPP_H
#define CAPP_H

#include "cMain.h"

class cApp final : public wxApp
{
public:
	cApp();
	virtual bool OnInit();
	~cApp();

private:
	cMain* m_cMainFrame{};
};

#endif // !CAPP_H

