"""
Restore empty source files in UHE/src from git history (VEGA/src/VEGA/...).
The directory rename was: VEGA/src/VEGA/X -> UHE/src/UHE/X
Also: VEGA/src/vgpch.h -> UHE/src/uhepch.h, VEGA/src/VEGA.h -> UHE/src/UHE.h
"""
import os
import subprocess

ROOT = r"C:\Users\rion\source\repos\UNHUMAN"

def git_show(git_path):
    result = subprocess.run(
        ["git", "show", f"HEAD:{git_path}"],
        capture_output=True, cwd=ROOT
    )
    if result.returncode != 0:
        return None
    return result.stdout

def apply_renames(content_bytes):
    c = content_bytes
    c = c.replace(b'vgpch.h', b'uhepch.h')
    c = c.replace(b'VGPCH_H', b'UHEPCH_H')
    c = c.replace(b'#include "VEGA/', b'#include "UHE/')
    c = c.replace(b'#include <VEGA/', b'#include <UHE/')
    c = c.replace(b'#include "VEGA.h"', b'#include "UHE.h"')
    c = c.replace(b'#include <VEGA.h>', b'#include <UHE.h>')
    c = c.replace(b'namespace VEGA', b'namespace UHE')
    c = c.replace(b'VEGA::', b'UHE::')
    c = c.replace(b'VEGA_API', b'UHE_API')
    c = c.replace(b'VEGA_EXPORTS', b'UHE_EXPORTS')
    c = c.replace(b'VEGA_ENABLE_ASSERTS', b'UHE_ENABLE_ASSERTS')
    c = c.replace(b'VEGA_ASSERT', b'UHE_ASSERT')
    c = c.replace(b'VEGA_CORE_ASSERT', b'UHE_CORE_ASSERT')
    c = c.replace(b'.vega', b'.unhuman')
    c = c.replace(b'"VEGA"', b'"UHE"')
    c = c.replace(b'VEGA_WARN', b'UHE_WARN')
    c = c.replace(b'VEGA_ERROR', b'UHE_ERROR')
    c = c.replace(b'VEGA_INFO', b'UHE_INFO')
    c = c.replace(b'VEGA_TRACE', b'UHE_TRACE')
    c = c.replace(b'VEGA_FATAL', b'UHE_FATAL')
    c = c.replace(b'VEGA_CORE_WARN', b'UHE_CORE_WARN')
    c = c.replace(b'VEGA_CORE_ERROR', b'UHE_CORE_ERROR')
    c = c.replace(b'VEGA_CORE_INFO', b'UHE_CORE_INFO')
    c = c.replace(b'VEGA_CORE_TRACE', b'UHE_CORE_TRACE')
    c = c.replace(b'VEGA_CORE_FATAL', b'UHE_CORE_FATAL')
    return c

def uhe_to_vega_git_path(rel_path):
    """
    Convert a UHE/ relative path to the original VEGA/ git path.
    UHE/src/UHE.h         -> VEGA/src/VEGA.h
    UHE/src/uhepch.h      -> VEGA/src/vgpch.h
    UHE/src/uhepch.cpp     -> VEGA/src/vgpch.cpp
    UHE/src/UHE/Core/X.h  -> VEGA/src/VEGA/Core/X.h
    UHE/src/Platform/X.h  -> VEGA/src/Platform/X.h  (no inner rename)
    """
    # Replace the top-level UHE -> VEGA
    p = rel_path.replace("\\", "/")
    
    # UHE/ -> VEGA/
    if p.startswith("UHE/"):
        p = "VEGA/" + p[4:]
    
    # UHE.h -> VEGA.h (the main engine header)
    p = p.replace("VEGA/src/UHE.h", "VEGA/src/VEGA.h")
    
    # uhepch -> vgpch
    p = p.replace("uhepch", "vgpch")
    
    # src/UHE/ -> src/VEGA/ (the inner source subdirectory)
    p = p.replace("VEGA/src/UHE/", "VEGA/src/VEGA/")
    
    return p

restored = 0
failed = 0
fail_list = []

for dirpath, dirnames, filenames in os.walk(os.path.join(ROOT, "UHE", "src")):
    for fname in filenames:
        if not fname.endswith(('.h', '.cpp', '.c')):
            continue
        full_path = os.path.join(dirpath, fname)
        if os.path.getsize(full_path) > 0:
            continue
        
        rel = os.path.relpath(full_path, ROOT)
        git_path = uhe_to_vega_git_path(rel)
        
        content = git_show(git_path)
        if content is None:
            print(f"FAIL: {git_path}")
            failed += 1
            fail_list.append(git_path)
            continue
        
        content = apply_renames(content)
        with open(full_path, 'wb') as f:
            f.write(content)
        restored += 1

# Also fix stb_image.cpp if needed
stb_path = os.path.join(ROOT, "UHE", "vendor", "stb_image", "stb_image.cpp")
if os.path.exists(stb_path) and os.path.getsize(stb_path) > 0:
    with open(stb_path, 'rb') as f:
        c = f.read()
    if b'vgpch' in c:
        c = c.replace(b'vgpch.h', b'uhepch.h')
        with open(stb_path, 'wb') as f:
            f.write(c)
        print("Fixed stb_image.cpp (vgpch -> uhepch)")

print(f"\nRestored: {restored}, Failed: {failed}")
if fail_list:
    print("Failed files:")
    for f in fail_list:
        print(f"  {f}")
