#ifndef TGCALLS_VIDEO_CAMERA_CAPTURER_H
#define TGCALLS_VIDEO_CAMERA_CAPTURER_H

#include "api/scoped_refptr.h"
#include "api/video/video_frame.h"
#include "api/video/video_source_interface.h"
#include "media/base/video_adapter.h"
#include "modules/video_capture/video_capture.h"

#include "VideoCaptureInterface.h"

#include <memory>
#include <vector>
#include <stddef.h>

namespace tgcalls {

class VideoCameraCapturer
	: public rtc::VideoSinkInterface<webrtc::VideoFrame> {
public:
	explicit VideoCameraCapturer(
		rtc::VideoSinkInterface<webrtc::VideoFrame> *sink);
	~VideoCameraCapturer();

	void setState(VideoState state);
	void setDeviceId(std::string deviceId);
	void setPreferredCaptureAspectRatio(float aspectRatio);

	std::pair<int, int> resolution() const;

	void OnFrame(const webrtc::VideoFrame &frame) override;

private:
	void create();
	bool create(
		webrtc::VideoCaptureModule::DeviceInfo *info,
		const std::string &deviceId);
	void destroy();

	rtc::VideoSinkInterface<webrtc::VideoFrame> *_sink = nullptr;
	rtc::scoped_refptr<webrtc::VideoCaptureModule> _module;
	webrtc::VideoCaptureCapability _capability;

	VideoState _state = VideoState::Inactive;
	std::string _requestedDeviceId;
	std::pair<int, int> _dimensions;
	float _aspectRatio = 0.;

};

}  // namespace tgcalls

#endif
