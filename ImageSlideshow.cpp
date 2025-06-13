#include "ImageSlideshow.h"

ImageSlideshow::ImageSlideshow(wxFrame* parent)
    : wxPanel(parent, wxID_ANY), m_currentImageIndex(0), m_slideshowActive(false),
      m_timer(new wxTimer(this)) 
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    m_scrolledWindow = new wxScrolledWindow(this, wxID_ANY);
    wxBoxSizer* imageSizer = new wxBoxSizer(wxHORIZONTAL);
    m_staticBitmap = new wxStaticBitmap(m_scrolledWindow, wxID_ANY, wxBitmap());
    imageSizer->Add(m_staticBitmap, 1, wxEXPAND | wxALL, 5);
    m_scrolledWindow->SetSizer(imageSizer);

    // create buttons
    wxButton* uploadButton = new wxButton(this, wxID_ANY, "Upload Images");
    uploadButton->Bind(wxEVT_BUTTON, &ImageSlideshow::OnUpload, this);

    wxButton* prevButton = new wxButton(this, wxID_ANY, "Previous");
    prevButton->Bind(wxEVT_BUTTON, &ImageSlideshow::OnPrev, this);

    wxButton* nextButton = new wxButton(this, wxID_ANY, "Next");
    nextButton->Bind(wxEVT_BUTTON, &ImageSlideshow::OnNext, this);

    wxButton* slideshowButton = new wxButton(this, wxID_ANY, "Start Slideshow");
    slideshowButton->Bind(wxEVT_BUTTON, &ImageSlideshow::OnToggleSlideshow, this);

    // adding buttons to main sizer
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(uploadButton, 0, wxALL, 5);
    buttonSizer->Add(prevButton, 0, wxALL, 5);
    buttonSizer->Add(nextButton, 0, wxALL, 5);
    buttonSizer->Add(slideshowButton, 0, wxALL, 5);

    mainSizer->Add(m_scrolledWindow, 1, wxEXPAND);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);
    SetSizer(mainSizer);

    
    wxButton* backBtn = new wxButton(this, wxID_ANY, "Back to Main");
    backBtn->Bind(wxEVT_BUTTON, &ImageSlideshow::OnBack, this);
    mainSizer->Add(backBtn, 0, wxALIGN_RIGHT | wxALL, 5);

    
    Bind(wxEVT_TIMER, &ImageSlideshow::OnTimer, this, m_timer->GetId());
}


void ImageSlideshow::OnUpload(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, "Open Image Files", "", "", 
                                "Image files (*.jpg;*.jpeg;*.png;*.bmp)|*.jpg;*.jpeg;*.png;*.bmp", 
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE);
    
    if (openFileDialog.ShowModal() == wxID_OK) {
        wxArrayString paths;
        openFileDialog.GetPaths(paths);

        for (const auto& path : paths) {
            m_imagePaths.push_back(path); 
        }

        // Show the first image
        if (!m_imagePaths.empty()) {
            m_currentImageIndex = 0;
            m_staticBitmap->SetBitmap(wxBitmap(m_imagePaths[m_currentImageIndex])); 
            m_staticBitmap->Refresh();
            m_scrolledWindow->SetVirtualSize(m_staticBitmap->GetSize());
            m_scrolledWindow->Layout();
        }
    }
}


void ImageSlideshow::OnPrev(wxCommandEvent& event) {
    if (m_imagePaths.empty()) return; 

    m_currentImageIndex--; 
    if (m_currentImageIndex < 0) {
        m_currentImageIndex = m_imagePaths.size() - 1; 
    }
    UpdateSlideshow(); 
}


void ImageSlideshow::OnNext(wxEvent& event) { 
    if (m_imagePaths.empty()) return; 

    m_currentImageIndex++; 
    if (m_currentImageIndex >= m_imagePaths.size()) {
        m_currentImageIndex = 0; 
    }
    UpdateSlideshow(); 
}

// start & stop  slideshow
void ImageSlideshow::OnToggleSlideshow(wxCommandEvent& event) {
    m_slideshowActive = !m_slideshowActive; // Toggle state

    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    if (m_slideshowActive) {
        m_timer->Start(2000); // Start slideshow
        button->SetLabel("End Slideshow");
        FindWindowByLabel("Previous")->Hide();
        FindWindowByLabel("Next")->Hide();
        FindWindowByLabel("Upload Images")->Hide();
    } else {
        m_timer->Stop(); // Stop slideshow
        button->SetLabel("Start Slideshow");
        FindWindowByLabel("Previous")->Show(); 
        FindWindowByLabel("Next")->Show();
        FindWindowByLabel("Upload Images")->Show();
    }
}

// Timer
void ImageSlideshow::OnTimer(wxTimerEvent& event) {
    OnNext(event); 
}


void ImageSlideshow::UpdateSlideshow() {
    if (m_imagePaths.empty()) return;

    m_staticBitmap->SetBitmap(wxBitmap(m_imagePaths[m_currentImageIndex])); 
    m_staticBitmap->Refresh(); 
}

// to main scrn
void ImageSlideshow::OnBack(wxCommandEvent& event) {
    FindWindowById(wxID_HIGHEST + 1)->Show();
    Hide(); 
}
