# PalSchema

> [!WARNING]
> ## Linux / NullPrism port — work in progress
>
> This fork contains an in-development Linux port of PalSchema for use with the
> NullPrism Linux port of RE-UE4SS.
>
> **It builds and has successfully run on a Palworld Linux dedicated server, but
> the port is not complete and should not yet be considered a finished Linux
> release.**
>
> `include/SDK/PalSignatures_Linux.h` currently contains a mixture of validated
> Linux signatures and placeholder copies of Windows signatures which have not
> yet been converted or validated for Linux.

PalSchema is a mod that allows modification of data tables and blueprints in
Palworld with JSON files without introducing conflicts with other mods that
modify the same game files.

It also makes heavy use of JSON Schema, allowing mod creators to have
autocompletion and error checking when creating table mods.

The original PalSchema project and documentation are maintained by
[Okaetsu](https://github.com/Okaetsu).

## Linux port status

The current Linux development target is:

- Palworld `v1.0.5.102999`
- Unreal Engine `5.1.1`
- Linux dedicated server
- NullPrism / RE-UE4SS Linux runtime

The current port reaches normal dedicated-server startup and PalSchema
initialisation.

Linux support is nevertheless still incomplete.

In particular, `include/SDK/PalSignatures_Linux.h` contains:

- Linux signatures which have been independently derived and validated;
- signatures which are still under investigation;
- placeholder copies of Windows signatures which have not yet been converted
  or validated for Linux.

A populated entry in `PalSignatures_Linux.h` must therefore **not** be assumed
to be a confirmed Linux signature simply because it exists.

Porting has also exposed places outside the signature tables where the original
code relies on Windows/MSVC ABI or compiler behaviour, including virtual
function table indices and assumptions about generated instruction layouts.
These are being audited as development proceeds.

## Linux dependency patches

The current Linux build requires small modifications to the NullPrism/RE-UE4SS
dependency tree.

Rather than modifying the submodule revisions recorded by PalSchema, the
required changes are preserved as patches in this repository:

```text
patches/RE-UE4SS-linux-port.patch
patches/Unreal-TopLevelAssetPath-linux-port.patch
```

`RE-UE4SS-linux-port.patch` contains the current RE-UE4SS-side Linux changes,
including Linux linker handling for the statically linked C++ standard library
and moving `UE4SSProgram::get_program()` to an exported out-of-line
implementation.

`Unreal-TopLevelAssetPath-linux-port.patch` supplies the required implementation
of:

```cpp
FTopLevelAssetPath::AppendString(FString& Builder) const
```

in the nested `deps/first/Unreal` dependency.

### Applying the dependency patches

Start from a clean checkout and initialise all submodules:

```bash
git submodule update --init --recursive
```

Apply the RE-UE4SS patch:

```bash
git -C deps/RE-UE4SS apply --check ../../patches/RE-UE4SS-linux-port.patch
git -C deps/RE-UE4SS apply ../../patches/RE-UE4SS-linux-port.patch
```

Apply the nested Unreal patch:

```bash
git -C deps/RE-UE4SS/deps/first/Unreal apply --check ../../../../../patches/Unreal-TopLevelAssetPath-linux-port.patch
git -C deps/RE-UE4SS/deps/first/Unreal apply ../../../../../patches/Unreal-TopLevelAssetPath-linux-port.patch
```

The Linux build currently expects an existing NullPrism/RE-UE4SS runtime
library.

Its location is configured by `UE4SS_RUNTIME_LIBRARY` in:

```text
deps/CMakeLists.txt
```

Set this to the location of `libUE4SS.so` in your Palworld server installation
before configuring the build.

The Linux build process is still development-oriented and may change as the
port progresses.

## Installation

The upstream in-depth installation guide can be found
[here](https://okaetsu.github.io/PalSchema/docs/installation).

The upstream documentation currently describes the established PalSchema
installation process; Linux/NullPrism support in this fork is still under
development.

## Documentation

Documentation for modders can be found
[here](https://okaetsu.github.io/PalSchema/docs/gettingstarted).

## Building from Source

### Upstream / Windows build

1. You must complete the **Build requirements** over at
   [UE4SS Docs](https://docs.ue4ss.com/#build-requirements) and make sure your
   GitHub account is linked to Epic Games for Unreal Engine source access.

2. Create your own fork of PalSchema and clone it.

3. Execute:

   ```bash
   git submodule update --init --recursive
   ```

4. Choose either MSVC or Ninja.

MSVC (multi-configuration, slower, allows switching configs without
reconfiguring):

```bash
cmake -B build -G "Visual Studio 17 2022"
```

Ninja (single-configuration, faster):

```bash
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Game__Shipping__Win64
```

### Linux / NullPrism build

Linux build instructions are not yet considered stable.

At minimum, initialise the recursive submodules and apply the two dependency
patches described in [Linux dependency patches](#linux-dependency-patches)
before configuring PalSchema.

The current branch is intended as development source rather than a packaged
Linux release. Build configuration and dependency handling may change while
the remaining Linux signatures and ABI assumptions are being investigated.

## Mods using PalSchema

I'll only include one mod per author to avoid cluttering the list too much.

[True Recipes](https://www.nexusmods.com/palworld/mods/2159) by The Sin of Pride

[Bounty Shop Plus](https://www.nexusmods.com/palworld/mods/2162) by TheGameAce

[Dog Coin Replacer](https://www.nexusmods.com/palworld/mods/2197) by DeltaJordan

[Additional Skins for PalSchema](https://www.nexusmods.com/palworld/mods/2199) by William112792

[Faster Yakumo for PalSchema](https://www.nexusmods.com/palworld/mods/2207) by MelwenMods

[Pal Fusion Mod](https://www.nexusmods.com/palworld/mods/2384) by Primarinabee

[Male Probability 50 for All Pals](https://www.nexusmods.com/palworld/mods/2285) by ZeroRin00

[All legendary head pieces match hexolite head gear](https://www.nexusmods.com/palworld/mods/2295) by Helionhell

[Expensive Palboxes](https://www.nexusmods.com/palworld/mods/708) by marksmango
