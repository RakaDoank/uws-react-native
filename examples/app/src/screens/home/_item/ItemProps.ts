import type {
	TableRowProps,
} from "@audira/carbon-react-native"

import type {
	ItemRef,
} from "./ItemRef"

export interface ItemProps extends Omit<TableRowProps, "children" | "ref"> {
	testName: string,
	endpoint: string,
	onPressTest: () => void,
	ref?: React.Ref<ItemRef>,
}
