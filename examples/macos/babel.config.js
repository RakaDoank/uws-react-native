module.exports = {
	presets: [
		require.resolve("@react-native/babel-preset"),
	],
	plugins: [
		require("@babel/plugin-transform-export-namespace-from"),
	],
}
