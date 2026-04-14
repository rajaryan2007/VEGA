import os

exts = {'.cpp', '.h', '.hpp', '.c', '.txt', '.cmake', '.slang', '.glsl', '.json', '.yml', '.md', '.vcxproj', '.filters', '.lua', '.ini'}

def fix_line_endings(file_path):
    try:
        with open(file_path, 'rb') as f:
            content = f.read()
            
        new_content = content.replace(b'\r\n', b'\n')
        new_content = new_content.replace(b'\r', b'\n')
        new_content = new_content.replace(b'\n', b'\r\n')
        
        if content != new_content:
            with open(file_path, 'wb') as f:
                f.write(new_content)
            return True
        return False
    except Exception as e:
        print(f"Error processing {file_path}: {e}")
        return False

fixed_count = 0
for root, dirs, files in os.walk('.'):
    # Skip non-source dirs
    if '.git' in dirs: dirs.remove('.git')
    if '.idea' in dirs: dirs.remove('.idea')
    if '.vs' in dirs: dirs.remove('.vs')
    if 'build' in dirs: dirs.remove('build')
    if 'out' in dirs: dirs.remove('out')
    if 'bin' in dirs: dirs.remove('bin')
    
    for file in files:
        if any(file.lower().endswith(ext) for ext in exts) or file.lower() == 'cmakelists.txt':
            file_path = os.path.join(root, file)
            if fix_line_endings(file_path):
                fixed_count += 1
                
print(f"Fixed line endings in {fixed_count} files.")
