#include <wx/wx.h>
#include "ImageSlideshow.h"
#include "VideoPlayer.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MainFrame : public wxFrame {
public:
    MainFrame();

private:
    void OnImageSlideshow(wxCommandEvent& event);
    void OnVideoPlayer(wxCommandEvent& event);

    wxPanel* mainPanel; // Main panel
    ImageSlideshow* slideshow; // Image slideshow panel
    VideoPlayer* videoPlayer; // Video player panel
};

bool MyApp::OnInit() {
    MainFrame* frame = new MainFrame();
    frame->Show(true);
    return true;
}

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "Glo Entertainment App", wxDefaultPosition, wxSize(800, 600)) {

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL); //box to hold diff panels.

    mainPanel = new wxPanel(this, wxID_HIGHEST + 1);
    mainPanel->SetBackgroundColour(*wxLIGHT_GREY);

    
    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    
    
    panelSizer->AddStretchSpacer(1); // heading bring down.

    // Heading
    wxStaticText* heading = new wxStaticText(mainPanel, wxID_ANY, "Glo Entertainment App", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    heading->SetFont(font);
    panelSizer->Add(heading, 0, wxALL | wxALIGN_CENTER, 10); // Center heading

    // Buttons
    wxButton* imageSlideshowButton = new wxButton(mainPanel, wxID_ANY, "Image Slideshow");
    wxButton* videoPlayerButton = new wxButton(mainPanel, wxID_ANY, "Video Player");


    imageSlideshowButton->Bind(wxEVT_BUTTON, &MainFrame::OnImageSlideshow, this);
    videoPlayerButton->Bind(wxEVT_BUTTON, &MainFrame::OnVideoPlayer, this);

    
    panelSizer->Add(imageSlideshowButton, 0, wxALL | wxALIGN_CENTER, 10); // Center button
    panelSizer->Add(videoPlayerButton, 0, wxALL | wxALIGN_CENTER, 10); // Center button

   
    panelSizer->AddStretchSpacer(1); // Space below the buttons

    
    mainPanel->SetSizer(panelSizer);

   
    slideshow = new ImageSlideshow(this);
    videoPlayer = new VideoPlayer(this);
    
    // hide image and video
    slideshow->Hide();
    videoPlayer->Hide();

    // Add panels to the main sizer
    mainSizer->Add(mainPanel, 1, wxEXPAND | wxALL, 5); 
    mainSizer->Add(slideshow, 1, wxEXPAND | wxALL, 5); 
    mainSizer->Add(videoPlayer, 1, wxEXPAND | wxALL, 5); 

    SetSizer(mainSizer);
}

void MainFrame::OnImageSlideshow(wxCommandEvent& event) {
    mainPanel->Hide();  
    slideshow->Show();  
    Layout(); 
}

void MainFrame::OnVideoPlayer(wxCommandEvent& event) {
    mainPanel->Hide(); 
    videoPlayer->Show(); 
    Layout();
}

wxIMPLEMENT_APP(MyApp);
