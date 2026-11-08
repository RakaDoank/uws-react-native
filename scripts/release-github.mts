import node_childProcess from "node:child_process"
import node_fs from "node:fs"
import node_path from "node:path"

const
	rootDir =
		node_path.join(import.meta.dirname, ".."),

	packageDir =
		node_path.join(rootDir, "package"),

	packageJsonFilePath =
		node_path.join(
			packageDir,
			"package.json",
		),

	packageJson =
		JSON.parse(
			node_fs.readFileSync(
				packageJsonFilePath,
				"utf8",
			),
		) as typeof import("../package/package.json")

// Bob
node_childProcess.execSync(
	`bun run package-builder bob`,
	{
		cwd: rootDir,
		stdio: "inherit",
	},
)

// GitHub Packages
{
	const packageJsonMod = { ...packageJson }

	// We have to use organization name or scope name for the library's name
	// Change the `uws-react-native` to `@rakadoank/uws-react-native`
	packageJsonMod.name = "@rakadoank/uws-react-native"

	// @ts-expect-error Add package to the GitHub Packages registry
	// https://docs.github.com/en/packages/working-with-a-github-packages-registry/working-with-the-npm-registry#publishing-a-package-using-publishconfig-in-the-packagejson-file
	packageJsonMod.publishConfig = {
		registry: "https://npm.pkg.github.com",
	}

	// write modified package.json
	node_fs.writeFileSync(
		packageJsonFilePath,
		JSON.stringify(
			packageJsonMod,
			null,
			2,
		),
		{
			encoding: "utf8",
		},
	)

	// Create the tarball file
	node_childProcess.execSync(
		"bun pm pack",
		{
			cwd: packageDir,
			stdio: "inherit",
		},
	)

	node_childProcess.execSync(
		"bunx npm publish"
			+ ` ./rakadoank-uws-react-native-${packageJson.version}.tgz`
			+ " --access public",
		{
			cwd: packageDir,
			stdio: "inherit",
		},
	)

	// Restore the original package.json content
	node_fs.writeFileSync(
		packageJsonFilePath,
		JSON.stringify(
			packageJson,
			null,
			2,
		),
		{
			encoding: "utf8",
		},
	)
}

// GitHub Release
{
	// Create the tarball file
	node_childProcess.execSync(
		"bun pm pack",
		{
			cwd: packageDir,
			stdio: "inherit",
		},
	)

	const
		version =
			packageJson.version,

		/**
		 * With double quotes
		 */
		gitTag =
			`"v${version}"`

	// Create GitHub release
	node_childProcess.execSync(
		`gh release create ${gitTag}` +
			` --title ${gitTag}` +
			` --generate-notes`,
		{
			cwd: rootDir,
			stdio: "inherit",
		},
	)

	// Upload the tarball
	node_childProcess.execSync(
		`gh release upload ${gitTag}` +
			` uws-react-native-${version}.tgz` +
			` --clobber`,
		{
			cwd: rootDir,
			stdio: "inherit",
		},
	)
}
