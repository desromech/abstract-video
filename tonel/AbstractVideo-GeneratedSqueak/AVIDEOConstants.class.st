Class {
	#name : #AVIDEOConstants,
	#classVars : [
		'AVIDEO_OK',
		'AVIDEO_ERROR',
		'AVIDEO_NULL_POINTER',
		'AVIDEO_INVALID_OPERATION',
		'AVIDEO_INVALID_PARAMETER',
		'AVIDEO_OUT_OF_BOUNDS',
		'AVIDEO_UNSUPPORTED',
		'AVIDEO_UNIMPLEMENTED',
		'AVIDEO_NOT_CURRENT_CONTEXT',
		'AVIDEO_OUT_OF_MEMORY',
		'AVIDEO_AGAIN',
		'AVIDEO_END_OF_STREAM'
	],
	#superclass : #SharedPool,
	#category : 'AbstractVideo-GeneratedSqueak'
}

{ #category : #'initialize' }
AVIDEOConstants class >> initialize [
"
	self initialize
"
	super initialize.


    self data pairsDo: [:k :v |
        self classPool at: k put: v
    ]
]

{ #category : #'initialization' }
AVIDEOConstants class >> data [
	^ #(
		AVIDEO_OK 0
		AVIDEO_ERROR -1
		AVIDEO_NULL_POINTER -2
		AVIDEO_INVALID_OPERATION -3
		AVIDEO_INVALID_PARAMETER -4
		AVIDEO_OUT_OF_BOUNDS -5
		AVIDEO_UNSUPPORTED -6
		AVIDEO_UNIMPLEMENTED -7
		AVIDEO_NOT_CURRENT_CONTEXT -8
		AVIDEO_OUT_OF_MEMORY -9
		AVIDEO_AGAIN -10
		AVIDEO_END_OF_STREAM -11
	)
]

