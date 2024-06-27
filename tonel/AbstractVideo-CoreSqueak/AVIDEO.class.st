Class {
	#name : #AVIDEO,
	#superclass : #AVIDEOBindingsCommon,
	#instVars : [
		'session',
		'mainPlatform',
		'mainContext'
	],
	#classVars : [
		'UniqueInstance',
		'UniqueSessionObject'
	],
	#category : #'AbstractVideo-CoreSqueak'
}

{ #category : #'platform querying' }
AVIDEO class >> firstPlatform [
	^ self uniqueInstance firstPlatform
]

{ #category : #'platform querying' }
AVIDEO class >> initialize [
	"AVIDEO initialize"
	Smalltalk addToStartUpList: self.
	Smalltalk addToShutDownList: self.
]

{ #category : #'main context' }
AVIDEO class >> mainContext [
	^ self uniqueInstance mainContext
]

{ #category : #'main context' }
AVIDEO class >> mainPlatform [
	^ self uniqueInstance mainPlatform
]

{ #category : #utilties }
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

{ #category : #'platform querying' }
AVIDEO class >> platforms [
	^ self uniqueInstance platforms
]

{ #category : #'as yet unclassified' }
AVIDEO class >> session [
	^ UniqueSessionObject ifNil: [ UniqueSessionObject := Object new ]
]

{ #category : #'platform querying' }
AVIDEO class >> startUp [
	UniqueSessionObject := Object new.
]

{ #category : #'platform querying' }
AVIDEO class >> uniqueInstance [
	UniqueInstance ifNil: [ UniqueInstance := self new. ].
	^ UniqueInstance
]

{ #category : #'main context' }
AVIDEO >> checkSession [
	(session ~~ AVIDEO session or: [mainContext isNil]) ifTrue: [
		self openMainContext.
		session := AVIDEO session.
	].

]

{ #category : #'main context' }
AVIDEO >> debugLayerEnabled [
	^ true
]

{ #category : #'platform querying' }
AVIDEO >> firstPlatform [
	^ self platforms first
]

{ #category : #'main context' }
AVIDEO >> mainContext [
	self checkSession.
	^ mainContext
]

{ #category : #'main context' }
AVIDEO >> mainPlatform [
	self checkSession.
	^ mainPlatform
]

{ #category : #'main context' }
AVIDEO >> openMainContext [
	| contextOpenInfo |
	mainPlatform := self firstPlatform.
	mainPlatform ifNil: [ self error: 'No AVIDEO platform is available.' ].

	contextOpenInfo := AVIDEOContextOpenInfo new.
	mainContext := mainPlatform openContext: contextOpenInfo.
	mainContext ifNil: [ self error: 'Failed to open the main AVIDEO context' ].

]

{ #category : #'platform querying' }
AVIDEO >> platformCount [
	| platformCount |
	platformCount := ExternalAddress allocate: 4.
	[
		self getPlatforms: 0 platforms: nil ret_numplatforms: platformCount.
		^ platformCount unsignedLongAt: 1
	] ensure: [ platformCount free ].
]

{ #category : #'platform querying' }
AVIDEO >> platforms [
	| platformCount platformPointers platformCountRet pointerSize |
	platformCount := self platformCount.
	platformCountRet := ExternalAddress allocate: 4.
	[
		pointerSize := Smalltalk wordSize.
		platformPointers := ExternalAddress allocate: pointerSize * platformCount.
		[
			self getPlatforms: platformCount platforms: platformPointers ret_numplatforms: platformCountRet.
			platformCount := platformCountRet unsignedLongAt: 1.
			^ (1 to: platformCount) collect: [ :i | (Smalltalk at: #AVIDEOPlatform) forManualHandle: (platformPointers pointerAt: (i-1)*pointerSize + 1)]
		] ensure: [ platformPointers free ]
	] ensure: [ platformCountRet free ].
]
