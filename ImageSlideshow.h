#ifndef IMAGE_SLIDESHOW_H
#define IMAGE_SLIDESHOW_H

#include <vector>
#include <wx/wx.h>
#include <wx/statbmp.h>
#include <wx/filedlg.h>
#include <wx/timer.h>

// image slideshow
class ImageSlideshow : public wxPanel {
public:
    ImageSlideshow(wxFrame* parent); 

private:
  
    wxStaticBitmap* m_staticBitmap; 
    wxScrolledWindow* m_scrolledWindow; // scrolling image
    std::vector<wxString> m_imagePaths; // Store paths of images
    int m_currentImageIndex; 
    wxTimer* m_timer; 
    bool m_slideshowActive; 

    // Event handlers
    void OnUpload(wxCommandEvent& event);
    void OnPrev(wxCommandEvent& event);
    void OnNext(wxEvent& event);
    void OnToggleSlideshow(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event); 
    void UpdateSlideshow(); 
    void OnBack(wxCommandEvent& event); 
};

#endif 