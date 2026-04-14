"""Fix remaining submodule paths after step 1 already completed."""
import os

ROOT = r"C:\Users\rion\source\repos\UNHUMAN"
GIT_DIR = os.path.join(ROOT, ".git")
NEW = "UHE"
OLD = "VEGA"
new_modules = os.path.join(GIT_DIR, "modules", NEW)

submodules = [
    "vendor/spdlog", "vendor/GLFW", "vendor/glm",
    "vendor/volk", "vendor/VulkanMemoryAllocator", "vendor/yaml-cpp",
    "vendor/imGuizmo", "vendor/tracy"
]

# Step 2: Fix .git files (skip imgui - it's a directory)
for sub in submodules:
    git_file = os.path.join(ROOT, NEW, sub, ".git")
    if os.path.isfile(git_file):
        with open(git_file, "r") as f:
            content = f.read()
        new_content = content.replace(f"modules/{OLD}/", f"modules/{NEW}/")
        if new_content != content:
            with open(git_file, "w") as f:
                f.write(new_content)
            print(f"Fixed .git file: {sub}")

# Step 3: Fix worktree in module configs
all_subs = submodules + ["vendor/imgui"]
for sub in all_subs:
    config_file = os.path.join(new_modules, sub, "config")
    if os.path.exists(config_file):
        with open(config_file, "r") as f:
            content = f.read()
        new_content = content.replace(f"/{OLD}/", f"/{NEW}/")
        new_content = new_content.replace(f"\\{OLD}\\", f"\\{NEW}\\")
        if new_content != content:
            with open(config_file, "w") as f:
                f.write(new_content)
            print(f"Fixed module config: {sub}")

# Step 4: Fix root .git/config
root_config = os.path.join(GIT_DIR, "config")
with open(root_config, "r") as f:
    content = f.read()
new_content = content.replace(f'submodule "{OLD}/', f'submodule "{NEW}/')
new_content = new_content.replace(f'"{OLD}/vendor/', f'"{NEW}/vendor/')
if new_content != content:
    with open(root_config, "w") as f:
        f.write(new_content)
    print("Fixed root .git/config")

print("Done!")
