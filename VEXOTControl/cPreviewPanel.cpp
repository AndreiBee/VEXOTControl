#include "cPreviewPanel.h"

BEGIN_EVENT_TABLE(cPreviewPanel, wxPanel)
	EVT_PAINT(cPreviewPanel::PaintEvent)
	EVT_SIZE(cPreviewPanel::OnSize)
	EVT_MOTION(cPreviewPanel::OnMouseMoved)
	EVT_MOUSEWHEEL(cPreviewPanel::OnMouseWheelMoved)
	EVT_LEFT_DOWN(cPreviewPanel::OnPreviewMouseLeftPressed)
	EVT_LEFT_UP(cPreviewPanel::OnPreviewMouseLeftReleased)
END_EVENT_TABLE()

cPreviewPanel::cPreviewPanel
(
	wxFrame* parent_frame, 
	wxSizer* parent_sizer,
	std::unique_ptr<PreviewPanelVariables::InputPreviewPanelArgs> input_preview_panel_args
) 
	: wxPanel(parent_frame)
{
	m_ParentArguments.reset(input_preview_panel_args.release());

	//m_XimeaCameraControl = std::make_unique<XimeaControl>();
	SetDoubleBuffered(true);
#ifdef _DEBUG
	SetBackgroundColour(wxColor(210, 185, 155));
#else
	SetBackgroundColour(wxColor(255, 255, 255));
#endif // _DEBUG
	parent_sizer->Add(this, 1, wxEXPAND);

	InitDefaultComponents();
}

auto cPreviewPanel::SetKETEKData
(
	unsigned long* const mcaData, 
	const unsigned long dataSize, 
	const unsigned long long sum
) -> void
{
	if (!mcaData) return;

	auto prevImageSize = m_ImageSize;

	if (dataSize != m_ImageSize.GetWidth())
	{
		// Veronika said that she needs only half of the whole spectrum, so we can display only half of the range
		m_ImageSize = wxSize(dataSize / 3, m_RBFinish.y - m_LUStart.y);
		//m_Image = wxImage(m_ImageSize.GetWidth(), m_ImageSize.GetHeight());
		m_ImageData = std::make_unique<unsigned long[]>(m_ImageSize.GetWidth());
	}
	else
	{
		//m_Image.Clear();
	}
	memcpy(m_ImageData.get(), mcaData, m_ImageSize.GetWidth() * sizeof(unsigned long));
	// Sending signal to wxThread, that we are done copying the data 
	mcaData[0] = ULONG_MAX - mcaData[0];

	double multiplicator{};
	auto maxValue = std::max_element(&m_ImageData[0], &m_ImageData[m_ImageSize.GetWidth()]);

	if (*maxValue)
	{
		m_MaxPosValueInData.first = std::distance(&m_ImageData[0], maxValue);
		m_MaxPosValueInData.second = *maxValue;
		multiplicator = abs((double)(m_ImageSize.GetHeight() - 1) / *maxValue);
		m_SumData = sum;
		m_MaxEventsCountOnGraph = *maxValue > m_MaxEventsCountOnGraph ? ((*maxValue + 9) / 10) * 10 : m_MaxEventsCountOnGraph;
		if (!m_ReferenceData)
			m_MaxEventsCountOnGraph = ((*maxValue + 9) / 10) * 10;
	}

	//LOGF("Multiplicator: ", multiplicator);

	/*
	Saving previous values for correct displaying of the image in the same place,
	where it was before capturing.
	*/
	{
		auto temp_zoom = m_Zoom;
		auto temp_pan_offset = m_PanOffset;
		auto temp_start_draw_pos = m_StartDrawPos;
		m_Zoom = 1.0;
		m_PanOffset = {};
		ChangeSizeOfImageInDependenceOnCanvasSize();

		if (m_IsImageSet)
		{
			m_Zoom = temp_zoom;
			m_PanOffset = temp_pan_offset;
			m_StartDrawPos = temp_start_draw_pos;
			if (prevImageSize != m_ImageSize)
			{
				m_Zoom = 1.0;
				m_PanOffset = {};
				m_StartDrawPos = m_NotZoomedGraphicsBitmapOffset;
			}
		}
	}

	m_IsImageSet = true;
	m_IsGraphicsBitmapSet = false;

	Refresh();
}

auto cPreviewPanel::SetKETEKReferenceData
(
	unsigned long* const mcaData, 
	const unsigned long dataSize, 
	const unsigned long long sum
) -> void
{
	if (!mcaData) return;

	auto prevImageSize = m_ImageSize;

	if (dataSize != m_ImageSize.GetWidth())
	{
		// Veronika said that she needs only half of the whole spectrum, so we can display only half of the range
		m_ImageSize = wxSize(dataSize / 3, m_RBFinish.y - m_LUStart.y);
		m_ReferenceData = std::make_unique<unsigned long[]>(m_ImageSize.GetWidth());
	}

	memcpy(m_ReferenceData.get(), mcaData, m_ImageSize.GetWidth() * sizeof(unsigned long));
	// Sending signal to wxThread, that we are done copying the data 
	mcaData[0] = ULONG_MAX - mcaData[0];

	auto maxValue = std::max_element(&m_ReferenceData[0], &m_ReferenceData[m_ImageSize.GetWidth()]);

	if (*maxValue)
	{
		m_MaxEventsCountOnGraph = *maxValue > m_MaxEventsCountOnGraph ? ((*maxValue + 9) / 10) * 10 : m_MaxEventsCountOnGraph;
	}

	/*
	Saving previous values for correct displaying of the image in the same place,
	where it was before capturing.
	*/
	{
		auto temp_zoom = m_Zoom;
		auto temp_pan_offset = m_PanOffset;
		auto temp_start_draw_pos = m_StartDrawPos;
		m_Zoom = 1.0;
		m_PanOffset = {};
		ChangeSizeOfImageInDependenceOnCanvasSize();

		if (m_IsImageSet)
		{
			m_Zoom = temp_zoom;
			m_PanOffset = temp_pan_offset;
			m_StartDrawPos = temp_start_draw_pos;
			if (prevImageSize != m_ImageSize)
			{
				m_Zoom = 1.0;
				m_PanOffset = {};
				m_StartDrawPos = m_NotZoomedGraphicsBitmapOffset;
			}
		}
	}

	m_IsImageSet = true;
	m_IsGraphicsBitmapSet = false;

	Refresh();

}

auto cPreviewPanel::SetBackgroundColor(wxColour bckg_colour) -> void
{
	SetBackgroundColour(bckg_colour);
}

auto cPreviewPanel::SetCrossHairButtonActive(bool activate) -> void
{
	m_CrossHairTool->ActivateToolButton(activate, activate);
	//m_CrossHairTool->SetCursorPosOnCanvas(m_CursorPosOnCanvas);
	ChangeCursorInDependenceOfCurrentParameters();
	Refresh();
}

auto cPreviewPanel::SetValueDisplayingActive(bool activate) -> void
{
	m_DisplayPixelValues = activate;
}

void cPreviewPanel::SetXCrossHairPosFromParentWindow(const int& x_pos)
{
	int corrected_x_pos = x_pos - 1;
	if (corrected_x_pos >= 0 && corrected_x_pos < m_ImageSize.GetWidth())
	{
		m_CrossHairPos.x = corrected_x_pos;
		m_CrossHairTool->SetXPosFromParent(corrected_x_pos);
		Refresh();
	}
}

void cPreviewPanel::SetYCrossHairPosFromParentWindow(const int& y_pos)
{
	int corrected_y_pos = y_pos - 1;
	if (corrected_y_pos >= 0 && corrected_y_pos < m_ImageSize.GetHeight())
	{
		m_CrossHairPos.y = corrected_y_pos;
		m_CrossHairTool->SetYPosFromParent(corrected_y_pos);
		Refresh();
	}
}

auto cPreviewPanel::SettingCrossHairPosFromParentWindow(bool set) -> void
{
	m_CrossHairTool->ActivateSetPositionFromParentWindow(set);
	//m_SettingCrossHairPos = set;
}

auto cPreviewPanel::InitializeSelectedCamera(const std::string& camera_sn) -> void
{
	//if (m_XimeaCameraControl->CloseCamera())
	//{
	//	m_SelectedCameraSN = camera_sn;
	//	m_XimeaCameraControl->InitializeCameraBySN(m_SelectedCameraSN);
	//}
}

void cPreviewPanel::SetCameraCapturedImage()
{
	/* 
	Saving previous values for correct displaying of the image in the same place, 
	where it was before capturing.
	*/
	{
		auto temp_zoom = m_Zoom;
		auto temp_pan_offset = m_PanOffset;
		auto temp_start_draw_pos = m_StartDrawPos;
		m_Zoom = 1.0;
		m_PanOffset = {};
		ChangeSizeOfImageInDependenceOnCanvasSize();
		if (m_IsImageSet)
		{
			m_Zoom = temp_zoom;
			m_PanOffset = temp_pan_offset;
			m_StartDrawPos = temp_start_draw_pos;
		}
	}

	/* CrossHair*/
	{
		m_CrossHairTool->SetImageDataType(ToolsVariables::DATA_U12);
		m_CrossHairTool->SetImageDimensions(m_ImageSize);
		m_CrossHairTool->SetZoomOfOriginalSizeImage(m_ZoomOnOriginalSizeImage);
		m_CrossHairTool->UpdateZoomValue(m_Zoom);
		m_CrossHairTool->SetImageStartDrawPos(wxRealPoint
		(
			m_StartDrawPos.x * m_Zoom / m_ZoomOnOriginalSizeImage,
			m_StartDrawPos.y * m_Zoom / m_ZoomOnOriginalSizeImage
		));
		//m_CrossHairTool->SetXPosFromParent(m_ImageSize.GetWidth() / 2);
		//m_CrossHairTool->SetYPosFromParent(m_ImageSize.GetHeight() / 2);
	}

	m_IsImageSet = true;
	m_IsGraphicsBitmapSet = false;
	Refresh();
}

void cPreviewPanel::CaptureAndSaveDataFromCamera
(
	const unsigned long& exposure_time_us, 
	const wxString& path, 
	const std::string& start_hours,
	const std::string& start_minutes,
	const std::string& start_seconds,
	const int& frame_number, 
	const float& first_axis_position, 
	const float& second_axis_position
)
{
	//auto image_ptr = m_XimeaCameraControl->GetImage();
	//if (!image_ptr) return;

	/* Save Captured Image */
	{
		std::string first_axis_position_str = std::format("{:.3f}", first_axis_position);
		std::replace(first_axis_position_str.begin(), first_axis_position_str.end(), '.', '_');

		std::string second_axis_position_str = std::format("{:.3f}", second_axis_position);
		std::replace(second_axis_position_str.begin(), second_axis_position_str.end(), '.', '_');
		
		const std::string file_name = std::string(path.mb_str()) + std::string("\\") +
			std::string("img_") + 
			std::to_string(frame_number) + std::string("_") + 
			start_hours + std::string("H_") + 
			start_minutes + std::string("M_") + 
			start_seconds + std::string("S_") + 
			std::to_string(exposure_time_us) + std::string("us") 
			+ std::string("_1A_") + first_axis_position_str 
			+ std::string("_2A_") + second_axis_position_str 
			+ std::string(".tif");

		//cv::Mat cv_img
		//(
		//	cv::Size(m_XimeaCameraControl->GetImageWidth(), m_XimeaCameraControl->GetImageHeight()),
		//	CV_8UC1, 
		//	image_ptr, 
		//	cv::Mat::AUTO_STEP
		//);
		//cv::imwrite(file_name, cv_img);
	}

	//SetCameraCapturedImage(image_ptr);
}

void cPreviewPanel::CalculateMatlabJetColormapPixelRGB8bit
(
	const unsigned char& value, 
	unsigned char& r, 
	unsigned char& g, 
	unsigned char& b
)
{
	unsigned char x0_8bit{ 31 }, x1_8bit{ 95 }, x2_8bit{ 159 }, x3_8bit{ 223 }, x4_8bit{ 255 };
	if (value < x0_8bit)
	{
		r = 0;
		g = 0;
		b = 255 * 0.51563f + (float)value * (255.0f - 255 * 0.51563f) / (float)x0_8bit;
	}
	else if (value >= x0_8bit && value <= x1_8bit)
	{
		r = 0;
		g = (float)(value - x0_8bit) * 255.0f / (float)(x1_8bit - x0_8bit);
		b = 255;
	}
	else if (value > x1_8bit && value < x2_8bit)
	{
		r = (float)(value - x1_8bit) * 255.0f / (float)(x2_8bit - x1_8bit);
		g = 255;
		b = (float)(x2_8bit - value) * 255.0f / (float)(x2_8bit - x1_8bit);
	}
	else if (value >= x2_8bit && value <= x3_8bit)
	{
		r = 255;
		g = (float)(x3_8bit - value) * 255.0f / (float)(x3_8bit - x2_8bit);
		b = 0;
	}
	else if (value > x3_8bit)
	{
		r = 255.0f * 0.5f + (float)(x4_8bit - value) * (255.0f - 255.0f * 0.5f) / (float)(x4_8bit - x3_8bit);
		g = 0;
		b = 0;
	}
}

void cPreviewPanel::CalculateMatlabJetColormapPixelRGB12bit(const unsigned short& value, unsigned char& r, unsigned char& g, unsigned char& b)
{
	unsigned short x0_12bit{ 498 }, x1_12bit{ 1526 }, x2_12bit{ 2553 }, x3_12bit{ 3581 }, x4_12bit{ 4095 };
	if (value < x0_12bit)
	{
		r = 0;
		g = 0;
		b = 255 * 0.51563f + (float)value * (255.0f - 255 * 0.51563f) / (float)x0_12bit;
	}
	else if (value >= x0_12bit && value <= x1_12bit)
	{
		r = 0;
		g = (float)(value - x0_12bit) * 255.0f / (float)(x1_12bit - x0_12bit);
		b = 255;
	}
	else if (value > x1_12bit && value < x2_12bit)
	{
		r = (float)(value - x1_12bit) * 255.0f / (float)(x2_12bit - x1_12bit);
		g = 255;
		b = (float)(x2_12bit - value) * 255.0f / (float)(x2_12bit - x1_12bit);
	}
	else if (value >= x2_12bit && value <= x3_12bit)
	{
		r = 255;
		g = (float)(x3_12bit - value) * 255.0f / (float)(x3_12bit - x2_12bit);
		b = 0;
	}
	else if (value > x3_12bit && value < x4_12bit)
	{
		r = 255.0f * 0.5f + (float)(x4_12bit - value) * (255.0f - 255.0f * 0.5f) / (float)(x4_12bit - x3_12bit);
		g = 0;
		b = 0;
	}
	else if (value == x4_12bit)
	{
		// Saturation (white)
		r = 255.f;
		g = 255.f;
		b = 255.f;
	}
}

void cPreviewPanel::CalculateMatlabJetColormapPixelRGB16bit
(
	const uint16_t& value, 
	unsigned char& r, 
	unsigned char& g, 
	unsigned char& b
)
{
	uint16_t x0{ 7967 }, x1{ 24415 }, x2{ 40863 }, x3{ 57311 }, x4{ 65535 };
	if (value < x0)
	{
		r = 0;
		g = 0;
		b = 255 * 0.51563f + (float)value * (255.0f - 255 * 0.51563f) / (float)x0;
	}
	else if (value >= x0 && value <= x1)
	{
		r = 0;
		g = (float)(value - x0) * 255.0f / (float)(x1 - x0);
		b = 255;
	}
	else if (value > x1 && value < x2)
	{
		r = (float)(value - x1) * 255.0f / (float)(x2 - x1);
		g = 255;
		b = (float)(x2 - value) * 255.0f / (float)(x2 - x1);
	}
	else if (value >= x2 && value <= x3)
	{
		r = 255;
		g = (float)(x3 - value) * 255.0f / (float)(x3 - x2);
		b = 0;
	}
	else if (value > x3)
	{
		r = 255.0f * 0.5f + (float)(x4 - value) * (255.0f - 255.0f * 0.5f) / (float)(x4 - x3);
		g = 0;
		b = 0;
	}
}

void cPreviewPanel::OnMouseMoved(wxMouseEvent& evt)
{
	if (!m_ImageData && !m_ReferenceData) return;

	//m_CursorPosOnCanvas.x = m_ZoomOnOriginalSizeImage * evt.GetPosition().x;
	//m_CursorPosOnCanvas.y = m_ZoomOnOriginalSizeImage * evt.GetPosition().y;
	m_CursorPosOnCanvas.x = evt.GetPosition().x;
	m_CursorPosOnCanvas.y = evt.GetPosition().y;


	/* Mouse position on Image */
	CalculatePositionOnImage();
	CheckIfMouseAboveImage();


	ChangeCursorInDependenceOfCurrentParameters();

	if (m_Panning)
	{
		ProcessPan(m_CursorPosOnCanvas, true);
		m_CrossHairTool->SetImageStartDrawPos(wxRealPoint
		(
			m_StartDrawPos.x * m_Zoom / m_ZoomOnOriginalSizeImage,
			m_StartDrawPos.y * m_Zoom / m_ZoomOnOriginalSizeImage
		));
	}

	if (m_CursorPosOnCanvas.x < m_LUStart.x || m_CursorPosOnCanvas.x > m_RBFinish.x) return;
	if (m_CursorPosOnCanvas.y < m_LUStart.y || m_CursorPosOnCanvas.y > m_RBFinish.y) return;
	Refresh();
}

void cPreviewPanel::OnMouseWheelMoved(wxMouseEvent& evt)
{
	if (m_Zoom <= 1.0 && evt.GetWheelRotation() < 0)
	{

	}
	else
	{
		// I don't want to enable zooming!!!
		return;
		//m_CursorPosOnCanvas = evt.GetPosition();
		if (evt.GetWheelRotation() > 0 && m_Zoom / m_ZoomOnOriginalSizeImage < 64.0)
		{
			AddZoom(2.0);
		}
		else if (evt.GetWheelRotation() < 0)
		{
			if (m_Zoom > 1.0)
			{
				AddZoom(0.5);
			}
		}
		/* CrossHair Tool */
		m_CrossHairTool->UpdateZoomValue(m_Zoom);
		m_CrossHairTool->CalculateCrossHairPositionOnCanvas();
		m_CrossHairTool->SetImageStartDrawPos(wxRealPoint
		(
			m_StartDrawPos.x * m_Zoom / m_ZoomOnOriginalSizeImage,
			m_StartDrawPos.y * m_Zoom / m_ZoomOnOriginalSizeImage
		));
	}
}

void cPreviewPanel::AddZoom(const double& zoom, bool zoom_in_center_of_window)
{
	wxRealPoint center = zoom_in_center_of_window ?
		wxRealPoint(GetSize().x / 2.0, GetSize().y / 2.0) :
		wxRealPoint(
			m_CursorPosOnCanvas.x,
			m_CursorPosOnCanvas.y);

	SetZoom(m_Zoom * zoom, center);
}

void cPreviewPanel::SetZoom(const double& zoom, const wxRealPoint& center_)
{
	wxRealPoint position_on_image{};
	position_on_image.x = (center_.x - m_PanOffset.x) / m_Zoom;
	position_on_image.y = (center_.y - m_PanOffset.y) / m_Zoom;

	m_Zoom = zoom;

	m_PanOffset.x = m_Zoom > 1.0 ? center_.x - position_on_image.x * m_Zoom : 0.0;
	m_PanOffset.y = m_Zoom > 1.0 ? center_.y - position_on_image.y * m_Zoom : 0.0;

	m_StartDrawPos.x = m_PanOffset.x / m_Zoom + m_NotZoomedGraphicsBitmapOffset.x;
	m_StartDrawPos.y = m_PanOffset.y / m_Zoom + m_NotZoomedGraphicsBitmapOffset.y;
	Refresh();
}

void cPreviewPanel::ProcessPan(const wxRealPoint& point_, bool refresh_)
{
	m_PanDeltaPoints = m_PanStartPoint - point_;
	//LOG2F("PanStartPoint x: ", m_PanStartPoint.x, " y: ", m_PanStartPoint.y);
	m_StartDrawPos.x = m_PanOffset.x / m_Zoom - m_PanDeltaPoints.x / m_Zoom + m_NotZoomedGraphicsBitmapOffset.x;
	m_StartDrawPos.y = m_PanOffset.y / m_Zoom - m_PanDeltaPoints.y / m_Zoom + m_NotZoomedGraphicsBitmapOffset.y;
	if (refresh_) Refresh();
}

void cPreviewPanel::FinishPan(bool refresh)
{
	if (m_Panning)
	{
		m_PanOffset.x -= m_PanDeltaPoints.x;
		m_PanOffset.y -= m_PanDeltaPoints.y;

		m_PanDeltaPoints = { 0.0, 0.0 };

		m_Panning = false;

		if (refresh) Refresh();
	}
}

void cPreviewPanel::CheckIfMouseAboveImage()
{
	m_IsCursorInsideImage = false;
	wxRealPoint cursor_pos_on_image =
	{
		m_CursorPosOnCanvas.x / m_Zoom - m_StartDrawPos.x,
		m_CursorPosOnCanvas.y / m_Zoom - m_StartDrawPos.y
	};
	if ((cursor_pos_on_image.x >= 0.0 &&
		(int)cursor_pos_on_image.x < m_ImageSize.GetWidth()) &&
		(cursor_pos_on_image.y >= 0.0 &&
			(int)cursor_pos_on_image.y < m_ImageSize.GetHeight()))
		m_IsCursorInsideImage = true;
}

void cPreviewPanel::CalculatePositionOnImage()
{
	m_NotCheckedCursorPosOnImage.x = m_CursorPosOnCanvas.x / m_Zoom - m_StartDrawPos.x;
	m_NotCheckedCursorPosOnImage.y = m_CursorPosOnCanvas.y / m_Zoom - m_StartDrawPos.y;

	/* Checking X */
	m_CheckedCursorPosOnImage.x = m_NotCheckedCursorPosOnImage.x >= 0.0 ? m_NotCheckedCursorPosOnImage.x : 0.0;
	m_CheckedCursorPosOnImage.x = m_NotCheckedCursorPosOnImage.x < (double)m_ImageSize.GetWidth() ? m_CheckedCursorPosOnImage.x : (double)m_ImageSize.GetWidth() - 1.0;
	/* Checking Y */
	m_CheckedCursorPosOnImage.y = m_NotCheckedCursorPosOnImage.y >= 0.0 ? m_NotCheckedCursorPosOnImage.y : 0.0;
	m_CheckedCursorPosOnImage.y = m_NotCheckedCursorPosOnImage.y < (double)m_ImageSize.GetHeight() ? m_CheckedCursorPosOnImage.y : (double)m_ImageSize.GetHeight() - 1.0;
}

void cPreviewPanel::OnPreviewMouseLeftPressed(wxMouseEvent& evt)
{
	if (m_ParentArguments->set_pos_tgl_btn->GetValue())
	{
		//m_CrossHairTool->SetXPosFromParent(m_CheckedCursorPosOnImage.x);
		//m_CrossHairTool->SetYPosFromParent(m_CheckedCursorPosOnImage.y);
		m_ParentArguments->x_pos_crosshair->SetValue(wxString::Format(wxT("%i"), (int)(m_CheckedCursorPosOnImage.x + 1)));
		m_ParentArguments->y_pos_crosshair->SetValue(wxString::Format(wxT("%i"), (int)(m_CheckedCursorPosOnImage.y + 1)));
		m_ParentArguments->set_pos_tgl_btn->SetValue(false);
		m_CrossHairTool->ActivateSetPositionFromParentWindow(false);
	}
	//else if (m_Zoom > 1.0 && m_IsCursorInsideImage && m_CrossHairTool->CanProcessPanning())
	else if (m_Zoom > 1.0 && m_IsCursorInsideImage)
	{
		m_Panning = true;
		m_PanStartPoint = m_CursorPosOnCanvas;
		ChangeCursorInDependenceOfCurrentParameters();
	}
}

void cPreviewPanel::OnPreviewMouseLeftReleased(wxMouseEvent& evt)
{
	if (m_Panning)
	{
		FinishPan(true);
		m_Panning = false;
	}
}

void cPreviewPanel::ChangeCursorInDependenceOfCurrentParameters()
{
	auto current_cursor = wxCURSOR_DEFAULT;

	/* CrossHair Tool */
	//current_cursor = m_SettingCrossHairPos ? wxCURSOR_QUESTION_ARROW : current_cursor;
	current_cursor = m_CrossHairTool->UpdateCursor(current_cursor);

	SetCursor(current_cursor);
}

void cPreviewPanel::DrawCrossHair(wxGraphicsContext* graphics_context)
{
	//graphics_context->SetPen(*wxRED_PEN);
	//m_CrossHairTool->DrawCrossHair(graphics_context, m_ImageData.get());
	//if (m_DisplayPixelValues)
	//	m_CrossHairTool->DrawPixelValues(graphics_context, m_ImageData.get());
}

void cPreviewPanel::InitDefaultComponents()
{
	//m_GraphicsBitmapImage = std::make_unique<wxGraphicsBitmap>();
	/* Tools */
	m_CrossHairTool = std::make_unique<CrossHairTool>
		(
			m_ParentArguments->x_pos_crosshair, 
			m_ParentArguments->y_pos_crosshair
		);
	//m_XimeaCameraControl = std::make_unique<XimeaControl>();
}

void cPreviewPanel::PaintEvent(wxPaintEvent& evt)
{
	wxBufferedPaintDC dc(this);
	Render(dc);
}

void cPreviewPanel::Render(wxBufferedPaintDC& dc)
{
	dc.Clear();
	wxGraphicsContext* gc_image{};
	gc_image = wxGraphicsContext::Create(dc);
	if (gc_image)
	{
		DrawReferenceData(gc_image, m_LUStart, m_RBFinish);
		DrawCapturedData(gc_image, m_LUStart, m_RBFinish);

		if (m_CursorPosOnCanvas.x >= m_LUStart.x && m_CursorPosOnCanvas.x <= m_RBFinish.x)
		{
			if (m_CursorPosOnCanvas.y >= m_LUStart.y && m_CursorPosOnCanvas.y <= m_RBFinish.y)
			{
				DrawVerticalLineBelowCursor(gc_image, m_LUStart, m_RBFinish);
				DrawReferenceValueBelowCursor(gc_image, m_LUStart, m_RBFinish);
				DrawCapturedValueBelowCursor(gc_image, m_LUStart, m_RBFinish);
			}
		}

		delete gc_image;

		wxGraphicsContext* gc_horizontal_ruller = wxGraphicsContext::Create(dc);
		if (gc_horizontal_ruller)
		{
			DrawHorizontalRuller(gc_horizontal_ruller, m_LUStart, m_RBFinish);
			delete gc_horizontal_ruller;
		}

		wxGraphicsContext* gc_vertical_ruller = wxGraphicsContext::Create(dc);
		if (gc_vertical_ruller)
		{
			DrawVerticalRuller(gc_vertical_ruller, m_LUStart, m_RBFinish);
			delete gc_vertical_ruller;
		}

		if (m_IsImageSet)
		{
			wxGraphicsContext* gc_max_value = wxGraphicsContext::Create(dc);
			if (gc_max_value)
			{
				DrawMaxValue(gc_max_value);
				delete gc_max_value;
			}

			wxGraphicsContext* gc_events_count = wxGraphicsContext::Create(dc);
			if (gc_events_count)
			{
				DrawSumEvents(gc_events_count);
				delete gc_events_count;
			}



			/* CrossHair */
			//wxGraphicsContext* gc_cross = wxGraphicsContext::Create(dc);
			//if (gc_cross)
			//{
			//	DrawCrossHair(gc_cross);
			//	delete gc_cross;
			//}
		}
	}
}

auto cPreviewPanel::AdjustKETEKImageMultithread
(
	const unsigned long* const data, 
	const double multiplicationValue,
	const int startX, 
	const int startY, 
	const int finishX, 
	const int finishY
) -> void
{
	if (!m_Image.IsOk()) return;
	int currentValue = 0U;
	unsigned char red{}, green{ 255 }, blue{};
	unsigned long long position_in_data_pointer{};
	auto imgHeight = m_ImageSize.GetHeight();
	int y{};

	for (auto x{ startX }; x < finishX; ++x)
	{
		currentValue = (int)(multiplicationValue * data[position_in_data_pointer]);
#ifdef _DEBUG
		//if (currentValue)
			//LOGI("Current Value: ", currentValue);

#endif // _DEBUG

		y = imgHeight - abs(currentValue) - 1;
		m_Image.SetRGB(x, y, red, green, blue);
		++position_in_data_pointer;
	}
}

void cPreviewPanel::CreateGraphicsBitmapImage(wxGraphicsContext* gc_)
{
	if (!m_IsGraphicsBitmapSet && m_IsImageSet)
	{
		if (m_Image.IsOk())
		{
			m_GraphicsBitmapImage = gc_->CreateBitmapFromImage(m_Image);
			m_IsGraphicsBitmapSet = true;
		}
	}
}

auto cPreviewPanel::DrawVerticalLineBelowCursor(wxGraphicsContext* gc, const wxRealPoint luStart, const wxRealPoint rbFinish) -> void
{
	if (!m_ImageData && !m_ReferenceData) return;

	gc->SetPen(*wxWHITE_PEN);
	// Draw vertical line
	{
		wxGraphicsPath path = gc->CreatePath();

		path.MoveToPoint
		(
			m_CursorPosOnCanvas.x,
			luStart.y
		);
		path.AddLineToPoint
		(
			m_CursorPosOnCanvas.x,
			rbFinish.y
		);
		gc->StrokePath(path);
	}


}

auto cPreviewPanel::DrawCapturedValueBelowCursor(wxGraphicsContext* gc, const wxRealPoint luStart, const wxRealPoint rbFinish) -> void
{
	if (!m_ImageData) return;

	wxFont font = wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	wxColour fontColour = wxColour(0, 255, 0, 100);
	gc->SetFont(font, fontColour);

	auto positionInData = (int)((m_CursorPosOnCanvas.x - luStart.x) * m_ImageSize.GetWidth() / (rbFinish.x - luStart.x));
	positionInData = positionInData < 0 ? 0 : positionInData;
	positionInData = positionInData >= m_ImageSize.GetWidth() ? m_ImageSize.GetWidth() - 1 : positionInData;

	// Draw value
	{
		wxString curr_value{};
		curr_value += "Energy: ";
		curr_value += wxString::Format(wxT("%.2f"), (double)positionInData * m_BinSize);
		curr_value += " Count: ";
		curr_value += wxString::Format(wxT("%lu"), m_ImageData[positionInData]);
		wxDouble widthText{}, heightText{};
		gc->GetTextExtent(curr_value, &widthText, &heightText);
		gc->DrawText
		(
			curr_value,
			m_CursorPosOnCanvas.x - widthText / 2.0,
			luStart.y - luStart.y / 4.0 - heightText
		);
	}

	gc->SetPen(wxPen(wxColour(200, 140, 255, 220)));
	// Draw Cross
	{
		auto crossWidth = 10.0;
		auto graphHeight = rbFinish.y - luStart.y;
		auto start_draw_y_position = rbFinish.y;
		auto current_y = graphHeight * (double)m_ImageData[positionInData] / (double)m_MaxEventsCountOnGraph;
		auto drawY = start_draw_y_position - current_y;
		gc->StrokeLine
		(
			m_CursorPosOnCanvas.x - crossWidth / 2.0,
			drawY - crossWidth / 2.0,
			m_CursorPosOnCanvas.x + crossWidth / 2.0,
			drawY + crossWidth / 2.0
		);

		gc->StrokeLine
		(
			m_CursorPosOnCanvas.x - crossWidth / 2.0,
			drawY + crossWidth / 2.0,
			m_CursorPosOnCanvas.x + crossWidth / 2.0,
			drawY - crossWidth / 2.0
		);
	}

}

auto cPreviewPanel::DrawReferenceValueBelowCursor(wxGraphicsContext* gc, const wxRealPoint luStart, const wxRealPoint rbFinish) -> void
{
	if (!m_ReferenceData) return;
	if (m_ReferenceBinSize < m_BinSize) return;

	wxFont font = wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	wxColour fontColour = wxColour(255, 0, 0, 100);
	gc->SetFont(font, fontColour);

	auto positionInData = (int)((m_CursorPosOnCanvas.x - luStart.x) * m_ImageSize.GetWidth() / (rbFinish.x - luStart.x));
	positionInData = positionInData < 0 ? 0 : positionInData;
	positionInData = positionInData >= m_ImageSize.GetWidth() ? m_ImageSize.GetWidth() - 1 : positionInData;

	// Draw value
	{
		wxString curr_value{};
		curr_value += "Energy: ";
		curr_value += wxString::Format(wxT("%.2f"), (double)positionInData * m_ReferenceBinSize);
		curr_value += " Count: ";
		curr_value += wxString::Format(wxT("%lu"), m_ReferenceData[positionInData]);
		wxDouble widthText{}, heightText{};
		gc->GetTextExtent(curr_value, &widthText, &heightText);
		gc->DrawText
		(
			curr_value,
			m_CursorPosOnCanvas.x - widthText / 2.0,
			luStart.y - luStart.y / 2.0 - heightText
		);
	}

	gc->SetPen(wxPen(wxColour(0, 255, 255, 220)));
	// Draw Cross
	{
		auto crossWidth = 10.0;
		auto graphHeight = rbFinish.y - luStart.y;
		auto start_draw_y_position = rbFinish.y;
		auto current_y = graphHeight * (double)m_ReferenceData[positionInData] / (double)m_MaxEventsCountOnGraph;
		auto drawY = start_draw_y_position - current_y;
		gc->StrokeLine
		(
			m_CursorPosOnCanvas.x - crossWidth / 2.0,
			drawY - crossWidth / 2.0,
			m_CursorPosOnCanvas.x + crossWidth / 2.0,
			drawY + crossWidth / 2.0
		);

		gc->StrokeLine
		(
			m_CursorPosOnCanvas.x - crossWidth / 2.0,
			drawY + crossWidth / 2.0,
			m_CursorPosOnCanvas.x + crossWidth / 2.0,
			drawY - crossWidth / 2.0
		);
	}
}

void cPreviewPanel::DrawCapturedData(wxGraphicsContext* gc, const wxRealPoint luStart, const wxRealPoint rbFinish)
{
	if (!m_ImageData) return;

	wxGraphicsPath path = gc->CreatePath();
	int start_draw_y_position{};
	double current_x{}, delta_x{}, current_y{};

	//auto offsetX = 50.0;
	//auto offsetY = 50.0;
	//auto graphHeight = GetSize().GetHeight() - 2 * offsetY;
	auto graphHeight = rbFinish.y - luStart.y;

	start_draw_y_position = rbFinish.y;

	delta_x = (rbFinish.x - luStart.x) / m_ImageSize.GetWidth();
	current_x = luStart.x;

	auto position_in_data = 0UL;;
	for (auto x{ 0 }; x < m_ImageSize.GetWidth() - 1; ++x)
	{
		current_y = graphHeight * (double)m_ImageData[position_in_data] / (double)m_MaxEventsCountOnGraph;
		path.MoveToPoint(current_x, (double)start_draw_y_position - current_y);
		current_x += delta_x;
		current_y = graphHeight * (double)m_ImageData[position_in_data + 1] / (double)m_MaxEventsCountOnGraph;
		path.AddLineToPoint(current_x, (double)start_draw_y_position - current_y);
		++position_in_data;
	}

	gc->SetPen(*wxGREEN_PEN);
	gc->DrawPath(path);
}

void cPreviewPanel::DrawReferenceData(wxGraphicsContext* gc, const wxRealPoint luStart, const wxRealPoint rbFinish)
{
	if (!m_ReferenceData) return;

	wxGraphicsPath path = gc->CreatePath();
	int start_draw_y_position{};
	double current_x{}, delta_x{}, current_y{};

	//auto offsetX = 50.0;
	//auto offsetY = 50.0;
	//auto graphHeight = GetSize().GetHeight() - 2 * offsetY;
	auto graphHeight = rbFinish.y - luStart.y;

	start_draw_y_position = rbFinish.y;

	if (m_ReferenceBinSize >= m_BinSize)
		delta_x = (rbFinish.x - luStart.x) / m_ImageSize.GetWidth();
	else
		return;

	current_x = luStart.x;

	auto position_in_data = 0UL;;
	for (auto x{ 0 }; x < m_ImageSize.GetWidth() - 1; ++x)
	{
		current_y = graphHeight * (double)m_ReferenceData[position_in_data] / (double)m_MaxEventsCountOnGraph;
		path.MoveToPoint(current_x, (double)start_draw_y_position - current_y);
		current_x += delta_x;
		current_y = graphHeight * (double)m_ReferenceData[position_in_data + 1] / (double)m_MaxEventsCountOnGraph;
		path.AddLineToPoint(current_x, (double)start_draw_y_position - current_y);
		++position_in_data;
	}

	gc->SetPen(*wxRED_PEN);
	gc->DrawPath(path);

}

auto cPreviewPanel::DrawMaxValue(wxGraphicsContext* gc) -> void
{
	if (!m_ImageData) return;

	auto screenWidth = GetSize().GetWidth();
	auto screenHeight = GetSize().GetHeight();
	auto incrementX = 10.0;
	auto startX = 20.0;
	auto startY = 70.0;

	wxFont font = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	wxColour fontColour = wxColour(160, 240, 180, 100);
	gc->SetFont(font, fontColour);

	// Draw value
	{
		wxString curr_value{};
		curr_value += "Energy: ";
		curr_value += wxString::Format(wxT("%.4f"), (double)m_MaxPosValueInData.first * m_BinSize);
		curr_value += " Counts: ";
		curr_value += wxString::Format(wxT("%lu"), m_MaxPosValueInData.second);
		wxDouble widthText{}, heightText{};
		gc->GetTextExtent(curr_value, &widthText, &heightText);
		gc->DrawText
		(
			curr_value,
			startX,
			startY - heightText
		);
	}
}

auto cPreviewPanel::DrawSumEvents(wxGraphicsContext* gc) -> void
{
	if (!m_ImageData) return;

	auto screenWidth = GetSize().GetWidth();
	auto screenHeight = GetSize().GetHeight();
	auto incrementX = 10.0;
	auto startX = 20.0;
	auto startY = 20.0;

	wxFont font = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	wxColour fontColour = wxColour(255, 128, 0, 100);
	gc->SetFont(font, fontColour);

	// Draw value
	{
		wxString curr_value{};
		curr_value += "Events: ";
		curr_value += wxString::Format(wxT("%llu"), m_SumData);
		wxDouble widthText{}, heightText{};
		gc->GetTextExtent(curr_value, &widthText, &heightText);
		gc->DrawText
		(
			curr_value,
			startX,
			startY
		);
	}

}

auto cPreviewPanel::DrawHorizontalRuller(wxGraphicsContext* gc, const wxRealPoint luStart, const wxRealPoint rbFinish) -> void
{
	if (!m_ImageData && !m_ReferenceData) return;

	wxColour fontColour = wxColour(0, 162, 232, 200);
	gc->SetPen(wxPen(fontColour));
	// Draw horizontal line
	{
		wxGraphicsPath path = gc->CreatePath();

		path.MoveToPoint
		(
			luStart.x,
			rbFinish.y + (GetSize().GetHeight() - rbFinish.y) / 2
		);
		path.AddLineToPoint
		(
			rbFinish.x,
			rbFinish.y + (GetSize().GetHeight() - rbFinish.y) / 2
		);
		gc->StrokePath(path);
	}

	wxFont font = wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	gc->SetFont(font, fontColour);

	// Draw scale values
	{
		wxString curr_value{};
		wxDouble widthText{}, heightText{};
		auto scaleValuesNumber = 10;
		auto scaleFactor = m_BinSize == 0.0 ? m_ImageSize.GetWidth() * m_ReferenceBinSize / scaleValuesNumber : m_ImageSize.GetWidth() * m_BinSize / scaleValuesNumber;
		for (auto i{ 0 }; i <= scaleValuesNumber; ++i)
		{
			curr_value = wxString::Format(wxT("%.2f"), (double)(i * scaleFactor));
			gc->GetTextExtent(curr_value, &widthText, &heightText);
			gc->DrawText
			(
				curr_value,
				luStart.x + i * (rbFinish.x - luStart.x) / scaleValuesNumber - widthText / 2.0,
				rbFinish.y + (GetSize().GetHeight() - rbFinish.y) / 8
			);

			gc->StrokeLine
			(
				luStart.x + i * (rbFinish.x - luStart.x) / scaleValuesNumber,
				rbFinish.y + (GetSize().GetHeight() - rbFinish.y) / 2 - (GetSize().GetHeight() - rbFinish.y) / 12.0,
				luStart.x + i * (rbFinish.x - luStart.x) / scaleValuesNumber,
				rbFinish.y + (GetSize().GetHeight() - rbFinish.y) / 2
			);
		}
	}

	// Draw [keV]
	{
		wxString curr_value{};
		curr_value = "[keV]";
		wxDouble widthText{}, heightText{};
		gc->GetTextExtent(curr_value, &widthText, &heightText);
		gc->DrawText
		(
			curr_value,
			luStart.x + (rbFinish.x - luStart.x) / 2.0 - widthText / 2.0,
			rbFinish.y + (GetSize().GetHeight() - rbFinish.y) * 3 / 4.0 - heightText / 2.0
		);
	}
}

auto cPreviewPanel::DrawVerticalRuller(wxGraphicsContext* gc, const wxRealPoint luStart, const wxRealPoint rbFinish) -> void
{
	if (!m_ImageData && !m_ReferenceData) return;

	wxColour fontColour = wxColour(0, 162, 232, 200);
	gc->SetPen(wxPen(fontColour));

	// Draw vertical line
	{
		wxGraphicsPath path = gc->CreatePath();

		path.MoveToPoint
		(
			luStart.x / 2.0,
			luStart.y
		);
		path.AddLineToPoint
		(
			luStart.x / 2.0,
			rbFinish.y
		);
		gc->StrokePath(path);
	}

	wxFont font = wxFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	gc->SetFont(font, fontColour);

	// Draw scale values
	wxString curr_value{};
	wxDouble widthText{}, heightText{};
	{
		auto scaleValuesNumber = 10;
		auto scaleFactor = m_MaxEventsCountOnGraph / scaleValuesNumber;
		for (auto i{ 0 }; i <= scaleValuesNumber; ++i)
		{
			curr_value = wxString::Format(wxT("%i"), (int)(i * scaleFactor));
			gc->GetTextExtent(curr_value, &widthText, &heightText);
			gc->DrawText
			(
				curr_value,
				luStart.x / 2.0 + luStart.x / 4.0,
				rbFinish.y - heightText / 2.0 - i * (m_RBFinish.y - m_LUStart.y) / scaleValuesNumber
			);

			// Stroking horizontal line
			gc->StrokeLine
			(
				luStart.x / 2.0,
				rbFinish.y - i * (m_RBFinish.y - m_LUStart.y) / scaleValuesNumber,
				luStart.x / 2.0 + luStart.x / 12.0,
				rbFinish.y - i * (m_RBFinish.y - m_LUStart.y) / scaleValuesNumber
			);
		}
	}

	// Draw Value of the Left side of the image
	{
		curr_value = "[Events]";
		gc->GetTextExtent(curr_value, &widthText, &heightText);
		wxRealPoint draw_point =
		{
			luStart.x / 4 - heightText / 2,
			luStart.y + (rbFinish.y - luStart.y) / 2 + widthText / 2.0
		};

		// Set up the transformation matrix for a 90-degree counterclockwise rotation
		gc->Translate(draw_point.x, draw_point.y);
		gc->Rotate(-M_PI / 2.0); // Rotate 90 degrees counterclockwise (pi/2 radians)
		gc->Translate(-draw_point.x, -draw_point.y);
		gc->DrawText(curr_value, draw_point.x, draw_point.y);
	}

}

void cPreviewPanel::OnSize(wxSizeEvent& evt)
{
	int newWidth{ evt.GetSize().x }, newHeight{ evt.GetSize().y };
	if (newWidth != m_CanvasSize.GetWidth() || newHeight != m_CanvasSize.GetHeight())
	{
		m_CanvasSize.SetWidth(newWidth);
		m_CanvasSize.SetHeight(newHeight);
		m_Zoom = 1.0;
		m_PanOffset = {};
		ChangeSizeOfImageInDependenceOnCanvasSize();
		UpdateCrossHairOnSize();
		m_IsGraphicsBitmapSet = false;
		m_LUStart = { GetSize().GetWidth() / 10.0, GetSize().GetHeight() / 10.0 };
		m_RBFinish = { GetSize().GetWidth() * 9 / 10.0, GetSize().GetHeight() * 9 / 10.0 };
		Refresh();
	}
}

void cPreviewPanel::ChangeSizeOfImageInDependenceOnCanvasSize()
{
	wxSize current_image_size{ m_ImageSize };
	wxSize canvas_size{ GetSize().GetWidth(), GetSize().GetHeight() };
	m_ZoomOnOriginalSizeImage = 1.0;
	while (canvas_size.GetWidth() < current_image_size.GetWidth() || canvas_size.GetHeight() < current_image_size.GetHeight())
	{
		current_image_size.SetWidth(current_image_size.GetWidth() / 2);
		current_image_size.SetHeight(current_image_size.GetHeight() / 2);
		m_ZoomOnOriginalSizeImage *= 2.0;
	}
	m_ImageOnCanvasSize.Set(current_image_size.GetWidth(), current_image_size.GetHeight());
	m_CrossHairTool->SetImageOnCanvasSize(current_image_size);
	m_NotZoomedGraphicsBitmapOffset.x = (canvas_size.GetWidth() - m_ImageOnCanvasSize.GetWidth()) / 2;
	m_NotZoomedGraphicsBitmapOffset.y = (canvas_size.GetHeight() - m_ImageOnCanvasSize.GetHeight()) / 2;
	m_NotZoomedGraphicsBitmapOffset.x *= m_ZoomOnOriginalSizeImage / m_Zoom;
	m_NotZoomedGraphicsBitmapOffset.y *= m_ZoomOnOriginalSizeImage / m_Zoom;
	m_StartDrawPos = m_NotZoomedGraphicsBitmapOffset;

}

auto cPreviewPanel::UpdateCrossHairOnSize() -> void
{
	m_CrossHairTool->SetImageDimensions(m_ImageSize);
	m_CrossHairTool->SetZoomOfOriginalSizeImage(m_ZoomOnOriginalSizeImage);
	m_CrossHairTool->UpdateZoomValue(m_Zoom);
	m_CrossHairTool->SetImageStartDrawPos(wxRealPoint
	(
		m_StartDrawPos.x * m_Zoom / m_ZoomOnOriginalSizeImage,
		m_StartDrawPos.y * m_Zoom / m_ZoomOnOriginalSizeImage
	));
	m_CrossHairTool->SetXPosFromParent(m_CrossHairPos.x);
	m_CrossHairTool->SetYPosFromParent(m_CrossHairPos.y);
}

