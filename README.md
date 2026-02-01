![Jadeite Lite Logo](resources/jadeite-lite-logo.png)
# Jadeite Lite

**Jadeite Lite** is a lightweight starter application built on the **Jadeite 2D Game Engine**, designed specifically for tutorials, experimentation, and rapid feature development.

It provides a clean, stable baseline so you can focus entirely on the topic being taught — without rebuilding windowing, rendering, or tooling boilerplate every time.

---

## Purpose

Jadeite Lite exists to remove friction when learning or demonstrating engine features.

Every tutorial starts from the same known state, making it easy to:
- Follow along with videos
- Reproduce results exactly
- Focus on one concept at a time
- Avoid setup repetition

---

## What This Is

- A reusable **starter application**
- A **known baseline** for tutorials
- A reference setup for engine subsystems
- A clean foundation for experiments and demos

---

## What This Is Not

- Not the full Jadeite engine
- No gameplay systems
- No ECS or scripting by default
- No asset pipelines beyond what is required

Those systems are introduced incrementally per tutorial.

---

## Included Systems

### Core
- SDL2 window and context creation
- Application lifecycle and main loop
- Platform-independent project structure

### Rendering
- OpenGL 4.5 renderer
- Framebuffer abstraction
- Texture system
- 2D camera - Easily chanded to support 3D!
- Resize-safe rendering pipeline

### UI & Tools
- ImGui with full docking support
- Debug and tooling panels

### Utilities
- Structured logging system
- Assertions and error handling
- Minimal configuration support

---

## Typical Workflow

1. Download or clone **Jadeite Starter**
2. Build and run to verify the baseline
3. Follow the tutorial
4. Implement only the feature being covered
5. Archive or discard after completion

Each tutorial starts from a fresh copy of Jadeite Lite.

---

## Use Cases

Jadeite Starter is used as the foundation for tutorials covering topics such as:
- Video playback
- Rendering techniques
- Post-processing
- Tooling and debug UI
- Engine subsystems
- Platform-specific features

---

# Build
----
Requires [CMake 3.26](https://cmake.org/) and [vcpkg](https://github.com/microsoft/vcpkg)
## Get VCPKG:
```ps
git clone https://github.com/microsoft/vcpkg
./vcpkg/bootstrap-vcpkg.bat -disableMetrics
```
### Make sure the following environment variables are set:
- Windows
```
VCPKG_ROOT=[path_to_vcpkg]
VCPKG_DEFAULT_TRIPLET=x64-windows
```
- Linux
Edit your profile's bashrc file:
```
nano ~/.bashrc
```
Add the following lines at the end:
```
export PATH=<path_to_vcpkg_installation_folder>:$PATH
export VCPKG_ROOT=<path_to_vcpkg_installation_folder>
export VCPKG_DEFAULT_TRIPLET=x64-linux
```
Apply changes:
```
source ~/.bashrc
```

## Install Dependencies
```
vcpkg install fmt glm entt glad soil2 sdl2
```

---

## License

This project is licensed under the JGS License.
See the `LICENSE` file for details.
