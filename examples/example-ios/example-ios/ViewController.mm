//
//  ViewController.m
//  example-ios
//
//  Created by Ragnar Hrafnkelsson on 01/11/2015.
//  Copyright © 2015 Reactify. All rights reserved.
//

#import "StereoSpread.h"
#import "TheAmazingAudioEngine.h"
#import "ViewController.h"

@interface ViewController ()
{
	StereoSpread* stereoSpread;
}
@property (nonatomic, strong) AEBlockFilter *filter;
@property (nonatomic, strong) AEAudioFilePlayer *loop1;
@property (nonatomic, strong) AEAudioController *audioController;
- (IBAction)onSliderValueChanged:(id)sender;
@end

@implementation ViewController

- (void)dealloc
{
	[_audioController removeFilter:_filter];
	[_audioController removeChannels:@[_loop1]];
	[_audioController stop];
	_filter = nil;
	_loop1 = nil;
	_audioController = nil;
	delete stereoSpread;
}

- (void)viewDidLoad
{
	[super viewDidLoad];
	
	stereoSpread = new StereoSpread();
	
	// Create an instance of the audio controller, set it up and start it running
	self.audioController = [[AEAudioController alloc] initWithAudioDescription:AEAudioStreamBasicDescriptionNonInterleavedFloatStereo inputEnabled:YES];
	_audioController.preferredBufferDuration = 0.005;
	_audioController.useMeasurementMode = YES;
	[_audioController start:NULL];
	
	self.loop1 = [AEAudioFilePlayer audioFilePlayerWithURL:[[NSBundle mainBundle] URLForResource:@"rain" withExtension:@"wav"] error:NULL];
	_loop1.volume = 1.0;
	_loop1.channelIsMuted = NO;
	_loop1.loop = YES;
	[self.audioController addChannels:@[self.loop1]];
	
	self.filter = [AEBlockFilter filterWithBlock:^(AEAudioFilterProducer producer, void *producerToken, const AudioTimeStamp *time, UInt32 frames, AudioBufferList *audio) {
		
		OSStatus status = producer(producerToken, audio, &frames);
		if ( status != noErr ) return;
		
		float *inBuffers[2] = {(float *)audio->mBuffers[0].mData, (float *)audio->mBuffers[1].mData};
		float *outBuffers[2] = {(float *)audio->mBuffers[0].mData, (float *)audio->mBuffers[1].mData};
		
		stereoSpread->process(inBuffers, outBuffers, frames);
	}];
	
	[self.audioController addFilter:self.filter];
}

- (IBAction)onSliderValueChanged:(UISlider *)sender
{
	stereoSpread->setWidth(sender.value);
}
@end
