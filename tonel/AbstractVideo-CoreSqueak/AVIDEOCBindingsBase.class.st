Class {
	#name : #AVIDEOCBindingsBase,
	#superclass : #ExternalLibrary,
	#classInstVars : [
		'uniqueInstance'
	],
	#category : #'AbstractVideo-CoreSqueak'
}

{ #category : #'as yet unclassified' }
AVIDEOCBindingsBase class >> moduleName [
	^ 'Avideo'
]

{ #category : #'as yet unclassified' }
AVIDEOCBindingsBase class >> uniqueInstance [
	^ uniqueInstance ifNil: [uniqueInstance := self new]
]
