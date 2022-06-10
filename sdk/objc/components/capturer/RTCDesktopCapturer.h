#import <AVFoundation/AVFoundation.h>
#import <Foundation/Foundation.h>

#import "RTCMacros.h"
#import "RTCVideoCapturer.h"
#import "RTCDesktopSource.h"

NS_ASSUME_NONNULL_BEGIN

RTC_OBJC_EXPORT
@protocol RTC_OBJC_TYPE
(DesktopCapturerDelegate)<NSObject>
- (void)didCaptureVideoFrame:(RTC_OBJC_TYPE(RTCVideoFrame) *) frame;
@end

RTC_OBJC_EXPORT
// Screen capture that implements RTCVideoCapturer. Delivers frames to a
// RTCVideoCapturerDelegate (usually RTCVideoSource).
@interface RTC_OBJC_TYPE (RTCDesktopCapturer) : RTC_OBJC_TYPE(RTCVideoCapturer)

@property(nonatomic, readonly) RTCDesktopSource *source;

- (instancetype)initWithSource:(RTCDesktopSource*)source delegate:(__weak id<RTC_OBJC_TYPE(RTCVideoCapturerDelegate)>)delegate;

- (instancetype)initWithDefaultScreen:(__weak id<RTC_OBJC_TYPE(RTCVideoCapturerDelegate)>)delegate;

// Starts the capture session asynchronously.
- (void)startCapture:(NSInteger)fps;

// Stops the capture session asynchronously.
- (void)stopCapture;

- (void)didCaptureVideoFrame
    : (RTC_OBJC_TYPE(RTCVideoFrame) *)frame;

@end

NS_ASSUME_NONNULL_END
