#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_MENU(MainFrameVariables::ID_MENUBAR_FILE_OPEN, cMain::OnOpenMCAFile)
	EVT_CLOSE(cMain::OnExit)
	EVT_MENU(MainFrameVariables::ID_MENUBAR_FILE_QUIT, cMain::OnExit)
	EVT_MENU(MainFrameVariables::ID_RIGHT_CAM_SINGLE_SHOT_BTN, cMain::OnSingleShotCameraImage)
	EVT_MENU(MainFrameVariables::ID_RIGHT_CAM_START_STOP_LIVE_CAPTURING_TGL_BTN, cMain::OnStartStopLiveCapturingMenu)
	EVT_MENU(MainFrameVariables::ID_MENUBAR_EDIT_ENABLE_DARK_MODE, cMain::OnEnableDarkMode)
	EVT_MENU(MainFrameVariables::ID_MENUBAR_EDIT_SETTINGS, cMain::OnOpenSettings)
	EVT_MENU(MainFrameVariables::ID_MENUBAR_TOOLS_CROSSHAIR, cMain::OnCrossHairButton)
	EVT_MENU(MainFrameVariables::ID_MENUBAR_TOOLS_VALUE_DISPLAYING, cMain::OnValueDisplayingCheck)
	EVT_MENU(MainFrameVariables::ID_MENUBAR_WINDOW_FULLSCREEN, cMain::OnFullScreen)
	EVT_MAXIMIZE(cMain::OnMaximizeButton)
	/* Detector X */
	EVT_TEXT_ENTER(MainFrameVariables::ID_RIGHT_SC_DET_X_ABS_TE_CTL, cMain::OnEnterTextCtrlDetectorXAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_DET_X_SET_BTN, cMain::OnSetDetectorXAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_DET_X_DEC_BTN, cMain::OnDecrementDetectorXAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_DET_X_INC_BTN, cMain::OnIncrementDetectorXAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_DET_X_CENTER_BTN, cMain::OnCenterDetectorX)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_DET_X_HOME_BTN, cMain::OnHomeDetectorX)
	/* Optics X */
	EVT_TEXT_ENTER(MainFrameVariables::ID_RIGHT_SC_OPT_X_ABS_TE_CTL, cMain::OnEnterTextCtrlOpticsXAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_X_SET_BTN, cMain::OnSetOpticsXAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_X_DEC_BTN, cMain::OnDecrementOpticsXAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_X_INC_BTN, cMain::OnIncrementOpticsXAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_X_CENTER_BTN, cMain::OnCenterOpticsX)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_X_HOME_BTN, cMain::OnHomeOpticsX)
	/* Optics Y */
	EVT_TEXT_ENTER(MainFrameVariables::ID_RIGHT_SC_OPT_Y_ABS_TE_CTL, cMain::OnEnterTextCtrlOpticsYAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_Y_SET_BTN, cMain::OnSetOpticsYAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_Y_DEC_BTN, cMain::OnDecrementOpticsYAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_Y_INC_BTN, cMain::OnIncrementOpticsYAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_Y_CENTER_BTN, cMain::OnCenterOpticsY)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_Y_HOME_BTN, cMain::OnHomeOpticsY)
	/* Optics Z */
	EVT_TEXT_ENTER(MainFrameVariables::ID_RIGHT_SC_OPT_Z_ABS_TE_CTL, cMain::OnEnterTextCtrlOpticsZAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_Z_SET_BTN, cMain::OnSetOpticsZAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_Z_DEC_BTN, cMain::OnDecrementOpticsZAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_Z_INC_BTN, cMain::OnIncrementOpticsZAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_Z_CENTER_BTN, cMain::OnCenterOpticsZ)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_Z_HOME_BTN, cMain::OnHomeOpticsZ)
	/* Optics Pitch */
	EVT_TEXT_ENTER(MainFrameVariables::ID_RIGHT_SC_OPT_PITCH_ABS_TE_CTL, cMain::OnEnterTextCtrlOpticsPitchAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_PITCH_SET_BTN, cMain::OnSetOpticsPitchAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_PITCH_DEC_BTN, cMain::OnDecrementOpticsPitchAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_PITCH_INC_BTN, cMain::OnIncrementOpticsPitchAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_PITCH_CENTER_BTN, cMain::OnCenterOpticsPitch)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_PITCH_HOME_BTN, cMain::OnHomeOpticsPitch)
	/* Optics Yaw */
	EVT_TEXT_ENTER(MainFrameVariables::ID_RIGHT_SC_OPT_YAW_ABS_TE_CTL, cMain::OnEnterTextCtrlOpticsYawAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_YAW_SET_BTN, cMain::OnSetOpticsYawAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_YAW_DEC_BTN, cMain::OnDecrementOpticsYawAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_YAW_INC_BTN, cMain::OnIncrementOpticsYawAbsPos)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_YAW_CENTER_BTN, cMain::OnCenterOpticsYaw)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_SC_OPT_YAW_HOME_BTN, cMain::OnHomeOpticsYaw)
	/* Camera */
	EVT_CHOICE(MainFrameVariables::ID_RIGHT_CAM_MANUFACTURER_CHOICE, cMain::ChangeCameraManufacturerChoice)
	EVT_TEXT_ENTER(MainFrameVariables::ID_RIGHT_CAM_EXPOSURE_TE_CTL, cMain::ExposureValueChanged)
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_CAM_SINGLE_SHOT_BTN, cMain::OnSingleShotCameraImage)
	EVT_TEXT(MainFrameVariables::ID_RIGHT_CAM_CROSS_HAIR_POS_X_TXT_CTRL, cMain::OnXPosCrossHairTextCtrl)
	EVT_TEXT(MainFrameVariables::ID_RIGHT_CAM_CROSS_HAIR_POS_Y_TXT_CTRL, cMain::OnYPosCrossHairTextCtrl)
	EVT_TOGGLEBUTTON(MainFrameVariables::ID_RIGHT_CAM_CROSS_HAIR_SET_POS_TGL_BTN, cMain::OnSetPosCrossHairTglBtn)
	/* Set Out Folder */
	EVT_BUTTON(MainFrameVariables::ID_RIGHT_MT_OUT_FLD_BTN, cMain::OnSetOutDirectoryBtn)
	/* First Stage */
	EVT_CHOICE(MainFrameVariables::ID_RIGHT_MT_FIRST_STAGE_CHOICE, cMain::OnFirstStageChoice)
	/* Second Stage */
	EVT_CHOICE(MainFrameVariables::ID_RIGHT_MT_SECOND_STAGE_CHOICE, cMain::OnSecondStageChoice)
	/* Start Capturing */
	EVT_TOGGLEBUTTON(MainFrameVariables::ID_RIGHT_MT_START_STOP_MEASUREMENT_TGL_BTN, cMain::OnStartStopCapturingButton)
	/* Start\Stop Live Capturing */
	EVT_TOGGLEBUTTON(MainFrameVariables::ID_RIGHT_CAM_START_STOP_LIVE_CAPTURING_TGL_BTN, cMain::OnStartStopLiveCapturingTglBtn)

	/* Live Capturing */
	EVT_THREAD(MainFrameVariables::ID_THREAD_LIVE_CAPTURING, cMain::LiveCapturingThread)
	/* Worker Thread */
	EVT_THREAD(MainFrameVariables::ID_THREAD_MAIN_CAPTURING, cMain::WorkerThreadEvent)
	/* Progress */
	EVT_THREAD(MainFrameVariables::ID_THREAD_PROGRESS_CAPTURING, cMain::UpdateProgress)
wxEND_EVENT_TABLE()

cMain::cMain(const wxString& title_) 
	: wxFrame(NULL, wxID_ANY, title_)
{
	CreateMainFrame();
	InitDefaultStateWidgets();

	SetIcon(logo_xpm);

	/* Creating, but not showing ProgressBar */
	CreateProgressBar();
	m_ProgressBar->SetIcon(logo_xpm);

	CenterOnScreen();
	Show();

	{
		m_MenuBar->menu_edit->Check(MainFrameVariables::ID_MENUBAR_EDIT_ENABLE_DARK_MODE, true);
		wxCommandEvent art_evt(wxEVT_MENU, MainFrameVariables::ID_MENUBAR_EDIT_ENABLE_DARK_MODE);
		ProcessEvent(art_evt);
	}

	// Artificiallly pressing Settings button
	{
		wxCommandEvent art_evt(wxEVT_MENU, MainFrameVariables::ID_MENUBAR_EDIT_SETTINGS);
		ProcessEvent(art_evt);
	}

	{
		//m_StartStopLiveCapturingTglBtn->SetValue(true);
		//wxCommandEvent art_start_live_capturing(wxEVT_TOGGLEBUTTON, MainFrameVariables::ID_RIGHT_CAM_START_STOP_LIVE_CAPTURING_TGL_BTN);
		//ProcessEvent(art_start_live_capturing);
	}
}

//auto cMain::StopLiveCapturing() -> bool
//{
	//return m_StopLiveCapturing;
//}

void cMain::CreateMainFrame()
{
	InitComponents();
	CreateMenuBarOnFrame();
	CreateVerticalToolBar();
	CreateLeftAndRightSide();
}

void cMain::InitComponents()
{
	/* Settings Frame */
	m_Settings = std::make_unique<cSettings>(this);
	//m_Settings->SetIcon(logo_xpm);
	/* Measurement */
	m_FirstStage = std::make_unique<MainFrameVariables::MeasurementStage>();
	m_SecondStage = std::make_unique<MainFrameVariables::MeasurementStage>();
}

void cMain::CreateMenuBarOnFrame()
{
	m_MenuBar = std::make_unique<MainFrameVariables::MenuBar>();
	this->SetMenuBar(m_MenuBar->menu_bar);

	// File Menu
	m_MenuBar->menu_file->Append(MainFrameVariables::ID_MENUBAR_FILE_OPEN, wxT("Open\tCtrl+O"));
	m_MenuBar->menu_file->Append(MainFrameVariables::ID_MENUBAR_FILE_QUIT, wxT("Quit\tCtrl+Q"));
	// Append File Menu to the Menu Bar
	m_MenuBar->menu_bar->Append(m_MenuBar->menu_file, wxT("&File"));

	// Edit Menu
	m_MenuBar->menu_edit->Append(MainFrameVariables::ID_RIGHT_CAM_SINGLE_SHOT_BTN, wxT("Single Shot\tS"));
	m_MenuBar->menu_edit->Enable(MainFrameVariables::ID_RIGHT_CAM_SINGLE_SHOT_BTN, false);
	m_MenuBar->menu_edit->AppendCheckItem(MainFrameVariables::ID_RIGHT_CAM_START_STOP_LIVE_CAPTURING_TGL_BTN, wxT("Start Live\tL"));
	m_MenuBar->menu_edit->AppendCheckItem(MainFrameVariables::ID_MENUBAR_EDIT_ENABLE_DARK_MODE, wxT("Dark Mode"));
	m_MenuBar->menu_edit->Append(MainFrameVariables::ID_MENUBAR_EDIT_SETTINGS, wxT("Settings\tCtrl+S"));
	// Append Edit Menu to the Menu Bar
	m_MenuBar->menu_bar->Append(m_MenuBar->menu_edit, wxT("&Edit"));

	// Intensity Profile SubMenu
	m_MenuBar->submenu_intensity_profile->AppendCheckItem(MainFrameVariables::ID_MENUBAR_TOOLS_CROSSHAIR, wxT("Crosshair\tC"));
	// Append Submenu Selection Tools to the Tools Menu
	m_MenuBar->menu_tools->Append(wxID_ANY, wxT("&Intensity Profile"), m_MenuBar->submenu_intensity_profile);
	// Append Value Displaying Check
	m_MenuBar->menu_tools->Append(MainFrameVariables::ID_MENUBAR_TOOLS_VALUE_DISPLAYING, wxT("Value Displaying\tV"), wxEmptyString, wxITEM_CHECK);
	// Append Tools Menu to the Menu Bar
	m_MenuBar->menu_bar->Append(m_MenuBar->menu_tools, wxT("&Tools"));
	// Window Menu
	m_MenuBar->menu_window->Append(MainFrameVariables::ID_MENUBAR_WINDOW_FULLSCREEN, wxT("Full screen mode\tF11"), wxEmptyString, wxITEM_CHECK);
	// Append Window Menu to the Menu Bar
	m_MenuBar->menu_bar->Append(m_MenuBar->menu_window, wxT("&Window"));

	// Help Menu
	m_MenuBar->menu_help->Append(MainFrameVariables::ID_MENUBAR_HELP_ABOUT, wxT("About MMCam\tF1"));
	m_MenuBar->menu_bar->Append(m_MenuBar->menu_help, wxT("&Help"));
}

void cMain::InitDefaultStateWidgets()
{
	m_MenuBar->menu_tools->Check(MainFrameVariables::ID_MENUBAR_TOOLS_VALUE_DISPLAYING, true);
	m_PreviewPanel->SetValueDisplayingActive(true);
	m_IsValueDisplayingChecked = true;

	m_MenuBar->menu_tools->Enable(MainFrameVariables::ID_MENUBAR_TOOLS_CROSSHAIR, false);
	m_VerticalToolBar->tool_bar->EnableTool(MainFrameVariables::ID_MENUBAR_TOOLS_CROSSHAIR, false);

	float default_absolute_value{ 0.0f }, default_relative_value{ 1.0f }, default_relative_value_pitch_yaw{ 0.1f };
	/* Default Detector Widgets */
	{
		/* X */
		{
			m_Detector[0].absolute_text_ctrl->ChangeValue(wxString::Format(wxT("%.3f"), default_absolute_value));
			m_Detector[0].relative_text_ctrl->ChangeValue(wxString::Format(wxT("%.3f"), default_relative_value));
			//m_X_Detector->DisableAllControls();
		}
	}
	/* Default Optics Widgets */
	{
		/* X */
		{
			m_Optics[0].absolute_text_ctrl->ChangeValue(wxString::Format(wxT("%.3f"), default_absolute_value));
			m_Optics[0].relative_text_ctrl->ChangeValue(wxString::Format(wxT("%.3f"), default_relative_value));
			//m_Optics[0].DisableAllControls();
		}
		/* Y */
		{
			m_Optics[1].absolute_text_ctrl->ChangeValue(wxString::Format(wxT("%.3f"), default_absolute_value));
			m_Optics[1].relative_text_ctrl->ChangeValue(wxString::Format(wxT("%.3f"), default_relative_value));
			//m_Y_Optics->DisableAllControls();
		}
		/* Z */
		{
			m_Optics[2].absolute_text_ctrl->ChangeValue(wxString::Format(wxT("%.3f"), default_absolute_value));
			m_Optics[2].relative_text_ctrl->ChangeValue(wxString::Format(wxT("%.3f"), default_relative_value));
			//m_Optics[0].DisableAllControls();
		}
		/* Pitch */
		{
			m_Optics[3].absolute_text_ctrl->ChangeValue(wxString::Format(wxT("%.3f"), default_absolute_value));
			m_Optics[3].relative_text_ctrl->ChangeValue(wxString::Format(wxT("%.3f"), default_relative_value_pitch_yaw));
			//m_Optics[0].DisableAllControls();
		}
		/* Yaw */
		{
			m_Optics[4].absolute_text_ctrl->ChangeValue(wxString::Format(wxT("%.3f"), default_absolute_value));
			m_Optics[4].relative_text_ctrl->ChangeValue(wxString::Format(wxT("%.3f"), default_relative_value_pitch_yaw));
			//m_Optics[0].DisableAllControls();
		}
	}

	/* Disabling Measurement Controls */
	{
		//m_OutDirTextCtrl->Disable();
		//m_OutDirBtn->Disable();

		float default_start{ 0.0f }, default_step{ 1.0f }, default_finish{ 24.0f };

		/* First Stage */
		{
			m_FirstStage->start->ChangeValue(wxString::Format(wxT("%.3f"), default_start));
			m_FirstStage->step->ChangeValue(wxString::Format(wxT("%.3f"), default_step));
			m_FirstStage->finish->ChangeValue(wxString::Format(wxT("%.3f"), default_finish));
			m_FirstStage->DisableAllControls();
		}
		/* Second Stage */
		{
			m_SecondStage->start->ChangeValue(wxString::Format(wxT("%.3f"), default_start));
			m_SecondStage->step->ChangeValue(wxString::Format(wxT("%.3f"), default_step));
			m_SecondStage->finish->ChangeValue(wxString::Format(wxT("%.3f"), default_finish));
			m_SecondStage->DisableAllControls();
		}
		/* Start Capturing */
		m_StartStopMeasurementTglBtn->Disable();
	}
}

void cMain::CreateLeftAndRightSide()
{
	wxBoxSizer* main_sizer = new wxBoxSizer(wxHORIZONTAL);

	int height_left_and_right_panels{ 600 };
	wxBoxSizer* right_sizer = new wxBoxSizer(wxVERTICAL);
	wxSize sizeOfRightSide = { 300, height_left_and_right_panels };
	right_sizer->SetMinSize(sizeOfRightSide);
	CreateRightSide(right_sizer);

	wxBoxSizer* left_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxSize sizeOfPreviewWindow = { 600, height_left_and_right_panels };
	left_sizer->SetMinSize(sizeOfPreviewWindow);
	CreateLeftSide(left_sizer);

	main_sizer->Add(left_sizer, 1, wxEXPAND);
	main_sizer->Add(right_sizer, 0, wxEXPAND);

	SetSizerAndFit(main_sizer);
}

void cMain::CreateLeftSide(wxSizer* left_side_sizer)
{
	//left_side_sizer->Add(m_VerticalToolBar->tool_bar, 0, wxEXPAND);
	auto input_args = std::make_unique<PreviewPanelVariables::InputPreviewPanelArgs>
		(
			m_CrossHairPosXTxtCtrl.get(),
			m_CrossHairPosYTxtCtrl.get(),
			m_SetCrossHairPosTglBtn.get()
			);

	m_PreviewPanel = std::make_unique<cPreviewPanel>
		(
		this, 
		left_side_sizer, 
		std::move(input_args)
		);
}

void cMain::CreateRightSide(wxSizer* right_side_sizer)
{
	m_RightSidePanel = new wxPanel(this);
#ifdef _DEBUG
	m_RightSidePanel->SetBackgroundColour(wxColor(150, 100, 180));
#else
	m_RightSidePanel->SetBackgroundColour(wxColor(255, 255, 255));
#endif // _DEBUG

	wxBoxSizer* right_side_panel_sizer = new wxBoxSizer(wxVERTICAL);

	CreateSteppersControl(m_RightSidePanel, right_side_panel_sizer);
	CreateDeviceControls(m_RightSidePanel, right_side_panel_sizer);
	CreateMeasurement(m_RightSidePanel, right_side_panel_sizer);

	m_RightSidePanel->SetSizer(right_side_panel_sizer);
	right_side_sizer->Add(m_RightSidePanel, 1, wxEXPAND);
}

void cMain::CreateSteppersControl(wxPanel* right_side_panel, wxBoxSizer* right_side_panel_sizer)
{
	wxSizer* const sc_static_box_sizer = new wxStaticBoxSizer(wxVERTICAL, right_side_panel, "&Steppers Constrol");

	wxSize absolute_text_ctrl_size = { 54, 20 }, relative_text_ctrl_size = {absolute_text_ctrl_size};
	wxSize set_btn_size = { 35, 20 };
	wxSize inc_dec_size = { 20, 20 };

	/* Center bitmap */
	wxImage centerImage = wxImage(center_xpm);
	wxBitmap centerBitmap = wxBitmap(centerImage);
	/* Home bitmap */
	wxImage homeImage = wxImage(home_xpm);
	wxBitmap homeBitmap = wxBitmap(homeImage);
	{
		wxSizer* const detector_static_box_sizer = new wxStaticBoxSizer(wxVERTICAL, right_side_panel, "&Detector");
		{
			/* Detector X */
			wxSizer* const x_detector = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&X");
			x_detector->AddStretchSpacer();
			{
				/* Absolute */
				{
					wxSizer* const abs_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Absolute [mm]");
					wxFloatingPointValidator<float>	abs_val(3, NULL, wxNUM_VAL_DEFAULT);
					abs_val.SetMin(-1000.f);
					abs_val.SetMax(1000.f);
					m_Detector[0].absolute_text_ctrl = new wxTextCtrl(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_DET_X_ABS_TE_CTL, 
						wxT("123.456"), 
						wxDefaultPosition, 
						absolute_text_ctrl_size, 
						wxTE_CENTRE | wxTE_PROCESS_ENTER, 
						abs_val
					);

					m_Detector[0].set_btn = new wxButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_DET_X_SET_BTN, 
						wxT("Set"), 
						wxDefaultPosition, 
						set_btn_size);
					m_Detector[0].set_btn->SetToolTip(wxT("Set the absolute motor position"));

					abs_sizer->Add(m_Detector[0].absolute_text_ctrl, 0, wxALIGN_CENTER);
					abs_sizer->Add(m_Detector[0].set_btn, 0, wxALIGN_CENTER | wxLEFT, 2);
					x_detector->Add(abs_sizer, 0, wxALIGN_CENTER);
				}

				/* Relative */
				{
					m_Detector[0].decrement_btn = new wxButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_DET_X_DEC_BTN, 
						wxT("-"), 
						wxDefaultPosition, 
						inc_dec_size);
					m_Detector[0].decrement_btn->SetToolTip(wxT("Decrement distance"));
					wxFloatingPointValidator<float>	rel_val(3, NULL, wxNUM_VAL_DEFAULT);
					rel_val.SetMin(-1000.f);
					rel_val.SetMax(1000.f);
					m_Detector[0].relative_text_ctrl = new wxTextCtrl(
						right_side_panel,
						MainFrameVariables::ID_RIGHT_SC_DET_X_REL_TE_CTL, 
						wxT("789.123"), 
						wxDefaultPosition, 
						relative_text_ctrl_size, 
						wxTE_CENTRE, 
						rel_val
					);
					m_Detector[0].increment_btn = new wxButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_DET_X_INC_BTN, 
						wxT("+"), 
						wxDefaultPosition, 
						inc_dec_size);
					m_Detector[0].increment_btn->SetToolTip(wxT("Increment distance"));

					wxSizer* const rel_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Relative [mm]");
					rel_sizer->Add(m_Detector[0].decrement_btn, 0, wxALIGN_CENTER | wxRIGHT, 2);
					rel_sizer->Add(m_Detector[0].relative_text_ctrl, 0, wxALIGN_CENTER);
					rel_sizer->Add(m_Detector[0].increment_btn, 0, wxALIGN_CENTER | wxLEFT, 2);
					x_detector->Add(rel_sizer, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 2);
				}

				/* Global positioning controls */
				{
					m_Detector[0].center_btn = new wxBitmapButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_DET_X_CENTER_BTN, 
						centerBitmap, 
						wxDefaultPosition, 
						inc_dec_size);
					m_Detector[0].center_btn->SetToolTip(wxT("Go to the center position of motor"));
					m_Detector[0].home_btn = new wxBitmapButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_DET_X_HOME_BTN, 
						homeBitmap, 
						wxDefaultPosition, 
						inc_dec_size);
					m_Detector[0].home_btn->SetToolTip(wxT("Go to the home position of motor"));

					wxSizer* const jump_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Jump");
					jump_sizer->Add(m_Detector[0].center_btn, 0, wxALIGN_CENTER | wxRIGHT, 2);
					jump_sizer->Add(m_Detector[0].home_btn, 0, wxALIGN_CENTER);

					x_detector->Add(jump_sizer, 0, wxALIGN_CENTER);
				}
			}
			x_detector->AddStretchSpacer();
			detector_static_box_sizer->Add(x_detector, 0, wxEXPAND);
		}
		sc_static_box_sizer->Add(detector_static_box_sizer, 0, wxEXPAND);

		wxSizer* const optics_static_box_sizer = new wxStaticBoxSizer(wxVERTICAL, right_side_panel, "&Optics");
		{
			/* Optics X */
			wxSizer* const x_optics = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&X");
			x_optics->AddStretchSpacer();
			{
				/* Absolute */
				{
					wxSizer* const abs_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Absolute [mm]");
					wxFloatingPointValidator<float>	abs_val(3, NULL, wxNUM_VAL_DEFAULT);
					abs_val.SetMin(-1000.f);
					abs_val.SetMax(1000.f);
					m_Optics[0].absolute_text_ctrl = new wxTextCtrl(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_X_ABS_TE_CTL, 
						wxT("123.456"), 
						wxDefaultPosition, 
						absolute_text_ctrl_size, 
						wxTE_CENTRE | wxTE_PROCESS_ENTER, 
						abs_val
					);

					m_Optics[0].set_btn = new wxButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_X_SET_BTN, 
						wxT("Set"), 
						wxDefaultPosition, 
						set_btn_size);
					m_Optics[0].set_btn->SetToolTip(wxT("Set the absolute motor position"));

					abs_sizer->Add(m_Optics[0].absolute_text_ctrl, 0, wxALIGN_CENTER);
					abs_sizer->Add(m_Optics[0].set_btn, 0, wxALIGN_CENTER | wxLEFT, 2);
					x_optics->Add(abs_sizer, 0, wxALIGN_CENTER);
				}

				/* Relative */
				{
					m_Optics[0].decrement_btn = new wxButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_X_DEC_BTN, 
						wxT("-"), 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[0].decrement_btn->SetToolTip(wxT("Decrement distance"));
					wxFloatingPointValidator<float>	rel_val(3, NULL, wxNUM_VAL_DEFAULT);
					rel_val.SetMin(-1000.f);
					rel_val.SetMax(1000.f);
					m_Optics[0].relative_text_ctrl = new wxTextCtrl(
						right_side_panel,
						MainFrameVariables::ID_RIGHT_SC_OPT_X_REL_TE_CTL, 
						wxT("789.123"), 
						wxDefaultPosition, 
						relative_text_ctrl_size, 
						wxTE_CENTRE, 
						rel_val
					);
					m_Optics[0].increment_btn = new wxButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_X_INC_BTN, 
						wxT("+"), 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[0].increment_btn->SetToolTip(wxT("Increment distance"));

					wxSizer* const rel_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Relative [mm]");
					rel_sizer->Add(m_Optics[0].decrement_btn, 0, wxALIGN_CENTER | wxRIGHT, 2);
					rel_sizer->Add(m_Optics[0].relative_text_ctrl, 0, wxALIGN_CENTER);
					rel_sizer->Add(m_Optics[0].increment_btn, 0, wxALIGN_CENTER | wxLEFT, 2);
					x_optics->Add(rel_sizer, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 2);
				}

				/* Global positioning controls */
				{
					m_Optics[0].center_btn = new wxBitmapButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_X_CENTER_BTN, 
						centerBitmap, 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[0].center_btn->SetToolTip(wxT("Go to the center position of motor"));
					m_Optics[0].home_btn = new wxBitmapButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_X_HOME_BTN, 
						homeBitmap, 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[0].home_btn->SetToolTip(wxT("Go to the home position of motor"));

					wxSizer* const jump_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Jump");
					jump_sizer->Add(m_Optics[0].center_btn, 0, wxALIGN_CENTER | wxRIGHT, 2);
					jump_sizer->Add(m_Optics[0].home_btn, 0, wxALIGN_CENTER);

					x_optics->Add(jump_sizer, 0, wxALIGN_CENTER);
				}
			}
			x_optics->AddStretchSpacer();
			optics_static_box_sizer->Add(x_optics, 0, wxEXPAND);

			/* Optics Y */
			wxSizer* const y_optics = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Y");
			y_optics->AddStretchSpacer();
			{
				/* Absolute */
				{
					wxSizer* const abs_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Absolute [mm]");
					wxFloatingPointValidator<float>	abs_val(3, NULL, wxNUM_VAL_DEFAULT);
					abs_val.SetMin(-1000.f);
					abs_val.SetMax(1000.f);
					m_Optics[1].absolute_text_ctrl = new wxTextCtrl(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_Y_ABS_TE_CTL, 
						wxT("123.456"), 
						wxDefaultPosition, 
						absolute_text_ctrl_size, 
						wxTE_CENTRE | wxTE_PROCESS_ENTER, 
						abs_val
					);

					m_Optics[1].set_btn = new wxButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_Y_SET_BTN, 
						wxT("Set"), 
						wxDefaultPosition, 
						set_btn_size);
					m_Optics[1].set_btn->SetToolTip(wxT("Set the absolute motor position"));

					abs_sizer->Add(m_Optics[1].absolute_text_ctrl, 0, wxALIGN_CENTER);
					abs_sizer->Add(m_Optics[1].set_btn, 0, wxALIGN_CENTER | wxLEFT, 2);
					y_optics->Add(abs_sizer, 0, wxALIGN_CENTER);
				}

				/* Relative */
				{
					m_Optics[1].decrement_btn = new wxButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_Y_DEC_BTN, 
						wxT("-"), 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[1].decrement_btn->SetToolTip(wxT("Decrement distance"));
					wxFloatingPointValidator<float>	rel_val(3, NULL, wxNUM_VAL_DEFAULT);
					rel_val.SetMin(-1000.f);
					rel_val.SetMax(1000.f);
					m_Optics[1].relative_text_ctrl = new wxTextCtrl(
						right_side_panel,
						MainFrameVariables::ID_RIGHT_SC_OPT_Y_REL_TE_CTL, 
						wxT("789.123"), 
						wxDefaultPosition, 
						relative_text_ctrl_size, 
						wxTE_CENTRE, 
						rel_val
					);
					m_Optics[1].increment_btn = new wxButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_Y_INC_BTN, 
						wxT("+"), 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[1].increment_btn->SetToolTip(wxT("Increment distance"));

					wxSizer* const rel_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Relative [mm]");
					rel_sizer->Add(m_Optics[1].decrement_btn, 0, wxALIGN_CENTER | wxRIGHT, 2);
					rel_sizer->Add(m_Optics[1].relative_text_ctrl, 0, wxALIGN_CENTER);
					rel_sizer->Add(m_Optics[1].increment_btn, 0, wxALIGN_CENTER | wxLEFT, 2);
					y_optics->Add(rel_sizer, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 2);
				}

				/* Global positioning controls */
				{
					m_Optics[1].center_btn = new wxBitmapButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_Y_CENTER_BTN, 
						centerBitmap, 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[1].center_btn->SetToolTip(wxT("Go to the center position of motor"));
					m_Optics[1].home_btn = new wxBitmapButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_Y_HOME_BTN, 
						homeBitmap, 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[1].home_btn->SetToolTip(wxT("Go to the home position of motor"));

					wxSizer* const jump_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Jump");
					jump_sizer->Add(m_Optics[1].center_btn, 0, wxALIGN_CENTER | wxRIGHT, 2);
					jump_sizer->Add(m_Optics[1].home_btn, 0, wxALIGN_CENTER);

					y_optics->Add(jump_sizer, 0, wxALIGN_CENTER);
				}
			}
			y_optics->AddStretchSpacer();
			optics_static_box_sizer->Add(y_optics, 0, wxEXPAND);

			/* Optics Z */
			wxSizer* const z_optics = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Z");
			z_optics->AddStretchSpacer();
			{
				/* Absolute */
				{
					wxSizer* const abs_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Absolute [mm]");
					wxFloatingPointValidator<float>	abs_val(3, NULL, wxNUM_VAL_DEFAULT);
					abs_val.SetMin(-1000.f);
					abs_val.SetMax(1000.f);
					m_Optics[2].absolute_text_ctrl = new wxTextCtrl(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_Z_ABS_TE_CTL, 
						wxT("123.456"), 
						wxDefaultPosition, 
						absolute_text_ctrl_size, 
						wxTE_CENTRE | wxTE_PROCESS_ENTER, 
						abs_val
					);

					m_Optics[2].set_btn = new wxButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_Z_SET_BTN, 
						wxT("Set"), 
						wxDefaultPosition, 
						set_btn_size);
					m_Optics[2].set_btn->SetToolTip(wxT("Set the absolute motor position"));

					abs_sizer->Add(m_Optics[2].absolute_text_ctrl, 0, wxALIGN_CENTER);
					abs_sizer->Add(m_Optics[2].set_btn, 0, wxALIGN_CENTER | wxLEFT, 2);
					z_optics->Add(abs_sizer, 0, wxALIGN_CENTER);
				}

				/* Relative */
				{
					m_Optics[2].decrement_btn = new wxButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_Z_DEC_BTN, 
						wxT("-"), 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[2].decrement_btn->SetToolTip(wxT("Decrement distance"));
					wxFloatingPointValidator<float>	rel_val(3, NULL, wxNUM_VAL_DEFAULT);
					rel_val.SetMin(-1000.f);
					rel_val.SetMax(1000.f);
					m_Optics[2].relative_text_ctrl = new wxTextCtrl(
						right_side_panel,
						MainFrameVariables::ID_RIGHT_SC_OPT_Z_REL_TE_CTL, 
						wxT("789.123"), 
						wxDefaultPosition, 
						relative_text_ctrl_size, 
						wxTE_CENTRE, 
						rel_val
					);
					m_Optics[2].increment_btn = new wxButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_Z_INC_BTN, 
						wxT("+"), 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[2].increment_btn->SetToolTip(wxT("Increment distance"));

					wxSizer* const rel_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Relative [mm]");
					rel_sizer->Add(m_Optics[2].decrement_btn, 0, wxALIGN_CENTER | wxRIGHT, 2);
					rel_sizer->Add(m_Optics[2].relative_text_ctrl, 0, wxALIGN_CENTER);
					rel_sizer->Add(m_Optics[2].increment_btn, 0, wxALIGN_CENTER | wxLEFT, 2);
					z_optics->Add(rel_sizer, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 2);
				}

				/* Global positioning controls */
				{
					m_Optics[2].center_btn = new wxBitmapButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_Z_CENTER_BTN, 
						centerBitmap, 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[2].center_btn->SetToolTip(wxT("Go to the center position of motor"));
					m_Optics[2].home_btn = new wxBitmapButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_Z_HOME_BTN, 
						homeBitmap, 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[2].home_btn->SetToolTip(wxT("Go to the home position of motor"));

					wxSizer* const jump_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Jump");
					jump_sizer->Add(m_Optics[2].center_btn, 0, wxALIGN_CENTER | wxRIGHT, 2);
					jump_sizer->Add(m_Optics[2].home_btn, 0, wxALIGN_CENTER);

					z_optics->Add(jump_sizer, 0, wxALIGN_CENTER);
				}
			}
			z_optics->AddStretchSpacer();
			optics_static_box_sizer->Add(z_optics, 0, wxEXPAND);

			/* Optics Pitch */
			wxSizer* const pitch_optics = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Pitch");
			pitch_optics->AddStretchSpacer();
			{
				/* Absolute */
				{
					wxSizer* const abs_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Absolute [mm]");
					wxFloatingPointValidator<float>	abs_val(3, NULL, wxNUM_VAL_DEFAULT);
					abs_val.SetMin(-1000.f);
					abs_val.SetMax(1000.f);
					m_Optics[3].absolute_text_ctrl = new wxTextCtrl(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_PITCH_ABS_TE_CTL, 
						wxT("123.456"), 
						wxDefaultPosition, 
						absolute_text_ctrl_size, 
						wxTE_CENTRE | wxTE_PROCESS_ENTER, 
						abs_val
					);

					m_Optics[3].set_btn = new wxButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_PITCH_SET_BTN, 
						wxT("Set"), 
						wxDefaultPosition, 
						set_btn_size);
					m_Optics[3].set_btn->SetToolTip(wxT("Set the absolute motor position"));

					abs_sizer->Add(m_Optics[3].absolute_text_ctrl, 0, wxALIGN_CENTER);
					abs_sizer->Add(m_Optics[3].set_btn, 0, wxALIGN_CENTER | wxLEFT, 2);
					pitch_optics->Add(abs_sizer, 0, wxALIGN_CENTER);
				}

				/* Relative */
				{
					m_Optics[3].decrement_btn = new wxButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_PITCH_DEC_BTN, 
						wxT("-"), 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[3].decrement_btn->SetToolTip(wxT("Decrement distance"));
					wxFloatingPointValidator<float>	rel_val(3, NULL, wxNUM_VAL_DEFAULT);
					rel_val.SetMin(-1000.f);
					rel_val.SetMax(1000.f);
					m_Optics[3].relative_text_ctrl = new wxTextCtrl(
						right_side_panel,
						MainFrameVariables::ID_RIGHT_SC_OPT_PITCH_REL_TE_CTL, 
						wxT("789.123"), 
						wxDefaultPosition, 
						relative_text_ctrl_size, 
						wxTE_CENTRE, 
						rel_val
					);
					m_Optics[3].increment_btn = new wxButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_PITCH_INC_BTN, 
						wxT("+"), 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[3].increment_btn->SetToolTip(wxT("Increment distance"));

					wxSizer* const rel_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Relative [mm]");
					rel_sizer->Add(m_Optics[3].decrement_btn, 0, wxALIGN_CENTER | wxRIGHT, 2);
					rel_sizer->Add(m_Optics[3].relative_text_ctrl, 0, wxALIGN_CENTER);
					rel_sizer->Add(m_Optics[3].increment_btn, 0, wxALIGN_CENTER | wxLEFT, 2);
					pitch_optics->Add(rel_sizer, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 2);
				}

				/* Global positioning controls */
				{
					m_Optics[3].center_btn = new wxBitmapButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_PITCH_CENTER_BTN, 
						centerBitmap, 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[3].center_btn->SetToolTip(wxT("Go to the center position of motor"));
					m_Optics[3].home_btn = new wxBitmapButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_PITCH_HOME_BTN, 
						homeBitmap, 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[3].home_btn->SetToolTip(wxT("Go to the home position of motor"));

					wxSizer* const jump_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Jump");
					jump_sizer->Add(m_Optics[3].center_btn, 0, wxALIGN_CENTER | wxRIGHT, 2);
					jump_sizer->Add(m_Optics[3].home_btn, 0, wxALIGN_CENTER);

					pitch_optics->Add(jump_sizer, 0, wxALIGN_CENTER);
				}
			}
			pitch_optics->AddStretchSpacer();
			optics_static_box_sizer->Add(pitch_optics, 0, wxEXPAND);

			/* Optics Yaw */
			wxSizer* const yaw_optics = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Yaw");
			yaw_optics->AddStretchSpacer();
			{
				/* Absolute */
				{
					wxSizer* const abs_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Absolute [mm]");
					wxFloatingPointValidator<float>	abs_val(3, NULL, wxNUM_VAL_DEFAULT);
					abs_val.SetMin(-1000.f);
					abs_val.SetMax(1000.f);
					m_Optics[4].absolute_text_ctrl = new wxTextCtrl(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_YAW_ABS_TE_CTL, 
						wxT("123.456"), 
						wxDefaultPosition, 
						absolute_text_ctrl_size, 
						wxTE_CENTRE | wxTE_PROCESS_ENTER, 
						abs_val
					);

					m_Optics[4].set_btn = new wxButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_YAW_SET_BTN, 
						wxT("Set"), 
						wxDefaultPosition, 
						set_btn_size);
					m_Optics[4].set_btn->SetToolTip(wxT("Set the absolute motor position"));

					abs_sizer->Add(m_Optics[4].absolute_text_ctrl, 0, wxALIGN_CENTER);
					abs_sizer->Add(m_Optics[4].set_btn, 0, wxALIGN_CENTER | wxLEFT, 2);
					yaw_optics->Add(abs_sizer, 0, wxALIGN_CENTER);
				}

				/* Relative */
				{
					m_Optics[4].decrement_btn = new wxButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_YAW_DEC_BTN, 
						wxT("-"), 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[4].decrement_btn->SetToolTip(wxT("Decrement distance"));
					wxFloatingPointValidator<float>	rel_val(3, NULL, wxNUM_VAL_DEFAULT);
					rel_val.SetMin(-1000.f);
					rel_val.SetMax(1000.f);
					m_Optics[4].relative_text_ctrl = new wxTextCtrl(
						right_side_panel,
						MainFrameVariables::ID_RIGHT_SC_OPT_YAW_REL_TE_CTL, 
						wxT("789.123"), 
						wxDefaultPosition, 
						relative_text_ctrl_size, 
						wxTE_CENTRE, 
						rel_val
					);
					m_Optics[4].increment_btn = new wxButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_YAW_INC_BTN, 
						wxT("+"), 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[4].increment_btn->SetToolTip(wxT("Increment distance"));

					wxSizer* const rel_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Relative [mm]");
					rel_sizer->Add(m_Optics[4].decrement_btn, 0, wxALIGN_CENTER | wxRIGHT, 2);
					rel_sizer->Add(m_Optics[4].relative_text_ctrl, 0, wxALIGN_CENTER);
					rel_sizer->Add(m_Optics[4].increment_btn, 0, wxALIGN_CENTER | wxLEFT, 2);
					yaw_optics->Add(rel_sizer, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 2);
				}

				/* Global positioning controls */
				{
					m_Optics[4].center_btn = new wxBitmapButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_YAW_CENTER_BTN, 
						centerBitmap, 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[4].center_btn->SetToolTip(wxT("Go to the center position of motor"));
					m_Optics[4].home_btn = new wxBitmapButton(
						right_side_panel, 
						MainFrameVariables::ID_RIGHT_SC_OPT_YAW_HOME_BTN, 
						homeBitmap, 
						wxDefaultPosition, 
						inc_dec_size);
					m_Optics[4].home_btn->SetToolTip(wxT("Go to the home position of motor"));

					wxSizer* const jump_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Jump");
					jump_sizer->Add(m_Optics[4].center_btn, 0, wxALIGN_CENTER | wxRIGHT, 2);
					jump_sizer->Add(m_Optics[4].home_btn, 0, wxALIGN_CENTER);

					yaw_optics->Add(jump_sizer, 0, wxALIGN_CENTER);
				}
			}
			yaw_optics->AddStretchSpacer();
			optics_static_box_sizer->Add(yaw_optics, 0, wxEXPAND);
		}
		sc_static_box_sizer->Add(optics_static_box_sizer, 0, wxEXPAND);
	}
	right_side_panel_sizer->Add(sc_static_box_sizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 2);
}

void cMain::CreateDeviceControls(wxPanel* right_side_panel, wxBoxSizer* right_side_panel_sizer)
{
	wxSizer* const static_box_sizer = new wxStaticBoxSizer(wxVERTICAL, right_side_panel, "&Device");
	wxSizer* const first_row_sizer = new wxBoxSizer(wxHORIZONTAL);
	{
		wxSizer* const box_sizer = new wxStaticBoxSizer(wxVERTICAL, right_side_panel, "&Selected Device");
		{
			m_DeviceChoice = std::make_unique<wxChoice>(right_side_panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_DeviceArrayString);
			m_DeviceChoice->SetSelection(0);
			m_DeviceChoice->Disable();
			box_sizer->AddStretchSpacer();
			box_sizer->Add(m_DeviceChoice.get(), 0, wxCENTER | wxBOTTOM, 4);

			auto txt_ctrl_size = wxSize(60, 24);
			m_SelectedDeviceStaticTXT = std::make_unique<wxTextCtrl>
				(
					right_side_panel, 
					wxID_ANY, 
					wxT("None"),
					wxDefaultPosition,
					txt_ctrl_size,
					wxTE_CENTRE | wxTE_READONLY
				);
			box_sizer->Add(m_SelectedDeviceStaticTXT.get(), 0, wxCENTER);
			box_sizer->AddStretchSpacer();
		}
		first_row_sizer->Add(box_sizer, 0, wxEXPAND);

		wxSizer* const settings_static_box_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Settings");
		{
			wxSizer* const exposure_static_box_sizer = new wxStaticBoxSizer(wxVERTICAL, right_side_panel, "&Exposure [s]");

			wxIntegerValidator<int>	exposure_val(NULL, wxNUM_VAL_ZERO_AS_BLANK);
			exposure_val.SetMin(1);
			exposure_val.SetMax(1000000);

			wxSize exposure_size = { 64, 24 };

			m_DeviceExposure = std::make_unique<wxTextCtrl>
				(
					right_side_panel, 
					MainFrameVariables::ID_RIGHT_CAM_EXPOSURE_TE_CTL, 
					wxT("1"), 
					wxDefaultPosition, 
					exposure_size, 
					wxTE_CENTRE | wxTE_PROCESS_ENTER, 
					exposure_val
				);

			exposure_static_box_sizer->AddStretchSpacer();
			exposure_static_box_sizer->Add(m_DeviceExposure.get(), 0, wxEXPAND);
			exposure_static_box_sizer->AddStretchSpacer();

			settings_static_box_sizer->Add(exposure_static_box_sizer, 0, wxEXPAND);
		}
		first_row_sizer->Add(settings_static_box_sizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 2);

		/* Preview And Start\Stop Live Capturing */
		{
			wxSizer* const ss_and_start_stop_box_sizer = new wxBoxSizer(wxVERTICAL);
			
			m_SingleShotBtn = std::make_unique<wxButton>(
				right_side_panel,
				MainFrameVariables::ID_RIGHT_CAM_SINGLE_SHOT_BTN,
				wxT("Single Shot (S)"), 
				wxDefaultPosition, 
				wxDefaultSize);
			m_SingleShotBtn->Disable();
			ss_and_start_stop_box_sizer->Add(m_SingleShotBtn.get(), 0, wxEXPAND);

			m_StartStopLiveCapturingTglBtn = std::make_unique<wxToggleButton>
				(
					right_side_panel,
					MainFrameVariables::ID_RIGHT_CAM_START_STOP_LIVE_CAPTURING_TGL_BTN, 
					wxT("Start Live (L)")
				);
			m_StartStopLiveCapturingTglBtn->Disable();
			ss_and_start_stop_box_sizer->Add(m_StartStopLiveCapturingTglBtn.get(), 0, wxEXPAND | wxTOP, 5);

			first_row_sizer->AddStretchSpacer();
			first_row_sizer->Add(ss_and_start_stop_box_sizer, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 2);
		}
	}
	static_box_sizer->Add(first_row_sizer, 0, wxEXPAND);

	wxSizer* const second_row_sizer = new wxBoxSizer(wxHORIZONTAL);
	{
		wxSizer* const cross_hair_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&CrossHair");
		/* X Position */
		{
			wxSizer* const x_pos_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&X");
			wxIntegerValidator<int>	x_pos_validator(NULL, wxNUM_VAL_ZERO_AS_BLANK);
			x_pos_validator.SetMin(1);
			x_pos_validator.SetMax(10000);

			m_CrossHairPosXTxtCtrl = std::make_unique<wxTextCtrl>
				(
					right_side_panel,
					MainFrameVariables::ID_RIGHT_CAM_CROSS_HAIR_POS_X_TXT_CTRL,
					wxT("1"), 
					wxDefaultPosition, 
					wxDefaultSize, 
					wxTE_CENTRE
					);
			m_CrossHairPosXTxtCtrl->Disable();
			x_pos_sizer->Add(m_CrossHairPosXTxtCtrl.get(), 1, wxEXPAND);
			cross_hair_sizer->Add(x_pos_sizer, 1, wxEXPAND | wxRIGHT, 2);
		}

		/* Y Position */
		{
			wxSizer* const y_pos_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Y");
			wxIntegerValidator<int>	y_pos_validator(NULL, wxNUM_VAL_ZERO_AS_BLANK);
			y_pos_validator.SetMin(1);
			y_pos_validator.SetMax(10000);

			m_CrossHairPosYTxtCtrl = std::make_unique<wxTextCtrl>
				(
					right_side_panel,
					MainFrameVariables::ID_RIGHT_CAM_CROSS_HAIR_POS_Y_TXT_CTRL,
					wxT("1"), 
					wxDefaultPosition, 
					wxDefaultSize, 
					wxTE_CENTRE
					);
			m_CrossHairPosYTxtCtrl->Disable();
			y_pos_sizer->Add(m_CrossHairPosYTxtCtrl.get(), 1, wxEXPAND);
			cross_hair_sizer->Add(y_pos_sizer, 1, wxEXPAND);
		}

		/* Set Postion */
		{
			m_SetCrossHairPosTglBtn = std::make_unique<wxToggleButton>
				(
					right_side_panel,
					MainFrameVariables::ID_RIGHT_CAM_CROSS_HAIR_SET_POS_TGL_BTN,
					wxT("Set")
				);
			m_SetCrossHairPosTglBtn->Disable();

			cross_hair_sizer->AddSpacer(2);
			cross_hair_sizer->Add(m_SetCrossHairPosTglBtn.get(), 0, wxALIGN_CENTER);
		}
		second_row_sizer->Add(cross_hair_sizer, 1, wxEXPAND);
	}
	static_box_sizer->Add(second_row_sizer, 0, wxEXPAND);

	right_side_panel_sizer->Add(static_box_sizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 2);
}

void cMain::CreateMeasurement(wxPanel* right_side_panel, wxBoxSizer* right_side_panel_sizer)
{
	wxSizer* const mmt_static_box_sizer = new wxStaticBoxSizer(wxVERTICAL, right_side_panel, "&Measurement");

	/* Output directory */
	{
		wxSizer* const out_dir_static_box_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Output directory");
		
		m_OutDirTextCtrl = std::make_unique<wxTextCtrl>(
			right_side_panel, 
			MainFrameVariables::ID_RIGHT_MT_OUT_FLD_TE_CTL, 
			wxT("Save directory..."), 
			wxDefaultPosition, 
			wxDefaultSize, 
			wxTE_LEFT | wxTE_READONLY
			);

		m_OutDirBtn = std::make_unique<wxButton>(
			right_side_panel, 
			MainFrameVariables::ID_RIGHT_MT_OUT_FLD_BTN, 
			wxT("Select folder"));
		m_OutDirBtn->SetToolTip(wxT("Set the output directory"));

		out_dir_static_box_sizer->Add(m_OutDirTextCtrl.get(), 1, wxEXPAND | wxRIGHT, 4);
		//out_dir_static_box_sizer->AddStretchSpacer();
		out_dir_static_box_sizer->Add(m_OutDirBtn.get(), 0, wxALIGN_CENTER);

		mmt_static_box_sizer->Add(out_dir_static_box_sizer, 0, wxEXPAND);
	}

	wxSize start_text_ctrl_size = { 54, 20 }, step_text_ctrl_size = {start_text_ctrl_size}, finish_text_ctrl_size{start_text_ctrl_size};

	{
		wxSizer* const directions_static_box_sizer = new wxStaticBoxSizer(wxVERTICAL, right_side_panel, "&Directions");

		/* First axis */
		{
			wxSizer* const first_axis_static_box_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&First axis");

			/* Stage */
			{
				wxSizer* const stage_static_box_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Stage");
				m_FirstStage->stage = new wxChoice(
					right_side_panel, 
					MainFrameVariables::ID_RIGHT_MT_FIRST_STAGE_CHOICE, 
					wxDefaultPosition, 
					wxDefaultSize, 
					m_FirstStage->motors);
				m_FirstStage->stage->SetSelection(0);
				stage_static_box_sizer->Add(m_FirstStage->stage, 0, wxEXPAND);
				first_axis_static_box_sizer->Add(stage_static_box_sizer, 0, wxEXPAND);
			}

			/* Start */
			{
				wxSizer* const start_static_box_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Start");

				wxFloatingPointValidator<float>	start_val(3, NULL, wxNUM_VAL_DEFAULT);
				start_val.SetMin(-1000.0);
				start_val.SetMax(1000.0);

				m_FirstStage->start = new wxTextCtrl(
					right_side_panel,
					MainFrameVariables::ID_RIGHT_MT_FIRST_STAGE_START,
					wxT("123.456"), 
					wxDefaultPosition, 
					start_text_ctrl_size, 
					wxTE_CENTRE, 
					start_val);

				start_static_box_sizer->Add(m_FirstStage->start, 0, wxEXPAND);

				first_axis_static_box_sizer->Add(start_static_box_sizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 2);
			}

			/* Step */
			{
				wxSizer* const step_static_box_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Step");

				wxFloatingPointValidator<float>	step_val(3, NULL, wxNUM_VAL_DEFAULT);
				step_val.SetMin(-1000.0);
				step_val.SetMax(1000.0);

				m_FirstStage->step = new wxTextCtrl(
					right_side_panel, 
					MainFrameVariables::ID_RIGHT_MT_FIRST_STAGE_STEP,
					wxT("123.456"), 
					wxDefaultPosition, 
					step_text_ctrl_size, 
					wxTE_CENTRE, 
					step_val);
				
				step_static_box_sizer->Add(m_FirstStage->step, 0, wxEXPAND);
				first_axis_static_box_sizer->Add(step_static_box_sizer, 0, wxEXPAND | wxRIGHT, 2);
			}

			/* Finish */
			{
				wxSizer* const finish_static_box_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Finish");

				wxFloatingPointValidator<float>	finish_val(3, NULL, wxNUM_VAL_DEFAULT);
				finish_val.SetMin(-1000.0);
				finish_val.SetMax(1000.0);

				m_FirstStage->finish = new wxTextCtrl(
					right_side_panel, 
					MainFrameVariables::ID_RIGHT_MT_FIRST_STAGE_FINISH,
					wxT("123.456"), 
					wxDefaultPosition, 
					finish_text_ctrl_size, 
					wxTE_CENTRE, 
					finish_val);

				finish_static_box_sizer->Add(m_FirstStage->finish, 0, wxEXPAND);
				first_axis_static_box_sizer->Add(finish_static_box_sizer, 0, wxEXPAND);
			}

			directions_static_box_sizer->Add(first_axis_static_box_sizer, 0, wxEXPAND);
		}

		/* Second axis */
		{
			wxSizer* const second_axis_static_box_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Second axis");

			/* Stage */
			{
				wxSizer* const stage_static_box_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Stage");
				m_SecondStage->stage = new wxChoice(
					right_side_panel, 
					MainFrameVariables::ID_RIGHT_MT_SECOND_STAGE_CHOICE, 
					wxDefaultPosition, 
					wxDefaultSize, 
					m_SecondStage->motors);
				m_SecondStage->stage->SetSelection(0);
				stage_static_box_sizer->Add(m_SecondStage->stage, 0, wxEXPAND);
				second_axis_static_box_sizer->Add(stage_static_box_sizer, 0, wxEXPAND);
			}

			/* Start */
			{
				wxSizer* const start_static_box_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Start");

				wxFloatingPointValidator<float>	start_val(3, NULL, wxNUM_VAL_DEFAULT);
				start_val.SetMin(-1000.0);
				start_val.SetMax(1000.0);

				m_SecondStage->start = new wxTextCtrl(
					right_side_panel,
					MainFrameVariables::ID_RIGHT_MT_SECOND_STAGE_START,
					wxT("123.456"), 
					wxDefaultPosition, 
					start_text_ctrl_size, 
					wxTE_CENTRE, 
					start_val);

				start_static_box_sizer->Add(m_SecondStage->start, 0, wxEXPAND);

				second_axis_static_box_sizer->Add(start_static_box_sizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 2);
			}

			/* Step */
			{
				wxSizer* const step_static_box_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Step");

				wxFloatingPointValidator<float>	step_val(3, NULL, wxNUM_VAL_DEFAULT);
				step_val.SetMin(-1000.0);
				step_val.SetMax(1000.0);

				m_SecondStage->step = new wxTextCtrl(
					right_side_panel, 
					MainFrameVariables::ID_RIGHT_MT_SECOND_STAGE_STEP,
					wxT("123.456"), 
					wxDefaultPosition, 
					step_text_ctrl_size, 
					wxTE_CENTRE, 
					step_val);
				
				step_static_box_sizer->Add(m_SecondStage->step, 0, wxEXPAND);
				second_axis_static_box_sizer->Add(step_static_box_sizer, 0, wxEXPAND | wxRIGHT, 2);
			}

			/* Finish */
			{
				wxSizer* const finish_static_box_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Finish");

				wxFloatingPointValidator<float>	finish_val(3, NULL, wxNUM_VAL_DEFAULT);
				finish_val.SetMin(-1000.0);
				finish_val.SetMax(1000.0);

				m_SecondStage->finish = new wxTextCtrl(
					right_side_panel, 
					MainFrameVariables::ID_RIGHT_MT_SECOND_STAGE_FINISH,
					wxT("123.456"), 
					wxDefaultPosition, 
					finish_text_ctrl_size, 
					wxTE_CENTRE, 
					finish_val);

				finish_static_box_sizer->Add(m_SecondStage->finish, 0, wxEXPAND);
				second_axis_static_box_sizer->Add(finish_static_box_sizer, 0, wxEXPAND);
			}

			directions_static_box_sizer->Add(second_axis_static_box_sizer, 0, wxEXPAND);
		}

		mmt_static_box_sizer->Add(directions_static_box_sizer, 0, wxEXPAND);
	}

	/* Start Capturing */
	{
		wxSizer* const horizontal_sizer = new wxBoxSizer(wxHORIZONTAL);

		wxSizer* const capturing_sizer = new wxStaticBoxSizer(wxHORIZONTAL, right_side_panel, "&Capturing");
		m_StartStopMeasurementTglBtn = std::make_unique<wxToggleButton>
			(
				right_side_panel,
				MainFrameVariables::ID_RIGHT_MT_START_STOP_MEASUREMENT_TGL_BTN,
				wxT("Start Capturing")					
			);
		horizontal_sizer->AddStretchSpacer();
		horizontal_sizer->Add(capturing_sizer);
		capturing_sizer->Add(m_StartStopMeasurementTglBtn.get());
		mmt_static_box_sizer->Add(horizontal_sizer, 0, wxEXPAND);
	}

	right_side_panel_sizer->Add(mmt_static_box_sizer, 0, wxEXPAND | wxLEFT | wxRIGHT, 2);
}

auto cMain::OnEnableDarkMode(wxCommandEvent& evt) -> void
{
	if (m_MenuBar->menu_edit->IsChecked(MainFrameVariables::ID_MENUBAR_EDIT_ENABLE_DARK_MODE))
	{
		m_PreviewPanel->SetBackgroundColor(m_BlackAppearenceColor);
		wxColour normalized_black = wxColour(100, 100, 100);
		m_VerticalToolBar->tool_bar->SetBackgroundColour(normalized_black);
		wxColour nb_color = wxColour(normalized_black.Red() + 40, normalized_black.Green() + 40, normalized_black.Blue() + 40);
		m_RightSidePanel->SetBackgroundColour(nb_color);
	}
	else
	{
		m_PreviewPanel->SetBackgroundColor(m_DefaultAppearenceColor);

		m_VerticalToolBar->tool_bar->SetBackgroundColour(m_DefaultAppearenceColor);
		m_RightSidePanel->SetBackgroundColour(m_DefaultAppearenceColor);
	}
	Refresh();
}

void cMain::CreateProgressBar()
{
	wxSize size_of_progress_bar{ 400, 190 };
	auto previewPanelSize = m_PreviewPanel->GetSize();
	wxPoint start_point_progress_bar
	{ 
		GetPosition().x + previewPanelSize.x - size_of_progress_bar.x, 
		GetPosition().y + GetSize().y - size_of_progress_bar.y 
	};
	m_ProgressBar = std::make_unique<ProgressBar>(this, start_point_progress_bar, size_of_progress_bar);
}

void cMain::OnSingleShotCameraImage(wxCommandEvent& evt)
{
	constexpr auto raise_exception_msg = []() 
	{
		wxString title = "Connection error";
		wxMessageBox(
			wxT
			(
				"Current camera can't provide a single shot."
				"\nPlease, check if the camera is connected properly and restart the program."
			),
			title,
			wxICON_ERROR);
	};
	wxBusyCursor busy_cursor{};

	auto timePointToWxString = []()
		{
			auto now = std::chrono::system_clock::now().time_since_epoch().count();
			wxString formattedTime = wxString::Format(wxT("%lld"), now);
			return formattedTime;
		};

	wxString exposure_time_str = m_DeviceExposure->GetValue().IsEmpty() 
		? wxString("1") 
		: m_DeviceExposure->GetValue();
	auto exposure_time = abs(wxAtoi(exposure_time_str)); // Because user input is in [ms], we need to recalculate exposure time to [us]

	auto start_live_capturing_after_ss = m_StartStopLiveCapturingTglBtn->GetValue();

	if (start_live_capturing_after_ss)
	{
		m_StartedThreads.back().second = false;

		m_SingleShotBtn->Disable();
		m_StartStopLiveCapturingTglBtn->Disable();
		while (!m_StartedThreads.back().first.IsEmpty())
		{
			wxThread::This()->Sleep(10);
		}

		m_SingleShotBtn->Enable();
	}

	{
		auto now = std::chrono::system_clock::now();
		auto cur_time = std::chrono::system_clock::to_time_t(now);
		auto str_time = std::string(std::ctime(&cur_time)).substr(11, 8);
		auto cur_hours = str_time.substr(0, 2);
		auto cur_mins = str_time.substr(3, 2);
		auto cur_secs = str_time.substr(6, 2);

		auto out_dir = m_OutDirTextCtrl->GetValue();
		const std::string file_name = std::string(out_dir.mb_str()) + std::string("\\") +
			std::string("ss_") + 
			cur_hours + std::string("H_") + 
			cur_mins + std::string("M_") + 
			cur_secs + std::string("S_") + 
			std::to_string(exposure_time) + std::string("s") 
			+ std::string(".mca");

		/* Ketek */
		{
			auto currThreadTimeStamp = timePointToWxString();
			m_StartedThreads.push_back(std::make_pair(currThreadTimeStamp, true));
			
			auto mcaData = std::make_unique<unsigned long[]>(m_KetekHandler->GetDataSize());

			m_KetekHandler->CaptureData(exposure_time, mcaData.get(), &m_StartedThreads.back().second);

			m_StartedThreads.back().second = false;
			m_StartedThreads.back().first = "";

			if (!mcaData)
			{
				raise_exception_msg();
				return;
			}

			unsigned long long sum{};
			sum = std::accumulate(&mcaData[0], &mcaData[m_KetekHandler->GetDataSize()], sum);

			MainFrameVariables::WriteMCAFile
			(
				file_name, 
				mcaData.get(), 
				m_KetekHandler.get(), 
				sum,
				exposure_time
			);

			m_PreviewPanel->SetKETEKData(mcaData.get(), m_KetekHandler->GetDataSize(), sum);
		}
	}

	m_StartStopLiveCapturingTglBtn->Enable();

	/* Only if user has already started Live Capturing, continue Live Capturing */
	if (start_live_capturing_after_ss)
	{
		//m_StopLiveCapturing = false;
		StartLiveCapturing();
	}
}

void cMain::OnSetOutDirectoryBtn(wxCommandEvent& evt)
{
	wxDirDialog save_dialog(NULL, "Choose save directory", "",
		wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

	if (save_dialog.ShowModal() == wxID_CANCEL)
		return;

	m_OutDirTextCtrl->SetValue(save_dialog.GetPath());
	m_FirstStage->EnableAllControls();
	//m_SecondStage->EnableAllControls();
	m_MenuBar->menu_edit->Enable(MainFrameVariables::ID_RIGHT_CAM_SINGLE_SHOT_BTN, true);
	if (m_SelectedDeviceStaticTXT->GetValue() != "-")
	{
		m_SingleShotBtn->Enable();
		m_StartStopMeasurementTglBtn->Enable();
	}

#ifdef _DEBUG
		m_StartStopMeasurementTglBtn->Enable();
#endif // _DEBUG
}

auto cMain::OnOpenMCAFile(wxCommandEvent& evt) -> void
{
	wxString filePath{};

#ifdef _DEBUG
	filePath = "D:\\Projects\\RIGAKU\\VEXOTControl\\VEXOTControl\\src\\data\\035-019_01.mca";
#else
	wxFileDialog openFileDialog(this, _("Open file"), "", "",
		"MCA files (*.mca)|*.mca|All files (*.*)|*.*",
		wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return; // the user changed idea...

	// Proceed loading the file chosen by the user
	filePath = openFileDialog.GetPath();
#endif // _DEBUG

	ParseMCAFile(filePath);
}

auto cMain::ParseMCAFile(const wxString filePath) -> void
{
	std::ifstream file(filePath.ToStdString());
	if (!file.is_open()) {
		wxLogError("Cannot open file '%s'.", filePath);
		return;
	}

	std::string line;
	double binSize = 0.0;
	std::unique_ptr<unsigned long[]> values;
	bool foundBinSize = false;
	bool found8192 = false;

	while (std::getline(file, line)) 
	{
		if (line.find("Bin Size") != std::string::npos) 
		{
			std::replace(line.begin(), line.end(), ',', '.');
			std::istringstream iss(line);
			std::string key, equalSign;
			iss >> key >> key >> equalSign >> binSize;
			foundBinSize = true;
		}

		if (line == "8192") {
			found8192 = true;
			break;
		}
	}

	if (!foundBinSize) {
		wxLogError("BinSize parameter not found.");
		return;
	}

	if (!found8192) {
		wxLogError("8192 row not found.");
		return;
	}

	auto numValues = 8192;

	values = std::make_unique<unsigned long[]>(numValues);

	unsigned long value;
	int i{};
	while (file >> value && i < numValues)
	{
		values[i] = value;
		++i;
	}

	wxLogMessage("Successfully loaded data. BinSize: %f, Values count: %lu", binSize, numValues);

	m_PreviewPanel->SetReferenceBinSize(binSize);

	unsigned long long sum{};
	sum = std::accumulate(&values[0], &values[numValues], sum);

	m_PreviewPanel->SetKETEKReferenceData(values.get(), numValues, sum);
}

void cMain::OnOpenSettings(wxCommandEvent& evt)
{
	m_PreviewPanel->SetFocus();
	m_Settings->ShowModal();
	if (!m_Settings->IsActive())
	{
		//InitializeSelectedCamera();
		UpdateStagePositions();
		EnableUsedAndDisableNonUsedMotors();	
		InitializeSelectedDevice();
	}
}

auto cMain::InitializeSelectedCamera() -> void
{
	auto curr_camera = m_Settings->GetSelectedCamera();
	if (curr_camera == "None") return;

	m_SelectedDeviceStaticTXT->SetLabel(curr_camera);	

	m_StartStopLiveCapturingTglBtn->SetValue(true);
	wxCommandEvent art_start_live_capturing(wxEVT_TOGGLEBUTTON, MainFrameVariables::ID_RIGHT_CAM_START_STOP_LIVE_CAPTURING_TGL_BTN);
	ProcessEvent(art_start_live_capturing);
}

auto cMain::InitializeSelectedDevice() -> void
{
	/* Ketek */
	if (m_DeviceChoice->GetString(m_DeviceChoice->GetSelection()) == "KETEK")
	{
		if (m_SelectedDeviceStaticTXT->GetValue().Find("UDXD") != wxNOT_FOUND) return;

		m_KetekHandler = std::make_unique<Ketek>(m_Settings->GetSelectedKETEK().ToStdString());
		if (m_KetekHandler->IsDeviceInitialized())
		{
			m_PreviewPanel->SetCurrentDevice(PreviewPanelVariables::KETEK);
			m_PreviewPanel->SetBinSize(m_KetekHandler->GetBinSize());
			m_SelectedDeviceStaticTXT->SetValue(m_Settings->GetSelectedKETEK());
			m_StartStopLiveCapturingTglBtn->Enable();
		}
		else
		{
			m_SelectedDeviceStaticTXT->SetValue(wxT("-"));
			m_StartStopLiveCapturingTglBtn->Disable();
		}

		m_VerticalToolBar->tool_bar->Disable();
		m_VerticalToolBar->tool_bar->Hide();
	}
}

void cMain::OnFullScreen(wxCommandEvent& evt)
{
	if (!IsMaximized())
	{
		Maximize(true);
		m_MenuBar->menu_window->Check(MainFrameVariables::ID_MENUBAR_WINDOW_FULLSCREEN, true);
	}
	else
	{
		Maximize(false);
		m_MenuBar->menu_window->Check(MainFrameVariables::ID_MENUBAR_WINDOW_FULLSCREEN, false);
	}
}

void cMain::OnMaximizeButton(wxMaximizeEvent& evt)
{
	if (m_MenuBar->menu_window->IsChecked(MainFrameVariables::ID_MENUBAR_WINDOW_FULLSCREEN))
	{
		m_MenuBar->menu_window->Check(MainFrameVariables::ID_MENUBAR_WINDOW_FULLSCREEN, false);
	}
	else
	{
		m_MenuBar->menu_window->Check(MainFrameVariables::ID_MENUBAR_WINDOW_FULLSCREEN, true);
	}
}

void cMain::OnExit(wxCloseEvent& evt)
{
#ifndef _DEBUG
	if (evt.CanVeto())
	{
		if (wxMessageBox("Are you sure?",
			"Exit application",
			wxICON_QUESTION | wxYES_NO) != wxYES)
		{
			evt.Veto();
			return;
		}
	}
#endif // !_DEBUG
	//m_XimeaControl->StopAcquisition();
	//m_XimeaControl->TurnOffLastThread();
	{
		wxString exposure_time_str = m_DeviceExposure->GetValue().IsEmpty() 
			? wxString("0") 
			: m_DeviceExposure->GetValue();
		unsigned long exposure_time = abs(wxAtoi(exposure_time_str)); // Because user input is in [ms], we need to recalculate the value to [us]
		wxThread::This()->Sleep(exposure_time);
	}
	//m_XimeaControl->ClearAllThreads();

	Destroy();  // you may also do:  event.Skip();
	evt.Skip();
	// since the default event handler does call Destroy(), too
}

void cMain::UpdateStagePositions()
{
	m_Detector[0].absolute_text_ctrl->SetValue
	(
		wxString::Format(wxT("%.3f"), 
			m_Settings->GetActualMotorPosition(SettingsVariables::DETECTOR_X))
	);

	m_Optics[0].absolute_text_ctrl->SetValue
	(
		wxString::Format(wxT("%.3f"), 
			m_Settings->GetActualMotorPosition(SettingsVariables::OPTICS_X))
	);

	m_Optics[1].absolute_text_ctrl->SetValue
	(
		wxString::Format(wxT("%.3f"), 
			m_Settings->GetActualMotorPosition(SettingsVariables::OPTICS_Y))
	);

	m_Optics[2].absolute_text_ctrl->SetValue
	(
		wxString::Format(wxT("%.3f"), 
			m_Settings->GetActualMotorPosition(SettingsVariables::OPTICS_Z))
	);

	m_Optics[3].absolute_text_ctrl->SetValue
	(
		wxString::Format(wxT("%.3f"), 
			m_Settings->GetActualMotorPosition(SettingsVariables::OPTICS_PITCH))
	);

	m_Optics[4].absolute_text_ctrl->SetValue
	(
		wxString::Format(wxT("%.3f"), 
			m_Settings->GetActualMotorPosition(SettingsVariables::OPTICS_YAW))
	);

}

void cMain::OnExit(wxCommandEvent& evt)
{
	wxCloseEvent artificialExit(wxEVT_CLOSE_WINDOW);
	ProcessEvent(artificialExit);
}

void cMain::EnableUsedAndDisableNonUsedMotors()
{
	/* Detector X */
	if (m_Settings->MotorHasSerialNumber(SettingsVariables::DETECTOR_X)) m_Detector[0].EnableAllControls();
	else m_Detector[0].DisableAllControls();

	/* Optics X */
	if (m_Settings->MotorHasSerialNumber(SettingsVariables::OPTICS_X)) m_Optics[0].EnableAllControls();
	else m_Optics[0].DisableAllControls();
	/* Optics Y */
	if (m_Settings->MotorHasSerialNumber(SettingsVariables::OPTICS_Y)) m_Optics[1].EnableAllControls();
	else m_Optics[1].DisableAllControls();
	/* Optics Z */
	if (m_Settings->MotorHasSerialNumber(SettingsVariables::OPTICS_Z)) m_Optics[2].EnableAllControls();
	else m_Optics[2].DisableAllControls();	
	/* Optics Pitch */
	if (m_Settings->MotorHasSerialNumber(SettingsVariables::OPTICS_PITCH)) m_Optics[3].EnableAllControls();
	else m_Optics[3].DisableAllControls();	
	/* Optics Yaw */
	if (m_Settings->MotorHasSerialNumber(SettingsVariables::OPTICS_YAW)) m_Optics[4].EnableAllControls();
	else m_Optics[4].DisableAllControls();
}

void cMain::CreateVerticalToolBar()
{
	m_VerticalToolBar = std::make_unique<MainFrameVariables::ToolBar>();
	m_VerticalToolBar->tool_bar = new wxToolBar
	(
		this, 
		wxID_ANY, 
		wxDefaultPosition, 
		wxDefaultSize, 
		wxTB_VERTICAL
	);

	// CrossHair
	wxImage crosshairToolImage = wxImage(cross_hair_xpm);
	wxBitmap crosshairToolBitmap = wxBitmap(crosshairToolImage);
	m_VerticalToolBar->tool_bar->AddCheckTool(MainFrameVariables::ID_MENUBAR_TOOLS_CROSSHAIR, _("Crosshair"), crosshairToolBitmap);
	m_VerticalToolBar->tool_bar->SetToolShortHelp(MainFrameVariables::ID_MENUBAR_TOOLS_CROSSHAIR, wxT("Crosshair (C)"));

	m_VerticalToolBar->tool_bar->SetToolBitmapSize(wxSize(30, 30));
	m_VerticalToolBar->tool_bar->Realize();
}

auto cMain::LiveCapturingFinishedCapturingAndDrawing(bool is_finished) -> void
{
	//m_LiveCapturingEndedDrawingOnCamPreview = is_finished;
}

auto cMain::WorkerThreadFinished(bool is_finished) -> void
{
	if (is_finished)
	{
		wxCommandEvent live_capturing_evt(wxEVT_TOGGLEBUTTON, MainFrameVariables::ID_RIGHT_CAM_START_STOP_LIVE_CAPTURING_TGL_BTN);
		ProcessEvent(live_capturing_evt);
	}
}

void cMain::UnCheckAllTools()
{
	/* Unchecking CrossHair Button */
	m_VerticalToolBar->tool_bar->ToggleTool(MainFrameVariables::ID_MENUBAR_TOOLS_CROSSHAIR, false);
	m_MenuBar->menu_tools->Check(MainFrameVariables::ID_MENUBAR_TOOLS_CROSSHAIR, false);
	//m_CamPreview->SetCrossHairButtonActive(false);
	m_CrossHairPosXTxtCtrl->Disable();
	m_CrossHairPosYTxtCtrl->Disable();
}

void cMain::OnFirstStageChoice(wxCommandEvent& evt)
{
	auto first_stage_selection = m_FirstStage->stage->GetCurrentSelection() - 1;
	double start_stage_value{}, step_stage_value{}, finish_stage_value{};
	switch (first_stage_selection)
	{
		/* Detector */
		case 0:
			if (!m_Detector[0].absolute_text_ctrl->GetValue().ToDouble(&start_stage_value)) return;
			break;
		/* Optics */
		case 1:
			if (!m_Optics[0].absolute_text_ctrl->GetValue().ToDouble(&start_stage_value)) return;
			break;
		case 2:
			if (!m_Optics[1].absolute_text_ctrl->GetValue().ToDouble(&start_stage_value)) return;
			break;
		case 3:
			if (!m_Optics[2].absolute_text_ctrl->GetValue().ToDouble(&start_stage_value)) return;
			break;
		case 4:
			if (!m_Optics[3].absolute_text_ctrl->GetValue().ToDouble(&start_stage_value)) return;
			break;
		case 5:
			if (!m_Optics[4].absolute_text_ctrl->GetValue().ToDouble(&start_stage_value)) return;
			break;
		default:
			break;
	}
	/* Set Start To Current position of motor */
	m_FirstStage->start->SetValue
	(
		wxString::Format
		(
			wxT("%.3f"), 
			(float)start_stage_value
		)
	);
	/* Set Finish To Current position of motor + Step */
	if (!m_FirstStage->step->GetValue().ToDouble(&step_stage_value)) return;
	finish_stage_value = start_stage_value + step_stage_value;
	m_FirstStage->finish->SetValue
	(
		wxString::Format
		(
			wxT("%.3f"), 
			(float)finish_stage_value
		)
	);
}

void cMain::OnSecondStageChoice(wxCommandEvent& evt)
{
	auto second_stage_selection = m_SecondStage->stage->GetCurrentSelection() - 1;
	double start_stage_value{}, step_stage_value{}, finish_stage_value{};
	switch (second_stage_selection)
	{
	/* Detector */
	case 0:
		if (!m_Detector[0].absolute_text_ctrl->GetValue().ToDouble(&start_stage_value)) return;
		break;
	/* Optics */
	case 1:
		if (!m_Optics[0].absolute_text_ctrl->GetValue().ToDouble(&start_stage_value)) return;
		break;
	case 2:
		if (!m_Optics[1].absolute_text_ctrl->GetValue().ToDouble(&start_stage_value)) return;
		break;
	case 3:
		if (!m_Optics[2].absolute_text_ctrl->GetValue().ToDouble(&start_stage_value)) return;
		break;
	case 4:
		if (!m_Optics[3].absolute_text_ctrl->GetValue().ToDouble(&start_stage_value)) return;
		break;
	case 5:
		if (!m_Optics[4].absolute_text_ctrl->GetValue().ToDouble(&start_stage_value)) return;
		break;
	default:
		break;
	}
	/* Set Start To Current position of motor */
	m_SecondStage->start->SetValue
	(
		wxString::Format
		(
			wxT("%.3f"), 
			(float)start_stage_value
		)
	);
	/* Set Finish To Current position of motor + Step */
	if (!m_SecondStage->step->GetValue().ToDouble(&step_stage_value)) return;
	finish_stage_value = start_stage_value + step_stage_value;
	m_SecondStage->finish->SetValue
	(
		wxString::Format
		(
			wxT("%.3f"), 
			(float)finish_stage_value
		)
	);
}

void cMain::OnStartStopCapturingButton(wxCommandEvent& evt)
{
#ifndef _DEBUG
	if (m_SelectedDeviceStaticTXT->GetValue() == "-")
	{
		wxLogError("There is no connected device for capturing.");
		return;
	}
#endif // !_DEBUG

	if (!std::filesystem::exists(m_OutDirTextCtrl->GetValue().ToStdString()))
	{
		wxLogError("Desired path doesn't exist.\nPlease, change the output directory to existing path and try again.");
		return;
	}

	if (m_StartStopLiveCapturingTglBtn->GetValue())
	{
		m_StartStopLiveCapturingTglBtn->SetValue(false);
		wxCommandEvent live_capturing_evt(wxEVT_TOGGLEBUTTON, MainFrameVariables::ID_RIGHT_CAM_START_STOP_LIVE_CAPTURING_TGL_BTN);
		ProcessEvent(live_capturing_evt);
	}

	if (m_StartStopMeasurementTglBtn->GetValue())
	{
		if (m_StartedThreads.size() && m_StartedThreads.back().second)
		{
			wxBusyCursor busy;
			m_StartedThreads.back().second = false;
			m_StartStopMeasurementTglBtn->Disable();
			while (!m_StartedThreads.back().first.empty())
				wxThread::This()->Sleep(100);
			m_StartStopMeasurementTglBtn->Enable();
		}

		if (!StartCapturing())
		{
			m_StartStopMeasurementTglBtn->SetValue(false);
			return;
		}
		m_StartStopMeasurementTglBtn->SetLabel("Stop Capturing");
	}
	else
	{
		m_StartedThreads.back().second = false;
		m_StartStopMeasurementTglBtn->Disable();
		while (!m_StartedThreads.back().first.empty())
			wxThread::This()->Sleep(100);
		m_StartStopMeasurementTglBtn->Enable();

		m_StartStopMeasurementTglBtn->SetLabel("Start Capturing");
	}
}

auto cMain::StartCapturing() -> bool
{
	constexpr auto raise_exception_msg = [](wxString axis) 
	{
		wxString title = "Finish position error";
		wxMessageBox(
			wxT
			(
				"Finish position of " + axis + " axis is not correct!"
				"\nPlease, check if STEP and FINISH values are correct!"
			),
			title,
			wxICON_ERROR);
	};

	auto timePointToWxString = []()
		{
			auto now = std::chrono::system_clock::now().time_since_epoch().count();
			wxString formattedTime = wxString::Format(wxT("%lld"), now);
			return formattedTime;
		};

	wxString exposure_time_str = m_DeviceExposure->GetValue().IsEmpty() 
		? wxString("1") 
		: m_DeviceExposure->GetValue();
	auto exposureSeconds = abs(wxAtoi(exposure_time_str)); // Because user input is in [ms], we need to recalculate the value to [us]

	auto first_axis = std::make_unique<MainFrameVariables::AxisMeasurement>();
	auto second_axis = std::make_unique<MainFrameVariables::AxisMeasurement>();
	double start_first_stage_value{}, step_first_stage_value{}, finish_first_stage_value{};
	double start_second_stage_value{}, step_second_stage_value{}, finish_second_stage_value{};
	int first_stage_step_count{}, second_stage_step_count{};
	/* Checking if user selected None as a stage */
	{
		/* Checking first stage */
		{
			if (m_FirstStage->stage->GetCurrentSelection() == 0) return false;
			else
			{
				first_axis->axis_number = m_FirstStage->stage->GetCurrentSelection() - 1;
			}
		}
		/* Checking Start, Step and Finish values */
		{
			if (!m_FirstStage->start->GetValue().ToDouble(&start_first_stage_value)) return false;
			first_axis->start = (int)(start_first_stage_value * 1000.0) / 1000.f;
			if (!m_FirstStage->step->GetValue().ToDouble(&step_first_stage_value)) return false;
			first_axis->step = (int)(step_first_stage_value * 1000.0) / 1000.f;
			if (!m_FirstStage->finish->GetValue().ToDouble(&finish_first_stage_value)) return false;
			first_axis->finish = (int)(finish_first_stage_value * 1000.0) / 1000.f;
			if (
				(finish_first_stage_value - start_first_stage_value < 0.0 && step_first_stage_value > 0.0)
				|| (finish_first_stage_value - start_first_stage_value > 0.0 && step_first_stage_value < 0.0)
				) 
				raise_exception_msg("first");
			first_axis->step_number = ((int)(finish_first_stage_value * 1000.0) - 
				(int)(start_first_stage_value * 1000.0)) / 
				(int)(step_first_stage_value * 1000.0) + 1;
		}
		/* Checking second stage */
		if (m_SecondStage->stage->GetCurrentSelection() - 1 == first_axis->axis_number) return false;
		/* 
		if (m_SecondStage->stage->GetCurrentSelection() == 0) return;
		else selected_second_stage = m_SecondStage->stage->GetCurrentSelection() - 1;		
		*/
	}
	{
		m_StartCalculationTime = std::chrono::steady_clock::now();

		{
			// Right bottom position
			//wxPoint start_point_progress_bar
			//{ 
			//	GetPosition().x + GetSize().x - m_ProgressBar->GetSize().x, 
			//	GetPosition().y + GetSize().y - m_ProgressBar->GetSize().y 
			//};

			wxDisplay display(wxDisplay::GetFromPoint(wxPoint(0, 0)));
			if (!display.IsOk())
			{
				wxLogError("No display found.");
				return false;
			}

			wxRect screenRect = display.GetGeometry();
			wxSize screenSize = screenRect.GetSize();
			wxPoint start_point_progress_bar
			{
				screenSize.GetWidth() / 2 - m_ProgressBar->GetSize().x / 2,
				0
			};

			m_ProgressBar->SetPosition(start_point_progress_bar);
		}

		m_Settings->ResetCapturing();
		m_ProgressBar->Show();

		m_AppProgressIndicator = std::make_unique<wxAppProgressIndicator>(this, 100);

		//this->Disable();
		//m_StartMeasurement->Disable();
	}

	auto currThreadTimeStamp = timePointToWxString();
	m_StartedThreads.push_back(std::make_pair(currThreadTimeStamp, true));
	/* Worker and Progress Threads */
	{
		auto out_dir = m_OutDirTextCtrl->GetValue();

		WorkerThread* worker_thread = new WorkerThread
		(
			this,
			m_Settings.get(),
			m_KetekHandler.get(),
			&m_StartedThreads.back().first,
			&m_StartedThreads.back().second,
			out_dir,
			exposureSeconds,
			first_axis.release(), 
			second_axis.release()
		);

		ProgressThread* progress_thread = new ProgressThread(this, m_Settings.get(), &m_StartedThreads.back().second);

		if (worker_thread->Create(wxTHREAD_DETACHED) != wxTHREAD_NO_ERROR)
		{
			delete worker_thread;
			worker_thread = nullptr;
			return false;
		}
		if (progress_thread->Create(wxTHREAD_DETACHED) != wxTHREAD_NO_ERROR)
		{
			delete progress_thread;
			progress_thread = nullptr;
			return false;
		}
		if (progress_thread->Run() != wxTHREAD_NO_ERROR)
		{
			delete progress_thread;
			progress_thread = nullptr;
			return false;
		}
		if (worker_thread->Run() != wxTHREAD_NO_ERROR)
		{
			delete progress_thread;
			progress_thread = nullptr;
			delete worker_thread;
			worker_thread = nullptr;
			return false;
		}
	}
	return true;
}

void cMain::StartLiveCapturing()
{
	auto timePointToWxString = []()
		{
			auto now = std::chrono::system_clock::now().time_since_epoch().count();
			wxString formattedTime = wxString::Format(wxT("%lld"), now);
			return formattedTime;
		};

	wxBusyCursor cursor;
	if (m_StartedThreads.size() && m_StartedThreads.back().second)
	{
		m_StartedThreads.back().second = false;
		while (!m_StartedThreads.back().first.empty())
			wxThread::This()->Sleep(100);
	}

	wxString exposure_time_str = m_DeviceExposure->GetValue().IsEmpty() 
		? wxString("1") 
		: m_DeviceExposure->GetValue();
	auto exposureSeconds = abs(wxAtoi(exposure_time_str)); // Because user input is in [ms], we need to recalculate the value to [us]
	//m_XimeaControl->SetExposureTime(exposure_time);

	auto currThreadTimeStamp = timePointToWxString();
	m_StartedThreads.push_back(std::make_pair(currThreadTimeStamp, true));

	LiveCapturing* live_capturing = new LiveCapturing
	(
		this, 
		m_KetekHandler.get(), 
		&m_StartedThreads.back().first, 
		&m_StartedThreads.back().second,
		exposureSeconds
	);

	if (live_capturing->Create(wxTHREAD_DETACHED) != wxTHREAD_NO_ERROR)
	{
		delete live_capturing;
		live_capturing = nullptr;
		return;
	}
	if (live_capturing->Run() != wxTHREAD_NO_ERROR)
	{
		delete live_capturing;
		live_capturing = nullptr;
		return;
	}
}

void cMain::ChangeCameraManufacturerChoice(wxCommandEvent& evt)
{
	wxCommandEvent simulate_change_exposure_value(wxEVT_TEXT_ENTER, MainFrameVariables::ID_RIGHT_CAM_EXPOSURE_TE_CTL);
	ProcessEvent(simulate_change_exposure_value);
}

void cMain::OnCrossHairButton(wxCommandEvent& evt)
{
	UnCheckAllTools();
	if (!m_IsCrossHairChecked)
	{
		m_MenuBar->menu_tools->Check(MainFrameVariables::ID_MENUBAR_TOOLS_CROSSHAIR, true);
		m_VerticalToolBar->tool_bar->ToggleTool(MainFrameVariables::ID_MENUBAR_TOOLS_CROSSHAIR, true);
		m_IsCrossHairChecked = true;
		//m_PreviewPanel->SetCrossHairButtonActive(true);
		m_CrossHairPosXTxtCtrl->Enable();
		m_CrossHairPosYTxtCtrl->Enable();
		{
			//auto img_size = m_PreviewPanel->GetImageSize();
			//m_CamPreview->SetXCrossHairPosFromParentWindow(img_size.GetWidth() / 2);
			//m_CamPreview->SetYCrossHairPosFromParentWindow(img_size.GetHeight() / 2);
			//m_CrossHairPosXTxtCtrl->SetValue(wxString::Format(wxT("%i"), img_size.GetWidth() / 2));
			//m_CrossHairPosYTxtCtrl->SetValue(wxString::Format(wxT("%i"), img_size.GetHeight() / 2));
		}
	}
	else
	{
		m_IsCrossHairChecked = false;
	}
}

auto cMain::LiveCapturingThread(wxThreadEvent& evt) -> void
{
	auto curr_code = evt.GetInt();

	// -1 == Camera is disconnected
	if (curr_code == -1)
	{
		m_StartStopLiveCapturingTglBtn->SetValue(false);
		wxCommandEvent live_capturing_evt(wxEVT_TOGGLEBUTTON, MainFrameVariables::ID_RIGHT_CAM_START_STOP_LIVE_CAPTURING_TGL_BTN);
		ProcessEvent(live_capturing_evt);
		return;
	}

	auto img_ptr = evt.GetPayload<unsigned long*>();
	auto dataSize = m_KetekHandler->GetDataSize();

	unsigned long long sum{};
	sum = std::accumulate(&img_ptr[0], &img_ptr[m_KetekHandler->GetDataSize()], sum);

	m_PreviewPanel->SetKETEKData(img_ptr, dataSize, sum);

	//delete[] img_ptr;
}

auto cMain::WorkerThreadEvent(wxThreadEvent& evt) -> void
{
	auto curr_code = evt.GetInt();

	// -1 == Camera is disconnected
	if (curr_code == -1)
	{
		//m_StartedThreads.back().second = false;
		//m_StartedThreads.back().first = "";
		m_StartStopMeasurementTglBtn->SetValue(false);
		wxCommandEvent measurement_capturing_evt(wxEVT_TOGGLEBUTTON, MainFrameVariables::ID_RIGHT_MT_START_STOP_MEASUREMENT_TGL_BTN);
		ProcessEvent(measurement_capturing_evt);
		return;
	}

	auto img_ptr = evt.GetPayload<unsigned long*>();
	auto dataSize = m_KetekHandler->GetDataSize();

	unsigned long long sum{};
	sum = std::accumulate(&img_ptr[0], &img_ptr[m_KetekHandler->GetDataSize()], sum);

	m_PreviewPanel->SetKETEKData(img_ptr, dataSize, sum);
}

void cMain::UpdateProgress(wxThreadEvent& evt)
{
	int progress = evt.GetInt();
	wxString msg = evt.GetString();
	unsigned long long elapsed_seconds{};

	if (progress != -1)
	{
		auto current_time = std::chrono::steady_clock::now();
		elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(current_time - m_StartCalculationTime).count();
		m_ProgressBar->UpdateProgressWithMessage(msg, progress);
		m_AppProgressIndicator->SetValue(progress);
		m_ProgressBar->UpdateElapsedTime(elapsed_seconds);
		m_ProgressBar->UpdateEstimatedTime(progress, elapsed_seconds);
	}
	else
	{
		m_ProgressBar->Hide();
		m_ProgressBar->UpdateProgressWithMessage("", 0);
		m_ProgressBar->UpdateElapsedTime(0);
		m_ProgressBar->UpdateEstimatedTime(0, 0);
		m_AppProgressIndicator->~wxAppProgressIndicator();
		UpdateAllAxisGlobalPositions();
		this->Enable();
	}
}

auto cMain::CreateMetadataFile() -> void
{
	wxString exposure_time_str = m_DeviceExposure->GetValue().IsEmpty() 
		? wxString("0") 
		: m_DeviceExposure->GetValue();
	unsigned long exposure_time = abs(wxAtoi(exposure_time_str)); // Because user input is in [ms], we need to recalculate the value to [us]

	double det_x_pos{}, det_y_pos{}, det_z_pos{};
	double opt_y_pos{};

	{
		/* Detector */
		if (!m_Detector[0].absolute_text_ctrl->GetValue().ToDouble(&det_x_pos)) return;
		/* Optics */
		if (!m_Optics[1].absolute_text_ctrl->GetValue().ToDouble(&opt_y_pos)) return;
	}

	std::string selected_axis{};
	switch (m_FirstStage->stage->GetCurrentSelection() - 1)
	{
	/* Detector */
	case 0:
		selected_axis = std::string("detector_x");
		break;
	/* Optics */
	case 1:
		selected_axis = std::string("optics_x");
		break;
	case 2:
		selected_axis = std::string("optics_y");
		break;
	case 3:
		selected_axis = std::string("optics_z");
		break;
	case 4:
		selected_axis = std::string("optics_pitch");
		break;
	case 5:
		selected_axis = std::string("optics_yaw");
		break;
	default:
		break;
	}

	double start_first_stage_value{}, step_first_stage_value{}, finish_first_stage_value{};
	{
		if (!m_FirstStage->start->GetValue().ToDouble(&start_first_stage_value)) return;
		if (!m_FirstStage->step->GetValue().ToDouble(&step_first_stage_value)) return;
		if (!m_FirstStage->finish->GetValue().ToDouble(&finish_first_stage_value)) return;
	}
	auto now = std::chrono::system_clock::now();
	auto cur_time = std::chrono::system_clock::to_time_t(now);
	std::string time_metadata_filename{};
	std::string cur_date_and_time{};
	{
		std::string cur_date(30, '\0');
		std::strftime(&cur_date[0], cur_date.size(), "%Y%m%d", std::localtime(&cur_time));
		cur_date_and_time = cur_date.substr(0, 8); 
		auto str_time = std::string(std::ctime(&cur_time)).substr(11, 8); // Cut date in format: 20230223
		auto cur_hours = str_time.substr(0, 2);
		auto cur_mins = str_time.substr(3, 2);
		auto cur_secs = str_time.substr(6, 2);
		time_metadata_filename = cur_hours + std::string("H_") + cur_mins + std::string("M_") + cur_secs + std::string("S");
		cur_date_and_time += std::string("_") + cur_hours + cur_mins + cur_secs;
	}

	nlohmann::json main_table{};
	main_table = 
	{
		{"units", "mm"},
		{"pos_source", 0.000},
		{"pos_optics", 123.456},
		{"pos_detector", 234.567},
		{"first_stage", 
			{
				{"title", "optics"}, 
				{"position", opt_y_pos}
			}
		},
		{"second_stage", 
			{
				{"title", "detector_x"}, 
				{"position", det_x_pos}
			}
		},
		{"third_stage", 
			{
				{"title", "detector_y"}, 
				{"position", det_y_pos}
			}
		},
		{"fourth_stage", 
			{
				{"title", "detector_z"}, 
				{"position", det_z_pos}
			}
		},
		{"measurement", 
			{
				{"stage", selected_axis}, 
				{"start", start_first_stage_value},
				{"step", step_first_stage_value},
				{"finish", finish_first_stage_value},
				{"exposure", 
					{
						{"units", "us"}, 
						{"time", exposure_time}, 
						{"gain", 1}
					}
				},
				{"date_time", cur_date_and_time}
			}
		},
		{"message", ""}
	};
	
	auto out_dir_with_filename = 
		m_OutDirTextCtrl->GetValue() + 
		wxString("\\metadata_") + 
		wxString(time_metadata_filename) + 
		wxString(".json");
	std::ofstream out_file(out_dir_with_filename.ToStdString());
	if (out_file.is_open())
	{
		out_file << main_table;
		out_file.close();
	}
}

bool cMain::Cancelled()
{
	wxCriticalSectionLocker lock(m_CSCancelled);
	return m_Cancelled;
}

void cMain::OnValueDisplayingCheck(wxCommandEvent& evt)
{
	m_IsValueDisplayingChecked = m_MenuBar->menu_tools->IsChecked(MainFrameVariables::ID_MENUBAR_TOOLS_VALUE_DISPLAYING);
	m_PreviewPanel->SetValueDisplayingActive(m_IsValueDisplayingChecked);
}

void cMain::UpdateAllAxisGlobalPositions()
{
	/* Detectors */
	m_Detector[0].absolute_text_ctrl->ChangeValue(wxString::Format(wxT("%.3f"), m_Settings->GetActualMotorPosition(SettingsVariables::DETECTOR_X)));
	/* Optics */
	m_Optics[0].absolute_text_ctrl->ChangeValue(wxString::Format(wxT("%.3f"), m_Settings->GetActualMotorPosition(SettingsVariables::OPTICS_X)));
	m_Optics[1].absolute_text_ctrl->ChangeValue(wxString::Format(wxT("%.3f"), m_Settings->GetActualMotorPosition(SettingsVariables::OPTICS_Y)));
	m_Optics[2].absolute_text_ctrl->ChangeValue(wxString::Format(wxT("%.3f"), m_Settings->GetActualMotorPosition(SettingsVariables::OPTICS_Z)));
	m_Optics[3].absolute_text_ctrl->ChangeValue(wxString::Format(wxT("%.3f"), m_Settings->GetActualMotorPosition(SettingsVariables::OPTICS_PITCH)));
	m_Optics[4].absolute_text_ctrl->ChangeValue(wxString::Format(wxT("%.3f"), m_Settings->GetActualMotorPosition(SettingsVariables::OPTICS_YAW)));
}

void cMain::ExposureValueChanged(wxCommandEvent& evt)
{
	//m_XimeaControl->StopAcquisition();
	//m_XimeaControl->TurnOffLastThread();
	//m_StopLiveCapturing = true;
	//if (m_XimeaControl->IsCameraInitialized()) m_XimeaControl->StopAcquisition();	

	{
		//wxString exposure_time_str = m_DeviceExposure->GetValue().IsEmpty() 
		//	? wxString("0") 
		//	: m_DeviceExposure->GetValue();
		//unsigned long exposure_time = abs(wxAtoi(exposure_time_str)); // Because user input is in [ms], we need to recalculate the value to [us]
		//wxThread::This()->Sleep(exposure_time);
	}
	//m_StopLiveCapturing = false;
	if (!m_StartStopLiveCapturingTglBtn->GetValue()) return;

	StartLiveCapturing();
}

void cMain::OnStartStopLiveCapturingMenu(wxCommandEvent& evt)
{
	if (m_MenuBar->menu_edit->IsChecked(MainFrameVariables::ID_RIGHT_CAM_START_STOP_LIVE_CAPTURING_TGL_BTN))
	{
		m_StartStopLiveCapturingTglBtn->SetValue(true);
	}
	else
	{
		m_StartStopLiveCapturingTglBtn->SetValue(false);
	}
	wxCommandEvent art_start_live_pressed(wxEVT_TOGGLEBUTTON, MainFrameVariables::ID_RIGHT_CAM_START_STOP_LIVE_CAPTURING_TGL_BTN);
	ProcessEvent(art_start_live_pressed);
}

void cMain::OnStartStopLiveCapturingTglBtn(wxCommandEvent& evt)
{
	if (m_StartStopLiveCapturingTglBtn->GetValue())
	{
		m_StartStopLiveCapturingTglBtn->SetLabel(wxT("Stop Live (L)"));
		if (!m_MenuBar->menu_edit->IsChecked(MainFrameVariables::ID_RIGHT_CAM_START_STOP_LIVE_CAPTURING_TGL_BTN))
			m_MenuBar->menu_edit->Check(MainFrameVariables::ID_RIGHT_CAM_START_STOP_LIVE_CAPTURING_TGL_BTN, true);

		StartLiveCapturing();
	}
	else
	{	
		if (m_StartedThreads.size())
		{
			m_StartedThreads.back().second = false;

			m_StartStopLiveCapturingTglBtn->Disable();
			while (!m_StartedThreads.back().first.empty())
			{
				wxThread::This()->Sleep(100);
			}
			//m_StartedThreads.pop_back();
			m_StartStopLiveCapturingTglBtn->Enable();
		}

		//m_XimeaControl->StopAcquisition();
		//m_XimeaControl->TurnOffLastThread();
		{
			//wxString exposure_time_str = m_DeviceExposure->GetValue().IsEmpty() 
			//	? wxString("1") 
			//	: m_DeviceExposure->GetValue();
			//unsigned long exposure_time = abs(wxAtoi(exposure_time_str)); // Because user input is in [ms], we need to recalculate the value to [us]
			//wxThread::This()->Sleep(exposure_time);
		}
		//m_XimeaControl->ClearAllThreads();

		m_StartStopLiveCapturingTglBtn->SetLabel(wxT("Start Live (L)"));
		if (m_MenuBar->menu_edit->IsChecked(MainFrameVariables::ID_RIGHT_CAM_START_STOP_LIVE_CAPTURING_TGL_BTN))
			m_MenuBar->menu_edit->Check(MainFrameVariables::ID_RIGHT_CAM_START_STOP_LIVE_CAPTURING_TGL_BTN, false);
	}
}

void cMain::OnXPosCrossHairTextCtrl(wxCommandEvent& evt)
{
	wxString str_x_pos = m_CrossHairPosXTxtCtrl->IsEmpty() ? wxString("1") : m_CrossHairPosXTxtCtrl->GetValue();
	int x_pos = wxAtoi(str_x_pos);
	//m_PreviewPanel->SetXCrossHairPosFromParentWindow(x_pos);
}

void cMain::OnYPosCrossHairTextCtrl(wxCommandEvent& evt)
{
	wxString str_y_pos = m_CrossHairPosYTxtCtrl->IsEmpty() ? wxString("1") : m_CrossHairPosYTxtCtrl->GetValue();
	int y_pos = wxAtoi(str_y_pos);
	//m_PreviewPanel->SetYCrossHairPosFromParentWindow(y_pos);
}

auto cMain::OnSetPosCrossHairTglBtn(wxCommandEvent& evt) -> void
{
	if (m_SetCrossHairPosTglBtn->GetValue())
	{
		//m_PreviewPanel->SettingCrossHairPosFromParentWindow(true);
	}
	else
	{	
		//m_PreviewPanel->SettingCrossHairPosFromParentWindow(false);
	}
}

/* ___ Start Live Capturing Thread ___ */
LiveCapturing::LiveCapturing
(
	cMain* mainFrame,
	Ketek* ketekHandler,
	wxString* threadKey,
	bool* continueCapturing,
	const int exposureSeconds
) 
	: m_MainFrame(mainFrame), 
	m_KetekHandler(ketekHandler),
	m_ThreadID(threadKey),
	m_ContinueCapturing(continueCapturing),
	m_ExposureSeconds(exposureSeconds) {}

wxThread::ExitCode LiveCapturing::Entry()
{
	wxLogDebug(*m_ThreadID);
	
	wxThreadEvent evt(wxEVT_THREAD, MainFrameVariables::ID_THREAD_LIVE_CAPTURING);

	auto mcaData = std::make_unique<unsigned long[]>(m_KetekHandler->GetDataSize());

	auto imageNumber{ 0 };
	while (m_MainFrame && *m_ContinueCapturing)
	{
		if (!m_KetekHandler->CaptureData(m_ExposureSeconds, mcaData.get(), m_ContinueCapturing))
		{
			*m_ThreadID = "";
			return (wxThread::ExitCode)0;
		}

		evt.SetInt(imageNumber);
		evt.SetPayload(mcaData.get());
		wxQueueEvent(m_MainFrame, evt.Clone());

		{
			auto signalValue = ULONG_MAX - mcaData[0];
			while (mcaData[0] != signalValue)
				wxThread::Sleep(10);
		}

		++imageNumber;
	}

	*m_ThreadID = "";
	return (wxThread::ExitCode)0;
}

auto LiveCapturing::CaptureImage
(
	unsigned short* short_data_ptr, 
	wxImage* image_ptr
) -> bool
{
//	unsigned long* data_ptr{};
//	if (!data_ptr) return false;
//
//	wxLogDebug("4");
//	//if (!m_XimeaControl->GetThreadState(m_ThreadID)) return false;
//#ifdef USE_MULTITHREAD
//	UpdatePixelsMultithread(data_ptr, image_ptr);
//#else
//	unsigned short current_value{};
//	unsigned char red{}, green{}, blue{};
//	for (auto y{ 0 }; y < m_ImageSize.GetHeight(); ++y)
//	{
//		for (auto x{ 0 }; x < m_ImageSize.GetWidth(); ++x)
//		{
//			current_value = data_ptr[y * m_ImageSize.GetWidth() + x];
//			//short_data_ptr[y * m_ImageSize.GetWidth() + x] = current_value;
//			/* Matlab implementation of JetColormap */
//			/* Because XIMEA camera can produce 12-bit per pixel maximum, we use RGB12bit converter */
//			m_CamPreviewWindow->CalculateMatlabJetColormapPixelRGB12bit(current_value, red, green, blue);
//			image_ptr->SetRGB(x, y, red, green, blue);
//		}
//	}
//#endif
//	if (!short_data_ptr) return false;
//	//if (!m_XimeaControl->GetThreadState(m_ThreadID)) return false;
//	memcpy
//	(
//		short_data_ptr, 
//		data_ptr, 
//		sizeof(unsigned short) * m_ImageSize.GetWidth() * m_ImageSize.GetHeight()
//	);
//	if (!short_data_ptr) return false;
//
	return true;
}

auto LiveCapturing::UpdatePixelsMultithread
(
	unsigned short* short_data_ptr, 
	wxImage* image_ptr
) -> void
{
	//auto numThreads = std::thread::hardware_concurrency();
	//auto tileSize = m_ImageSize.GetHeight() % numThreads > 0 ? m_ImageSize.GetHeight() / numThreads + 1 : m_ImageSize.GetHeight() / numThreads;

	//std::vector<std::thread> threads;
	//threads.reserve(numThreads);

	//for (auto i{ 0 }; i < numThreads; ++i)
	//{
	//	auto start_x = 0;
	//	auto start_y = i * tileSize;
	//	auto finish_x = m_ImageSize.GetWidth();
	//	auto finish_y = (i + 1) * tileSize > m_ImageSize.GetHeight() ? m_ImageSize.GetHeight() : (i + 1) * tileSize;

	//	threads.emplace_back
	//	(
	//		std::thread
	//		(
	//		&LiveCapturing::AdjustImageParts, 
	//		this, 
	//		&short_data_ptr[start_y * m_ImageSize.GetWidth() + start_x], 
	//		image_ptr, 
	//		start_x, 
	//		start_y, 
	//		finish_x, 
	//		finish_y
	//		)
	//	);
	//}

	//for (auto& thread : threads)
	//{
	//	thread.join();
	//}
}

auto LiveCapturing::AdjustImageParts
(
	const unsigned short* data_ptr, 
	wxImage* image_ptr,
	const unsigned int start_x, 
	const unsigned int start_y, 
	const unsigned int finish_x, 
	const unsigned int finish_y
) -> void
{
	//if (!data_ptr) return;
	//if (!image_ptr->IsOk()) return;
	//unsigned short current_value{};
	//unsigned char red{}, green{}, blue{};
	//unsigned long long position_in_data_pointer{};

	//for (auto y{ start_y }; y < finish_y; ++y)
	//{
	//	for (auto x{ start_x }; x < finish_x; ++x)
	//	{
	//		current_value = data_ptr[position_in_data_pointer];
	//		/* Matlab implementation of JetColormap */
	//		/* Because XIMEA camera can produce 12-bit per pixel maximum, we use RGB12bit converter */
	//		m_CamPreviewWindow->CalculateMatlabJetColormapPixelRGB12bit(current_value, red, green, blue);
	//		image_ptr->SetRGB(x, y, red, green, blue);
	//		++position_in_data_pointer;
	//	}
	//}
}

LiveCapturing::~LiveCapturing()
{
	m_MainFrame = nullptr;
	m_KetekHandler = nullptr;
}
/* ___ End Live Capturing Thread ___ */

/* ___ Start Worker Thread ___ */
wxThread::ExitCode WorkerThread::Entry()
{
	constexpr auto raise_exception_msg = [](wxString camera_name) 
	{
		wxString title = "Connection error";
		wxMessageBox(
			wxT
			(
				"The " + camera_name + " camera can't capture an image."
				"\nPlease, check if the " + camera_name + " camera is connected properly and restart the program."
			),
			title,
			wxICON_ERROR);
	};
	//auto exit_thread = [&](XimeaControl* cam_control)
	//{
	//	m_Settings->SetCurrentProgress(m_FirstAxis->step_number, m_FirstAxis->step_number);
	//	cam_control = nullptr;
	//	m_MainFrame->WorkerThreadFinished(true);
	//};

	//m_MainFrame->WorkerThreadFinished(false);
	m_Settings->SetCurrentProgress(0, m_FirstAxis->step_number);

	auto now = std::chrono::system_clock::now();
	auto cur_time = std::chrono::system_clock::to_time_t(now);
	auto str_time = std::string(std::ctime(&cur_time)).substr(11, 8);
	auto cur_hours = str_time.substr(0, 2);
	auto cur_mins = str_time.substr(3, 2);
	auto cur_secs = str_time.substr(6, 2);

	wxThreadEvent evt(wxEVT_THREAD, MainFrameVariables::ID_THREAD_MAIN_CAPTURING);

	auto mcaData = std::make_unique<unsigned long[]>(m_KetekHandler->GetDataSize());

	float first_axis_rounded_go_to{};
	float first_axis_position{}, second_axis_position{};
	for (auto i{ 0 }; i < m_FirstAxis->step_number; ++i)
	{
		if (!*m_ContinueCapturing)
		{
			*m_ThreadID = "";
			evt.SetInt(-1);
			wxQueueEvent(m_MainFrame, evt.Clone());
			return 0;
		}
		m_Settings->SetCurrentProgress(i, m_FirstAxis->step_number);
		/* Here we need to round values, for the correct positioning of motors */
		auto correctedStart = static_cast<int>(m_FirstAxis->start * 1000.f + .5f);
		auto correctedStep = static_cast<int>(m_FirstAxis->step * 1000.f + .5f);
		auto correctedPos = static_cast<float>(correctedStart + i * correctedStep);
		first_axis_rounded_go_to = correctedPos / 1000.f;

		first_axis_position = MoveFirstStage(first_axis_rounded_go_to);

		if (!CaptureAndSaveData
		(
			mcaData.get(),
			i + 1,
			first_axis_position,
			second_axis_position,
			cur_hours, cur_mins, cur_secs
		))
		{
			*m_ThreadID = "";
			evt.SetInt(-1);
			wxQueueEvent(m_MainFrame, evt.Clone());
			return 0;
		}

		evt.SetInt(i);
		evt.SetPayload(mcaData.get());
		wxQueueEvent(m_MainFrame, evt.Clone());

		/* Update Current Progress */
		m_Settings->SetCurrentProgress(i, m_FirstAxis->step_number);

		auto signalValue = ULONG_MAX - mcaData[0];
		while (mcaData[0] != signalValue && *m_ContinueCapturing)
			wxThread::Sleep(10);
	}

#ifdef ENABLE_SECOND_AXIS
	switch (m_SecondAxis->axis_number)
	{
		/* Detector */
		case 0:
			first_axis_position = m_Settings->GoToAbsPos(SettingsVariables::DETECTOR_X, first_axis_rounded_go_to);
			break;
		/* Optics */
		case 1:
			first_axis_position = m_Settings->GoToAbsPos(SettingsVariables::OPTICS_X, first_axis_rounded_go_to);
			break;
		case 2:
			first_axis_position = m_Settings->GoToAbsPos(SettingsVariables::OPTICS_Y, first_axis_rounded_go_to);
			break;
		case 3:
			first_axis_position = m_Settings->GoToAbsPos(SettingsVariables::OPTICS_Z, first_axis_rounded_go_to);
			break;
		case 4:
			first_axis_position = m_Settings->GoToAbsPos(SettingsVariables::OPTICS_PITCH, first_axis_rounded_go_to);
			break;
		case 5:
			first_axis_position = m_Settings->GoToAbsPos(SettingsVariables::OPTICS_YAW, first_axis_rounded_go_to);
			break;
		default:
			break;
	}
#endif // FALSE

	*m_ThreadID = "";
	evt.SetInt(-1);
	wxQueueEvent(m_MainFrame, evt.Clone());

	// Go to the best captured position
	if (m_MaxElementDuringCapturing)
	{
		auto message = wxString(
			"The maximum value was: " + wxString::Format(wxT("%ld"), m_MaxElementDuringCapturing) + "\n" 
			+ " at position: "  + wxString::Format(wxT("%.3f"), m_BestFirstAxisPosition)
		);
		message += "\nDo you want to move stage to the best position?";
		if (
			wxMessageBox
			(
			message,
			"Move stage?",
			wxICON_QUESTION | wxYES_NO) == wxYES
			)
		{
			MoveFirstStage(m_BestFirstAxisPosition);
		}
	}

	return (wxThread::ExitCode)0;
}

auto WorkerThread::CaptureAndSaveData
(
	unsigned long* const mca,
	const int& image_number,
	const float& first_stage_position,
	const float& second_stage_position,
	const std::string& hours,
	const std::string& minutes,
	const std::string& seconds
) -> bool
{
	if (!mca) return false;
	if (!m_KetekHandler->CaptureData(m_ExposureTimeSeconds, mca, m_ContinueCapturing)) return false;

	if (!std::filesystem::exists(m_DataPath.ToStdString()))
	{
		wxLogError("Desired path doesn't exist.");
		return false;
	}

	/* Save Data */
	{
		std::string first_axis_position_str = std::format("{:.3f}", first_stage_position);
		std::replace(first_axis_position_str.begin(), first_axis_position_str.end(), '.', '_');

		std::string second_axis_position_str = std::format("{:.3f}", second_stage_position);
		std::replace(second_axis_position_str.begin(), second_axis_position_str.end(), '.', '_');
		
		std::string file_name = std::string(m_DataPath.mb_str()) + std::string("\\") +
			std::string("ktk_");
		file_name += image_number < 10 ? std::string("0") : std::string("");
		file_name += std::to_string(image_number) + std::string("_") + 
			hours + std::string("H_") + 
			minutes + std::string("M_") + 
			seconds + std::string("S_") + 
			std::to_string(m_ExposureTimeSeconds) + std::string("s") 
			+ std::string("_1A_") + first_axis_position_str 
			+ std::string("_2A_") + second_axis_position_str 
			+ std::string(".mca");


		unsigned long long sum{};
		sum = std::accumulate(&mca[0], &mca[m_KetekHandler->GetDataSize()], sum);

		auto maxElement = MainFrameVariables::WriteMCAFile
		(
			file_name, 
			mca, 
			m_KetekHandler, 
			sum,
			m_ExposureTimeSeconds
		);

		if (maxElement > m_MaxElementDuringCapturing)
		{
			m_MaxElementDuringCapturing = maxElement;
			m_BestFirstAxisPosition = first_stage_position;
		}
	}

	return true;
}
auto WorkerThread::MoveFirstStage(const float position) -> float
{
	float firstAxisPos{};
	switch (m_FirstAxis->axis_number)
	{
		/* Detector */
		case 0:
			firstAxisPos = m_Settings->GoToAbsPos(SettingsVariables::DETECTOR_X, position);
			break;
		/* Optics */
		case 1:
			firstAxisPos = m_Settings->GoToAbsPos(SettingsVariables::OPTICS_X, position);
			break;
		case 2:
			firstAxisPos = m_Settings->GoToAbsPos(SettingsVariables::OPTICS_Y, position);
			break;
		case 3:
			firstAxisPos = m_Settings->GoToAbsPos(SettingsVariables::OPTICS_Z, position);
			break;
		case 4:
			firstAxisPos = m_Settings->GoToAbsPos(SettingsVariables::OPTICS_PITCH, position);
			break;
		case 5:
			firstAxisPos = m_Settings->GoToAbsPos(SettingsVariables::OPTICS_YAW, position);
			break;
		default:
			break;
	}

	return firstAxisPos;
}
/* ___ End Worker Thread ___ */

/* ___ Start Progress Thread ___ */
wxThread::ExitCode ProgressThread::Entry()
{
	m_Progress = 0;
	m_ProgressMsg = "";
	wxThreadEvent evt(wxEVT_THREAD, MainFrameVariables::ID_THREAD_PROGRESS_CAPTURING);
	while (*m_ContinueWaiting)
	{
		//wxThreadEvent calc_event(wxEVT_THREAD, MainFrameVariables::ID_THREAD_PROGRESS_CAPTURING);
		m_Settings->ProvideProgressInfo(&m_ProgressMsg, &m_Progress);

		evt.SetInt(m_Progress);
		evt.SetString(m_ProgressMsg);

		wxQueueEvent(m_Frame, evt.Clone());

		wxThread::This()->Sleep(100);
	}
	evt.SetInt(-1);
	wxQueueEvent(m_Frame, evt.Clone());

	return (wxThread::ExitCode)0;
}
/* ___ End Progress Thread ___ */

/* ___ Start ProgressBar ___ */
BEGIN_EVENT_TABLE(ProgressBar, wxFrame)
END_EVENT_TABLE()

ProgressBar::ProgressBar(wxWindow* parent, const wxPoint& pos, const wxSize& size)
	: wxFrame(parent, wxID_ANY, wxT("Progress"), pos, size, wxFRAME_FLOAT_ON_PARENT), m_MainSize(size)
{
	CreateProgressBar();
}

void ProgressBar::UpdateProgressWithMessage(const wxString& msg, const int& progress)
{
	m_ProgressPanel->SetProgress(progress);
	m_ProgressPanel->SetComment(msg);
}

void ProgressBar::UpdateElapsedTime(const uint64_t& elapsed_seconds)
{
	m_ProgressPanel->SetElapsedTime(elapsed_seconds);
}

void ProgressBar::UpdateEstimatedTime(const int& prgs, const uint64_t& elapsed_seconds)
{
	m_ProgressPanel->SetEstimatedTime(prgs, elapsed_seconds);
}

void ProgressBar::CreateProgressBar()
{
	wxSizer* const main_sizer = new wxBoxSizer(wxVERTICAL);
	m_ProgressPanel = new ProgressPanel(this, m_MainSize);
	main_sizer->Add(m_ProgressPanel, wxSizerFlags(1).Expand().Border());
	this->SetBackgroundColour(wxColour(255, 255, 255));
	SetSizerAndFit(main_sizer);
}

ProgressBar::~ProgressBar()
{
	//m_ProgressPanel->Destroy();
}
/* ___ End ProgressBar ___ */

/* ___ Start ProgressPanel ___ */
BEGIN_EVENT_TABLE(ProgressPanel, wxPanel)
EVT_PAINT(ProgressPanel::PaintEvent)
EVT_SIZE(ProgressPanel::OnSize)
END_EVENT_TABLE()

ProgressPanel::ProgressPanel(
	wxFrame* parent, const wxSize& size)
	: wxPanel(parent)
{
	this->SetDoubleBuffered(true);
	this->SetBackgroundColour(wxColour(*wxWHITE));

	this->SetMinSize(size);
	//SetSize(size);
	//Refresh();
}

void ProgressPanel::SetSize(const wxSize& new_size)
{
	m_Width = new_size.x;
	m_Height = new_size.y;
	Refresh();
}

void ProgressPanel::SetProgress(const int& progress)
{
	m_Progress = progress <= 100 ? progress : 100;
}

void ProgressPanel::SetElapsedTime(const int& elapsed_time)
{
	m_ElapsedTime = elapsed_time;

	m_ElapsedHours = elapsed_time / 3600;
	m_ElapsedMinutes = elapsed_time / 60 - m_ElapsedHours * 60;
	m_ElapsedSeconds = elapsed_time - m_ElapsedHours * 3600 - m_ElapsedMinutes * 60;
}

void ProgressPanel::SetEstimatedTime(const int& progress, const int& elapsed_time)
{
	if (progress > 0 && progress != m_PreviousEstimateProgress)
	{
		m_EstimatedTime = (double)elapsed_time / (double)progress * 100.0 - elapsed_time;
		m_PreviousEstimateProgress = progress;
	}
	else if (progress == 0)
	{
		/* Reset Estimated time variables */
		m_EstimatedTime = 0;
		m_PreviousEstimateProgress = 0;
	}

	Refresh();
}

void ProgressPanel::SetComment(const wxString& progress_comment)
{
	m_ProgressComment = progress_comment;
}

void ProgressPanel::PaintEvent(wxPaintEvent& evt)
{
	wxBufferedPaintDC dc(this);
	Render(dc);
}

void ProgressPanel::Render(wxBufferedPaintDC& dc)
{
	dc.Clear();
	wxGraphicsContext* gc{};
	gc = wxGraphicsContext::Create(dc);
	if (gc)
	{
		int borderWidthProgressRectangle{ 1 };
		gc->SetPen(wxPen(wxColour(0, 0, 0), borderWidthProgressRectangle));
		wxFont font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
		gc->SetFont(font, *wxBLACK);
		wxGraphicsPath path = gc->CreatePath();

		wxDouble widthText{}, heightText{};
		wxString text_01("Progress");
		gc->GetTextExtent(text_01, &widthText, &heightText);

		wxDouble drawPointXText = this->GetSize().x / 2 - widthText / 2;
		wxDouble offsetYText{ 10 };
		wxDouble drawPointYText = offsetYText;
		gc->DrawText(text_01, drawPointXText, drawPointYText);

		// Progress in percents
		drawPointYText += heightText + offsetYText;
		wxString text_progress = wxString::Format(wxT("%i"), m_Progress) + "%";
		gc->GetTextExtent(text_progress, &widthText, &heightText);
		drawPointXText = this->GetSize().x / 2 - widthText / 2;
		gc->DrawText(text_progress, drawPointXText, drawPointYText);

		int leftAndRightOffsetRectangle{ 10 }; // [%]
		wxPoint startUpperLeftBorderRectangle{ this->GetSize().x * leftAndRightOffsetRectangle / 100, (int)(drawPointYText + heightText + offsetYText) };
		wxSize sizeBorderRectangle{ this->GetSize().x - this->GetSize().x * leftAndRightOffsetRectangle / 100 * 2, 40 };

		unsigned char red{}, green{}, blue{};
		green = (unsigned char)(255 * (int)m_Progress / 100);
		red = 255 - green;
		wxColour currentRectangleColour{ red, green, blue };

		gc->SetBrush(wxBrush(currentRectangleColour));
		wxDouble widthProgress = (100 - (wxDouble)m_Progress) * (wxDouble)sizeBorderRectangle.x / 100.0;
		path.AddRectangle(
			(wxDouble)startUpperLeftBorderRectangle.x + (wxDouble)sizeBorderRectangle.x - widthProgress,
			startUpperLeftBorderRectangle.y,
			widthProgress,
			(wxDouble)sizeBorderRectangle.y);
		//gc->FillPath(path);

		path.AddRectangle(
			startUpperLeftBorderRectangle.x,
			startUpperLeftBorderRectangle.y,
			sizeBorderRectangle.x,
			sizeBorderRectangle.y);
		// Drawing buffered path
		gc->DrawPath(path);

		// Progress comment
		gc->GetTextExtent(m_ProgressComment, &widthText, &heightText);
		drawPointXText = (wxDouble)startUpperLeftBorderRectangle.x + 5.0;
		drawPointYText = (wxDouble)startUpperLeftBorderRectangle.y + (wxDouble)sizeBorderRectangle.y + offsetYText;
		gc->DrawText(m_ProgressComment, drawPointXText, drawPointYText);

		// Elapsed time
		{
			wxString elapsed_text("Elapsed time: ");
			wxString elapsed_hours = m_ElapsedHours >= 10 ? wxString::Format(wxT("%i"), m_ElapsedHours) : wxString::Format(wxT("0%i"), m_ElapsedHours);
			wxString elapsed_minutes = m_ElapsedMinutes >= 10 ? wxString::Format(wxT("%i"), m_ElapsedMinutes) : wxString::Format(wxT("0%i"), m_ElapsedMinutes);
			wxString elapsed_seconds = m_ElapsedSeconds >= 10 ? wxString::Format(wxT("%i"), m_ElapsedSeconds) : wxString::Format(wxT("0%i"), m_ElapsedSeconds);
			elapsed_text += elapsed_hours + ":" + elapsed_minutes + ":" + elapsed_seconds;

			drawPointYText += heightText + offsetYText;
			gc->GetTextExtent(elapsed_text, &widthText, &heightText);
			drawPointXText = (wxDouble)startUpperLeftBorderRectangle.x + 5.0;
			gc->DrawText(elapsed_text, drawPointXText, drawPointYText);
		}

		delete gc;
	}
}

void ProgressPanel::OnSize(wxSizeEvent& evt)
{
	int newWidth{ evt.GetSize().x }, newHeight{ evt.GetSize().y };
	if (newWidth != m_Width || newHeight != m_Height)
	{
		m_Width = newWidth;
		m_Height = newHeight;
		Refresh();
	}
}
/* ___ End ProgressPanel ___ */

