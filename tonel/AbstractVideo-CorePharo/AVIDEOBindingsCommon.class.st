"
I provide common APIs for the different AVIDEO bindings.
"
Class {
	#name : 'AVIDEOBindingsCommon',
	#superclass : 'Object',
	#category : 'AbstractVideo-CorePharo',
	#package : 'AbstractVideo-CorePharo'
}

{ #category : 'as yet unclassified' }
AVIDEOBindingsCommon class >> checkErrorCode: errorCode [
	errorCode < 0 ifTrue: [
		self error: 'Got an error from AVIDEO.'
	]
]

{ #category : 'accessing' }
AVIDEOBindingsCommon class >> validHandleOf: anObject [
	^ anObject ifNil: [ ExternalAddress null ] ifNotNil: [ anObject validHandle ]
]

{ #category : 'error checking' }
AVIDEOBindingsCommon >> checkErrorCode: errorCode [
	errorCode < 0 ifTrue: [
		^ AVIDEOError new
			errorCode: errorCode;
			signal: 'AVIDEO error code: ' , errorCode asString
	]
]

{ #category : 'freeing resources' }
AVIDEOBindingsCommon >> release [
	self primitiveRelease.
]

{ #category : 'accessing' }
AVIDEOBindingsCommon >> validHandleOf: anObject [
	^ anObject ifNotNil: [ anObject validHandle ]
]
