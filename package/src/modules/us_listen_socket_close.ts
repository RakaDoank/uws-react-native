import NativeReactNativeUws from "../_internal/native-modules/NativeReactNativeUws";

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
	NativeReactNativeUws._us_listen_socket_close(token);
}
