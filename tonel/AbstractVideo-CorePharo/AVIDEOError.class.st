"
I wrap an AVIDEO error code.
"
Class {
	#name : #AVIDEOError,
	#superclass : #Error,
	#instVars : [
		'errorCode'
	],
	#category : #'AbstractVideo-CorePharo'
}

{ #category : #accessing }
AVIDEOError >> errorCode [
	^ errorCode
]

{ #category : #accessing }
AVIDEOError >> errorCode: anObject [
	errorCode := anObject
]
