export interface WebSocketUserData {
	getBoolean(
		key: string,
	): boolean | undefined,

	setBoolean(
		key: string,
		value: boolean,
	): void,

	getNumber(
		key: string,
	): number | undefined,

	setNumber(
		key: string,
		value: number,
	): void,

	getString(
		key: string,
	): string | undefined,

	setString(
		key: string,
		value: string,
	): void,
}
