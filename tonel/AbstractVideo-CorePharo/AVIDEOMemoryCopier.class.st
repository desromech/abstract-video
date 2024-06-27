"
I am an utility for copying bits between buffers.
"
Class {
	#name : #AVIDEOMemoryCopier,
	#superclass : #Object,
	#instVars : [
		'externalAddress'
	],
	#category : #'AbstractVideo-CorePharo'
}

{ #category : #constructing }
AVIDEOMemoryCopier class >> forExternalAddress: anExternalAddress [
	^ self basicNew externalAddress: anExternalAddress; yourself
]

{ #category : #accessing }
AVIDEOMemoryCopier >> copyBytes: byteCount at: start into: destination at: destinationStart [
	| sourceAddress destAddress |
	sourceAddress := externalAddress + (start - 1).
	destAddress := destination tfPointerAddress + (destinationStart - 1).
	LibC memCopy: sourceAddress to: destAddress size: byteCount
]

{ #category : #accessing }
AVIDEOMemoryCopier >> externalAddress [

	^ externalAddress
]

{ #category : #accessing }
AVIDEOMemoryCopier >> externalAddress: anExternalAddress [

	externalAddress := anExternalAddress
]

{ #category : #accessing }
AVIDEOMemoryCopier >> replaceFrom: start to: stop with: replacement startingAt: repStart [
	| sourceAddress destAddress size |
	sourceAddress := replacement tfPointerAddress + (repStart - 1).
	destAddress := externalAddress + (start - 1).
	size := stop - start + 1.
	LibC memCopy: sourceAddress to: destAddress size: size
]
