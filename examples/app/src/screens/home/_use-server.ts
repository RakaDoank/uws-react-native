import {
	useEffect,
} from "react"

import * as uWS from "uws-react-native"

/**
 * This is the actual uWebSockets server.
 * 
 * You need to run the server inside of useEffect.
 * Otherwise, your server may run forever until the app is killed.
 * 
 * `useEffect` is a perfect tool for production usage, and even in development.
 * 
 * In development mode, you can try update these code below, and the server will be restarted automatically because of the `useEffect` cycle
 */
export function useServer({
	port,
}: {
	port: number,
}) {

	useEffect(() => {
		const app = uWS.App()

		app.get("/test", res => {
			res.end("Yeay");
		})

		app.get("/long-operation", async res => {
			let isAborted = false
			res.onAborted(() => {
				console.log("onAborted long operation")
				isAborted = true
			})

			await new Promise(resolver => {
				setTimeout(() => {
					resolver(true)
				}, 3000)
			})

			if(!isAborted) {
				res.end("long operation")
			}
		})

		app.get("/headers", (res, req) => {
			res.write("<html><body><h2>Hello, your headers are:</h2><ul>")

			req.forEach((k, v) => {
				res.write("<li>")
				res.write(k)
				res.write(" = ")
				res.write(v)
				res.write("</li>")
			})

			res.end("</ul></body></html>");
		})

		app.post("/ondata", res => {
			let isAborted = false
			res.onAborted(() => {
				isAborted = true
			})

			res.onData((chunk, isLast) => {
				if(isLast && !isAborted) {
					res.writeHeader("content-type", "application/json")
					res.end(
						JSON.stringify({
							type: "onData",
							byteLength: chunk.byteLength,
						}),
					)
				}
			})
		})

		app.post("/ondatav2", (res) => {
			let isAborted = false
			res.onAborted(() => {
				isAborted = true
			})

			res.onDataV2((chunk, maxRemainingBodyLength) => {
				console.log("onDataV2", chunk.byteLength, maxRemainingBodyLength)
				if(!maxRemainingBodyLength && !isAborted) {
					res.writeHeader("content-type", "application/json")
					res.end(
						JSON.stringify({
							type: "onDataV2",
							byteLength: chunk.byteLength,
						}),
					)
				}

				// already stop collecting because the `maxBodySize` option
				// if(chunk.byteLength >= 1024 * 1024) {
				// 	res.writeHeader("content-type", "application/json")
				// 	res.end(
				// 		JSON.stringify({
				// 			type: "onDataV2",
				// 			byteLength: chunk.byteLength,
				// 			maxRemainingBodyLength,
				// 		}),
				// 	)
				// }
			})
		})

		app.post("/onfulldata", res => {
			let isAborted = false
			res.onAborted(() => {
				isAborted = true
			})

			res.onFullData(chunk => {
				console.log("onFullData", chunk.byteLength)
				if(!isAborted) {
					res.writeHeader("content-type", "application/json")
					res.end(
						JSON.stringify({
							type: "onFullData",
							byteLength: chunk.byteLength,
						}),
					)
				}
			})
		})

		app.post("/get-form-data", (res, req) => {
			const requestContentType = req.getHeader("content-type")

			console.log("/get-form-data requestContentType", requestContentType)
			if(requestContentType.startsWith("multipart/form-data")) {
				res.onFullData(body => {
					res.writeHeader("content-type", "application/json")
					console.log("/get-form-data fulldata", body.byteLength, requestContentType)

					try {
						const multipartField = uWS.getParts(body, requestContentType)

						if(multipartField?.length) {
							const textDecoder = new TextDecoder("utf-8")
							const text1Part = multipartField.find(p => p.name == "text1")

							let text1 = ""

							if(text1Part) {
								text1 = textDecoder.decode(text1Part.data)
							}

							res.end(
								JSON.stringify({
									fields: multipartField.map(field => {
										return {
											_byteLength: field.data.byteLength,
											name: field.name,
											filename: field.filename,
											type: field.type,
										}
									}),
									decodedFields: {
										text1,
									},
									success: true,
								}),
							)
						} else {
							throw new Error()
						}
					} catch(err) {
						console.log("/get-form-data error", err instanceof Error ? err.message : err)
						res.end(
							JSON.stringify({
								data: null,
								success: false,
							}),
						)
					}
				})
			} else {
				res.writeHeader("content-type", "application/json")
				res.end(
					JSON.stringify({
						data: null,
						success: false,
						message: "Header content-type is not multipart/form-data",
					}),
				)
			}
		})

		// ++++++++++++++++++++++++++++++
		// +++++ For UI tester tool +++++
		// ++++++++++++++++++++++++++++++

		app.get("/request/:foo/:bar", (res, req) => {
			console.log("/request/:foo/:bar")
			res.onAborted(() => {
				console.log("onAbort")
			})

			const forEachResult: Record<string, string> = {}

			req.forEach((key, val) => {
				forEachResult[key] = val
			})

			console.log("forEach", forEachResult)

			res.writeHeader("content-type", "application/json")
			res.end(
				JSON.stringify({
					forEach: forEachResult,
					getCaseSensitiveMethod: req.getCaseSensitiveMethod(),
					getHeader: req.getHeader("connection"),
					getParameter: `${req.getParameter(0)} - ${req.getParameter("foo")} | ${req.getParameter(1)} - ${req.getParameter("bar")}`,
					getMethod: req.getMethod(),
					getUrl: req.getUrl(),
					getQuery: req.getQuery() || null,
				}),
			)
		})

		// TextDecoder is supported only for React Native 0.85 and latest
		app.post("/read-json-from-arraybuffer", res => {
			let isAborted = false
			res.onAborted(() => {
				isAborted = true
			})

			if(!isAborted) {
				res.onFullData(chunk => {
					try {
						const textDecoder = new TextDecoder("utf-8")
						const text = textDecoder.decode(chunk)
						const json = JSON.parse(text) as unknown

						if(!isAborted) {
							// send it back in JSON
							res.writeHeader("content-type", "application/json")
							res.end(
								JSON.stringify(json),
							)
						}
					} catch {
						res.end("not valid data")
					}
				})
			}
		})

		app.post("/read-json-from-text", res => {
			let isAborted = false
			res.onAborted(() => {
				isAborted = true
			})

			if(!isAborted) {
				res.onFullDataText(body => {
					try {
						const json = JSON.parse(body) as unknown

						if(!isAborted) {
							// send it back in JSON
							res.writeHeader("content-type", "application/json")
							res.end(
								JSON.stringify(json),
							)
						}
					} catch {
						res.end("not valid data")
					}
				})
			}
		})

		// ------------------------------
		// ----- For UI tester tool -----
		// ------------------------------

		// iOS will fail to listen/run the server without explicit host 127.0.0.1
		app.listen("127.0.0.1", port, token => {
			if(token) {
				console.log("Listening at 5000")
			} else {
				console.log("Failed to listen")
			}
		})

		return () => {
			app.close()
		}
	}, [
		port,
	])

}
