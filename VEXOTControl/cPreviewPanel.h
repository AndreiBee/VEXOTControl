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
#include <format>
#include <algorithm>

#include <opencv2/opencv.hpp>

#include "cPreviewTools.h"
//#include "XimeaControl.h"

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
	auto SetBackgroundColor(wxColour bckg_colour) -> void;
	auto SetCrossHairButtonActive(bool activate = false) -> void;
	auto SetValueDisplayingActive(bool activate = false) -> void;
	void SetXCrossHairPosFromParentWindow(const int& x_pos);
	void SetYCrossHairPosFromParentWindow(const int& y_pos);
	auto SettingCrossHairPosFromParentWindow(bool set = false) -> void;
	auto SetImageSize(const wxSize& img_size) -> void;
	auto GetDataPtr() const -> unsigned short*;
	auto GetImagePtr() const -> wxImage*;
	auto GetImageSize() const->wxSize;
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

private:
	void InitDefaultComponents();
	void PaintEvent(wxPaintEvent& evt);
	void Render(wxBufferedPaintDC& dc);
	void DrawImage(wxGraphicsContext* gc);
	void CreateGraphicsBitmapImage(wxGraphicsContext* gc_);
	void DrawCameraCapturedImage(wxGraphicsContext* gc_);
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
	std::unique_ptr<wxGraphicsBitmap> m_GraphicsBitmapImage{};

	std::shared_ptr<wxImage> m_Image{};
	std::shared_ptr<unsigned short[]> m_ImageData{};
	
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

	DECLARE_EVENT_TABLE();
};

#endif // !CPREVIEWPANEL_H

