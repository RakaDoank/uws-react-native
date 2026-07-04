# Contributing
Thank you for your support to this library. This documentation will help you how to contribute to this library. There are some requirements and conventions that we and i must fill and follow.

- [Knowledges](#knowledges)
- [Environments](#environments)
  - [macOS](#macos)
  - [Linux](#linux)
  - [Windows](#windows)
  - [IDE for TypeScript and JavaScript](#ide-for-typescript-and-javascript)
- [Clone](#clone)
- [Setup](#setup)
  - [1. Dependencies Installation](#1-dependencies-installation)
  - [2. IDE Setup for Library Development with Example App](#2-ide-setup-for-library-development-with-example-app)
    - [Android](#android)
    - [iOS](#ios)
    - [macOS](#macos-1)
- [Run the Example App](#run-the-example-app)
  - [Android](#android-1)
  - [iOS](#ios-1)
- [Conventions](#conventions)
  - [JavaScript/TypeScript](#javascripttypescript)
  - [Java/Kotlin](#javakotlin)
  - [Objective-C](#objective-c)
- [About the Example App and the Library in Monorepo Setup](#about-the-example-app-and-the-library-in-monorepo-setup)

---

## Knowledges
To contribute to this project, we assummed that you know about app development with React Native including:
- **JavaScript** or **TypeScript** language as the bridge for library users to consume native modules of platform and for the build user interface with [React.js](https://react.dev) in the React Native app
- **C/C++** language as the main language in this library core. You will have a lot of interaction with React Native JSI C++, and the core [uWebSockets](https://github.com/uNetworking/uWebSockets) library
- Optional, but it is nice if you have knowledge and experience with **Java**, **Kotlin** for Android library development, and **Objective-C** for iOS and macOS library development
- [Turbo Native Modules](https://reactnative.dev/docs/turbo-native-modules-introduction) for React Native module development with new architecture. You can also refer to the [reactwg](https://github.com/reactwg/react-native-new-architecture) documentation for additional information about React Native New Architecture
- (Deprecated) [Legacy Native Modules](https://reactnative.dev/docs/legacy/native-modules-intro) for React Native module development with old/legacy architecture
- A bit of [react-native-builder-bob](https://callstack.github.io/react-native-builder-bob) knowledges as the builder for React Native libraries for various targets

You do not have to know it all at advanced level. **Feel free to learn and embrace it**. Do the actual fix and any improvements. I encourage you.

---

## Environments
Beforehand, let's admit that there are no perfect environment guides for your machine and your preferences.
There are a lot of way to go the Rome, you can do in your own way of how to complete these environment requirements.

You can refer directly to this [environment setup](https://reactnative.dev/docs/set-up-your-environment) guide from React Native documentation.

If you prefer our documented guide, you can read it below
> We are assuming that you have already understand basic knowledges about terminal or command, and system configuration of your macOS, or Linux, or Windows machines.

### macOS
Install these in your machine
- [Homebrew](https://brew.sh/)
- [Mise](https://mise.jdx.dev). Install it through Homebrew. See [Getting Started](https://mise.jdx.dev/getting-started.html). It is useful for Node.js and Ruby installation and easy version switch
- [Node.js](https://nodejs.org) >=24. Install and switch Node.js easily through [Mise](https://mise.jdx.dev)
- [PNPM](https://pnpm.io) >= 11. Install it through Homebrew. See the [installation guide](https://pnpm.io/installation)

#### Development for iOS & macOS
These are required for iOS and macOS development
> You can skip this if you are using macOS machine but it is only for Android development

- [Xcode](https://developer.apple.com/xcode) latest version
- [Ruby](https://www.ruby-lang.org/en/) >= 3.x. Install it through [Mise](https://mise.jdx.dev). **We recommend not to use** the macOS system provided Ruby
- [Cocoapods](https://cocoapods.org/). Beforehand, please make sure that you are using Ruby version 3.x that you have installed through Mise. After that, run `gem install cocoapods`. For ensuring Cocoapods has installed, run `pod --version`

#### Development for Android
You need to install Azul Zulu JDK in your macOS machine
1. Install [Azul Zulu JDK](https://www.azul.com) version 17.x with [Homebrew](https://brew.sh/)
   ```
   brew install --cask zulu@17
   ```

2. Run `brew info --cask zulu@17`
   You will likely have this output in your terminal
   ```
   ==> zulu@17 ✔ (Azul Zulu Java Standard Edition Development Kit): 17.0.19,17.66.19
   OpenJDK distribution from Azul
   https://www.azul.com/downloads/
   Installed (on request)
   /opt/homebrew/Caskroom/zulu@17/17.0.19,17.66.19 (192.9MB)
     Installed using the formulae.brew.sh API on 2026-01-16 at 19:19:07
   From: https://github.com/Homebrew/homebrew-cask/blob/HEAD/Casks/z/zulu@17.rb
   ```
   Then, copy the location path `/opt/homebrew/Caskroom/zulu@17/17.0.19,17.66.19`

3. Run
   ```
   open /opt/homebrew/Caskroom/zulu@17/17.0.19,17.66.19
   ```
   It will open the finder to the exact location path, and double click the `Double-Click to Install Azul Zulu JDK 17.pkg` file to install the JDK

4. Update `JAVA_HOME` environment variable in `~/.zshenv` file
   ```
   export JAVA_HOME=/Library/Java/JavaVirtualMachines/zulu-17.jdk/Contents/Home
   ```

After you complete the JDK installation step, install [Android Studio](https://developer.android.com/studio) with Meerkat version or latest version in your macOS machine.

You need additional binaries for Android such as Android SDK, Android NDK, and CMake. You can open Android Studio > Settings > Language & Frameworks > Android SDK, and you need these binaries
- Android SDK Build Tools version >= 36.x.x
- Android SDK Command-line Tools version >= 19.0
- NDK version >= 27.1.x
- CMake version >= 3.22.1

Finally, update your `ANDROID_HOME` environment variable in your `~/.zshenv` file
```
export ANDROID_HOME=$HOME/Library/Android/sdk
```

### Linux
There is a lot of Linux distributions and a lot of way to install in Linux,
but in simple words, you need these binaries or softwares

- [Mise](https://mise.jdx.dev). It is useful for Node.js and Ruby installation and easy version switch
- [Node.js](https://nodejs.org) >=24. Install and switch Node.js easily through [Mise](https://mise.jdx.dev)
- [PNPM](https://pnpm.io) >= 11. See the [installation guide](https://pnpm.io/installation)
- [OpenJDK](https://openjdk.org/) version 17. You can download or install from [Adoptium](https://adoptium.net/) or your system package manager
- [Android Studio](https://developer.android.com/studio) with Meerkat version or latest version in your Linux machine

After Android Studio has installed, you need additional binaries for Android such as Android SDK, Android NDK, and CMake.

You can open Android Studio > Settings > Language & Frameworks > Android SDK, and you need these binaries
- Android SDK Build Tools version >= 36.x.x
- Android SDK Command-line Tools version >= 19.0
- NDK version >= 27.1.x
- CMake version >= 3.22.1

Finally, update your `ANDROID_HOME` environment variable in your `~/.bash_profile` file
```
export ANDROID_HOME=$HOME/Library/Android/sdk
```

### Windows
Install these in your machine
- [Chocolatey](https://chocolatey.org/). See [Chocolatey CLI Setup](https://docs.chocolatey.org/en-us/choco/setup)
- [Mise](https://mise.jdx.dev). Install it through Chocolatey. See [Getting Started](https://mise.jdx.dev/getting-started.html). It is useful for Node.js and Ruby installation and easy version switch
- [Node.js](https://nodejs.org) >=24. Install and switch Node.js easily through [Mise](https://mise.jdx.dev)
- [PNPM](https://pnpm.io) >= 11. Install it through Chocolatey. See the [installation guide](https://pnpm.io/installation)
- [Microsoft OpenJDK](https://www.microsoft.com/openjdk) version 17.x.x. Install it through Chocolatey
  ```
  choco install microsoft-openjdk17
  ```
- [Android Studio](https://developer.android.com/studio) with Meerkat version or latest version in your Windows machine

After Android Studio has installed, you need additional binaries for Android such as Android SDK, Android NDK, and CMake.

You can open Android Studio > Settings > Language & Frameworks > Android SDK, and you need these binaries
- Android SDK Build Tools version >= 36.x.x
- Android SDK Command-line Tools version >= 19.0
- NDK version >= 27.1.x
- CMake version >= 3.22.1

### IDE for TypeScript and JavaScript
Install [Visual Studio Code](https://code.visualstudio.com/) in your macOS, Linux, or Windows machine. In addition, install [ESLint extension](https://marketplace.visualstudio.com/items?itemName=dbaeumer.vscode-eslint) in your Visual Studio Code. TypeScript compiler and ESLint will check our code quickly without manually run `tsc` and `eslint` command to check the cleaness and potential bug by ESLint, and compiler warn and error by TypeScript.

---

## Clone
Clone this repository in your machine
```
git clone https://github.com/RakaDoank/uws-react-native.git
```

---

## Setup
Make your environment is ready and the repository has been cloned. After that, do these next steps

### 1. Dependencies Installation
1. Go to the repository's directory in your terminal or cmd and do the installation with your `pnpm`
   ```
   pnpm install
   ```
   This installation will install all the dependencies including the `react-native` example app.

2. After that, run
   ```
   pnpm run package-builder uws-mod
   ```
   This is our custom script to fetch [uSockets](https://github.com/uNetworking/uSockets) and [uWebSockets](https://github.com/uNetworking/uWebSockets) source code files
and write it in our repository with correct directory setup. We prefer this rather than cloning the entire uSockets and uWebSockets project repository.

3. Finally, locate to the `uws-react-native/example` directory in your terminal, and then run
   ```
   pnpm run prebuild
   ```
   This is an Expo script known as [Continuous Native Generation](https://docs.expo.dev/workflow/continuous-native-generation/) to build and write necessary Android and iOS files since those are ignored by GIT.

### 2. IDE Setup for Library Development with Example App
In this project, the example app at the `uws-react-native/example` directory is the app we will use as the library playground to use for the library development. The app was bootstrapped [Expo](https://expo.dev).
To setup the React Native app and link the actual (`uwas-react-native`) library itself are similar like the usual React Native or Expo CLI installation with autolinking of React Native libraries

#### Android
1. Open the `uws-react-native/example/android` directory with **Android Studio**
2. Sync project with gradle files
   > If you have encountered a problem issue such as `cannot run program 'node'` or similar, you can run the example android app first, see [run the example app](#run-the-example-app), and retry the Gradle sync in Android Studio
4. In the sidebar explorer of Android Studio with `Android` mode directory, you should can see our `cpp` directory in the `app` directory. The `cpp` directory is where the library C++ code lives you can actually do any fixes

#### iOS
1. Open your terminal
2. Go to the `uws-react-native/example/ios` directory
3. Install the pods by run this command
   ```
   pod install
   ```
   You do not have do this everytime. Running `npm run prebuild` in the example directory is also doing pod installation internally
4. Open the `uws-react-native/example/ios/example.xcworkspace` directory with **Xcode**
5. You should see `UwsReactNative` directory in the `Pods > Development Tools` from the sidebar navigator. This is where the library code lives you can actually do any fixes

#### macOS
⚠️ We do not provide the example app for React Native macOS yet. Soon this documentation will be updated

---

## Run the Example App

### Android
Run your Android emulator first, and then go to the `example` directory, run `npm run android`. Alternatively, you can run the metro first by execute `npm run start`, and then run `npm run android` later.

### iOS
For iOS, you need to run your iPhone/iPad Simulator first.

After it's completely booted up, you can run the app. Go the `example` directory, run `npm run ios`. Alternatively, you can run the metro first by execute `npm run start`, and then run `npm run ios` later.

---

## Conventions

### JavaScript/TypeScript
All the JavaScript/TypeScript has been lint-checked with ESLint, and type-checked with TypeScript. Please follow the rule that has been made e.g indentation with Tab. Do not modify the rule or add `// eslint-disable` mark to your code with no reasons.

While development, ensure that your ESLint Extension of your Visual Studio Code is running if you are using that IDE. Alternatively, you can run `npm run code-check` in the root of repository.

You can check the lint rules at [uws-react-native/eslint.config.mjs](https://github.com/RakaDoank/uws-react-native/blob/main/eslint.config.mjs) and the `compilerOptions` of TypeScript at [uws-react-native/tsconfig.json](https://github.com/RakaDoank/uws-react-native/blob/main/tsconfig.base.json) and other `tsconfig.json` files in the `example` and `package` directory.

### Java/Kotlin
Please, follow the [Google Objective-C Style Guide](https://google.github.io/styleguide/).

### Objective-C
Please, follow the [Google Objective-C Style Guide](https://google.github.io/styleguide/objcguide.html).

---

## Directories
- `.github`: GitHub conventional directory, such as for GitHub Actions, pull request template, etc.
- `example`: This is the React Native app as the playground of the library development
- `package`: This is the actual `uws-react-native` library source code lives. This directory will be used as the actual `uws-react-native` library in the npm registry
- `package-builder`: This directory is our custom scripts for the builder of the actual library with hard-coded path configuration to the `package` directory (you can read [this documentation](https://callstack.github.io/react-native-builder-bob/build)).
  This directory does also contain our `uws-mod` script to fetch [uSockets](https://github.com/uNetworking/uSockets) and [uWebSockets](https://github.com/uNetworking/uWebSockets) source code files
and write it in our repository with correct directory setup. We prefer this rather than cloning the entire uSockets and uWebSockets project repository

---

## About the Example App and the Library in Monorepo Setup
The app was actually bootstrapped with [npx create-expo-app@latest](https://github.com/react-native-community/cli), but since this project is a monorepo setup with `PNPM` to scaffold both app and actual library deployment. There are modifications that have been done in the example app to split between the app, the actual `uws-react-native` library, and other development tools or the `devDependencies`
- `uws-react-native/example/metro.config.js`: The example app has to know where the actual `uws-react-native` directory lives without including the `uws-react-native` in the `dependencies` of the `package.json` example app
- `uws-react-native/example/react-native.config.js`: Since the actual `uws-react-native` library is not included as `dependencies` in the `package.json` file of example app, we have to tell React Native CLI where the `uws-react-native` directory lives to auto-linked the example app with `uws-react-native` library in development
- `@react-native/eslint-config` development dependency (`devDependencies`) was moved out to the root of `package.json` (repository) from the `example` app
