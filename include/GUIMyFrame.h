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
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <wx/dirdlg.h>
#include <wx/dcclient.h>
#include <wx/colordlg.h>
#include <sstream>
#include <iomanip>
#include "GUIOtherSettings.h"
#include <thread>
#include <functional>
#include <memory>
#include <wx/timer.h>
#include <wx/dcclient.h>



/**
 * @brief structure which contains a single frame, which consists of duration time and image
 * 
 * @param Time duration time of a frame
 * @param Image a texture containing loaded image
 */
struct Frame
{
	int Time;
	sf::Texture Image;
	Frame(sf::RenderTexture &buf, int time);
	Frame(sf::Texture &img, int time);
};

/**
 * @brief class handling the application, user interactions, showing animations on the screen and allowing the user to save the animation to a chosen folder
 * 
 * @param Animation a vector containing all the loaded frames
 * @param ReadingOption w.e
 * @param States an enum container holding various states in which the program can be
 * @param AnimationState current state of the application
 * @param ShowBg defines whether the background should be shown
 * @param Background contains the background
 * @param FileNumeration determines whether there is a prefix in the numeration of the files which are being saved (if true - 0001, 0002, 0003, 0004, else - 1, 2, 3, 4)
 * @param FileName name of the saved file
 * @param weight width of the frame
 * @param height height of the frame
 * 	
 */
class GUIMyFrame : public MyFrame, public wxTimer
{
	protected:
		// Handlers for MyFrame events.

		/**
		 * @brief calls for Repaint() method
		 * 
		 * @param event event called by wxWidgets to update GUI
		 */
		void Repaint_AnimationPanel( wxUpdateUIEvent& event );

		/**
		 * @brief defines the speed @ which the animation should be played by reading the slider position
		 * 
		 * @param event slider position change
		 */
		void OnSlide_AnimationSpeed( wxScrollEvent& event );

		/**
		 * @brief replay the animation from the beginning
		 * 
		 * @param event replay button click
		 */
		void OnClick_RewindAnimation( wxCommandEvent& event );

		/**
		 * @brief play/pause the animation
		 * 
		 * @param event play/pause button click
		 */
		void OnClick_PlayStopAnimation( wxCommandEvent& event );

		/**
		 * @brief skip a few frames - forwards  //few = tbd
		 * 
		 * @param event forward button click
		 */
		void OnClick_GoForwardAnimation( wxCommandEvent& event );

		/**
		 * @brief skip a few frames - backwards //few = tbd
		 * 
		 * @param event backwards button click
		 */
		void OnClick_RestartAnimation( wxCommandEvent& event );

		/**
		 * @brief depending on the state of @ReadingFileOption variable selects the type of reading the animation, then opens a dialog box which allows to select an animation file
		 * 
		 * @param event File -> Open button click
		 */
		void OnClick_OpenFileOnMenuSelection( wxCommandEvent& event );

		/**
		 * @brief saves all the frames from the Animation vector using multithreading
		 * 
		 * @param event File -> Save button click
		 */
		void OnClick_SaveAnimationToFile( wxCommandEvent& event );

		/**
		 * @brief sets background color of the dialog box
		 * 
		 * @param event Settings -> Background color -> color selection -> OK
		 */
		void OnClick_SetBacgroundColor(wxCommandEvent& event);

		/**
		 * @brief opens "Other settings" dialog box
		 * 
		 * @param event Settings -> Other settings button click
		 */
		void OnClick_ShowSavingOptions(wxCommandEvent& event);

	public:
		/**
		 * @brief Construct a new GUIMyFrame object
		 * 
		 * @param parent wxWindow of instance higher to the main window of our application
		 */
		GUIMyFrame( wxWindow* parent );
	////

		friend class GUIOtherSettings;
	private:
		std::vector<Frame> Animation;
		bool ReadingOption;
		enum class States{ NoInBuffer, LoadingToBuffer, ReadyToDisplay, DuringDisplay, AfterDisplay, DisplayStopped };
		States AnimationState;
		bool ShowBg = false;
		sf::Image Background;
		bool FileNumeration;
		std::string FileName;
		int width = 800, height = 600;
		int currentFrame = 0;
		int sliderPosition = 4;
		double speedMultiplier = 1;


		/**
		 * @brief method which saves the animation to a specified folder
		 * 
		 * @param DirPath path to a folder in which the animation should be saved
		 */
		void SaveAnimationToDir(const char *DirPath);

		/**
		 * @brief enable/disable buttons basing on the state of @AnimationState
		 * 
		 */
		void setButtonsActive();

		/**
		 * @brief reads images to a @Animation vector in alphanumerical order
		 * 
		 * @param paths paths to said images
		 * @return true - reading successful and data saved to vector
		 * @return false - reading unsuccessful
		 */
		bool ReadImagesToVector(wxArrayString &paths);

		/**
		 * @brief reads commands from .txt file and creates frames
		 * 
		 * @param FileName path to said .txt file
		 * @return true - reading successful and data saved to vector
		 * @return false - reading unsuccessful
		 */
		bool ReadDataToVector(const char *FileName);

		/**
		 * @brief reads 3D commands from .txt file and creates frames
		 * 
		 * @param FileName path to said .txt file
		 * @return true - reading successful and data saved to vector
		 * @return false - reading unsuccessful
		 */
		bool Read3DToVector(const char* FileName);

		/**
		 * @brief method responsible for displaying images on the screen
		 * 
		 */
		void Repaint();

		void Notify() override;
};

#endif // __GUIMyFrame__
