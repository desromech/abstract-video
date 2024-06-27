"
I hold the global AVIDEO entry points, and some facilities for selecting contexts and platforms.
"
Class {
	#name : 'AVIDEO',
	#superclass : 'AVIDEOBindingsCommon',
	#instVars : [
		'mainPlatform',
		'mainContext',
		'contextSession',
		'platformSession',
		'platforms',
		'contextDescriptions'
	],
	#classVars : [
		'UniqueInstance'
	],
	#category : 'AbstractVideo-CorePharo',
	#package : 'AbstractVideo-CorePharo'
}

{ #category : 'platform querying' }
AVIDEO class >> firstPlatform [
	^ self uniqueInstance firstPlatform
]

{ #category : 'main context' }
AVIDEO class >> mainContext [
	^ self uniqueInstance mainContext
]

{ #category : 'main context' }
AVIDEO class >> mainPlatform [
	^ self uniqueInstance mainPlatform
]

{ #category : 'utilties' }
AVIDEO class >> packListOfReferences: aListOfReferences [
	| pointerSize packedList destIndex |
	pointerSize := Smalltalk wordSize.
	packedList := ByteArray new: pointerSize * aListOfReferences size.
	destIndex := 1.
	aListOfReferences do: [ :ref |
		packedList pointerAt: destIndex put: ref validHandle getHandle.
		destIndex := destIndex + pointerSize
	].

	^ packedList
]

{ #category : 'platform querying' }
AVIDEO class >> platforms [
	^ self uniqueInstance platforms
]

{ #category : 'accessing' }
AVIDEO class >> session [
	^ Smalltalk session
]

{ #category : 'accessing' }
AVIDEO class >> uniqueInstance [
	UniqueInstance ifNil: [ UniqueInstance := self new. ].
	^ UniqueInstance
]

{ #category : 'main context' }
AVIDEO >> checkContextSession [
	(contextSession ~~ Smalltalk session or: [mainContext isNil]) ifTrue: [
		self openMainContext.
		contextSession := Smalltalk session.
	].

]

{ #category : 'platform querying' }
AVIDEO >> checkPlatformsSession [
	(platformSession ~~ Smalltalk session or: [platforms isNil]) ifTrue: [
		self fetchPlatforms.
		platformSession := Smalltalk session.
	].

]

{ #category : 'platform querying' }
AVIDEO >> contextDescriptions [
	self checkPlatformsSession.
	^ contextDescriptions
]

{ #category : 'platform querying' }
AVIDEO >> fetchPlatforms [
	| platformCount platformPointers platformCountRet pointerSize |
	platformCount := self platformCount.
	platformCountRet := ExternalAddress allocate: 4.
	platforms := [
		pointerSize := Smalltalk wordSize.
		platformPointers := ExternalAddress allocate: pointerSize * platformCount.
		[
			self getPlatforms: platformCount platforms: platformPointers ret_numplatforms: platformCountRet.
			platformCount := platformCountRet unsignedLongAt: 1.
			(1 to: platformCount) collect: [ :i | (Smalltalk at: #AVIDEOPlatform) forManualHandle: (platformPointers pointerAt: (i-1)*pointerSize + 1)]
		] ensure: [ platformPointers free ]
	] ensure: [ platformCountRet free ].
]

{ #category : 'platform querying' }
AVIDEO >> firstPlatform [
	^ self platforms first
]

{ #category : 'main context' }
AVIDEO >> mainContext [
	self checkContextSession.
	^ mainContext
]

{ #category : 'main context' }
AVIDEO >> mainPlatform [
	self checkContextSession.
	^ mainPlatform
]

{ #category : 'main context' }
AVIDEO >> openMainContext [
	| contextOpenInfo |
	mainPlatform := self firstPlatform.
	contextOpenInfo := AVIDEOContextOpenInfo new.

	mainContext := mainPlatform openContext: contextOpenInfo.
	mainContext ifNil: [ self error: 'Failed to open the main AVIDEO context' ].

]

{ #category : 'platform querying' }
AVIDEO >> platformCount [
	| platformCount |
	platformCount := ExternalAddress allocate: 4.
	[
		self getPlatforms: 0 platforms: nil ret_numplatforms: platformCount.
		^ platformCount unsignedLongAt: 1
	] ensure: [ platformCount free ].
]

{ #category : 'platform querying' }
AVIDEO >> platforms [
	self checkPlatformsSession.
	^ platforms
]
