import {
	View,
	type ViewProps,
} from "react-native"

import {
	CarbonReactNative,
	CarbonStyleSheet,
	DialogProvider,
	ToastProvider,
} from "@audira/carbon-react-native"

import {
	Screens,
} from "@examples/app"

import {
	SafeAreaProvider,
} from "react-native-safe-area-context"

export function App() {

	return (
		<SafeAreaProvider>
			<CarbonReactNative>
				<ToastProvider>
					<DialogProvider>
						<BgView>
							<Screens.Home.Page/>
						</BgView>
					</DialogProvider>
				</ToastProvider>
			</CarbonReactNative>
		</SafeAreaProvider>
	)

}

const
	carbonStyleSheet =
		CarbonStyleSheet.create({
			bgView: {
				backgroundColor: CarbonStyleSheet.color.background,
			},
		})

interface BgViewProps extends ViewProps {
}
function BgView({
	style,
	...props
}: BgViewProps) {

	CarbonStyleSheet.use()

	return (
		<View
			{ ...props }
			style={ [
				CarbonStyleSheet.g.flex_auto,
				carbonStyleSheet.bgView,
				style,
			] }
		/>
	)

}
