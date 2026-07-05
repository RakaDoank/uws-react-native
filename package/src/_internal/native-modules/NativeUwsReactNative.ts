import {
	TurboModuleRegistry,
	type CodegenTypes,
	type TurboModule,
} from "react-native"

/**
 * This spec is only for C++.
 */
export interface Spec extends TurboModule {
	App: (
		/**
		 * @see {@link file:///./../../types/AppOptions.ts}
		 */
		appOptions?: CodegenTypes.UnsafeObject,
	) => CodegenTypes.UnsafeObject,

	getParts: (
		/**
		 * Has to be an ArrayBuffer.
		 * Codegen map this to facebook::jsi::Object.
		 */
		body: unknown,
		contentType: string,
	) => unknown, // Codegen map this to facebook::jsi::Object

	_us_listen_socket_close: (
		id: CodegenTypes.Int32,
		// listenSocket: CodegenTypes.UnsafeObject,
	) => void,

	_us_socket_local_port: (
		id: CodegenTypes.Int32,
		// socket: CodegenTypes.UnsafeObject,
	) => number,

	/**
	 * No compression (always a good idea if you operate using an efficient binary protocol)
	 */
	DISABLED: () => number,

	/**
	 * Zero memory overhead compression.
	 */
	SHARED_COMPRESSOR: () => number,

	/**
	 * Zero memory overhead decompression.
	 */
	SHARED_DECOMPRESSOR: () => number,

	/**
	 * Sliding dedicated compress window, requires 3KB of memory per socket
	 */
	DEDICATED_COMPRESSOR_3KB: () => number,

	/**
	 * Sliding dedicated compress window, requires 4KB of memory per socket
	 */
	DEDICATED_COMPRESSOR_4KB: () => number,

	/**
	 * Sliding dedicated compress window, requires 8KB of memory per socket
	 */
	DEDICATED_COMPRESSOR_8KB: () => number,

	/**
	 * Sliding dedicated compress window, requires 16KB of memory per socket
	 */
	DEDICATED_COMPRESSOR_16KB: () => number,

	/**
	 * Sliding dedicated compress window, requires 32KB of memory per socket
	 */
	DEDICATED_COMPRESSOR_32KB: () => number,

	/**
	 * Sliding dedicated compress window, requires 64KB of memory per socket
	 */
	DEDICATED_COMPRESSOR_64KB: () => number,

	/**
	 * Sliding dedicated compress window, requires 128KB of memory per socket
	 */
	DEDICATED_COMPRESSOR_128KB: () => number,

	/**
	 * Sliding dedicated compress window, requires 256KB of memory per socket
	 */
	DEDICATED_COMPRESSOR_256KB: () => number,

	/**
	 * Sliding dedicated decompress window, requires 32KB of memory per socket (plus about 23KB)
	 */
	DEDICATED_DECOMPRESSOR_32KB: () => number,

	/**
	 * Sliding dedicated decompress window, requires 16KB of memory per socket (plus about 23KB)
	 */
	DEDICATED_DECOMPRESSOR_16KB: () => number,

	/**
	 * Sliding dedicated decompress window, requires 8KB of memory per socket (plus about 23KB)
	 */
	DEDICATED_DECOMPRESSOR_8KB: () => number,

	/**
	 * Sliding dedicated decompress window, requires 4KB of memory per socket (plus about 23KB)
	 */
	DEDICATED_DECOMPRESSOR_4KB: () => number,

	/**
	 * Sliding dedicated decompress window, requires 2KB of memory per socket (plus about 23KB)
	 */
	DEDICATED_DECOMPRESSOR_2KB: () => number,

	/**
	 * Sliding dedicated decompress window, requires 1KB of memory per socket (plus about 23KB)
	 */
	DEDICATED_DECOMPRESSOR_1KB: () => number,

	/**
	 * Sliding dedicated decompress window, requires 512B of memory per socket (plus about 23KB)
	 */
	DEDICATED_DECOMPRESSOR_512B: () => number,

	/**
	 * Sliding dedicated decompress window, requires 32KB of memory per socket (plus about 23KB)
	 */
	DEDICATED_DECOMPRESSOR: () => number,
}

export default TurboModuleRegistry.getEnforcing<Spec>(
	"UwsReactNative",
)
