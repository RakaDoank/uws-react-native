const
	node_path =
		require("node:path"),

	{ makeMetroConfig } =
		require("@rnx-kit/metro-config"),

	MetroSymlinksResolver =
		require("@rnx-kit/metro-resolver-symlinks")

const
	workspaceRoot =
		node_path.join(__dirname, "..", ".."),

	workspaceNodeModules =
		node_path.join(workspaceRoot, "node_modules"),

	rnxKitMetroConfig =
		makeMetroConfig()

/**
 * Metro configuration
 * https://reactnative.dev/docs/metro
 *
 * @type {import('@react-native/metro-config').MetroConfig}
 */
const config = {

	...rnxKitMetroConfig,

	projectRoot: __dirname,

	resolver: {
		...rnxKitMetroConfig.resolver,
		assetExts: [
			...(rnxKitMetroConfig.resolver?.assetExts?.filter(ext => ext !== "svg") ?? []),
		],
		nodeModulesPaths: [
			node_path.join(__dirname, "node_modules"),
			workspaceNodeModules,
		],
		resolveRequest: MetroSymlinksResolver(),
		sourceExts: [
			...(rnxKitMetroConfig.resolver?.sourceExts ?? []),
			"svg",
		],
	},

	watchFolders: [
		node_path.join(workspaceRoot, "examples", "app"),
		node_path.join(workspaceRoot, "package"),
		workspaceNodeModules,
	],

	transformer: {
		...rnxKitMetroConfig.transformer,
		babelTransformerPath: require.resolve("react-native-svg-transformer/react-native"),
	},

}

module.exports = config
