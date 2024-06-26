Class {
	#name : #AVIDEOTypes,
	#classVars : [
		'avideo_error',
		'avideo_byte',
		'avideo_sbyte',
		'avideo_short',
		'avideo_ushort',
		'avideo_int',
		'avideo_uint',
		'avideo_pointer',
		'avideo_size',
		'avideo_enum',
		'avideo_bool',
		'avideo_float',
		'avideo_double',
		'avideo_bitfield',
		'avideo_cstring',
		'avideo_string',
		'avideo_string_length',
		'avideo_cstring_buffer',
		'avideo_string_buffer',
		'avideo_platform',
		'avideo_context',
		'avideo_stream',
		'avideo_context_open_info'
	],
	#superclass : #SharedPool,
	#category : 'AbstractVideo-GeneratedPharo'
}

{ #category : #'initialize' }
AVIDEOTypes class >> initialize [
"
	self initialize
"
	super initialize.

	avideo_error := #int.
	avideo_byte := #'uchar'.
	avideo_sbyte := #'char'.
	avideo_short := #'short'.
	avideo_ushort := #'ushort'.
	avideo_int := #'int'.
	avideo_uint := #'uint'.
	avideo_pointer := #'void*'.
	avideo_size := #'uint'.
	avideo_enum := #'int'.
	avideo_bool := #'int'.
	avideo_float := #'float'.
	avideo_double := #'double'.
	avideo_bitfield := #'uint'.
	avideo_cstring := #'char*'.
	avideo_string := #'byte*'.
	avideo_string_length := #'int'.
	avideo_cstring_buffer := #'char*'.
	avideo_string_buffer := #'byte*'.
	avideo_platform := #'void'.
	avideo_context := #'void'.
	avideo_stream := #'void'.
	avideo_context_open_info := AVIDEOContextOpenInfo.
]

