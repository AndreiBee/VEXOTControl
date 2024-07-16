#pragma once
#ifndef CMAIN_H
#define CMAIN_H

#include "wx/wx.h"
#include "wx/tglbtn.h"
#include "wx/valnum.h"
#include "wx/thread.h"
#include "wx/display.h"
#include "wx/appprogress.h"

#include <string>
#include <memory>
#include <chrono>
#include <utility>
#include <algorithm>

#include "json.hpp"

#include "cPreviewPanel.h"
#include "cSettings.h"
#include "Ketek.h"

#include "src/img/cross_hair.xpm"
#include "src/img/center.xpm"
#include "src/img/home.xpm"

#include "src/img/logo.xpm"


namespace MainFrameVariables
{
	enum
	{
		/* Menu Bar */
		ID_MENUBAR_FILE_OPEN,
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
		ID_RIGHT_MT_START_STOP_MEASUREMENT_TGL_BTN,
		/* Live Capturing */
		ID_THREAD_LIVE_CAPTURING,
		/* Worker Thread */
		ID_THREAD_MAIN_CAPTURING,
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

	static auto WriteMCAFile
	(
		const wxString filePath, 
		const unsigned long* const mcaData, 
		Ketek* handler, 
		const unsigned long long sumValues, 
		const int exposureSec = 1
	) -> unsigned long
	{
		auto replace_dot_to_comma = []
		(
			std::string str,
			const std::string oldStr,
			const std::string newStr
			)
			{
				std::string::size_type pos = 0u;
				while ((pos = str.find(oldStr, pos)) != std::string::npos) {
					str.replace(pos, oldStr.length(), newStr);
					pos += newStr.length();
				}
				return str;
			};

		auto writeHeader = [&](std::ofstream& outStream, const unsigned long maxValue, const int maxValuePos) 
			{
				outStream << "File Version = " << 1 << '\n';
				outStream << "MCA data = " << "<Generated by ProSpect - v1.1.36>" << '\n';
				outStream << "Title = " << "SingleShot" << '\n';
				outStream << "Setup = " << "" << '\n';
				outStream << "Sample = " << "" << '\n';
				outStream << "User Name = " << "VM" << '\n';
				// Writing current date
				{
					// Get the current time
					std::time_t now = std::time(nullptr);

					// Convert it to a tm structure
					std::tm* local_time = std::localtime(&now);

					// Print the current date in YYYY-MM-DD format
					auto currYear = (1900 + local_time->tm_year);
					auto currMonth = (1 + local_time->tm_mon);
					auto currDay = local_time->tm_mday;
					outStream << "Current Date = " << currDay << "." << currMonth << "." << currYear << '\n';
				}
				auto binSize = replace_dot_to_comma(std::to_string(handler->GetBinSize()), std::string("."), std::string(","));
				outStream << "Bin Size = " << binSize << '\n';
				outStream << "Board Type = " << "KETEK DPP2" << '\n';
				outStream << "Serial = " << handler->GetSerialNumber() << '\n';
				outStream << "Channel = " << 0 << '\n';
				outStream << "Reset Interval = " << "5,000" << " us" << '\n';
				outStream << "Polarity = " << "(+) Positive" << '\n';
				outStream << "Peaking Time Range = " << "0,1 - 24" << '\n';
				outStream << "Peaking Time = " << "24,00" << '\n';
				outStream << "Genset = " << "4" << '\n';
				outStream << "MCA Bin Width (1: Finest) = " << 1 << '\n';
				auto baseGain = replace_dot_to_comma(std::to_string(handler->GetGain()), std::string("."), std::string(","));
				outStream << "Base Gain (1-100) = " << baseGain << '\n';
				outStream << "Number MCA Bins = " << handler->GetDataSize() << '\n';
				outStream << "Dynamic Range (keV) = " << "20,000" << '\n';
				outStream << "Fine Gain Trim (0.5-2.0) = " << "1,32095336914062" << '\n';
				outStream << "Baseline (0-4095) = " << 0 << '\n';
				outStream << "Energy (0-4095) = " << 0 << '\n';
				outStream << "Trigger (0-4095) = " << 30 << '\n';
				outStream << "Baseline Average Length = " << 512 << '\n';
				outStream << "Events = " << sumValues << '\n';
				outStream << "MaxValue = " << maxValue << '\n';
				outStream << "MaxValuePosition = " << maxValuePos + 1 << '\n';
				outStream << "ICR: = " << "2,4866 kcps" << '\n';
				outStream << "OCR: = " << "2,2000 kcps" << '\n';
				outStream << "Live Time: = " << exposureSec << ",0 s" << '\n';
				outStream << "Real Time: = " << exposureSec << ",0 s" << '\n';
				
				outStream << '\n';
				outStream << handler->GetDataSize() << '\n';

			};

		auto dataSize = handler->GetDataSize();
		auto maxElement = std::max_element(mcaData, mcaData + dataSize);
		auto maxElementPos = static_cast<int>(std::distance(mcaData, maxElement));

		std::ofstream outFile(filePath.ToStdString());

		if (!outFile)
		{
			return *maxElement;
		}
		
		writeHeader(outFile, *maxElement, maxElementPos);

		for (auto i{ 0 }; i < handler->GetDataSize(); ++i)
		{
			outFile << mcaData[i] << '\n';
		}

		outFile.close();

		return *maxElement;
	}

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
	void UpdateStagePositions();
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

	auto OnOpenMCAFile(wxCommandEvent& evt) -> void;
	auto ParseMCAFile(const wxString filePath) -> void;
	void OnOpenSettings(wxCommandEvent& evt);
	auto InitializeSelectedCamera() -> void;
	auto InitializeSelectedDevice() -> void;
	void EnableUsedAndDisableNonUsedMotors();

	void OnCrossHairButton(wxCommandEvent& evt);
	void OnValueDisplayingCheck(wxCommandEvent& evt);

	void OnFullScreen(wxCommandEvent& evt);
	void OnMaximizeButton(wxMaximizeEvent& evt);

	void OnExit(wxCloseEvent& evt);
	void OnExit(wxCommandEvent& evt);

	/* Stepper Control Functions */
	/* _____________________Detector X_____________________ */
	void OnEnterTextCtrlDetectorXAbsPos(wxCommandEvent& evt) 
	{
		wxCommandEvent enter_evt(wxEVT_BUTTON, MainFrameVariables::ID_RIGHT_SC_DET_X_SET_BTN);
		ProcessEvent(enter_evt);
	};

	void OnSetDetectorXAbsPos(wxCommandEvent& evt)
	{
		wxBusyCursor cursor;
		double absolute_position{};
		if (!m_Detector[0].absolute_text_ctrl->GetValue().ToDouble(&absolute_position)) return;
		auto position = m_Settings->GoToAbsPos(SettingsVariables::DETECTOR_X, (float)absolute_position);
		m_Detector[0].absolute_text_ctrl->SetValue(wxString::Format(wxT("%.3f"), position));
	};

	void OnDecrementDetectorXAbsPos(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		double delta_position{};
		if (!m_Detector[0].relative_text_ctrl->GetValue().ToDouble(&delta_position)) return;
		m_Detector[0].absolute_text_ctrl->SetValue(
			wxString::Format
			(
				wxT("%.3f"), 
				m_Settings->GoOffsetMotor(SettingsVariables::DETECTOR_X, -(float)delta_position)
			));
	};

	void OnIncrementDetectorXAbsPos(wxCommandEvent& evt)
	{
		wxBusyCursor cursor;
		double delta_position{};
		if (!m_Detector[0].relative_text_ctrl->GetValue().ToDouble(&delta_position)) return;
		m_Detector[0].absolute_text_ctrl->SetValue(
			wxString::Format
			(
				wxT("%.3f"), 
				m_Settings->GoOffsetMotor(SettingsVariables::DETECTOR_X, (float)delta_position)
			));
	};

	void OnCenterDetectorX(wxCommandEvent& evt)
	{
		wxBusyCursor cursor;
		m_Detector[0].absolute_text_ctrl->SetValue(
			wxString::Format(
				wxT("%.3f"), 
				m_Settings->CenterMotor(SettingsVariables::DETECTOR_X)
			));
	};

	void OnHomeDetectorX(wxCommandEvent& evt)
	{
		wxBusyCursor cursor;
		m_Detector[0].absolute_text_ctrl->ChangeValue(
			wxString::Format(
				wxT("%.3f"), 
				m_Settings->HomeMotor(SettingsVariables::DETECTOR_X)
			));
	};
	
	/* _____________________Optics X_____________________ */

	void OnEnterTextCtrlOpticsXAbsPos(wxCommandEvent& evt)
	{
		wxCommandEvent enter_evt(wxEVT_BUTTON, MainFrameVariables::ID_RIGHT_SC_OPT_X_SET_BTN);
		ProcessEvent(enter_evt);
	};

	void OnSetOpticsXAbsPos(wxCommandEvent& evt)
	{
		wxBusyCursor cursor;
		double absolute_position{};
		if (!m_Optics[0].absolute_text_ctrl->GetValue().ToDouble(&absolute_position)) return;
		auto position = m_Settings->GoToAbsPos(SettingsVariables::OPTICS_X, (float)absolute_position);
		m_Optics[0].absolute_text_ctrl->SetValue(wxString::Format(wxT("%.3f"), position));
	};

	void OnDecrementOpticsXAbsPos(wxCommandEvent& evt)
	{
		wxBusyCursor cursor;
		double delta_position{};
		if (!m_Optics[0].relative_text_ctrl->GetValue().ToDouble(&delta_position)) return;
		m_Optics[0].absolute_text_ctrl->SetValue(
			wxString::Format
			(
				wxT("%.3f"), 
				m_Settings->GoOffsetMotor(SettingsVariables::OPTICS_X, -(float)delta_position)
			));
	};

	void OnIncrementOpticsXAbsPos(wxCommandEvent& evt)
	{
		wxBusyCursor cursor;
		double delta_position{};
		if (!m_Optics[0].relative_text_ctrl->GetValue().ToDouble(&delta_position)) return;
		m_Optics[0].absolute_text_ctrl->SetValue(
			wxString::Format
			(
				wxT("%.3f"), 
				m_Settings->GoOffsetMotor(SettingsVariables::OPTICS_X, (float)delta_position)
			));

	};

	void OnCenterOpticsX(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		m_Optics[0].absolute_text_ctrl->SetValue(
			wxString::Format(
				wxT("%.3f"), 
				m_Settings->CenterMotor(SettingsVariables::OPTICS_X)
			));
	};

	void OnHomeOpticsX(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		m_Optics[0].absolute_text_ctrl->ChangeValue(
			wxString::Format(
				wxT("%.3f"), 
				m_Settings->HomeMotor(SettingsVariables::OPTICS_X)
			));
	};

	/* _____________________Optics Y_____________________ */
	void OnEnterTextCtrlOpticsYAbsPos(wxCommandEvent& evt) 
	{
		wxCommandEvent enter_evt(wxEVT_BUTTON, MainFrameVariables::ID_RIGHT_SC_OPT_Y_SET_BTN);
		ProcessEvent(enter_evt);
	};

	void OnSetOpticsYAbsPos(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		double absolute_position{};
		if (!m_Optics[1].absolute_text_ctrl->GetValue().ToDouble(&absolute_position)) return;
		auto position = m_Settings->GoToAbsPos(SettingsVariables::OPTICS_Y, (float)absolute_position);
		m_Optics[1].absolute_text_ctrl->SetValue(wxString::Format(wxT("%.3f"), position));
	};

	void OnDecrementOpticsYAbsPos(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		double delta_position{};
		if (!m_Optics[1].relative_text_ctrl->GetValue().ToDouble(&delta_position)) return;
		m_Optics[1].absolute_text_ctrl->SetValue(
			wxString::Format
			(
				wxT("%.3f"), 
				m_Settings->GoOffsetMotor(SettingsVariables::OPTICS_Y, -(float)delta_position)
			));
	};

	void OnIncrementOpticsYAbsPos(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		double delta_position{};
		if (!m_Optics[1].relative_text_ctrl->GetValue().ToDouble(&delta_position)) return;
		m_Optics[1].absolute_text_ctrl->SetValue(
			wxString::Format
			(
				wxT("%.3f"), 
				m_Settings->GoOffsetMotor(SettingsVariables::OPTICS_Y, (float)delta_position)
			));
	};

	void OnCenterOpticsY(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		m_Optics[1].absolute_text_ctrl->SetValue(
			wxString::Format(
				wxT("%.3f"), 
				m_Settings->CenterMotor(SettingsVariables::OPTICS_Y)
			));
	};

	void OnHomeOpticsY(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		m_Optics[1].absolute_text_ctrl->SetValue(
			wxString::Format(
				wxT("%.3f"), 
				m_Settings->HomeMotor(SettingsVariables::OPTICS_Y)
			));
	};

	/* _____________________Optics Z_____________________ */
	void OnEnterTextCtrlOpticsZAbsPos(wxCommandEvent& evt) 
	{
		wxCommandEvent enter_evt(wxEVT_BUTTON, MainFrameVariables::ID_RIGHT_SC_OPT_Z_SET_BTN);
		ProcessEvent(enter_evt);
	};

	void OnSetOpticsZAbsPos(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		double absolute_position{};
		if (!m_Optics[2].absolute_text_ctrl->GetValue().ToDouble(&absolute_position)) return;
		auto position = m_Settings->GoToAbsPos(SettingsVariables::OPTICS_Z, (float)absolute_position);
		m_Optics[2].absolute_text_ctrl->SetValue(wxString::Format(wxT("%.3f"), position));
	};

	void OnDecrementOpticsZAbsPos(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		double delta_position{};
		if (!m_Optics[2].relative_text_ctrl->GetValue().ToDouble(&delta_position)) return;
		m_Optics[2].absolute_text_ctrl->SetValue(
			wxString::Format
			(
				wxT("%.3f"), 
				m_Settings->GoOffsetMotor(SettingsVariables::OPTICS_Z, -(float)delta_position)
			));
	};

	void OnIncrementOpticsZAbsPos(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		double delta_position{};
		if (!m_Optics[2].relative_text_ctrl->GetValue().ToDouble(&delta_position)) return;
		m_Optics[2].absolute_text_ctrl->SetValue(
			wxString::Format
			(
				wxT("%.3f"), 
				m_Settings->GoOffsetMotor(SettingsVariables::OPTICS_Z, (float)delta_position)
			));
	};

	void OnCenterOpticsZ(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		m_Optics[2].absolute_text_ctrl->SetValue(
			wxString::Format(
				wxT("%.3f"), 
				m_Settings->CenterMotor(SettingsVariables::OPTICS_Z)
			));
	};

	void OnHomeOpticsZ(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		m_Optics[2].absolute_text_ctrl->SetValue(
			wxString::Format(
				wxT("%.3f"), 
				m_Settings->HomeMotor(SettingsVariables::OPTICS_Z)
			));
	};

	/* _____________________Optics Pitch_____________________ */
	void OnEnterTextCtrlOpticsPitchAbsPos(wxCommandEvent& evt) 
	{
		wxCommandEvent enter_evt(wxEVT_BUTTON, MainFrameVariables::ID_RIGHT_SC_OPT_PITCH_SET_BTN);
		ProcessEvent(enter_evt);
	};

	void OnSetOpticsPitchAbsPos(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		double absolute_position{};
		if (!m_Optics[3].absolute_text_ctrl->GetValue().ToDouble(&absolute_position)) return;
		auto position = m_Settings->GoToAbsPos(SettingsVariables::OPTICS_PITCH, (float)absolute_position);
		m_Optics[3].absolute_text_ctrl->SetValue(wxString::Format(wxT("%.3f"), position));
	};

	void OnDecrementOpticsPitchAbsPos(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		double delta_position{};
		if (!m_Optics[3].relative_text_ctrl->GetValue().ToDouble(&delta_position)) return;
		m_Optics[3].absolute_text_ctrl->SetValue(
			wxString::Format
			(
				wxT("%.3f"), 
				m_Settings->GoOffsetMotor(SettingsVariables::OPTICS_PITCH, -(float)delta_position)
			));
	};

	void OnIncrementOpticsPitchAbsPos(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		double delta_position{};
		if (!m_Optics[3].relative_text_ctrl->GetValue().ToDouble(&delta_position)) return;
		m_Optics[3].absolute_text_ctrl->SetValue(
			wxString::Format
			(
				wxT("%.3f"), 
				m_Settings->GoOffsetMotor(SettingsVariables::OPTICS_PITCH, (float)delta_position)
			));
	};

	void OnCenterOpticsPitch(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		m_Optics[3].absolute_text_ctrl->SetValue(
			wxString::Format(
				wxT("%.3f"), 
				m_Settings->CenterMotor(SettingsVariables::OPTICS_PITCH)
			));
	};

	void OnHomeOpticsPitch(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		m_Optics[3].absolute_text_ctrl->SetValue(
			wxString::Format(
				wxT("%.3f"), 
				m_Settings->HomeMotor(SettingsVariables::OPTICS_PITCH)
			));
	};

	/* _____________________Optics Yaw_____________________ */
	void OnEnterTextCtrlOpticsYawAbsPos(wxCommandEvent& evt) 
	{
		wxCommandEvent enter_evt(wxEVT_BUTTON, MainFrameVariables::ID_RIGHT_SC_OPT_YAW_SET_BTN);
		ProcessEvent(enter_evt);
	};

	void OnSetOpticsYawAbsPos(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		double absolute_position{};
		if (!m_Optics[4].absolute_text_ctrl->GetValue().ToDouble(&absolute_position)) return;
		auto position = m_Settings->GoToAbsPos(SettingsVariables::OPTICS_YAW, (float)absolute_position);
		m_Optics[4].absolute_text_ctrl->SetValue(wxString::Format(wxT("%.3f"), position));
	};

	void OnDecrementOpticsYawAbsPos(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		double delta_position{};
		if (!m_Optics[4].relative_text_ctrl->GetValue().ToDouble(&delta_position)) return;
		m_Optics[4].absolute_text_ctrl->SetValue(
			wxString::Format
			(
				wxT("%.3f"), 
				m_Settings->GoOffsetMotor(SettingsVariables::OPTICS_YAW, -(float)delta_position)
			));
	};

	void OnIncrementOpticsYawAbsPos(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		double delta_position{};
		if (!m_Optics[4].relative_text_ctrl->GetValue().ToDouble(&delta_position)) return;
		m_Optics[4].absolute_text_ctrl->SetValue(
			wxString::Format
			(
				wxT("%.3f"), 
				m_Settings->GoOffsetMotor(SettingsVariables::OPTICS_YAW, (float)delta_position)
			));
	};

	void OnCenterOpticsYaw(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		m_Optics[4].absolute_text_ctrl->SetValue(
			wxString::Format(
				wxT("%.3f"), 
				m_Settings->CenterMotor(SettingsVariables::OPTICS_YAW)
			));
	};

	void OnHomeOpticsYaw(wxCommandEvent& evt) 
	{
		wxBusyCursor cursor;
		m_Optics[4].absolute_text_ctrl->SetValue(
			wxString::Format(
				wxT("%.3f"), 
				m_Settings->HomeMotor(SettingsVariables::OPTICS_YAW)
			));
	};

	/* First Stage */
	void OnFirstStageChoice(wxCommandEvent& evt);
	/* Second Stage */
	void OnSecondStageChoice(wxCommandEvent& evt);
	/* Changed Exposure value */
	void ExposureValueChanged(wxCommandEvent& evt);
	/* Start Capturing */
	void OnStartStopCapturingButton(wxCommandEvent& evt);
	auto StartCapturing() -> bool;
	void OnStartStopLiveCapturingMenu(wxCommandEvent& evt);
	void OnStartStopLiveCapturingTglBtn(wxCommandEvent& evt);

	/* Thread Live Capturing */
	auto LiveCapturingThread(wxThreadEvent& evt) -> void;
	auto WorkerThreadEvent(wxThreadEvent& evt) -> void;
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

	/* Device */
	//std::unique_ptr<XimeaControl> m_XimeaControl{};
	std::unique_ptr<wxChoice> m_DeviceChoice{};
	wxArrayString m_DeviceArrayString{ "KETEK", "Raspberry", "xPIN" };
	std::unique_ptr<wxTextCtrl> m_SelectedDeviceStaticTXT{};
	std::unique_ptr<wxTextCtrl> m_DeviceExposure{};
	std::unique_ptr<wxButton> m_SingleShotBtn{};
	std::unique_ptr<wxToggleButton> m_StartStopLiveCapturingTglBtn{};
	/* CrossHair */
	std::unique_ptr<wxTextCtrl> m_CrossHairPosXTxtCtrl{}, m_CrossHairPosYTxtCtrl{};
	std::unique_ptr<wxToggleButton> m_SetCrossHairPosTglBtn{};

	/* Measurement */
	std::unique_ptr<wxTextCtrl> m_OutDirTextCtrl{};
	std::unique_ptr<wxButton> m_OutDirBtn{};
	std::unique_ptr<MainFrameVariables::MeasurementStage> m_FirstStage{}, m_SecondStage{};
	std::unique_ptr<wxToggleButton> m_StartStopMeasurementTglBtn{};

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

	// Ketek
	std::unique_ptr<Ketek> m_KetekHandler{};

	/* Capturing */
	std::vector<std::pair<wxString, bool>> m_StartedThreads{};

	wxDECLARE_EVENT_TABLE();
};
/* ___ End cMain ___ */

/* ___ Start Live Capturing Theread ___ */
class LiveCapturing final: public wxThread
{
public:
	LiveCapturing
	(
		cMain* mainFrame,
		Ketek* ketekHandler,
		wxString* threadKey,
		bool* continueCapturing,
		const int exposureSeconds
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
	Ketek* m_KetekHandler{};
	wxString* m_ThreadID{};
	bool* m_ContinueCapturing{};
	int m_ExposureSeconds{};
};
/* ___ End Worker Thread ___ */

/* ___ Start Worker Theread ___ */
class WorkerThread final: public wxThread
{
public:
	WorkerThread
	(
		cMain* mainFrame,
		cSettings* settings,
		Ketek* ketekHandler,
		wxString* threadKey,
		bool* continueCapturing,
		const wxString& path,
		const unsigned long exposureSeconds,
		MainFrameVariables::AxisMeasurement* first_axis,
		MainFrameVariables::AxisMeasurement* second_axis
	)
		: m_MainFrame(mainFrame), 
		m_Settings(settings), 
		m_KetekHandler(ketekHandler), 
		m_ThreadID(threadKey), 
		m_ContinueCapturing(continueCapturing), 
		m_DataPath(path), 
		m_ExposureTimeSeconds(exposureSeconds), 
		m_FirstAxis(first_axis), 
		m_SecondAxis(second_axis) {};

	~WorkerThread() 
	{
		delete m_FirstAxis;
		m_FirstAxis = nullptr;
		delete m_SecondAxis;
		m_SecondAxis = nullptr;
	};

	virtual void* Entry();

private:
	auto CaptureAndSaveData
	(
		unsigned long* const mca,
		const int& image_number,
		const float& first_stage_position,
		const float& second_stage_position,
		const std::string& hours,
		const std::string& minutes,
		const std::string& seconds
	) -> bool;

	auto MoveFirstStage(const float position) -> float;

	auto SaveImageOnDisk(const int& image_number) -> bool;

private:
	cMain* m_MainFrame{};
	cSettings* m_Settings{};
	Ketek* m_KetekHandler{};
	wxString* m_ThreadID{};
	bool* m_ContinueCapturing{};
	wxString m_DataPath{};
	unsigned long m_ExposureTimeSeconds{};
	MainFrameVariables::AxisMeasurement* m_FirstAxis{}, * m_SecondAxis{};
	unsigned long m_MaxElementDuringCapturing{};
	float m_BestFirstAxisPosition{}, m_BestSecondAxisPosition{};
};
/* ___ End Worker Thread ___ */

/* ___ Start Progress Thread ___ */
class ProgressThread final : public wxThread
{
public:
	ProgressThread
	(
		cMain* mainFrame,
		cSettings* settings,
		bool* continueWaiting
	)
		: m_Frame(mainFrame), 
		m_Settings(settings), 
		m_ContinueWaiting(continueWaiting) {};

	virtual void* Entry();

	~ProgressThread() 
	{
		m_Frame = nullptr;
		m_Settings = nullptr;
	};

private:
	cSettings* m_Settings{};
	cMain* m_Frame{};
	int m_Progress{};
	bool* m_ContinueWaiting{};
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
