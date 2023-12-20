#pragma once
#ifndef CSETTINGS_H
#define CSETTINGS_H

#include "wx/wx.h"

#include <memory>
#include <map>
#include <set>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

#include "Motor.h"
//#include "XimeaControl.h"


namespace SettingsVariables
{
	enum
	{
		/* Work Station */
		ID_WORK_STATION_CHOICE,
		/* Detector X */
		ID_MOT_DET_X_MOTOR_TXT_CTRL,
		ID_MOT_DET_X_RANGE_ST_TEXT,
		/* Optics X */
		ID_MOT_OPT_X_MOTOR_TXT_CTRL,
		ID_MOT_OPT_X_RANGE_ST_TEXT,
		/* Optics Y */
		ID_MOT_OPT_Y_MOTOR_TXT_CTRL,
		ID_MOT_OPT_Y_RANGE_ST_TEXT,
		/* Optics Z */
		ID_MOT_OPT_Z_MOTOR_TXT_CTRL,
		ID_MOT_OPT_Z_RANGE_ST_TEXT,	
		/* Optics Pitch */
		ID_MOT_OPT_PITCH_MOTOR_TXT_CTRL,
		ID_MOT_OPT_PITCH_RANGE_ST_TEXT,
		/* Optics Yaw */
		ID_MOT_OPT_YAW_MOTOR_TXT_CTRL,
		ID_MOT_OPT_YAW_RANGE_ST_TEXT,
		/* Cameras */
		ID_KETEK_TXT_CTRL,
	};

	struct MotorSettings
	{
		wxTextCtrl* motor{}; 
		wxStaticText* ranges{};
		wxString motor_sn{};
		//uint8_t current_selection[2], prev_selection[2];
		~MotorSettings()
		{
			motor->~wxTextCtrl();
		}
	};

	struct MotorSettingsArray
	{
		std::unique_ptr<MotorSettings[]> m_Detector{}, m_Optics{};

		wxArrayString xml_all_motors[2];
		wxArrayString xml_selected_motors[2];

		std::map<unsigned int, float> unique_motors_map;
		//std::set<float> unique_motors_set[2];
		wxArrayString unique_motors[2];

		MotorSettingsArray()
		{
			m_Detector = std::make_unique<MotorSettings[]>(1); // Only Detector X
			m_Optics = std::make_unique<MotorSettings[]>(5); // Optics X, Y, Z, Pitch, Yaw
		}
	};

	struct MeasurementDevice
	{
		wxTextCtrl* device{};
		wxString selected_device_str{};

		~MeasurementDevice()
		{
			device->~wxTextCtrl();
		}
	};

	struct WorkStationData
	{
		wxArrayString selected_motors_in_data_file{};
		//wxString selected_camera_in_data_file{};
		wxString selected_ketek_in_data_file{};
		wxString work_station_name{};
	};

	struct WorkStations
	{
		wxChoice* work_station_choice{};
		unsigned short work_stations_count{};
		std::unique_ptr<WorkStationData[]> work_station_data{};
		wxArrayString all_work_station_array_str{};
		wxString initialized_work_station{};
		unsigned short initialized_work_station_num{};

		~WorkStations()
		{
			work_station_choice->~wxChoice();
		}
	};

	struct ProgressValues
	{
		int current_capture{}, whole_captures_num{};
		bool is_finished{};
	};
}

class cSettings final : public wxDialog
{
public:
	cSettings(wxWindow* parent_frame);

	/* Getters */
	bool DetectorXHasSerialNumber() const;
	float GetActualDetectorXStagePos() const;

	bool OpticsXHasSerialNumber() const;
	float GetActualOpticsXStagePos() const;
	bool OpticsYHasSerialNumber() const;
	float GetActualOpticsYStagePos() const;
	bool OpticsZHasSerialNumber() const;
	float GetActualOpticsZStagePos() const;	
	bool OpticsPitchHasSerialNumber() const;
	float GetActualOpticsPitchStagePos() const;
	bool OpticsYawHasSerialNumber() const;
	float GetActualOpticsYawStagePos() const;


	/* Progress Getter */
	bool IsCapturingFinished() const;
	void ProvideProgressInfo(wxString* msg, int* prgrs);

	/* Progress Setter */
	void ResetCapturing();

	/* Setters */
	/* Detector X */
	float GoToAbsDetectorX(float absolute_position);
	float GoOffsetDetectorX(float delta);
	float CenterDetectorX();
	float HomeDetectorX();
	/* Detector Y */
	float GoToAbsDetectorY(float absolute_position);
	float GoOffsetDetectorY(float delta);
	float CenterDetectorY();
	float HomeDetectorY();
	/* Detector Z */
	float GoToAbsDetectorZ(float absolute_position);
	float GoOffsetDetectorZ(float delta);
	float CenterDetectorZ();
	float HomeDetectorZ();
	/* Optics Y */
	float GoToAbsOpticsY(float absolute_position);
	float GoOffsetOpticsY(float delta);
	float CenterOpticsY();
	float HomeOpticsY();
	/* Progress */
	void SetCurrentProgress(const int& curr_capturing_num, const int& whole_capturing_num);

	/* Camera */
	auto GetSelectedCamera() const -> wxString;
private:
	void CreateMainFrame();
	void CreateSettings();
	void CreateMotorsSelection(wxBoxSizer* panel_sizer);
	void InitDefaultStateWidgets();
	void InitComponents();

	void BindControls();
	void UpdateRangesTextCtrls();

	auto OnWorkStationChoice(wxCommandEvent& evt) -> void;
	auto UpdateMotorsAndCameraTXTCtrls(const short selected_work_station = -1) -> void;
	void OnRefreshBtn(wxCommandEvent& evt);
	void OnOkBtn(wxCommandEvent& evt);
	bool CheckIfThereIsCollisionWithMotors();
	bool CheckIfUserSelectedAllRangesForAllSelectedMotors();
	bool CheckIfUserSelectedAllMotorsForAllSelectedRanges();
	void OnCancelBtn(wxCommandEvent& evt);

	unsigned int FindSerialNumber(const uint8_t selection_number, const SettingsVariables::MotorSettings* motor_settings) const;

	/* Working with XML data and operating with m_Motors variables */
	auto CompareXMLWithConnectedDevices();
	auto ReadInitializationFile() -> void;
	auto ReadWorkStationFiles() -> void;
	void UpdateUniqueArray();
	void SelectMotorsAndRangesFromXMLFile();

	auto RewriteInitializationFile() -> void;

private:
	const wxString initialization_file_path = "src\\init.ini";
	const wxString work_stations_path = "src\\";
	//const wxString xml_file_path = "src\\old_xml\\mtrs.xml";
	std::unique_ptr<SettingsVariables::WorkStations> m_WorkStations{};
	std::unique_ptr<wxButton> m_OkBtn{}, m_CancelBtn{}, m_RefreshBtn{};
	std::unique_ptr<SettingsVariables::MotorSettingsArray> m_Motors{};
	std::unique_ptr<MotorArray> m_PhysicalMotors{};
	std::unique_ptr<SettingsVariables::MeasurementDevice> m_Ketek{};
	const int m_MotorsCount{ 6 };
	std::unique_ptr<SettingsVariables::ProgressValues> m_Progress = std::make_unique<SettingsVariables::ProgressValues>();
};

#endif // !CSETTINGS_H

