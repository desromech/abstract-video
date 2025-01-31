Class {
	#name : 'BaselineOfAbstractVideo',
	#superclass : 'BaselineOf',
	#category : 'BaselineOfAbstractVideo',
	#package : 'BaselineOfAbstractVideo'
}

{ #category : 'baselines' }
BaselineOfAbstractVideo >> baseline: spec [
    <baseline>

	spec for: #pharo do: [ self baselineForPharo: spec ].
	spec for: #squeak do: [ self baselineForSqueak: spec ].
]

{ #category : 'baselines' }
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
		]

]

{ #category : 'baselines' }
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
		]
]

{ #category : 'baselines' }
BaselineOfAbstractVideo >> postLoadActionsForPharo [
	(Smalltalk globals at: #AVIDEOGeneratedDoIt) initializeBindings.
]

{ #category : 'baselines' }
BaselineOfAbstractVideo >> postLoadActionsForSqueak [
	(Smalltalk globals at: #AVIDEOGeneratedDoIt) initializeBindings.
]
