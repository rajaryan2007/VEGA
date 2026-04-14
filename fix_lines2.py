import os

exts = {'.cpp','.h','.hpp','.c','.txt','.cmake','.slang','.glsl','.json','.yml','.md','.vcxproj','.filters','.lua','.ini'}

fixed = 0
for r, d, files in os.walk('.'):
    if any(x in r.split(os.sep) for x in ['.git', '.idea', '.vs', 'build', 'out', 'bin', 'vendor']):
        continue
    for f in files:
        if any(f.endswith(e) for e in exts) or f.lower() == 'cmakelists.txt':
            fp = os.path.join(r, f)
            try:
                with open(fp, 'rb') as file:
                    content = file.read()
                if b'\r\n\r\n' in content:
                    # Keep replacing until there are no double blank lines inside macros
                    content = content.replace(b'\\\r\n\r\n', b'\\\r\n')
                    # And maybe just compress all \r\n\r\n
                    content = content.replace(b'\r\n\r\n', b'\r\n')
                    with open(fp, 'wb') as file:
                        file.write(content)
                    fixed += 1
            except Exception as e:
                print(f"Skipped {fp}: {e}")

print(f"Fixed {fixed} files.")
