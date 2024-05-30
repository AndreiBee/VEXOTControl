#pragma once
#ifndef CPREVIEWPANEL_H
#define CPREVIEWPANEL_H

#include "wx/wx.h"
#include "wx/dcbuffer.h"
#include "wx/graphics.h"
#include "wx/tglbtn.h"

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <format>
#include <algorithm>

#include <opencv2/opencv.hpp>

#include "cPreviewTools.h"
//#include "XimeaControl.h"

// Macros
#ifdef _DEBUG
#define LOG(message) wxLogDebug(message);
#define LOGST(message, number) wxLogDebug(message + wxString::Format(wxT("%i"), number))
#define LOGF(message, number) wxLogDebug(message + wxString::Format(wxT("%.2f"), number))
#define LOGI(message, number) wxLogDebug(message + wxString::Format(wxT("%i"), number))
#define LOG2I(first_message, first_number, second_message, second_number) wxLogDebug(first_message + wxString::Format(wxT("%i"), first_number) + second_message + wxString::Format(wxT("%i"), second_number))
#define LOG2F(first_message, first_number, second_message, second_number) wxLogDebug(first_message + wxString::Format(wxT("%.2f"), first_number) + second_message + wxString::Format(wxT("%.2f"), second_number))
#define LOG6F(first_message, first_number, second_message, second_number, third_message, third_number, fourth_message, fourth_number, fifth_message, fifth_number, sixth_message, sixth_number) wxLogDebug(first_message + wxString::Format(wxT("%.2f"), first_number) + second_message + wxString::Format(wxT("%.2f"), second_number) + third_message + wxString::Format(wxT("%.2f"), third_number) + fourth_message + wxString::Format(wxT("%.2f"), fourth_number) + fifth_message + wxString::Format(wxT("%.2f"), fifth_number) + sixth_message + wxString::Format(wxT("%.2f"), sixth_number))
#else
#define LOG(message)
#define LOGST(message, number)
#define LOGF(message, number)
#define LOGI(message, number)
#define LOG2I(first_message, first_number, second_message, second_number) 
#define LOG2F(first_message, first_number, second_message, second_number) 
#define LOG6F(first_message, first_number, second_message, second_number, third_message, third_number, fourth_message, fourth_number, fifth_message_fifth_number, sixth_message, sixth_number)
#endif // _DEBUG

namespace PreviewPanelVariables
{
	enum Device
	{
		XPIN,
		KETEK,
		TIMEPIX_ADVACAM,
		FLI_CAMERA
	};

	struct InputPreviewPanelArgs
	{
		wxTextCtrl* x_pos_crosshair{}, * y_pos_crosshair{};
		wxToggleButton* set_pos_tgl_btn{};
		InputPreviewPanelArgs() {};
		InputPreviewPanelArgs
		(
			wxTextCtrl* par_x_pos_crosshair,
			wxTextCtrl* par_y_pos_crosshair,
			wxToggleButton* par_pos_crosshair_tgl_btn
		) : x_pos_crosshair(par_x_pos_crosshair),
			y_pos_crosshair(par_y_pos_crosshair), 
			set_pos_tgl_btn(par_pos_crosshair_tgl_btn) {};
	};
}

class cPreviewPanel final : public wxPanel
{
public:
	cPreviewPanel
	(
		wxFrame* parent_frame, 
		wxSizer* parent_sizer, 
		std::unique_ptr<PreviewPanelVariables::InputPreviewPanelArgs> input_preview_panel_args
	);
	auto SetCurrentDevice(const int device) -> void { m_CurrentDeivce = device; };
	auto SetKETEKData(unsigned long* const mcaData, const unsigned long dataSize, const unsigned long long sum) -> void;

	auto SetBackgroundColor(wxColour bckg_colour) -> void;
	auto SetCrossHairButtonActive(bool activate = false) -> void;
	auto SetValueDisplayingActive(bool activate = false) -> void;
	void SetXCrossHairPosFromParentWindow(const int& x_pos);
	void SetYCrossHairPosFromParentWindow(const int& y_pos);
	auto SettingCrossHairPosFromParentWindow(bool set = false) -> void;
	auto SetImageSize() -> wxSize { return m_Image.GetSize(); };
	auto InitializeSelectedCamera(const std::string& camera_sn) -> void;
	auto SetCameraCapturedImage() -> void;
	void CaptureAndSaveDataFromCamera
	(
		const unsigned long& exposure_time_us, 
		const wxString& path, 
		const std::string& start_hours,
		const std::string& start_minutes,
		const std::string& start_seconds,
		const int& frame_number, 
		const float& first_axis_position, 
		const float& second_axis_position = 0.f
	);
	void CalculateMatlabJetColormapPixelRGB8bit
	(
		const unsigned char& value, 
		unsigned char& r, 
		unsigned char& g, 
		unsigned char& b
	);
	void CalculateMatlabJetColormapPixelRGB12bit
	(
		const unsigned short& value, 
		unsigned char& r, 
		unsigned char& g, 
		unsigned char& b
	);

	auto SetBinSize(const double binSize) -> void { m_BinSize = binSize; };

private:
	void InitDefaultComponents();
	void PaintEvent(wxPaintEvent& evt);
	void Render(wxBufferedPaintDC& dc);
	void DrawImage(wxGraphicsContext* gc);
	auto AdjustKETEKImageMultithread
	(
		const unsigned long* const data, 
		const double multiplicationValue,
		const int startX, 
		const int startY, 
		const int finishX, 
		const int finishY
	) -> void;
	void CreateGraphicsBitmapImage(wxGraphicsContext* gc_);
	void DrawCameraCapturedImage(wxGraphicsContext* gc_);
	auto DrawMaxValue(wxGraphicsContext* gc) -> void;
	auto DrawSumEvents(wxGraphicsContext* gc) -> void;
	auto DrawHorizontalRuller(wxGraphicsContext* gc) -> void;
	void OnSize(wxSizeEvent& evt);
	void ChangeSizeOfImageInDependenceOnCanvasSize();
	auto UpdateCrossHairOnSize() -> void;
	void CalculateMatlabJetColormapPixelRGB16bit(const uint16_t& value, unsigned char& r, unsigned char& g, unsigned char& b);
	void OnMouseMoved(wxMouseEvent& evt);
	/* Zooming */
	void OnMouseWheelMoved(wxMouseEvent& evt);
	void AddZoom(const double& zoom, bool zoom_in_center_of_window = false);
	void SetZoom(const double& zoom, const wxRealPoint& center_);
	/* Panning */
	void ProcessPan(const wxRealPoint& point_, bool refresh_);
	void FinishPan(bool refresh);

	void CheckIfMouseAboveImage();
	void CalculatePositionOnImage();

	void OnPreviewMouseLeftPressed(wxMouseEvent& evt);
	void OnPreviewMouseLeftReleased(wxMouseEvent& evt);

	void ChangeCursorInDependenceOfCurrentParameters();

	/* CrossHair */
	void DrawCrossHair(wxGraphicsContext* graphics_context);

private:
	int m_Width{}, m_Height{};
	bool m_IsGraphicsBitmapSet{}, m_IsImageSet{};

	wxImage m_Image{};
	wxGraphicsBitmap m_GraphicsBitmapImage{};
	std::unique_ptr<unsigned long[]> m_ImageData{};

	std::pair<unsigned short, unsigned long> m_MaxPosValueInData{};
	unsigned long long m_SumData{};
	double m_BinSize{};
	
	wxSize m_ImageSize{}, m_ImageOnCanvasSize{}, m_CanvasSize{};
	wxRealPoint m_NotCheckedCursorPosOnImage{}, m_CheckedCursorPosOnImage{}, m_CursorPosOnCanvas{};
	wxRealPoint m_NotZoomedGraphicsBitmapOffset{}, m_StartDrawPos{};
	bool m_IsCursorInsideImage{};
	/* Panning */
	bool m_Panning{};
	wxRealPoint m_PanOffset{}, m_PanStartPoint{}, m_PanDeltaPoints{};

	/* Zoom */
	double m_Zoom{}, m_ZoomOnOriginalSizeImage{};

	//std::unique_ptr<XimeaControl> m_XimeaCameraControl{};
	std::string m_SelectedCameraSN{};

	/* CrossHair Tool */
	std::unique_ptr<CrossHairTool> m_CrossHairTool{};
	wxPoint m_CrossHairPos{};
	bool m_ChangingCrossHairPosition{};
	//bool m_SettingCrossHairPos{};

	bool m_DisplayPixelValues{};

	std::unique_ptr<PreviewPanelVariables::InputPreviewPanelArgs> m_ParentArguments{};

	int m_CurrentDeivce{};

	DECLARE_EVENT_TABLE();
};

#endif // !CPREVIEWPANEL_H

