Class {
	#name : #AVIDEOStream,
	#superclass : #AVIDEOInterface,
	#category : 'AbstractVideo-GeneratedPharo'
}

{ #category : #'wrappers' }
AVIDEOStream >> addReference [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance addReference_stream: (self validHandle).
	self checkErrorCode: resultValue_
]

{ #category : #'wrappers' }
AVIDEOStream >> primitiveRelease [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance release_stream: (self validHandle).
	self checkErrorCode: resultValue_
]

