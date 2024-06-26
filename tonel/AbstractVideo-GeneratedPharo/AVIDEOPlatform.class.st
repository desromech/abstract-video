Class {
	#name : #AVIDEOPlatform,
	#superclass : #AVIDEOInterface,
	#category : 'AbstractVideo-GeneratedPharo'
}

{ #category : #'wrappers' }
AVIDEOPlatform >> openContext: openInfo [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance openContext_platform: (self validHandle) openInfo: openInfo.
	^ AVIDEOContext forHandle: resultValue_
]

{ #category : #'wrappers' }
AVIDEOPlatform >> getName [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance getName_platform: (self validHandle).
	^ resultValue_
]

