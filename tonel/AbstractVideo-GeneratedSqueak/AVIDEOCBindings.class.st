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

{ #category : #'global c functions' }
AVIDEOCBindings >> getPlatforms_numplatforms: numplatforms platforms: platforms ret_numplatforms: ret_numplatforms [
	<cdecl: long 'avideoGetPlatforms' (ulong void* ulong*)>
	^ self externalCallFailed
]

