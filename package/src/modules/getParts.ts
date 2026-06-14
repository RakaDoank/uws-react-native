import NativeReactNativeUws from "../_internal/native-modules/NativeReactNativeUws"

/**
 * Takes a POSTed body and contentType, and returns an array of parts if the request is a multipart request
 */
export function getParts(
	body: ArrayBuffer | string,
	contentType: string,
) : MultipartField[] | undefined {
	// TODO
}
