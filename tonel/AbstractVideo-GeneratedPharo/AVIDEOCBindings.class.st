Class {
	#name : #AVIDEOCBindings,
	#pools : [
		'AVIDEOConstants',
		'AVIDEOTypes'
	],
	#superclass : #AVIDEOCBindingsBase,
	#category : 'AbstractVideo-GeneratedPharo'
}

{ #category : #'platform' }
AVIDEOCBindings >> openContext_platform: platform openInfo: openInfo [
	^ self ffiCall: #(avideo_context* avideoOpenDevice (avideo_platform* platform , avideo_context_open_info* openInfo) )
]

{ #category : #'platform' }
AVIDEOCBindings >> getName_platform: platform [
	^ self ffiCall: #(avideo_cstring avideoGetPlatformName (avideo_platform* platform) )
]

{ #category : #'context' }
AVIDEOCBindings >> addReference_context: context [
	^ self ffiCall: #(avideo_error avideoAddContextReference (avideo_context* context) )
]

{ #category : #'context' }
AVIDEOCBindings >> release_context: context [
	^ self ffiCall: #(avideo_error avideoReleaseContext (avideo_context* context) )
]

{ #category : #'context' }
AVIDEOCBindings >> openContainerWithURL_context: context url: url [
	^ self ffiCall: #(avideo_container* avideoOpenContainerWithURL (avideo_context* context , avideo_cstring url) )
]

{ #category : #'container' }
AVIDEOCBindings >> addReference_container: container [
	^ self ffiCall: #(avideo_error avideoAddContainerReference (avideo_container* container) )
]

{ #category : #'container' }
AVIDEOCBindings >> release_container: container [
	^ self ffiCall: #(avideo_error avideoReleaseContainer (avideo_container* container) )
]

{ #category : #'container' }
AVIDEOCBindings >> getStartTime_container: container [
	^ self ffiCall: #(avideo_double avideoContainerGetStartTime (avideo_container* container) )
]

{ #category : #'container' }
AVIDEOCBindings >> getDuration_container: container [
	^ self ffiCall: #(avideo_double avideoContainerGetDuration (avideo_container* container) )
]

{ #category : #'container' }
AVIDEOCBindings >> seekTime_container: container time: time [
	^ self ffiCall: #(avideo_error avideoContainerSeekTime (avideo_container* container , avideo_double time) )
]

{ #category : #'container' }
AVIDEOCBindings >> seekFrame_container: container frame_index: frame_index [
	^ self ffiCall: #(avideo_error avideoContainerSeekFrameIndex (avideo_container* container , avideo_size frame_index) )
]

{ #category : #'container' }
AVIDEOCBindings >> hasVideoStream_container: container [
	^ self ffiCall: #(avideo_bool avideoContainerHasVideoStream (avideo_container* container) )
]

{ #category : #'container' }
AVIDEOCBindings >> getVideoStreamWidth_container: container [
	^ self ffiCall: #(avideo_size avideoContainerGetVideoStreamWidth (avideo_container* container) )
]

{ #category : #'container' }
AVIDEOCBindings >> getVideoStreamHeight_container: container [
	^ self ffiCall: #(avideo_size avideoContainerGetVideoStreamHeight (avideo_container* container) )
]

{ #category : #'container' }
AVIDEOCBindings >> getVideoStreamFrameCount_container: container [
	^ self ffiCall: #(avideo_size avideoContainerGetVideoStreamFrameCount (avideo_container* container) )
]

{ #category : #'container' }
AVIDEOCBindings >> getVideoStreamFrameRate_container: container [
	^ self ffiCall: #(avideo_float avideoContainerGetVideoStreamFrameRate (avideo_container* container) )
]

{ #category : #'container' }
AVIDEOCBindings >> fetchAndDecodeNextPacket_container: container [
	^ self ffiCall: #(avideo_error avideoContainerFetchAndDecodeNextPacket (avideo_container* container) )
]

{ #category : #'container' }
AVIDEOCBindings >> fetchAndDecodeNextVideoFrame_container: container [
	^ self ffiCall: #(avideo_error avideoContainerFetchAndDecodeNextVideoFrame (avideo_container* container) )
]

{ #category : #'container' }
AVIDEOCBindings >> getVideoFrameIndex_container: container [
	^ self ffiCall: #(avideo_size avideoContainerGetVideoFrameIndex (avideo_container* container) )
]

{ #category : #'container' }
AVIDEOCBindings >> getVideoFrameWidth_container: container [
	^ self ffiCall: #(avideo_size avideoContainerGetVideoFrameWidth (avideo_container* container) )
]

{ #category : #'container' }
AVIDEOCBindings >> getVideoFrameHeight_container: container [
	^ self ffiCall: #(avideo_size avideoContainerGetVideoFrameHeight (avideo_container* container) )
]

{ #category : #'container' }
AVIDEOCBindings >> hasAudioStream_container: container [
	^ self ffiCall: #(avideo_bool avideoContainerHasAudioStream (avideo_container* container) )
]

{ #category : #'container' }
AVIDEOCBindings >> getAudioStreamChannels_container: container [
	^ self ffiCall: #(avideo_size avideoContainerGetAudioStreamChannels (avideo_container* container) )
]

{ #category : #'container' }
AVIDEOCBindings >> getAudioStreamSampleRate_container: container [
	^ self ffiCall: #(avideo_size avideoContainerGetAudioStreamSampleRate (avideo_container* container) )
]

{ #category : #'global c functions' }
AVIDEOCBindings >> getPlatforms_numplatforms: numplatforms platforms: platforms ret_numplatforms: ret_numplatforms [
	^ self ffiCall: #(avideo_error avideoGetPlatforms (avideo_size numplatforms , avideo_platform* platforms , avideo_size* ret_numplatforms) )
]

