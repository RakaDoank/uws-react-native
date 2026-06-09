<h1 align="center">
  react-native-uws
</h1>

The [uWebSockets](https://github.com/uNetworking/uWebSockets) ported library for React Native.

## Development Phase
The library is still in development and research. All the uWebSockets instances are not fully implemented yet.

These below are the item that we need to implement in this library

- Implement missing methods from the `TemplatedAppObject` e.g. `ws`, `addServerName`, etc.
- `getParts` API like in uWebSockets.js to get body data `JSON`, `multipart/form-data`, or raw text
- App options for SSL configuration
- Implement `ArrayBuffer` support for all the `RecognizedString` typed data
- Missing `upgrade` method from `HttpResponse` object

## Usage
Since react-native-uws is just a reimplementation of uWebSockets in React Native JSI, this library is really similar of how to use the [uWebSockets](https://github.com/uNetworking/uWebSockets) in C++ or the [uWebSockets.js](https://github.com/uNetworking/uWebSockets.js) in Node.js.
You can refer to the [uWebSockets.js](https://github.com/uNetworking/uWebSockets.js) example.

This repository does also contain the [example](https://github.com/RakaDoank/react-native-uws/blob/main/example/src/app/index.tsx) app. You can also refer to it, but it's currently for library development playground.
