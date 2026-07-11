import type {
	ItemState,
} from "./ItemState"

export interface ItemRef {
	setState: (
		data: ItemState,
	) => void,
}
