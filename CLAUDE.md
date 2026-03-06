# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build

This project uses CMake. On Windows, system dependencies (glew, glfw, assimp) are expected at `D:/dev/external/` (include and lib subdirs). On Linux/macOS they are expected at `/usr/local/`.

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

The output binary is `r3d_demo`. Resources and DLLs (Windows) are automatically copied next to the binary post-build.

No tests exist in this project.

## Architecture

Everything lives under the `r3d` namespace. `main.cpp` is the application entry point and demo — not part of the engine library itself.

**Core loop:** `scene::update()` is called each frame. It ticks time, pre-renders the window/UI, runs `behaviour` scripts on game objects, renders all objects (with shader/VAO/texture rebinding optimised via `last_render_object` diffing), renders debug geometry, the skybox, and finally the UI.

**Key classes:**
- `r3d::scene` — top-level manager owning all game objects, lights, camera, skybox, UI canvas, and the render loop
- `r3d::game_object` — transform + optional `mesh_renderer` + list of `behaviour` scripts; position/rotation/scale exposed via getters/setters; rotation stored internally as `glm::quat`; `set_rotation`/`get_rotation` use **radians**, `set_rotation_degrees`/`get_rotation_degrees` for degree convenience
- `r3d::mesh_renderer` — holds shared ptrs to `mesh`, `material`, `shader`, and `bounds`; `render()` accepts flags to skip redundant state changes
- `r3d::shader` — loaded from GLSL files in `resources/shaders/`; selected via `shader::id` enum (`UNLIT_TEXTURE`, `DIFFUSE_TEXTURE`, `DIFFUSE_TEXTURE_BUMP`, `DIFFUSE_COLOR`, `VERTEX_COLOR`, `UI`)

**Instancing pattern:** `scene::instantiate_object()` creates a new `game_object` that shares the same `renderer` (mesh/material/shader) as the source object — no GPU data is duplicated.

**Render optimisation:** The scene's render loop groups objects by renderer and draws each group with instanced rendering, avoiding redundant state changes.

**Module layout:**
- `r3d/core/` — `scene`, `game_object`, `camera`, `light`, `behaviour`, `time`, `mesh`, `bounds`, `constants`
- `r3d/render/` — `mesh_renderer`, `shader`, `material`, `gl_window`, `gl_includes`
- `r3d/load/` — mesh loading (Assimp), shader loading, texture loading (stb_image)
- `r3d/primitive/` — `skybox`
- `r3d/ui/` — ImGui wrapper (`ui`)
- `r3d/util/` — `debug`, `stats`, `file`
- `resources/shaders/` — GLSL source files, one `.vert`/`.frag` pair per shader ID
- `external/include/` — vendored headers (imgui, stb_image, tiny_obj_loader)
