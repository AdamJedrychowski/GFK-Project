#include "GUIMyFrame.h"

GUIMyFrame::GUIMyFrame( wxWindow* parent )
:
MyFrame( parent )
{
	AnimationIsReady = false;
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
}
