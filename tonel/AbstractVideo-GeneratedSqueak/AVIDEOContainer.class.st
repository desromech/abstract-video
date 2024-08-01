Class {
	#name : #AVIDEOContainer,
	#superclass : #AVIDEOInterface,
	#category : 'AbstractVideo-GeneratedSqueak'
}

{ #category : #'wrappers' }
AVIDEOContainer >> addReference [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance addReference_container: (self validHandle).
	self checkErrorCode: resultValue_
]

{ #category : #'wrappers' }
AVIDEOContainer >> primitiveRelease [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance release_container: (self validHandle).
	self checkErrorCode: resultValue_
]

{ #category : #'wrappers' }
AVIDEOContainer >> getStartTime [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance getStartTime_container: (self validHandle).
	^ resultValue_
]

{ #category : #'wrappers' }
AVIDEOContainer >> getDuration [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance getDuration_container: (self validHandle).
	^ resultValue_
]

{ #category : #'wrappers' }
AVIDEOContainer >> seekTime: time [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance seekTime_container: (self validHandle) time: time.
	self checkErrorCode: resultValue_
]

{ #category : #'wrappers' }
AVIDEOContainer >> seekFrame: frame_index [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance seekFrame_container: (self validHandle) frame_index: frame_index.
	self checkErrorCode: resultValue_
]

{ #category : #'wrappers' }
AVIDEOContainer >> hasVideoStream [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance hasVideoStream_container: (self validHandle).
	^ resultValue_
]

{ #category : #'wrappers' }
AVIDEOContainer >> getVideoStreamWidth [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance getVideoStreamWidth_container: (self validHandle).
	^ resultValue_
]

{ #category : #'wrappers' }
AVIDEOContainer >> getVideoStreamHeight [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance getVideoStreamHeight_container: (self validHandle).
	^ resultValue_
]

{ #category : #'wrappers' }
AVIDEOContainer >> getVideoStreamFrameCount [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance getVideoStreamFrameCount_container: (self validHandle).
	^ resultValue_
]

{ #category : #'wrappers' }
AVIDEOContainer >> getVideoStreamFrameRate [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance getVideoStreamFrameRate_container: (self validHandle).
	^ resultValue_
]

{ #category : #'wrappers' }
AVIDEOContainer >> fetchAndDecodeNextPacket [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance fetchAndDecodeNextPacket_container: (self validHandle).
	self checkErrorCode: resultValue_
]

{ #category : #'wrappers' }
AVIDEOContainer >> fetchAndDecodeNextVideoFrame [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance fetchAndDecodeNextVideoFrame_container: (self validHandle).
	self checkErrorCode: resultValue_
]

{ #category : #'wrappers' }
AVIDEOContainer >> getVideoFrameIndex [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance getVideoFrameIndex_container: (self validHandle).
	^ resultValue_
]

{ #category : #'wrappers' }
AVIDEOContainer >> getVideoFrameWidth [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance getVideoFrameWidth_container: (self validHandle).
	^ resultValue_
]

{ #category : #'wrappers' }
AVIDEOContainer >> getVideoFrameHeight [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance getVideoFrameHeight_container: (self validHandle).
	^ resultValue_
]

{ #category : #'wrappers' }
AVIDEOContainer >> readSRGB32ConvertedFrame: pitch buffer: buffer [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance readSRGB32ConvertedFrame_container: (self validHandle) pitch: pitch buffer: buffer.
	self checkErrorCode: resultValue_
]

{ #category : #'wrappers' }
AVIDEOContainer >> hasAudioStream [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance hasAudioStream_container: (self validHandle).
	^ resultValue_
]

{ #category : #'wrappers' }
AVIDEOContainer >> getAudioStreamChannels [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance getAudioStreamChannels_container: (self validHandle).
	^ resultValue_
]

{ #category : #'wrappers' }
AVIDEOContainer >> getAudioStreamSampleRate [
	| resultValue_ |
	resultValue_ := AVIDEOCBindings uniqueInstance getAudioStreamSampleRate_container: (self validHandle).
	^ resultValue_
]

