import NativeUwsReactNative from "../_internal/native-modules/NativeUwsReactNative";

// import type {
// 	us_listen_socket,
// } from "../types"

/**
 * Closes a uSockets listen socket.
 */
export function us_listen_socket_close(
	token: number,
	// listenSocket: us_listen_socket,
) {
	NativeUwsReactNative._us_listen_socket_close(token);
}
