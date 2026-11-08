import {
	Config,
} from "bundo.rn/appgen"

export default {
	name: "UWS Example",

	macos: {
		appicon: "ReactNativeAppIcon",

		assetCatalogs: {
			// https://developer.apple.com/documentation/xcode/configuring-your-app-icon
			appiconsets: [
				Config.Apple.createOSXappiconset({
					name: "ReactNativeAppIcon",
					images: {
						"1024x1024": "./assets/react-native.png",
						"512x512": "./assets/react-native-512.png",
						"256x256": "./assets/react-native-256.png",
						"128x128": "./assets/react-native-128.png",
						"64x64": "./assets/react-native-64.png",
						"32x32": "./assets/react-native-32.png",
						"16x16": "./assets/react-native-16.png",
					},
				}),
			],
		},
		buildVersion: "1",
		bundleIdentifier: "id.sufeni.oss.reactnativeuws.example",
		version: "1.0.0",

		resources: [
			"../../node_modules/@audira/carbon-react-native/assets/fonts",
		],

		infoPlist: {
			ATSApplicationFontsPath: "fonts/",
		},
	},

	plugins: [
		[
			"bundo-window",
			{
				hideTitleBar: true,
			},
		],
	],
} satisfies Config.Data
