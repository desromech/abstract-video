Class {
	#name : #AVIDEOContext,
	#superclass : #AVIDEOInterface,
	#category : 'AbstractVideo-GeneratedSqueak'
}

{ #category : #'wrappers' }
AVIDEOContext >> addReference [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance addReference_context: (self validHandle).
	self checkErrorCode: resultValue_
]

{ #category : #'wrappers' }
AVIDEOContext >> primitiveRelease [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance release_context: (self validHandle).
	self checkErrorCode: resultValue_
]

