const
	node_path =
		require("node:path"),

	{ getDefaultConfig, mergeConfig } =
		require("@react-native/metro-config"),

	{ makeMetroConfig } =
		require("@rnx-kit/metro-config"),

	MetroSymlinksResolver =
		require("@rnx-kit/metro-resolver-symlinks")

const
	workspaceRoot =
		node_path.join(__dirname, "..", ".."),

	defaultConfig =
		getDefaultConfig(__dirname)

/**
 * Metro configuration
 * https://reactnative.dev/docs/metro
 *
 * @type {import('@react-native/metro-config').MetroConfig}
 */
const config = {

	projectRoot: __dirname,

	resolver: {
		...defaultConfig.resolver,
		assetExts: [
			...(defaultConfig.resolver?.assetExts?.filter(ext => ext !== "svg") ?? []),
		],
		extraNodeModules: {
			...defaultConfig.resolver?.extraNodeModules,
			"react": node_path.join(__dirname, "node_modules", "react"),
			"uws-react-native": node_path.join(workspaceRoot, "package", "src"),
		},
		// only for monorepo setup
		nodeModulesPaths: [
			...defaultConfig.resolver?.nodeModulesPaths ?? [],
			node_path.join(__dirname, "node_modules"),
			node_path.join(workspaceRoot, "node_modules"),
		],
		resolveRequest: MetroSymlinksResolver(),
		sourceExts: [
			...(defaultConfig.resolver?.sourceExts ?? []),
			"svg",
		],
	},

	transformer: {
		...defaultConfig.transformer,
		babelTransformerPath: require.resolve("react-native-svg-transformer/react-native"),
	},

	// only for monorepo setup
	watchFolders: [
		workspaceRoot,
	],

}

module.exports = makeMetroConfig(
	mergeConfig(defaultConfig, config),
)
