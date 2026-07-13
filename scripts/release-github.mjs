import node_childProcess from "node:child_process"
import node_fs from "node:fs"
import node_path from "node:path"

const
	rootDir =
		node_path.join(import.meta.dirname, ".."),

	packageJsonFilePath =
		node_path.join(
			rootDir,
			"package",
			"package.json",
		),

	packageJson =
		JSON.parse(
			node_fs.readFileSync(
				packageJsonFilePath,
				"utf8",
			),
		)

// GitHub Packages
{
	const packageJsonMod = { ...packageJson }

	// We have to use organization name or scope name for the library's name
	// Change the `uws-react-native` to `@rakadoank/uws-react-native`
	packageJsonMod.name = "@rakadoank/uws-react-native"

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

	node_childProcess.execSync(
		"pnpm publish --filter uws-react-native --access public --no-git-checks",
		{
			cwd: rootDir,
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
	node_childProcess.execSync(
		`pnpm pack --filter uws-react-native`,
		{
			cwd: rootDir,
			stdio: "inherit",
		},
	)

	const
		version =
			packageJson.version,

		/**
		 * With double quotes
		 */
		gitTagArgument =
			`"v${version}"`

	// Create GitHub release
	node_childProcess.execSync(
		`gh release create ${gitTagArgument}` +
			` --title ${gitTagArgument}` +
			` --generate-notes`,
		{
			cwd: rootDir,
			stdio: "inherit",
		},
	)

	// Upload the tarball
	node_childProcess.execSync(
		`gh release upload ${gitTagArgument}` +
			` uws-react-native-${version}.tgz` +
			` --clobber`,
		{
			cwd: rootDir,
			stdio: "inherit",
		},
	)
}
