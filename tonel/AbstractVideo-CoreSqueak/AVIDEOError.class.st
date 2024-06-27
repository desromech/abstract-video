Class {
	#name : #AVIDEOError,
	#superclass : #Error,
	#instVars : [
		'errorCode'
	],
	#category : #'AbstractVideo-CoreSqueak'
}

{ #category : #accessing }
AVIDEOError >> errorCode [
	^ errorCode
]

{ #category : #accessing }
AVIDEOError >> errorCode: anObject [
	errorCode := anObject
]
