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
AVIDEOCBindings >> openStreamWithURL_context: context url: url [
	<cdecl: void* 'avideoOpenStreamWithURL' (void* byte*)>
	^ self externalCallFailed
]

{ #category : #'stream' }
AVIDEOCBindings >> addReference_stream: stream [
	<cdecl: long 'avideoAddStreamReference' (void*)>
	^ self externalCallFailed
]

{ #category : #'stream' }
AVIDEOCBindings >> release_stream: stream [
	<cdecl: long 'avideoReleaseStream' (void*)>
	^ self externalCallFailed
]

{ #category : #'global c functions' }
AVIDEOCBindings >> getPlatforms_numplatforms: numplatforms platforms: platforms ret_numplatforms: ret_numplatforms [
	<cdecl: long 'avideoGetPlatforms' (ulong void* ulong*)>
	^ self externalCallFailed
]

