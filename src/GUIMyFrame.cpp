#include "GUIMyFrame.h"

GUIMyFrame::GUIMyFrame( wxWindow* parent )
:
MyFrame( parent ), Panel{ (HWND)AnimationPanel->GetHandle() }
{
	wxMenu *ReadingFileOption = new wxMenu();
	ReadingFileOption->Append(wxID_ANY, _("Command file"), _(""), wxITEM_RADIO);
	ReadingFileOption->Append(wxID_ANY, _("Image"), _(""), wxITEM_RADIO);

	wxMenuItem* ReadingFileOptionItem = new wxMenuItem( SettingsBar, wxID_ANY, wxT("Read animation from..."), wxEmptyString, wxITEM_NORMAL, ReadingFileOption);
	SettingsBar->Append( ReadingFileOptionItem );
	SettingsBar->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUIMyFrame::IfChecked_setReadTXT), this, ReadingFileOption->FindItemByPosition(0)->GetId());
	SettingsBar->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(GUIMyFrame::IfChecked_setReadImage), this, ReadingFileOption->FindItemByPosition(1)->GetId());

	ReadingOption = AnimationIsReady = false;
}

void GUIMyFrame::ChangeSizeOfAnimation( wxMoveEvent& event )
{
// TODO: Implement ChangeSizeOfAnimation
}

void GUIMyFrame::Repaint_AnimationPanel( wxUpdateUIEvent& event )
{
// TODO: Implement Repaint_AnimationPanel
}

void GUIMyFrame::ChangeSizeOfProgressSlider( wxMoveEvent& event )
{
// TODO: Implement ChangeSizeOfProgressSlider
}

void GUIMyFrame::Repaint_ProgressSlider( wxUpdateUIEvent& event )
{
// TODO: Implement Repaint_ProgressSlider
}

void GUIMyFrame::OnSlide_AnimationSpeed( wxScrollEvent& event )
{
// TODO: Implement OnSlide_AnimationSpeed
}

void GUIMyFrame::OnClick_RewindAnimation( wxCommandEvent& event )
{
// TODO: Implement OnClick_RewindAnimation
}

void GUIMyFrame::OnClick_PlayStopAnimation( wxCommandEvent& event )
{
// TODO: Implement OnClick_PlayStopAnimation
}

void GUIMyFrame::OnClick_GoForwardAnimation( wxCommandEvent& event )
{
// TODO: Implement OnClick_GoForwardAnimation
}

void GUIMyFrame::OnClick_RestartAnimation( wxCommandEvent& event )
{
// TODO: Implement OnClick_RestartAnimation
}

void GUIMyFrame::OnClick_OpenFileOnMenuSelection(wxCommandEvent& event)
{
	// TODO: Implement OnClick_OpenFileOnMenuSelection
	wxFileDialog OpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Text file (*.txt)|*.txt"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (OpenFileDialog.ShowModal() == wxID_OK)
	{
		AnimationIsReady = ReadDataToVector(OpenFileDialog.GetFilename());
		setButtonsActive(AnimationIsReady);
	}
}

void GUIMyFrame::OnClick_SaveAnimationToFile( wxCommandEvent& event )
{
// TODO: Implement OnClick_SaveAnimationToFile
	wxDirDialog OpenDirDialog(this, _("Choose a directory"), "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
	if (OpenDirDialog.ShowModal() == wxID_OK)
		SaveAnimationToDir(OpenDirDialog.GetPath());
}

void GUIMyFrame::OnClick_SetBacgroundColor(wxCommandEvent& event)
{
	// TODO: Implement OnClick_SetBacgroundColor
	wxColourDialog ChooseColor(this);
	if (ChooseColor.ShowModal() == wxID_OK)
		this->SetBackgroundColour(ChooseColor.GetColourData().GetColour());
	Refresh();
}

void GUIMyFrame::OnClick_ShowSavingOptions(wxCommandEvent& event)
{
	// TODO: Implement OnClick_ShowSavingOptions
}

void GUIMyFrame::IfChecked_setReadTXT(wxCommandEvent& event)
{
	ReadingOption = false;
}

void GUIMyFrame::IfChecked_setReadImage(wxCommandEvent& event)
{
	ReadingOption = true;
}