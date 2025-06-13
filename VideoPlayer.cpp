#include "VideoPlayer.h"

VideoPlayer::VideoPlayer(wxFrame* parent)
    : wxPanel(parent, wxID_ANY), m_pipeline(nullptr)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    //gstream inital
    gst_init(nullptr, nullptr);
    m_pipeline = gst_element_factory_make("playbin", "player");

    //horzontal box for btns
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    m_videoPanel = new wxPanel(this, wxID_ANY);
    m_videoPanel->SetBackgroundColour(*wxBLACK); 
    mainSizer->Add(m_videoPanel, 1, wxEXPAND | wxALL, 5); 

    
    wxButton* backButton = new wxButton(this, wxID_ANY, "Back to Main");
    buttonSizer->Add(backButton, 0, wxALL, 5);
    backButton->Bind(wxEVT_BUTTON, &VideoPlayer::OnBack, this);

    
    wxButton* openButton = new wxButton(this, wxID_ANY, "Open Video/Audio");
    buttonSizer->Add(openButton, 0, wxALL, 5);
    openButton->Bind(wxEVT_BUTTON, &VideoPlayer::OnOpenVideo, this);

   
    m_toggleButton = new wxButton(this, wxID_ANY, "Play");
    buttonSizer->Add(m_toggleButton, 0, wxALL, 5);
    m_toggleButton->Bind(wxEVT_BUTTON, &VideoPlayer::OnTogglePlayPause, this);

    
    wxButton* stopButton = new wxButton(this, wxID_ANY, "Stop");
    buttonSizer->Add(stopButton, 0, wxALL, 5);
    stopButton->Bind(wxEVT_BUTTON, &VideoPlayer::OnStop, this);

    
    m_volumeSlider = new wxSlider(this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL);
    m_volumeSlider->Bind(wxEVT_SCROLL_THUMBTRACK, &VideoPlayer::OnVolumeChange, this);

    
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxBOTTOM, 5); 
    mainSizer->Add(m_volumeSlider, 0, wxEXPAND | wxALL, 5); 

    SetSizer(mainSizer); 
}

VideoPlayer::~VideoPlayer() {
    if (m_pipeline) {
        gst_element_set_state(m_pipeline, GST_STATE_NULL); 
        gst_object_unref(m_pipeline); 
    }
}

//open video/audio
void VideoPlayer::OnOpenVideo(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, "Open Video/Audio File", "", "",
                                "Media files (*.mp4;*.avi;*.mp3;*.wav)|*.mp4;*.avi;*.mp3;*.wav",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    
    if (openFileDialog.ShowModal() == wxID_OK) {
        wxString filePath = openFileDialog.GetPath();
        g_object_set(m_pipeline, "uri", ("file://" + filePath.ToStdString()).c_str(), nullptr);
        gst_element_set_state(m_pipeline, GST_STATE_PLAYING); 
    }
}

//play&pause
void VideoPlayer::OnTogglePlayPause(wxCommandEvent& event) {
    GstState state;
    gst_element_get_state(m_pipeline, &state, nullptr, GST_CLOCK_TIME_NONE);

    if (state == GST_STATE_PLAYING) {
        gst_element_set_state(m_pipeline, GST_STATE_PAUSED); 
        m_toggleButton->SetLabel("Play"); 
    } else {
        gst_element_set_state(m_pipeline, GST_STATE_PLAYING); 
        m_toggleButton->SetLabel("Pause"); 
    }
}

//stop
void VideoPlayer::OnStop(wxCommandEvent& event) {
    gst_element_set_state(m_pipeline, GST_STATE_NULL); 
    m_toggleButton->SetLabel("Play");
}

//volumeSlider change volume
void VideoPlayer::OnVolumeChange(wxScrollEvent& event) {
    int volume = m_volumeSlider->GetValue();
    g_object_set(m_pipeline, "volume", volume / 100.0, nullptr);
}

//back to main
void VideoPlayer::OnBack(wxCommandEvent& event) {
    gst_element_set_state(m_pipeline, GST_STATE_NULL); 
    FindWindowById(wxID_HIGHEST + 1)->Show();
    Hide();
}
