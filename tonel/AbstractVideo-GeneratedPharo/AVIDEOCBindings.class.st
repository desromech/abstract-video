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
AVIDEOCBindings >> openStreamWithURL_context: context url: url [
	^ self ffiCall: #(avideo_stream* avideoOpenStreamWithURL (avideo_context* context , avideo_cstring url) )
]

{ #category : #'stream' }
AVIDEOCBindings >> addReference_stream: stream [
	^ self ffiCall: #(avideo_error avideoAddStreamReference (avideo_stream* stream) )
]

{ #category : #'stream' }
AVIDEOCBindings >> release_stream: stream [
	^ self ffiCall: #(avideo_error avideoReleaseStream (avideo_stream* stream) )
]

{ #category : #'global c functions' }
AVIDEOCBindings >> getPlatforms_numplatforms: numplatforms platforms: platforms ret_numplatforms: ret_numplatforms [
	^ self ffiCall: #(avideo_error avideoGetPlatforms (avideo_size numplatforms , avideo_platform* platforms , avideo_size* ret_numplatforms) )
]

