import NativeUwsReactNative from "../_internal/native-modules/NativeUwsReactNative"

/**
 * WebSocket compression options. Combine any compressor with any decompressor using bitwise OR.
 */
export enum CompressOptions {
	/**
	 * No compression (always a good idea if you operate using an efficient binary protocol)
	 */
	DISABLED					= NativeUwsReactNative.DISABLED(),

	/**
	 * Zero memory overhead compression.
	 */
	SHARED_COMPRESSOR			= NativeUwsReactNative.SHARED_COMPRESSOR(),

	/**
	 * Zero memory overhead decompression.
	 */
	SHARED_DECOMPRESSOR			= NativeUwsReactNative.SHARED_DECOMPRESSOR(),

	/**
	 * Sliding dedicated compress window, requires 3KB of memory per socket
	 */
	DEDICATED_COMPRESSOR_3KB	= NativeUwsReactNative.DEDICATED_COMPRESSOR_3KB(),

	/**
	 * Sliding dedicated compress window, requires 4KB of memory per socket
	 */
	DEDICATED_COMPRESSOR_4KB	= NativeUwsReactNative.DEDICATED_COMPRESSOR_4KB(),

	/**
	 * Sliding dedicated compress window, requires 8KB of memory per socket
	 */
	DEDICATED_COMPRESSOR_8KB	= NativeUwsReactNative.DEDICATED_COMPRESSOR_8KB(),

	/**
	 * Sliding dedicated compress window, requires 16KB of memory per socket
	 */
	DEDICATED_COMPRESSOR_16KB	= NativeUwsReactNative.DEDICATED_COMPRESSOR_16KB(),

	/**
	 * Sliding dedicated compress window, requires 32KB of memory per socket
	 */
	DEDICATED_COMPRESSOR_32KB	= NativeUwsReactNative.DEDICATED_COMPRESSOR_32KB(),

	/**
	 * Sliding dedicated compress window, requires 64KB of memory per socket
	 */
	DEDICATED_COMPRESSOR_64KB	= NativeUwsReactNative.DEDICATED_COMPRESSOR_64KB(),

	/**
	 * Sliding dedicated compress window, requires 128KB of memory per socket
	 */
	DEDICATED_COMPRESSOR_128KB	= NativeUwsReactNative.DEDICATED_COMPRESSOR_128KB(),

	/**
	 * Sliding dedicated compress window, requires 256KB of memory per socket
	 */
	DEDICATED_COMPRESSOR_256KB	= NativeUwsReactNative.DEDICATED_COMPRESSOR_256KB(),

	/**
	 * Sliding dedicated decompress window, requires 32KB of memory per socket (plus about 23KB)
	 */
	DEDICATED_DECOMPRESSOR_32KB	= NativeUwsReactNative.DEDICATED_DECOMPRESSOR_32KB(),

	/**
	 * Sliding dedicated decompress window, requires 16KB of memory per socket (plus about 23KB)
	 */
	DEDICATED_DECOMPRESSOR_16KB	= NativeUwsReactNative.DEDICATED_DECOMPRESSOR_16KB(),

	/**
	 * Sliding dedicated decompress window, requires 8KB of memory per socket (plus about 23KB)
	 */
	DEDICATED_DECOMPRESSOR_8KB	= NativeUwsReactNative.DEDICATED_DECOMPRESSOR_8KB(),

	/**
	 * Sliding dedicated decompress window, requires 4KB of memory per socket (plus about 23KB)
	 */
	DEDICATED_DECOMPRESSOR_4KB	= NativeUwsReactNative.DEDICATED_DECOMPRESSOR_4KB(),

	/**
	 * Sliding dedicated decompress window, requires 2KB of memory per socket (plus about 23KB)
	 */
	DEDICATED_DECOMPRESSOR_2KB	= NativeUwsReactNative.DEDICATED_DECOMPRESSOR_2KB(),

	/**
	 * Sliding dedicated decompress window, requires 1KB of memory per socket (plus about 23KB)
	 */
	DEDICATED_DECOMPRESSOR_1KB	= NativeUwsReactNative.DEDICATED_DECOMPRESSOR_1KB(),

	/**
	 * Sliding dedicated decompress window, requires 512B of memory per socket (plus about 23KB)
	 */
	DEDICATED_DECOMPRESSOR_512B	= NativeUwsReactNative.DEDICATED_DECOMPRESSOR_512B(),

	/**
	 * Sliding dedicated decompress window, requires 32KB of memory per socket (plus about 23KB)
	 */
	DEDICATED_DECOMPRESSOR		= NativeUwsReactNative.DEDICATED_DECOMPRESSOR(),
}
