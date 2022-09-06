from os.path import join, isfile
import os

Import("env")

project_dir = env['PROJECT_DIR']
patch = join(project_dir, '..', '..', 'scripts', 'patch.py')
patches_dir = join(project_dir, '..', '..', 'libdeps', 'patches')

os.chdir(join(project_dir, '..', '..'))

for i in os.listdir(patches_dir):
    env.Execute("python %s %s --debug" % (patch, join(patches_dir, i)))

os.chdir(project_dir)
