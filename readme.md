# VEGA Engine

VEGA is a modern 2D/3D game engine built with C++ and OpenGL. It is designed with a modular layer-based architecture and a powerful ECS system using `entt`.

---

## 🏗️ Project Architecture

The workspace is divided into several main components:
- **VEGA**: The core engine library containing the renderer, scene management, ECS, and core utilities.
- **VEGA_EDITOR**: A built-in editor application for scene manipulation, built using ImGui.
- **vendor**: Contains third-party dependencies such as `GLFW`, `Glad`, `glm`, `entt`, `ImGui`, and `yaml-cpp`.
- **sandbox**: A boilerplate project for testing engine features.

### Core Engine (`VEGA/src/VEGA`)
| Component | Description | 
| :--- | :--- |
| `Core.h` | Macros, logging, and base definitions. |
| `Application` | Main engine class that handles the main loop, window management, and LayerStack. |
| `Renderer` | High-level rendering API (Buffers, Shaders, Textures, Framebuffers). Supports 2D and 3D. |
| `Scene` | ECS-based scene management. Uses `entt` for entity storage. |
| `Events` | Event dispatch system for window, keyboard, and mouse events. |
| `Animation` | Dedicated 2D/Sprite animation system. |

### Renderer Architecture
VEGA uses a command-based rendering architecture. 
- **Platform/OpenGL**: Specific implementation for the OpenGL backend.
- **RendererAPI**: Abstract interface for different rendering backends.
- **RenderCommand**: Static methods to execute draws and clears.

---

## 🛠️ Build and Development

### Build Systems
VEGA supports both **CMake** and **Premake**.
- **CMake**: Recommended for modern IDE integration (VS Code, CLion, Visual Studio).
  ```bash
  mkdir build
  cd build
  cmake ..
  ```
- **Premake**: Traditional workspace generation.
  ```bash
  premake5 vs2022
  ```

### Getting Things Done (Common Tasks)

#### 1. Adding a New Component
Components are defined as simple structs in `VEGA/src/VEGA/Scene/Components.h`.
```cpp
struct MyComponent {
  float MyData = 0.0f;
  // ...
};
```

#### 2. Creating an Entity
Entities are created via the `Scene` object.
```cpp
auto entity = m_ActiveScene->CreateEntity("MyEntity");
entity.AddComponent<SpriteRendererComponent>(glm::vec4{1, 0, 0, 1});
```

#### 3. Handling Events
Inherit from high-level event classes or use the `OnEvent` function in your Layer.
```cpp
void MyLayer::OnEvent(VEGA::Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(MyLayer::OnWindowResize));
}
```

---

## 📂 Key Files to Explore
- [Application.h](/repos/VEGA/VEGA/src/VEGA/Application.h)
- [Scene.h](VEGA/VEGA/src/VEGA/Scene/Scene.h)
- [Renderer.h](VEGA/VEGA/src/VEGA/Renderer/Renderer.h)
- [Editor.cpp](VEGA/VEGA_EDITOR/src/Editor.cpp)
