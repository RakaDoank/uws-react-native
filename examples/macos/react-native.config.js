const
	node_path =
		require("node:path"),

	libraryPackageJson =
		require("../../package/package.json")

/**
 * @type {import("@react-native-community/cli-types").Config}
 * @see {@link https://github.com/react-native-community/cli/blob/main/docs/configuration.md}
 * @see {@link https://github.com/react-native-community/cli/blob/main/docs/autolinking.md#how-can-i-autolink-a-local-library}
 */
module.exports = {
	dependencies: {
		/**
		 * https://github.com/react-native-community/cli/blob/main/docs/autolinking.md#how-can-i-autolink-a-local-library
		 */
		[libraryPackageJson.name]: {
			root: node_path.join(__dirname, "..", "..", "package"),
		},
	},
}
