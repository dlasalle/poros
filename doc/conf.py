import subprocess

# run doxygen
subprocess.call("cd ..; doxygen doxygen.conf", shell=True)


html_extra_path = ["html"]
