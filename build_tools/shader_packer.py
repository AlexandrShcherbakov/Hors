#!/usr/bin/python3

import os
import sys

SHADER_DIR = "shaders"
SHADER_TYPES = {
    ".vert": "VertexShader",
    ".frag": "FragmentShader",
}

def decorate(line):
    return "\"    {}\\n\"".format(line)

def parse_shaders_type(shader_type):
    return {
        sh[:-len(shader_type)].replace(" ", ""): "\n".join([
            decorate(line.rstrip())
            for line in open(os.path.join(SHADER_DIR, sh))
        ]) for sh in shader_files if sh.endswith(shader_type)
    }

with open(os.path.join(SHADER_DIR, "shader_list.txt"), "r") as fin:
    shader_files = [sh.strip() for sh in fin.readlines() if sh.strip()]

for i in shader_files:
    flag = False
    for shader_type in SHADER_TYPES:
        flag = flag or i.endswith(shader_type)
    if not flag:
        sys.stderr.write("Unrecognized shader file: {}\n".format(i))

with open("include/ShaderSources.h", "w") as fout:
    fout.write("namespace Hors {\n\n")

    for shader_type, class_name in SHADER_TYPES.items():
        sys.stderr.write("Start to process shaders {} for class {}\n".format(shader_type, class_name))
        shaders = parse_shaders_type(shader_type)
        sys.stderr.write(str(shaders))
        fout.write("class {} {{\npublic:\n".format(class_name))
        for shader_name, shader_src in shaders.items():
            fout.write("    static constexpr const char * {} =\n".format(shader_name))
            for line in shader_src:
                fout.write(line)
            fout.write("\n\"\\n\";\n\n")
        fout.write("};\n\n")

    fout.write("}\n")