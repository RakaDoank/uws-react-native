import {
	useCallback,
	useContext,
	useImperativeHandle,
	useState,
} from "react"

import {
	Pressable,
} from "react-native"

import {
	Button,
	CarbonStyleSheet,
	DialogContext,
	InlineLoading,
	Modal,
	ModalContent,
	TableCell,
	TableCellText,
	TableRow,
	Text,
	ThemeContext,
} from "@audira/carbon-react-native"

import {
	Color,
} from "@audira/carbon-react-native-elements"

import IconView from "@carbon/icons/svg/32/view.svg"

import type {
	ItemProps,
} from "./ItemProps"

import type {
	ItemState,
} from "./ItemState"

export function Item({
	testName,
	endpoint,
	onPressTest,
	ref,
	...props
}: ItemProps) {

	const
		themeContext =
			useContext(ThemeContext),

		dialogContext =
			useContext(DialogContext),

		[state, setState] =
			useState<ItemState>({
				status: "inactive",
				message: null,
			})

	const
		runTestHandler =
			useCallback(() => {
				setState(currState => ({
					status: "active",
					message: currState.message,
				}))

				onPressTest()
			}, [
				onPressTest,
			]),

		showMessage =
			useCallback((
				message: string,
			) => {
				dialogContext.show({
					component: (
						<Modal
							title="Message"
							buttonCloseProps={{
								onPress() {
									dialogContext.dismiss()
								},
							}}
						>
							<ModalContent>
								<Text>
									{ message }
								</Text>
							</ModalContent>

							<Button.Primary
								text="Okay"
								onPress={ () => {
									dialogContext.dismiss()
								} }
								style={ [
									CarbonStyleSheet.g.self_end,
								] }
							/>
						</Modal>
					),
				})
			}, [
				dialogContext,
			])

	useImperativeHandle(ref, () => {
		return {
			setState,
		}
	}, [])

	return (
		<TableRow
			{ ...props }
		>
			<TableCell
				text={ testName }
				width={ Widths[0] }
			/>

			<TableCell
				text={ endpoint }
				width={ Widths[1] }
			/>

			<TableCell
				width={ Widths[2] }
			>
				<InlineLoading
					state={ state.status == "pending" ? "active" : state.status }
					text={ mapStatusText[state.status] }
				/>
			</TableCell>

			<TableCell
				width={ Widths[3] }
			>
				<Pressable
					disabled={ !state.message }
					onPress={ () => showMessage(state.message!) }
					style={ [
						CarbonStyleSheet.g.flex_row,
						CarbonStyleSheet.g.items_center,
						CarbonStyleSheet.g.gap_x_03,
					] }
				>
					{ !!state.message && (
						<IconView
							width={ 14 }
							height={ 14 }
							fill={ mapMessageIconColor[themeContext.colorScheme] }
						/>
					) }
					<TableCellText
						numberOfLines={ 1 }
						ellipsizeMode="tail"
					>
						{ state.message || "-" }
					</TableCellText>
				</Pressable>
			</TableCell>

			<TableCell
				width={ Widths[4] }
			>
				<Button.Ghost
					size="small"
					disabled={ state.status == "active" }
					text="Run Test"
					onPress={ runTestHandler }
				/>
			</TableCell>
		</TableRow>
	)

}

const Widths = [
	250,
	200,
	200,
	250,
	200,
] as const

Item.Widths = Widths

const
	mapStatusText: Record<ItemState["status"], string> =
		{
			active: "Running",
			error: "Failed",
			finished: "Success",
			inactive: "None",
			pending: "Pending",
		},

	mapMessageIconColor: Record<ThemeContext["colorScheme"], string> =
		{
			gray_10: Color.Token.gray_10.icon_primary,
			gray_100: Color.Token.gray_100.icon_primary,
		}
