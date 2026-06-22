# uws-react-native

The port of [**uWebSockets**](https://github.com/uNetworking/uWebSockets) library for React Native. Inspired by the [**uWebSockets.js**](https://github.com/uNetworking/uWebSockets.js) for Node.js and tailored for React Native app.

- **uWebSockets** is simple, secure & standards compliant web server for the most demanding of applications. See [**uWebSockets**](https://github.com/uNetworking/uWebSockets) for more information
- **uws-react-native** is library that allows you to easily use **uWebSockets** in your React Native through new architecture with JSI to the native C++

> ⚠️ uws-react-native is still in heavy development and research. All the uWebSockets instances are not fully implemented yet.

## Installation

npm
```
npm install uws-react-native
```

yarn
```
yarn add uws-react-native
```

pnpm
```
pnpm install uws-react-native
```

## Usage

Since uws-react-native is a port of uWebSockets library for JavaScript, this library is really similar of how to use the [uWebSockets](https://github.com/uNetworking/uWebSockets) in C++, or the [uWebSockets.js](https://github.com/uNetworking/uWebSockets.js) for Node.js.
You can refer to the [uWebSockets.js](https://github.com/uNetworking/uWebSockets.js) example.

This repository does also contain the [example](https://github.com/RakaDoank/uws-react-native/blob/main/example/src/app/index.tsx) app. You can also refer to it, but it is currently for library development playground rather than proper example.

## Compatibility

`uws-react-native` is only compatible for new architecture of React Native.

### Platform

uws-react-native is supported in Android, iOS, and macOS. Windows is currently not supported, and Web is impossible.

### Unsupported APIs

- **SSL options**. We need to research how to provide .pem file in React Native app and its platform architecture regarding the SSL topic
- **WebSocket server**. Not implemented yet. It will be supported later.

### New APIs

There are some new APIs in uws-react-native. The most reason is because of the differentiation of React Native's architecture compared to the casual server program

- The route method handler like `any`, `get`, `post` and others expects third argument as the handler options optionally. See [`HttpRouterOptions`](https://github.com/RakaDoank/uws-react-native/blob/main/package/src/types/HttpRouterOptions.ts)
- In [`HttpResponse`](https://github.com/RakaDoank/uws-react-native/blob/main/package/src/types/HttpResponse.ts) object,
  - `onFullData`. This is an equivalent of `res.collectBody` from uWebSockets.js, but to set the max size, provide it through route method handler options
  - `onFullDataText`. Same as the `onFullData`, but provides the body data in raw text instead of ArrayBuffer. This is useful if you are using React Native 0.84 version or older because TextDecoder is natively supported only in React Native 0.85 version

## Development & Research

uws-react-native is still in heavy development and research. All the uWebSockets instances are not fully implemented yet.

There are development and research things that you can read for your informations, especially if you are already familiar with uWebSockets. The most things are because of the React Native's architecture differentiation compared to the casual uWebSockets server program.

### Performance & Stability

This library is indeed focusing on performance, but we will focus more of it later until we reach the stability of uws-react-native due to [threading](#threading) issue. It does not mean uws-react-native will performs badly in terms of performance speed, but it is not stable enough in under a stress situation.

I have tested a stress test in an Android device. A lot of incoming request roughly 100 requests per second in roughly 10 seconds for files uploading (multipart/form-data) may crash the app. We do not have the proper benchmark yet, but it is as I expected from a platform restriction of memory usage for an app. An Android device with 12GB RAM does not mean an app can use all of it. I am keeping my eyes on this issue to keep improving this stress test.

### Threading

We are embracing the main chaos of supporting uWebSockets in React Native architecture, which is to prevent UI/Main thread from blocking.

Intentionally, we make the uWebSockets runs in another thread, therefore we have to make sure the communication safety between uWebSockets runner thread to the JS thread and vice versa. In theory, we can make uWebSockets runs in the main thread, but the app will be unusable, and then force closing the app is the only way to stop the server.

We have another issue because of the uWebSockets runs in another thread. From the JSI C++ side, we have to assume any JS function as a callback especially the route method handler is asynchronous. We cannot make a sync call to the JS function from an arbitrary thread to the JS thread, and it makes JS call to the uWebSockets runner is also late.

For this case especially, we have to predefined two instances in the C++ uWebSockets route method handler because of the late call, and the late call would not be tolerated by the uWebSockets internally for some instances

- `res.onAborted`

We have to predefined the `onAborted` callback in C++ side and prevent `res.end` call from JavaScript internally in C++ side. Normally, you would check if it is already aborted or not before calling the end method, but our predefined `onAborted` callback may also late to tell to the JavaScript side. If we are not predefining this method, uWebSockets assumes that you have not assign `onAborted` callback at the time due to the `res.onAborted` assignment from JavaScript is also late.

- `res.onDataV2`

For the `onData` and `onDataV2`, we have predefined it with a single `onDataV2` callback in C++ side. If this method is not predefined, uWebSockets will not collect any incoming body data. If a route method handler is sure that it doesn't expect any body data at all, a route method handler can disable the body reading through the third argument in `any`, `get`, `post`, and other route methods.
