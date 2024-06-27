Class {
	#name : #BaselineOfAbstractVideo,
	#superclass : #BaselineOf,
	#category : #BaselineOfAbstractVideo
}

{ #category : #baselines }
BaselineOfAbstractVideo >> baseline: spec [
    <baseline>

	spec for: #pharo do: [ self baselineForPharo: spec ].
	spec for: #squeak do: [ self baselineForSqueak: spec ].
]

{ #category : #baselines }
BaselineOfAbstractVideo >> baselineForPharo: spec [
	spec postLoadDoIt: #postLoadActionsForPharo.
	spec
		baseline: #'PhaNAPI' with: [
			spec repository: 'github://desromech/phanapi'
		];
		package: #'AbstractVideo-CorePharo' with: [
			spec requires: #(#'PhaNAPI' ).
		];
		package: #'AbstractVideo-GeneratedPharo' with: [
			spec requires: #(#'AbstractVideo-CorePharo' )
		];
		package: #'AbstractVideo-Samples' with: [
			spec requires: #(#'AbstractVideo-Window' #'AbstractVideo-CorePharo' #'AbstractVideo-GeneratedPharo' )
		];
		package: #'AbstractVideo-Utility' with: [
			spec requires: #(#'AbstractVideo-GeneratedPharo' #'AbstractVideo-CorePharo' )
		];
		package: #'AbstractVideo-Window' with: [
			spec requires: #(#'AbstractVideo-GeneratedPharo' #'AbstractVideo-CorePharo' #'AbstractVideo-Utility').
		]

]

{ #category : #baselines }
BaselineOfAbstractVideo >> baselineForSqueak: spec [
	spec postLoadDoIt: #postLoadActionsForSqueak.
	spec
		project: 'FFI' with: [
			spec
				className: 'ConfigurationOfFFI';
				repository: 'http://www.squeaksource.com/MetacelloRepository';
				versionString: #development;
				loads: #('Core')
		];
		baseline: #'PhaNAPI' with: [
			spec repository: 'github://desromech/phanapi'
		];
		package: #'AbstractVideo-CoreSqueak' with: [
			spec requires: #(#'PhaNAPI' )
		];
		package: #'AbstractVideo-GeneratedSqueak' with: [
			spec requires: #(#'AbstractVideo-CoreSqueak' )
		];
		package: #'AbstractVideo-Samples' with: [
			spec requires: #(#'AbstractVideo-Window' #'AbstractVideo-CoreSqueak' #'AbstractVideo-GeneratedSqueak')
		];
		package: #'AbstractVideo-Utility' with: [
			spec requires: #(#'AbstractVideo-CoreSqueak' #'AbstractVideo-GeneratedSqueak')
		];
		package: #'AbstractVideo-Window' with: [
			spec requires: #(#'AbstractVideo-CoreSqueak' #'AbstractVideo-GeneratedSqueak' #'AbstractVideo-Utility').
		]

]

{ #category : #baselines }
BaselineOfAbstractVideo >> postLoadActionsForPharo [
	(Smalltalk globals at: #AVIDEOCBindings) fetchLibraryInPostLoadAction.
	(Smalltalk globals at: #AVIDEOGeneratedDoIt) initializeBindings.
]

{ #category : #baselines }
BaselineOfAbstractVideo >> postLoadActionsForSqueak [
	(Smalltalk globals at: #AVIDEOGeneratedDoIt) initializeBindings.
]
