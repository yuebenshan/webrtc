/*
 * Copyright 2022 LiveKit
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SDK_OBJC_NATIVE_SRC_OBJC_DESKTOP_CAPTURE_H_
#define SDK_OBJC_NATIVE_SRC_OBJC_DESKTOP_CAPTURE_H_

#import "base/RTCMacros.h"

#include "api/video/i420_buffer.h"
#include "api/video/video_frame.h"
#include "modules/desktop_capture/desktop_capture_options.h"
#include "modules/desktop_capture/desktop_capturer.h"
#include "modules/desktop_capture/desktop_frame.h"
#include "rtc_base/thread.h"

@protocol RTC_OBJC_TYPE
(DesktopCapturerDelegate);

namespace webrtc {

class ObjCDesktopCapturer : public DesktopCapturer::Callback, public rtc::MessageHandler {
 public:
  enum CaptureState { CS_RUNNING, CS_STOPPED, CS_FAILED};

  enum DesktopType { kScreen, kWindow };

 public:
  ObjCDesktopCapturer(DesktopType type,
    webrtc::DesktopCapturer::SourceId source_id, 
    id<RTC_OBJC_TYPE(DesktopCapturerDelegate)> delegate);
  virtual ~ObjCDesktopCapturer();

  virtual CaptureState Start();

  virtual void Stop();

  virtual bool IsRunning();

 protected:
  virtual void OnCaptureResult(webrtc::DesktopCapturer::Result result,
                               std::unique_ptr<webrtc::DesktopFrame> frame) override;
  virtual void OnMessage(rtc::Message* msg) override;

 private:
  void CaptureFrame();
  std::unique_ptr<webrtc::DesktopCapturer> capturer_;
  std::unique_ptr<rtc::Thread> thread_;
  rtc::scoped_refptr<webrtc::I420Buffer> i420_buffer_;
  CaptureState capture_state_ = CS_STOPPED;
  webrtc::DesktopCapturer::SourceId source_id_;
  id<RTC_OBJC_TYPE(DesktopCapturerDelegate)> delegate_;
};

}  // namespace webrtc

#endif  // SDK_OBJC_NATIVE_SRC_OBJC_DESKTOP_CAPTURE_H_
