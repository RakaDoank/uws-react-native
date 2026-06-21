import node_fs from "node:fs"
import node_path from "node:path"

/**
 * @param {string} workspaceDir 
 */
export async function prepack(
	workspaceDir,
) {

	{
		// Copy files

		const
			/**
			 * @type {{
			 * 	src: string,
			 * 	dest: string,
			 * }[]}
			 */
			filesToCopy =
				[
					{
						src: node_path.join(workspaceDir, "LICENSE"),
						dest: node_path.join(workspaceDir, "package", "LICENSE"),
					},
					{
						src: node_path.join(workspaceDir, "README.md"),
						dest: node_path.join(workspaceDir, "package", "README.md"),
					},
				]

		await Promise.all(
			filesToCopy.map(file => {
				return node_fs.promises.cp(
					file.src,
					file.dest,
				)
			}),
		)
	}

}
