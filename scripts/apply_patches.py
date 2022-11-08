from os.path import join, abspath
import logging

Import("env")

# try:
#     import patch
# except ImportError:
#     env.Execute("$PYTHONEXE -m pip install git+https://github.com/liangyingy/python-patch.git")

logging.basicConfig(level = logging.DEBUG, format='%(levelname)s %(message)s')
logger = logging.getLogger('platformio-patch')

project_dir = env['PROJECT_DIR']
patch_exe = join(project_dir, '..', '..', 'scripts', 'patch.py')

section = env.GetProjectOption('custom_patch_section')
config = env.GetProjectConfig()
root_dir = abspath(config.get(section, 'root_dir', default=join(project_dir)))
patches = config.get(section, 'patches', default="").splitlines()

logger.info('root directory for applying patch: %s' % root_dir)
logger.info('patch list:')
for i in patches:
    logger.info('  %s' % i)

for i in patches:
    logger.info("patching %s" % (abspath(i)))
    env.Execute("$PYTHONEXE %s %s --debug -d %s" % (patch_exe,
                                                    abspath(i),
                                                    root_dir
                                                    )
                )

def post_program_action(source, target, env):
    global root_dir
    global patches
    project_dir = env['PROJECT_DIR']
    patch_exe = join(project_dir, '..', '..', 'scripts', 'patch.py')
    for i in patches:
        logger.info("unpatching %s" % abspath(i))
        env.Execute("$PYTHONEXE %s %s --debug -d %s --revert" % (patch_exe,
                                                                 abspath(i),
                                                                 root_dir
                                                                )
                    )

env.AddPostAction("$PROGPATH", post_program_action)
