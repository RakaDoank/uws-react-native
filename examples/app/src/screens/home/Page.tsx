/* eslint-disable @typescript-eslint/no-misused-promises */
import {
	useContext,
	useRef,
} from "react"

import {
	CarbonStyleSheet,
	Notification,
	Table,
	TableCell,
	TableHeader,
	TableRowHeader,
	TableToolbar,
	TableToolbarButton,
	ToastContext,
} from "@audira/carbon-react-native"

import {
	Item,
	type ItemRef,
} from "./_item"

import {
	useServer,
} from "./_use-server"

/**
 * This bunch of UI is just a tester tool with a nice display.
 * 
 * For the actual server code, see the "./_use-server.ts" instead.
 */
export function Page() {

	/**
	 * This is the actual server
	 */
	useServer({ port: PORT })

	const
		toastContext =
			useContext(ToastContext),

		itemRefs =
			useRef<(ItemRef | null)[]>([]),

		isRunningTests =
			useRef<boolean[]>([]),

		setItemRef =
			(
				itemRef: ItemRef | null,
				index: number,
			) => {
				itemRefs.current[index] = itemRef
			},

		test_0 =
			async () => {
				isRunningTests.current[0] = true

				try {
					const
						param1 =
							"im",

						param2 =
							"okay",

						isValid =
							await fetch(`${SERVER_BASE_URL}/request/${param1}/${param2}?foo=bar&im=okay`, {
								method: "GET",
							})
								.then(async res => {
									try {
										const json = await res.json() as unknown as Record<string, string>

										return typeof json.forEach === "object" && json.forEach &&
											json.getCaseSensitiveMethod === "GET" &&

											typeof json.getHeader === "string" &&
											json.getHeader.length &&

											json.getMethod === "get" &&

											typeof json.getParameter == "string" &&
											json.getParameter === `${param1} - ${param1} | ${param2} - ${param2}` &&

											json.getQuery === "foo=bar&im=okay" &&

											json.getUrl === `/request/${param1}/${param2}`
									} catch {
										// is not valid json
										return false
									}
								})

					if(isValid) {
						itemRefs.current[0]?.setState({
							status: "finished",
							message: "HttpRequest object is valid",
						})
					} else {
						throw new Error("Invalid parameters")
					}
				} catch(err) {
					itemRefs.current[0]?.setState({
						status: "error",
						message: err instanceof Error ? err.message : null,
					})
				}

				isRunningTests.current[0] = false
			},

		test_1 =
			async () => {
				isRunningTests.current[1] = true

				try {
					const response = await fetch(`${SERVER_BASE_URL}/long-operation`, {
						method: "GET",
					})

					if(response.status == 200) {
						itemRefs.current[1]?.setState({
							status: "finished",
							message: null,
						})
					} else {
						throw new Error("Server is not responding")
					}
				} catch(err) {
					itemRefs.current[1]?.setState({
						status: "error",
						message: err instanceof Error ? err.message : null,
					})
				}

				isRunningTests.current[1] = false
			},

		test_2 =
			async () => {
				isRunningTests.current[2] = true

				try {
					const response = await fetch(`${SERVER_BASE_URL}/randomass`, {
						method: "GET",
					})

					if(response.status === 404) {
						itemRefs.current[2]?.setState({
							status: "finished",
							message: "Response is 404",
						})
					} else {
						throw new Error("Server is not responding with 404 status")
					}
				} catch(err) {
					itemRefs.current[2]?.setState({
						status: "error",
						message: err instanceof Error ? err.message : null,
					})
				}

				isRunningTests.current[2] = false
			},

		test_3 =
			async () => {
				isRunningTests.current[3] = true

				try {
					const
						resJson =
							await fetch(`${SERVER_BASE_URL}/read-json-from-arraybuffer`, {
								method: "POST",
								body: jsonString,
							})
								.then(res => res.text())

					if(resJson === jsonString) {
						itemRefs.current[3]?.setState({
							status: "finished",
							message: "Valid JSON",
						})
					} else {
						throw new Error("JSON from server and client is not equal")
					}
				} catch(err) {
					itemRefs.current[3]?.setState({
						status: "error",
						message: err instanceof Error ? err.message : null,
					})
				}

				isRunningTests.current[3] = false
			},

		test_4 =
			async () => {
				isRunningTests.current[4] = true

				try {
					const
						resJson =
							await fetch(`${SERVER_BASE_URL}/read-json-from-text`, {
								method: "POST",
								body: jsonString,
							})
								.then(res => res.text())

					if(resJson === jsonString) {
						itemRefs.current[4]?.setState({
							status: "finished",
							message: "Valid JSON",
						})
					} else {
						throw new Error("JSON from server and client is not equal")
					}
				} catch(err) {
					itemRefs.current[4]?.setState({
						status: "error",
						message: err instanceof Error ? err.message : null,
					})
				}

				isRunningTests.current[4] = false
			},

		runAllTests =
			() => {
				if(isRunningTests.current.indexOf(true) > -1) {
					toastContext.show(() => (
						<Notification.Toast.Error
							title="Not Allowed"
							subtitle="Wait until all testing is complete"
						/>
					), {
						duration: 3000,
					})

					return
				}

				itemRefs.current.forEach(itemRef => {
					itemRef?.setState({
						status: "active",
						message: null,
					})
				})

				Promise.all([
					test_0(),
					test_1(),
					test_2(),
					test_3(),
					test_4(),
				])
			}

	return (
		<Table
			header={ <>
				<TableHeader
					title="UWS Example"
					description="Hit the server from your PC to the iOS simulator via localhost, or Android Emulator (through ADB port forwarding), or to an Android device IP in the same network. You can also run this simple test below"
				/>

				<TableToolbar
					buttons={ <>
						<TableToolbarButton.Primary
							text="Run All Tests"
							onPress={ runAllTests }
						/>
					</> }
				/>
			</> }
			style={ [
				CarbonStyleSheet.g.py_10,
				CarbonStyleSheet.g.mx_05,
			] }
		>
			<TableRowHeader>
				<TableCell
					text="Test Name"
					width={ Item.Widths[0] }
				/>
				<TableCell
					text="Endpoint"
					width={ Item.Widths[1] }
				/>
				<TableCell
					text="Status"
					width={ Item.Widths[2] }
				/>
				<TableCell
					text="Message"
					width={ Item.Widths[3] }
				/>
				<TableCell
					text=""
					width={ Item.Widths[4] }
				/>
			</TableRowHeader>

			<Item
				ref={ itemRef => setItemRef(itemRef, 0) }
				testName="HttpRequest Instance"
				endpoint="/request/:foo/:bar"
				onPressTest={ test_0 }
			/>

			<Item
				ref={ itemRef => setItemRef(itemRef, 1) }
				testName="Long Operation Mock"
				endpoint="/long-operation"
				onPressTest={ test_1 }
			/>

			<Item
				ref={ itemRef => setItemRef(itemRef, 2) }
				testName="404 Status"
				endpoint="/random"
				onPressTest={ test_2 }
			/>

			<Item
				ref={ itemRef => setItemRef(itemRef, 3) }
				testName="Tell server to read JSON from ArrayBuffer"
				endpoint="/read-json-from-arraybuffer"
				onPressTest={ test_3 }
			/>

			<Item
				ref={ itemRef => setItemRef(itemRef, 4) }
				testName="Tell server to read JSON from raw text"
				endpoint="/read-json-from-text"
				onPressTest={ test_4 }
			/>
		</Table>
	)

}

const
	PORT =
		5000,

	SERVER_BASE_URL =
		`http://localhost:${PORT}`,

	jsonString =
		JSON.stringify({
			boolean: {
				true: true,
				false: false,
			},
			number: {
				negative: -1,
				zero: 0,
				positive: 1,
			},
			string: "Ich liebe dich",
			array: {
				boolean: [true, false, true, false],
				number: [-1024, 0, 1024],
				string: ["Ich", "liebe", "dich"],
			},
		})
