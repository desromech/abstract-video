Class {
	#name : #AVIDEOInterface,
	#superclass : #AVIDEOBindingsCommon,
	#instVars : [
		'handle'
	],
	#category : #'AbstractVideo-CoreSqueak'
}

{ #category : #'instance creation' }
AVIDEOInterface class >> forHandle: aHandle [
	(aHandle isNil or: [ aHandle isNull ]) ifTrue: [ ^ nil ].
	^ self new handle: aHandle; autoRelease; yourself
]

{ #category : #'instance creation' }
AVIDEOInterface class >> forManualHandle: aHandle [
	^ self new handle: aHandle
]

{ #category : #finalization }
AVIDEOInterface >> autoRelease [
	^ self class finalizationRegistry add: self
]

{ #category : #accessing }
AVIDEOInterface >> finalize [
	(handle ~~ nil and: [ handle isNull not ]) ifTrue: [
		self primitiveRelease
	]

]

{ #category : #accessing }
AVIDEOInterface >> handle [
	^ handle
]

{ #category : #accessing }
AVIDEOInterface >> handle: aHandle [
	handle := aHandle
]

{ #category : #testing }
AVIDEOInterface >> isNull [
	^ handle isNil or: [ handle isNull ]
]

{ #category : #finalization }
AVIDEOInterface >> release [
	self class finalizationRegistry remove: self.
	self primitiveRelease.
	handle := nil.
]

{ #category : #accessing }
AVIDEOInterface >> validHandle [
	handle ifNil: [ self error: 'Trying to use an object with an invalid handle.' ].
	^ handle
]
