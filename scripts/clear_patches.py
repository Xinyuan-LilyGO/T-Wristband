from os.path import join, isfile
import os

Import("env")

def post_program_action(source, target, env):
    project_dir = env['PROJECT_DIR']
    patches_dir = join(project_dir, '..', '..', 'libdeps', 'patches')
    patch = join(project_dir, '..', '..', 'scripts', 'patch.py')
    for i in os.listdir(patches_dir):
        print("unpatching %s" % join(patches_dir, i))
        env.Execute("$PYTHONEXE %s %s --debug -d %s --revert" % (patch,
                                                                 join(patches_dir, i),
                                                                 join(project_dir, '..', '..')
                                                                )
                    )

env.AddPostAction("$PROGPATH", post_program_action)
