#include "GUIMyFrame.h"

GUIMyFrame::GUIMyFrame( wxWindow* parent )
:
	MyFrame(parent), AnimationState{ States::NoInBuffer },
	ShowBg{ false }, FileNumeration{ false }, FileName{ "output" }
{
}


void GUIMyFrame::Notify()
{
	if (currentFrame >= Animation.size()-1)
	{
		Stop();
		AnimationState = States::AfterDisplay;
		currentFrame = 0;
		return;
	}
	currentFrame++;
	Start(Animation[currentFrame].Time * speedMultiplier);
	Repaint();
}



void GUIMyFrame::Repaint()
{
	wxClientDC temp(AnimationPanel);
	sf::RenderWindow Panel((HWND)AnimationPanel->GetHandle());

	switch (AnimationState)
	{
	case States::NoInBuffer:
		temp.Clear();
		temp.DrawText("No animations in buffer, please load one from a file", width / 2 - 120, height / 2 - 10);
		break;

	case States::LoadingToBuffer:
		temp.Clear();
		temp.DrawText("Loading the animation", width / 2 - 100, height / 2 - 10);
		break;

	case States::ReadyToDisplay:
		temp.Clear();
		temp.DrawText("Ready to display, press the \"play\" button", width / 2 - 140, height / 2 - 10);
		break;

	case States::DuringDisplay:
	case States::DisplayStopped:
		Panel.clear(sf::Color::White);

		if (ShowBg == true)
		{
			sf::Texture temp;
			temp.loadFromImage(Background);

			Panel.draw(sf::Sprite(temp));
		}
		Panel.draw(sf::Sprite(Animation[currentFrame].Image));
		Panel.display();
		break;

	case States::AfterDisplay:
		temp.Clear();
		temp.DrawText("Animation has ended, press the \"replay\" to \nplay it again or select a different one", width / 2 - 140, height / 2 - 20);
		break;
	}
}


void GUIMyFrame::Repaint_AnimationPanel( wxUpdateUIEvent& event )
{
// TODO: Implement Repaint_AnimationPanel
	Repaint();
}


void GUIMyFrame::OnSlide_AnimationSpeed( wxScrollEvent& event )
{
// TODO: Implement OnSlide_AnimationSpeeds
	int sliderPosition = ChoiceSpeed->GetValue();

	if (sliderPosition == 0)
	{
		speedMultiplier = 16;
	}
	else if (sliderPosition == 1)
	{
		speedMultiplier = 8;
	}
	else if (sliderPosition == 2)
	{
		speedMultiplier = 4;
	}
	else if (sliderPosition == 3)
	{
		speedMultiplier = 2;
	}
	else if (sliderPosition == 4)
	{
		speedMultiplier = 1;
	}
	else if (sliderPosition == 5)
	{
		speedMultiplier = 0.5;
	}
	else if (sliderPosition == 6)
	{
		speedMultiplier = 0.25;
	}
	else
	{
		speedMultiplier = 0.125;
	}
}

void GUIMyFrame::OnClick_RewindAnimation( wxCommandEvent& event )
{
// TODO: Implement OnClick_RewindAnimation
	if (currentFrame > 4) currentFrame -= 5;
	else currentFrame = 0;
	Repaint();
}

void GUIMyFrame::OnClick_PlayStopAnimation( wxCommandEvent& event )
{
// TODO: Implement OnClick_PlayStopAnimation

	switch (AnimationState)
	{
	case States::ReadyToDisplay:

		AnimationState = States::DuringDisplay;
		Repaint();
		Start(Animation[currentFrame].Time);
		AnimationReplay->Enable(true);

		PlayAndStop->SetLabel(_T("pause"));

		break;
	case States::DuringDisplay:

		AnimationState = States::DisplayStopped;
		Stop();

		PlayAndStop->SetLabel(_T("play"));

		break;
	case States::DisplayStopped:

		AnimationState = States::DuringDisplay;
		Repaint();
		Start(Animation[currentFrame].Time);
		AnimationReplay->Enable(true);

		PlayAndStop->SetLabel(_T("pause"));

		break;
	}

}

void GUIMyFrame::OnClick_GoForwardAnimation( wxCommandEvent& event )
{
// TODO: Implement OnClick_GoForwardAnimation
	if (currentFrame < Animation.size() - 6) currentFrame += 5;
	else currentFrame = Animation.size() - 1;
	Repaint();
}

void GUIMyFrame::OnClick_RestartAnimation( wxCommandEvent& event )
{
// TODO: Implement OnClick_RestartAnimation
	AnimationState = States::ReadyToDisplay;
	currentFrame = 0;
	Start(Animation[currentFrame].Time);
	Repaint();
	AnimationReplay->Enable(false);
	PlayAndStop->SetLabel(_T("play"));
}

void GUIMyFrame::OnClick_OpenFileOnMenuSelection(wxCommandEvent& event)
{
	// TODO: Implement OnClick_OpenFileOnMenuSelection
	Stop();
	if (ReadingFileOption->FindItemByPosition(1)->IsChecked())
	{
		wxFileDialog OpenFileDialog(this, wxT("Choose a files"), wxT(""), wxT(""), wxT(""), wxFD_MULTIPLE | wxFD_FILE_MUST_EXIST);


		if (OpenFileDialog.ShowModal() == wxID_OK)
		{
			Animation.clear();
			AnimationState = States::LoadingToBuffer;
			setButtonsActive();
			wxArrayString Images;
			OpenFileDialog.GetPaths(Images);
			Images.Sort();
			if (ReadImagesToVector(Images)) AnimationState = States::ReadyToDisplay;
		}
	}
	else
	{
		wxFileDialog OpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Text file (*.txt)|*.txt"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

		if (OpenFileDialog.ShowModal() == wxID_OK)
		{
			Animation.clear();
			AnimationState = States::LoadingToBuffer;
			setButtonsActive();
			if (ReadingFileOption->FindItemByPosition(0)->IsChecked())
			{
				if (ReadDataToVector(OpenFileDialog.GetPath())) AnimationState = States::ReadyToDisplay;
			}
			else
			{
				if (Read3DToVector(OpenFileDialog.GetPath())) AnimationState = States::ReadyToDisplay;
			}
		}
	}
	currentFrame = 0;
	setButtonsActive();
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
	GUIOtherSettings dialog(this, this);
	dialog.ShowModal();
}