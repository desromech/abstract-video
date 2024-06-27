"
I provide the base glue code for the generated C API bindings.
"
Class {
	#name : #AVIDEOCBindingsBase,
	#superclass : #PhaNAPILibrary,
	#category : #'AbstractVideo-CorePharo'
}

{ #category : #'library downloading' }
AVIDEOCBindingsBase >> fetchLibrary [
	PhaNAPIGitHubRelease fetchLibrary: 'Agpu' fromIcebergRepoOfClass: self class

]

{ #category : #'library path' }
AVIDEOCBindingsBase >> findLibraryPath [
	^ PhaNAPI fullLibraryPathForCurrentPlatform: 'Agpu' package: 'abstract-gpu'
]
