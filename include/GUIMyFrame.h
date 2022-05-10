#ifndef __GUIMyFrame__
#define __GUIMyFrame__

/**
@file
Subclass of MyFrame, which is generated by wxFormBuilder.
*/

#include "GUI.h"

//// end generated include
#include <iostream>
#include <wx/filedlg.h>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <string>
#include <wx/dirdlg.h>

struct Frame
{
	int Time;
	wxImage Image;
	Frame(sf::Image &img, int time);
};
/** Implementing MyFrame */
class GUIMyFrame : public MyFrame
{
	protected:
		// Handlers for MyFrame events.
		void ChangeSizeOfAnimation( wxMoveEvent& event );
		void Repaint_AnimationPanel( wxUpdateUIEvent& event );
		void ChangeSizeOfProgressSlider( wxMoveEvent& event );
		void Repaint_ProgressSlider( wxUpdateUIEvent& event );
		void OnSlide_AnimationSpeed( wxScrollEvent& event );
		void OnClick_RewindAnimation( wxCommandEvent& event );
		void OnClick_PlayStopAnimation( wxCommandEvent& event );
		void OnClick_GoForwardAnimation( wxCommandEvent& event );
		void OnClick_RestartAnimation( wxCommandEvent& event );
		void OnClick_OpenFileOnMenuSelection( wxCommandEvent& event );
		void OnClick_SaveAnimationToFile( wxCommandEvent& event );
	public:
		/** Constructor */
		GUIMyFrame( wxWindow* parent );
	//// end generated class members

		bool ReadDataToVector(const char *FileName);
		void SaveAnimationToDir(wxString DirPath);
		void setButtonsActive(bool active);

	private:
		std::vector<Frame> Animation;
		bool AnimationIsReady;
};

#endif // __GUIMyFrame__
