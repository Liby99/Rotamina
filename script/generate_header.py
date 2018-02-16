import os, sys
name = sys.argv[1]
root_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), "../src/extern/")
header_dir = os.path.join(root_dir, name)
if not os.path.exists(header_dir):
    os.makedirs(header_dir)
files = []
dirs = [("", root_dir)]
for i in range(4):
    subdirs = []
    for (p, d) in dirs:
        files = files + [os.path.join(p, item) for item in os.listdir(d) if os.path.isfile(os.path.join(d, item))]
        subdirs = subdirs + [(os.path.join(p, sd), os.path.join(d, sd)) for sd in os.listdir(d) if os.path.isdir(os.path.join(d, sd))]
    dirs = subdirs
recartyar_header  = open(os.path.join(root_dir, name + "/"  + name + ".h"), "w+")
for f in [f for f in files if name not in f]:
    recartyar_header.write("#include \"" + f + "\"\n")
recartyar_header.close()
