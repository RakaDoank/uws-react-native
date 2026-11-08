const
	{
		getDefaultConfig,
	} =
		require("expo/metro-config"),

	{
		mergeConfig,
	} =
		require("@expo/metro/metro-config")

const
	projectRoot =
		__dirname,

	defaultConfig =
		getDefaultConfig(__dirname)

/**
 * Metro configuration
 * https://reactnative.dev/docs/metro
 *
 * @type {import('@expo/metro-config').MetroConfig}
 */
const config = {

	projectRoot,

	resolver: {
		...defaultConfig.resolver,
		assetExts: defaultConfig.resolver.assetExts.filter(ext => ext !== "svg"),
		sourceExts: [
			...defaultConfig.resolver.sourceExts,
			"svg",
		],
	},

	transformer: {
		...defaultConfig.transformer,
		babelTransformerPath: require.resolve("react-native-svg-transformer/expo"),
	},

};

module.exports = mergeConfig(defaultConfig, config);
