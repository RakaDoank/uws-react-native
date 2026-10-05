import node_childProcess from "node:child_process"
import node_path from "node:path"

import SemverPrelease from "semver/functions/prerelease.js"

import UwsReactNativePackageJson from "../package/package.json" with { type: "json" }

const
	rootDir =
		node_path.join(import.meta.dirname, ".."),

	packageDir =
		node_path.join(rootDir, "package"),

	libraryVersionPrerelease =
		SemverPrelease(UwsReactNativePackageJson.version)

// Bob
node_childProcess.execSync(
	`bun run package-builder bob`,
	{
		cwd: rootDir,
		stdio: "inherit",
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

let publishCommand =
	"bunx npm publish"
		+ ` ./${UwsReactNativePackageJson.name}-${UwsReactNativePackageJson.version}.tgz`
		+ " --access public"

if(typeof libraryVersionPrerelease?.[0] == "string") {
	publishCommand += ` --tag ${libraryVersionPrerelease[0]}`
}

node_childProcess.execSync(
	publishCommand,
	{
		cwd: packageDir,
		stdio: "inherit",
	},
)
