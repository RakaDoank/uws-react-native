import NativeUwsReactNative from "../_internal/native-modules/NativeUwsReactNative";

// import type {
// 	us_listen_socket,
// 	us_socket,
// } from "../types"

/**
 * Gets local port of socket (or listenSocket) or -1.
 */
export function us_socket_local_port(
	token: number,
	// socket: us_socket | us_listen_socket,
) : number {
	return NativeUwsReactNative._us_socket_local_port(token);
}
