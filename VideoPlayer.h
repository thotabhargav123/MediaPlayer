#ifndef VIDEO_PLAYER_H
#define VIDEO_PLAYER_H

#include <wx/wx.h>
#include <gst/gst.h> // Include GStreamer

// Class for video player functionality
class VideoPlayer : public wxPanel {
public:
    VideoPlayer(wxFrame* parent);  // Constructor
    ~VideoPlayer();  // Destructor

private:
    GstElement* m_pipeline;  // GStreamer pipeline element for media control
     wxPanel* m_videoPanel; // Panel for video display

    wxButton* m_toggleButton;
    wxSlider* m_volumeSlider;

    // Event handlers
    void OnOpenVideo(wxCommandEvent& event);
    void OnTogglePlayPause(wxCommandEvent& event);
    void OnStop(wxCommandEvent& event);
    void OnVolumeChange(wxScrollEvent& event);
    void OnBack(wxCommandEvent& event);
};

#endif // VIDEO_PLAYER_H
