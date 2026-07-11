import type {
	InlineLoadingState,
} from "@audira/carbon-react-native"

export interface ItemState {
	status: InlineLoadingState | "pending",
	message: string | null,
}
