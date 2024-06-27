"
I am an utility for copying bits between buffers.
"
Class {
	#name : #AVIDEOMemoryCopier,
	#superclass : #Object,
	#instVars : [
		'alien'
	],
	#category : #'AbstractVideo-CoreSqueak'
}

{ #category : #'constructing' }
AVIDEOMemoryCopier class >> forExternalAddress: anExternalAddress [
	^ self basicNew externalAddress: anExternalAddress; yourself
]
{ #category : #accessing }
AVIDEOMemoryCopier >> externalAddress: anExternalAddress [

	alien := (Smalltalk at: #Alien ifAbsent: [Smalltalk at: #AlienStub]) forPointer: anExternalAddress asInteger
]

{ #category : #accessing }
AVIDEOMemoryCopier >> replaceFrom: start to: stop with: replacement startingAt: repStart [
	^ alien replaceFrom: start to: stop with: replacement startingAt: repStart
]
