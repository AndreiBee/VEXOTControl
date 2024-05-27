#pragma once
#ifndef CMAIN_H
#define CMAIN_H

#include "wx/wx.h"
#include "wx/tglbtn.h"
#include "wx/valnum.h"
#include "wx/thread.h"
#include "wx/appprogress.h"

#include <string>
#include <memory>
#include <chrono>

#include "json.hpp"

#include "cPreviewPanel.h"
#include "cSettings.h"

#include "src/img/cross_hair.xpm"
#include "src/img/center.xpm"
#include "src/img/home.xpm"

//#include "src/img/logo.xpm"


namespace MainFrameVariables
{
	enum
	{
		/* Menu Bar */
		ID_MENUBAR_FILE_QUIT,
		ID_MENUBAR_EDIT_ENABLE_DARK_MODE,
		ID_MENUBAR_EDIT_SETTINGS,
		ID_MENUBAR_TOOLS_CROSSHAIR,
		ID_MENUBAR_TOOLS_VALUE_DISPLAYING,
		ID_MENUBAR_WINDOW_FULLSCREEN,
		ID_MENUBAR_HELP_ABOUT,
		/* Detector X */
		ID_RIGHT_SC_DET_X_ABS_TE_CTL,
		ID_RIGHT_SC_DET_X_SET_BTN,
		ID_RIGHT_SC_DET_X_REL_TE_CTL,
		ID_RIGHT_SC_DET_X_DEC_BTN,
		ID_RIGHT_SC_DET_X_INC_BTN,
		ID_RIGHT_SC_DET_X_CENTER_BTN,
		ID_RIGHT_SC_DET_X_HOME_BTN,
		/* Optics X */
		ID_RIGHT_SC_OPT_X_ABS_TE_CTL,
		ID_RIGHT_SC_OPT_X_SET_BTN,
		ID_RIGHT_SC_OPT_X_REL_TE_CTL,
		ID_RIGHT_SC_OPT_X_DEC_BTN,
		ID_RIGHT_SC_OPT_X_INC_BTN,
		ID_RIGHT_SC_OPT_X_CENTER_BTN,
		ID_RIGHT_SC_OPT_X_HOME_BTN,	
		/* Optics Y */
		ID_RIGHT_SC_OPT_Y_ABS_TE_CTL,
		ID_RIGHT_SC_OPT_Y_SET_BTN,
		ID_RIGHT_SC_OPT_Y_REL_TE_CTL,
		ID_RIGHT_SC_OPT_Y_DEC_BTN,
		ID_RIGHT_SC_OPT_Y_INC_BTN,
		ID_RIGHT_SC_OPT_Y_CENTER_BTN,
		ID_RIGHT_SC_OPT_Y_HOME_BTN,
		/* Optics Z */
		ID_RIGHT_SC_OPT_Z_ABS_TE_CTL,
		ID_RIGHT_SC_OPT_Z_SET_BTN,
		ID_RIGHT_SC_OPT_Z_REL_TE_CTL,
		ID_RIGHT_SC_OPT_Z_DEC_BTN,
		ID_RIGHT_SC_OPT_Z_INC_BTN,
		ID_RIGHT_SC_OPT_Z_CENTER_BTN,
		ID_RIGHT_SC_OPT_Z_HOME_BTN,
		/* Optics Pitch */
		ID_RIGHT_SC_OPT_PITCH_ABS_TE_CTL,
		ID_RIGHT_SC_OPT_PITCH_SET_BTN,
		ID_RIGHT_SC_OPT_PITCH_REL_TE_CTL,
		ID_RIGHT_SC_OPT_PITCH_DEC_BTN,
		ID_RIGHT_SC_OPT_PITCH_INC_BTN,
		ID_RIGHT_SC_OPT_PITCH_CENTER_BTN,
		ID_RIGHT_SC_OPT_PITCH_HOME_BTN,	
		/* Optics Yaw */
		ID_RIGHT_SC_OPT_YAW_ABS_TE_CTL,
		ID_RIGHT_SC_OPT_YAW_SET_BTN,
		ID_RIGHT_SC_OPT_YAW_REL_TE_CTL,
		ID_RIGHT_SC_OPT_YAW_DEC_BTN,
		ID_RIGHT_SC_OPT_YAW_INC_BTN,
		ID_RIGHT_SC_OPT_YAW_CENTER_BTN,
		ID_RIGHT_SC_OPT_YAW_HOME_BTN,
		/* Camera */
		ID_RIGHT_CAM_EXPOSURE_TE_CTL,
		ID_RIGHT_CAM_MANUFACTURER_CHOICE,
		ID_RIGHT_CAM_SINGLE_SHOT_BTN,
		ID_RIGHT_CAM_START_STOP_LIVE_CAPTURING_TGL_BTN,
		ID_RIGHT_CAM_CROSS_HAIR_POS_X_TXT_CTRL,
		ID_RIGHT_CAM_CROSS_HAIR_POS_Y_TXT_CTRL,
		ID_RIGHT_CAM_CROSS_HAIR_SET_POS_TGL_BTN,
		/* Measurement */
		ID_RIGHT_MT_OUT_FLD_TE_CTL,
		ID_RIGHT_MT_OUT_FLD_BTN,
		ID_RIGHT_MT_FIRST_STAGE_CHOICE,
		ID_RIGHT_MT_FIRST_STAGE_START,
		ID_RIGHT_MT_FIRST_STAGE_STEP,
		ID_RIGHT_MT_FIRST_STAGE_FINISH,
		ID_RIGHT_MT_SECOND_STAGE_CHOICE,
		ID_RIGHT_MT_SECOND_STAGE_START,
		ID_RIGHT_MT_SECOND_STAGE_STEP,
		ID_RIGHT_MT_SECOND_STAGE_FINISH,
		ID_RIGHT_MT_START_MEASUREMENT,
		/* Live Capturing */
		ID_THREAD_LIVE_CAPTURING,
		/* Progress */
		ID_THREAD_PROGRESS_CAPTURING,
	};
	struct MenuBar
	{
		wxMenuBar* menu_bar{};
		wxMenu* menu_file{};
		wxMenu* menu_edit{};
		wxMenu* menu_tools{};
		wxMenu* submenu_intensity_profile{};
		wxMenu* menu_window{};
		wxMenu* menu_help{};
		MenuBar() :
			menu_bar(new wxMenuBar()),
			menu_file(new wxMenu()),
			menu_edit(new wxMenu()),
			menu_tools(new wxMenu()),
			submenu_intensity_profile(new wxMenu()),
			menu_window(new wxMenu()),
			menu_help(new wxMenu()) {};
		~MenuBar()
		{
			menu_file->~wxMenu();
			menu_edit->~wxMenu();
			submenu_intensity_profile->~wxMenu();
			menu_tools->~wxMenu();
			menu_window->~wxMenu();
			menu_help->~wxMenu();
			menu_bar->~wxMenuBar();
		}
	};
	
	struct ToolBar
	{
		wxToolBar* tool_bar{};
		ToolBar() {};
	};

	struct StepperControl
	{
		wxTextCtrl* absolute_text_ctrl{}, *relative_text_ctrl{};
		wxButton* set_btn{}, * increment_btn{}, * decrement_btn{};
		wxBitmapButton* center_btn{}, * home_btn{};
		void DisableAllControls()
		{
			absolute_text_ctrl->Disable();
			relative_text_ctrl->Disable();
			set_btn->Disable();
			increment_btn->Disable();
			decrement_btn->Disable();
			center_btn->Disable();
			home_btn->Disable();
		}
		void EnableAllControls()
		{
			absolute_text_ctrl->Enable();
			relative_text_ctrl->Enable();
			set_btn->Enable();
			increment_btn->Enable();
			decrement_btn->Enable();
			center_btn->Enable();
			home_btn->Enable();
		}
	};
	struct MeasurementStage
	{
		wxChoice* stage{};
		wxTextCtrl* start{}, * step{}, * finish{};
		wxArrayString motors;

		MeasurementStage()
		{
			motors.Add("None");
			motors.Add("Detector X");
			//motors.Add("Detector Y");
			//motors.Add("Detector Z");
			motors.Add("Optics X");
			motors.Add("Optics Y");
			motors.Add("Optics Z");
			motors.Add("Optics Pitch");
			motors.Add("Optics Yaw");
		};

		void DisableAllControls()
		{
			stage->Disable();
			start->Disable();
			step->Disable();
			finish->Disable();
		}
		void EnableAllControls()
		{
			stage->Enable();
			start->Enable();
			step->Enable();
			finish->Enable();
		}
	};
	/* Struct to transfer axis data to WorkerThread */
	struct AxisMeasurement
	{
		int axis_number{ -1 };
		float start{}, step{}, finish{};
		int step_number{};
	};
}

class ProgressBar;
class ProgressPanel;
class WorkerThread;
class ProgressThread;

#define USE_MULTITHREAD

/* ___ Start cMain ___ */
class cMain final : public wxFrame
{
public:
	cMain(const wxString& title_);
	//auto StopLiveCapturing() -> bool;
	auto LiveCapturingFinishedCapturingAndDrawing(bool is_finished) -> void;
	auto WorkerThreadFinished(bool is_finished) -> void;
private:
	void CreateMainFrame();
	void InitComponents();
	void InitDefaultStateWidgets();
	void CreateMenuBarOnFrame();
	void CreateVerticalToolBar();
	void CreateLeftAndRightSide();
	void CreateLeftSide(wxSizer* left_side_sizer);
	void CreateRightSide(wxSizer* right_side_sizer);
	void CreateSteppersControl(wxPanel* right_side_panel, wxBoxSizer* right_side_panel_sizer);
	void CreateDeviceControls(wxPanel* right_side_panel, wxBoxSizer* right_side_panel_sizer);
	void CreateMeasurement(wxPanel* right_side_panel, wxBoxSizer* right_side_panel_sizer);

	auto OnEnableDarkMode(wxCommandEvent& evt) -> void;

	void UnCheckAllTools();
	/* ProgressBar */
	void CreateProgressBar();

	/* Live Capturing */
	void StartLiveCapturing();

	void ChangeCameraManufacturerChoice(wxCommandEvent& evt);
	void OnSingleShotCameraImage(wxCommandEvent& evt);
	void OnSetOutDirectoryBtn(wxCommandEvent& evt);

	void OnOpenSettings(wxCommandEvent& evt);
	auto InitializeSelectedCamera() -> void;
	void UpdateStagePositions();
	void EnableUsedAndDisableNonUsedMotors();

	void OnCrossHairButton(wxCommandEvent& evt);
	void OnValueDisplayingCheck(wxCommandEvent& evt);

	void OnFullScreen(wxCommandEvent& evt);
	void OnMaximizeButton(wxMaximizeEvent& evt);

	void OnExit(wxCloseEvent& evt);
	void OnExit(wxCommandEvent& evt);

	/* Stepper Control Functions */
	/* Detector X */
	void OnEnterTextCtrlDetectorXAbsPos(wxCommandEvent& evt);
	void OnSetDetectorXAbsPos(wxCommandEvent& evt);
	void OnDecrementDetectorXAbsPos(wxCommandEvent& evt);
	void OnIncrementDetectorXAbsPos(wxCommandEvent& evt);
	void OnCenterDetectorX(wxCommandEvent& evt);
	void OnHomeDetectorX(wxCommandEvent& evt);
	/* Optics Y */
	void OnEnterTextCtrlOpticsYAbsPos(wxCommandEvent& evt);
	void OnSetOpticsYAbsPos(wxCommandEvent& evt);
	void OnDecrementOpticsYAbsPos(wxCommandEvent& evt);
	void OnIncrementOpticsYAbsPos(wxCommandEvent& evt);
	void OnCenterOpticsY(wxCommandEvent& evt);
	void OnHomeOpticsY(wxCommandEvent& evt);

	/* First Stage */
	void OnFirstStageChoice(wxCommandEvent& evt);
	/* Second Stage */
	void OnSecondStageChoice(wxCommandEvent& evt);
	/* Changed Exposure value */
	void ExposureValueChanged(wxCommandEvent& evt);
	/* Start Capturing */
	void OnStartCapturingButton(wxCommandEvent& evt);
	void OnStartStopLiveCapturingMenu(wxCommandEvent& evt);
	void OnStartStopLiveCapturingTglBtn(wxCommandEvent& evt);

	/* Thread Live Capturing */
	auto LiveCapturingThread(wxThreadEvent& evt) -> void;
	/* Progress */
	void UpdateProgress(wxThreadEvent& evt);
	bool Cancelled();

	void UpdateAllAxisGlobalPositions();

	/* CrossHair */
	void OnXPosCrossHairTextCtrl(wxCommandEvent& evt);
	void OnYPosCrossHairTextCtrl(wxCommandEvent& evt);
	auto OnSetPosCrossHairTglBtn(wxCommandEvent& evt) -> void;

	auto CreateMetadataFile() -> void;

private:
	/* Settings Menu */
	std::unique_ptr<cSettings> m_Settings{};
	/* Menu Bar */
	std::unique_ptr<MainFrameVariables::MenuBar> m_MenuBar{};
	/* Tool Bar */
	std::unique_ptr<MainFrameVariables::ToolBar> m_VerticalToolBar{};
	/* Preview Panel */
	std::unique_ptr<cPreviewPanel> m_PreviewPanel{};
	/* Steppers Control */
	std::unique_ptr<MainFrameVariables::StepperControl[]> m_Detector = std::make_unique<MainFrameVariables::StepperControl[]>(1);
	std::unique_ptr<MainFrameVariables::StepperControl[]> m_Optics = std::make_unique<MainFrameVariables::StepperControl[]>(5);

	/* Camera */
	//std::unique_ptr<XimeaControl> m_XimeaControl{};
	std::unique_ptr<wxTextCtrl> m_CamExposure{};
	std::unique_ptr<wxStaticText> m_SelectedDeviceStaticTXT{};
	std::unique_ptr<wxButton> m_SingleShotBtn{};
	std::unique_ptr<wxToggleButton> m_StartStopLiveCapturingTglBtn{};
	std::unique_ptr<wxTextCtrl> m_CrossHairPosXTxtCtrl{}, m_CrossHairPosYTxtCtrl{};
	std::unique_ptr<wxToggleButton> m_SetCrossHairPosTglBtn{};

	/* Measurement */
	std::unique_ptr<wxTextCtrl> m_OutDirTextCtrl{};
	std::unique_ptr<wxButton> m_OutDirBtn{};
	std::unique_ptr<MainFrameVariables::MeasurementStage> m_FirstStage{}, m_SecondStage{};
	std::unique_ptr<wxButton> m_StartMeasurement{};

	/* Progress */
	bool m_Cancelled{}, m_DataCalculatedInThisApp{};
	wxCriticalSection m_CSCancelled{};
	std::unique_ptr<ProgressBar> m_ProgressBar{};
	std::chrono::steady_clock::time_point m_StartCalculationTime;
	std::unique_ptr<wxAppProgressIndicator> m_AppProgressIndicator{};

	int m_Progress{};
	wxString m_ProgressMsg{};

	/* CrossHair */
	bool m_IsCrossHairChecked{};

	/* Value Displaying */
	bool m_IsValueDisplayingChecked{};

	/* Live Capturing */
	//bool m_StopLiveCapturing{};
	//bool m_LiveCapturingEndedDrawingOnCamPreview{ true };

	/* Appearance Colors */
	wxColour m_DefaultAppearenceColor = wxColour(255, 255, 255);
	wxColour m_BlackAppearenceColor = wxColour(30, 30, 30);

	/* wxPanels */
	wxPanel* m_RightSidePanel{};

	wxDECLARE_EVENT_TABLE();
};
/* ___ End cMain ___ */

/* ___ Start Live Capturing Theread ___ */
class LiveCapturing final: public wxThread
{
public:
	LiveCapturing
	(
		cMain* main_frame,
		cPreviewPanel* cam_preview_window,
		//XimeaControl* ximea_control,
		//const std::string& selected_camera,
		const int exposure_us
	);
	~LiveCapturing();

	virtual void* Entry();

private:
	auto CaptureImage
	(
		unsigned short* short_data_ptr, 
		wxImage* image_ptr
	) -> bool;
	auto UpdatePixelsMultithread
	(
		unsigned short* short_data_ptr, 
		wxImage* image_ptr
	) -> void;
	auto AdjustImageParts
	(
		const unsigned short* data_ptr,
		wxImage* image_ptr,
		const unsigned int start_x,
		const unsigned int start_y,
		const unsigned int finish_x,
		const unsigned int finish_y
	) -> void;

private:
	cMain* m_MainFrame{};
	cPreviewPanel* m_CamPreviewWindow{};
	//XimeaControl* m_XimeaControl{};
	//std::string m_SelectedCameraSN{};
	int m_ExposureUS{};
	//std::unique_ptr<XimeaControl> m_XimeaCameraControl{};
	wxSize m_ImageSize{};
	int m_ThreadID{ -1 };
};
/* ___ End Worker Thread ___ */

/* ___ Start Worker Theread ___ */
class WorkerThread final: public wxThread
{
public:
	WorkerThread
	(
		cMain* main_frame,
		cSettings* settings, 
		cPreviewPanel* camera_preview_panel,
		//XimeaControl* ximea_control,
		const wxString& path, 
		const unsigned long& exp_time_us,
		MainFrameVariables::AxisMeasurement* first_axis, 
		MainFrameVariables::AxisMeasurement* second_axis
	);
	~WorkerThread();

	virtual void* Entry();

private:
	auto CaptureAndSaveImage
	(
		const auto& camera_pointer, 
		unsigned short* short_data_ptr, 
		wxImage* image_ptr,
		const int& image_number,
		const float& first_stage_position,
		const float& second_stage_position,
		const std::string& hours,
		const std::string& minutes,
		const std::string& seconds
	) -> bool;
	auto SaveImageOnDisk(const int& image_number) -> bool;

private:
	cMain* m_MainFrame{};
	cSettings* m_Settings{};
	cPreviewPanel* m_PreviewPanel{};
	//XimeaControl* m_XimeaControl{};
	wxString m_ImagePath{};
	unsigned long m_ExposureTimeUS{};
	MainFrameVariables::AxisMeasurement* m_FirstAxis{}, * m_SecondAxis{};
};
/* ___ End Worker Thread ___ */

/* ___ Start Progress Thread ___ */
class ProgressThread final : public wxThread
{
public:
	ProgressThread(cSettings* settings, cMain* main_frame);
	virtual void* Entry();
	~ProgressThread();

private:
	cSettings* m_Settings{};
	cMain* m_Frame{};
	int m_Progress{};
	wxString m_ProgressMsg{};
};
/* ___ End  Progress Thread ___ */

/* ___ Start ProgressBar ___ */
class ProgressBar final : public wxFrame
{
public:
	ProgressBar(wxWindow* parent, const wxPoint& pos, const wxSize& size);
	void UpdateProgressWithMessage(const wxString& msg, const int& progress);
	void UpdateElapsedTime(const uint64_t& elapsed_seconds);
	void UpdateEstimatedTime(const int& prgs, const uint64_t& estimated_seconds);
	~ProgressBar();
private:
	void CreateProgressBar();

private:
	ProgressPanel* m_ProgressPanel{};
	wxSize m_MainSize{};

	DECLARE_EVENT_TABLE()
};
/* ___ End ProgressBar ___ */

/* ___ Start ProgressPanel ___ */
class ProgressPanel final : public wxPanel
{
public:
	ProgressPanel(wxFrame* parent, const wxSize& size);
	void SetSize(const wxSize& new_size);
	void SetProgress(const int& progress);
	void SetElapsedTime(const int& elapsed_time);
	void SetEstimatedTime(const int& progress, const int& estimated_time);
	void SetComment(const wxString& progress_comment);

private:
	void PaintEvent(wxPaintEvent& evt);
	void Render(wxBufferedPaintDC& dc);
	void OnSize(wxSizeEvent& evt);

private:
	int m_Width{}, m_Height{};
	int m_Progress{}, m_PreviousEstimateProgress{};
	int m_ElapsedTime{}, m_EstimatedTime{}; // Time in seconds
	int m_ElapsedHours{}, m_ElapsedMinutes{}, m_ElapsedSeconds{};
	wxString m_ProgressComment{ "Moving to start position" };

	DECLARE_EVENT_TABLE()
};
/* ___ End ProgressPanel ___ */

#endif // !CMAIN_H
