export enum WebSocketSendStatus {
	/**
	 * For built up backpressure that will drain over time.
	 */
	BACKPRESSURE = 0,
	/**
	 * Success
	 */
	SUCCESS,
	/**
	 * Dropped due to backpressure limit
	 */
	DROPPED,
}
