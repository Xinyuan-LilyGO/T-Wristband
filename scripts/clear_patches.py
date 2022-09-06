from os.path import join, isfile
import os

Import("env")

def post_program_action(source, target, env):
    project_dir = env['PROJECT_DIR']
    os.chdir(join(project_dir, '..', '..', 'libdeps'))
    env.Execute("git checkout .")
    os.chdir(project_dir)

env.AddPostAction("$PROGPATH", post_program_action)
