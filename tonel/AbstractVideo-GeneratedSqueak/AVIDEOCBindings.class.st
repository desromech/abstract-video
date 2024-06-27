Class {
	#name : #AVIDEOCBindings,
	#pools : [
		'AVIDEOConstants'
	],
	#superclass : #AVIDEOCBindingsBase,
	#category : 'AbstractVideo-GeneratedSqueak'
}

{ #category : #'platform' }
AVIDEOCBindings >> openContext_platform: platform openInfo: openInfo [
	<cdecl: void* 'avideoOpenDevice' (void* AVIDEOContextOpenInfo*)>
	^ self externalCallFailed
]

{ #category : #'platform' }
AVIDEOCBindings >> getName_platform: platform [
	<cdecl: char* 'avideoGetPlatformName' (void*)>
	^ self externalCallFailed
]

{ #category : #'context' }
AVIDEOCBindings >> addReference_context: context [
	<cdecl: long 'avideoAddContextReference' (void*)>
	^ self externalCallFailed
]

{ #category : #'context' }
AVIDEOCBindings >> release_context: context [
	<cdecl: long 'avideoReleaseContext' (void*)>
	^ self externalCallFailed
]

{ #category : #'context' }
AVIDEOCBindings >> openContainerWithURL_context: context url: url [
	<cdecl: void* 'avideoOpenContainerWithURL' (void* byte*)>
	^ self externalCallFailed
]

{ #category : #'container' }
AVIDEOCBindings >> addReference_container: container [
	<cdecl: long 'avideoAddContainerReference' (void*)>
	^ self externalCallFailed
]

{ #category : #'container' }
AVIDEOCBindings >> release_container: container [
	<cdecl: long 'avideoReleaseContainer' (void*)>
	^ self externalCallFailed
]

{ #category : #'container' }
AVIDEOCBindings >> getStartTime_container: container [
	<cdecl: double 'avideoContainerGetStartTime' (void*)>
	^ self externalCallFailed
]

{ #category : #'container' }
AVIDEOCBindings >> getDuration_container: container [
	<cdecl: double 'avideoContainerGetDuration' (void*)>
	^ self externalCallFailed
]

{ #category : #'container' }
AVIDEOCBindings >> seekTime_container: container time: time [
	<cdecl: long 'avideoContainerSeekTime' (void* double)>
	^ self externalCallFailed
]

{ #category : #'container' }
AVIDEOCBindings >> seekFrame_container: container frame_index: frame_index [
	<cdecl: long 'avideoContainerSeekFrameIndex' (void* ulong)>
	^ self externalCallFailed
]

{ #category : #'container' }
AVIDEOCBindings >> hasVideoStream_container: container [
	<cdecl: long 'avideoContainerHasVideoStream' (void*)>
	^ self externalCallFailed
]

{ #category : #'container' }
AVIDEOCBindings >> getVideoStreamWidth_container: container [
	<cdecl: ulong 'avideoContainerGetVideoStreamWidth' (void*)>
	^ self externalCallFailed
]

{ #category : #'container' }
AVIDEOCBindings >> getVideoStreamHeight_container: container [
	<cdecl: ulong 'avideoContainerGetVideoStreamHeight' (void*)>
	^ self externalCallFailed
]

{ #category : #'container' }
AVIDEOCBindings >> getVideoStreamFrameCount_container: container [
	<cdecl: ulong 'avideoContainerGetVideoStreamFrameCount' (void*)>
	^ self externalCallFailed
]

{ #category : #'container' }
AVIDEOCBindings >> getVideoStreamFrameRate_container: container [
	<cdecl: float 'avideoContainerGetVideoStreamFrameRate' (void*)>
	^ self externalCallFailed
]

{ #category : #'container' }
AVIDEOCBindings >> hasAudioStream_container: container [
	<cdecl: long 'avideoContainerHasAudioStream' (void*)>
	^ self externalCallFailed
]

{ #category : #'container' }
AVIDEOCBindings >> getAudioStreamChannels_container: container [
	<cdecl: ulong 'avideoContainerGetAudioStreamChannels' (void*)>
	^ self externalCallFailed
]

{ #category : #'container' }
AVIDEOCBindings >> getAudioStreamSampleRate_container: container [
	<cdecl: ulong 'avideoContainerGetAudioStreamSampleRate' (void*)>
	^ self externalCallFailed
]

{ #category : #'global c functions' }
AVIDEOCBindings >> getPlatforms_numplatforms: numplatforms platforms: platforms ret_numplatforms: ret_numplatforms [
	<cdecl: long 'avideoGetPlatforms' (ulong void* ulong*)>
	^ self externalCallFailed
]

