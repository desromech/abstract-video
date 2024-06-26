Extension { #name : #AVIDEO }

{ #category : #'*AbstractVideo-GeneratedSqueak' }
AVIDEO >> getPlatforms: numplatforms platforms: platforms ret_numplatforms: ret_numplatforms [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance getPlatforms_numplatforms: numplatforms platforms: platforms ret_numplatforms: ret_numplatforms.
	self checkErrorCode: resultValue_
]

