//
//  AppDelegate.m
//  YYEventSource
//
//  Created by xiaotian on 2021/2/23.
//

#import <Foundation/Foundation.h>

typedef enum {
    kEventStateConnecting = 0,
    kEventStateOpen = 1,
    kEventStateClosed = 2,
} EventState;


/// Describes an Event received from an EventSource
@interface Event : NSObject

/// The Event ID
@property (nonatomic, strong) id eventId;
/// The name of the Event
@property (nonatomic, strong) NSString *eventType;
/// The data received from the EventSource
@property (nonatomic, strong) NSString *data;

/// The current state of the connection to the EventSource
@property (nonatomic, assign) EventState readyState;
/// Provides details of any errors with the connection to the EventSource
@property (nonatomic, strong) NSError *error;

@end


typedef void (^EventSourceEventHandler)(Event *event);


/// Connect to and receive Server-Sent Events (SSEs).
@interface EventSource : NSObject

@property (nonatomic, assign) BOOL retryWhenConnectError;

/// Returns a new instance of EventSource with the specified URL.
///
/// @param URL The URL of the EventSource.
+ (instancetype)eventSourceWithURL:(NSURL *)URL;

/// Returns a new instance of EventSource with the specified Task.
/// @param task The task of the EventSource.
+ (instancetype)eventSourceWithTask:(NSURLSessionDataTask *)task;

/// Returns a new instance of EventSource with the specified URL.
///
/// @param URL The URL of the EventSource.
/// @param timeoutInterval The request timeout interval in seconds. See <tt>NSURLRequest</tt> for more details. Default: 5 minutes.
+ (instancetype)eventSourceWithURL:(NSURL *)URL timeoutInterval:(NSTimeInterval)timeoutInterval;

/// Creates a new instance of EventSource with the specified URL.
///
/// @param URL The URL of the EventSource.
- (instancetype)initWithURL:(NSURL *)URL;

/// Creates a new instance of EventSource with the specified URL.
///
/// @param URL The URL of the EventSource.
/// @param timeoutInterval The request timeout interval in seconds. See <tt>NSURLRequest</tt> for more details. Default: 5 minutes.
- (instancetype)initWithURL:(NSURL *)URL timeoutInterval:(NSTimeInterval)timeoutInterval;

/// Registers an event handler for the Message event.
///
/// @param handler The handler for the Message event.
- (void)onMessage:(EventSourceEventHandler)handler;

/// Registers an event handler for the Error event.
///
/// @param handler The handler for the Error event.
- (void)onError:(EventSourceEventHandler)handler;

/// Registers an event handler for the Open event.
///
/// @param handler The handler for the Open event.
- (void)onOpen:(EventSourceEventHandler)handler;

- (void)onReadyStateChanged:(EventSourceEventHandler)handler;

/// Registers an event handler for a named event.
///
/// @param eventName The name of the event you registered.
/// @param handler The handler for the Message event.
- (void)addEventListener:(NSString *)eventName handler:(EventSourceEventHandler)handler;

/// Closes the connection to the EventSource.
- (void)close;

@end


extern NSString *const MessageEvent;
extern NSString *const ErrorEvent;
extern NSString *const OpenEvent;
extern NSString *const ReadyStateEvent;
