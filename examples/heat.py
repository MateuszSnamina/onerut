#!/usr/bin/python3

import os
import subprocess
import re

############################
###  Runner  ###############
############################

class Runner:
  def __init__(self, script_file_path, env):
    self.onerut_elf_shell_invocation = 'onerut'
    self.script_file_path = script_file_path
    self.env = env

  def run(self):
    command = self.onerut_elf_shell_invocation
    command += ' ' + self.script_file_path
    if hasattr(self, 'n_max_iter'):
      command += ' ' + '-n ' + str(self.n_max_iter)
    print("[COMMAND] " + command)
    self.proc = subprocess.Popen(command,
                                 shell=True,
                                 stdout=subprocess.PIPE,
                                 stderr=subprocess.PIPE,
                                 env = self.env)
    self.outs, self.errs = self.proc.communicate()
    returncode = self.proc.returncode
    print("[COMMAND] " + "returncode = " + str(returncode) + ".")

  def returncode(self):
    return self.proc.returncode

  def print_outs(self):
    outs_lines = self.outs.split(b'\n')
    for line in outs_lines:
      print("[STDOUT] " + line.decode())

  def print_errs(self):
    errs_lines = self.errs.split(b'\n')
    for line in errs_lines:
      print("[STDERR] " + line.decode())

  def scan(self):
    out_lines = self.outs.split(b'\n')
    out_lines_iterator = iter(out_lines)
    in_summary = False
    while True:
      try: 
        line = next(out_lines_iterator)
      except:
        break
      if b"[DECLARATIVE MODE] [STEP] [SELF-CONSISTENT LOOP] [SUMMARY]" in line:
        in_summary = True
        continue
      if in_summary and b"[PRINT VALUE REQUEST] {:anonymous:|`VALUE(mean_Sz)`}" in line:
        output_line = next(out_lines_iterator)
        pattern = re.compile(b"\[request\] \[value\] (?:.*) = (.*)")
        match = pattern.search(output_line)
        if match:
          #print("match")
          #print("value_str:", match.group(1))
          print("[SCAN  ] [VALUE] mean_Sz:", float(match.group(1)))

############################
###  RunnerBuilder  ########
############################

class RunnerBuilder:
  def __init__(self):
    self._script_file_path = None
    self._env = dict()

  def script(self, script_file_path):
    self._script_file_path = script_file_path
    return self

  def env(self, name, value):
    self._env[name] = value
    return self

  def n_max_iter(self, n_max_iter):
    self._n_max_iter = n_max_iter
    return self

  def build(self):
    # script file:
    if (self._script_file_path == None):
      raise RuntimeError('Script file path was not provied.')
    # env:
    run_env = os.environ.copy()
    for name, value in self._env.items():
      run_env[name] = str(value)
    # biuld:
    runner = Runner(self._script_file_path, run_env)
    # n_max_iter:
    if hasattr(self, '_n_max_iter'):
      runner.n_max_iter = self._n_max_iter
    # return
    return runner


############################
###  main  #################
############################
if (__name__ == "__main__"):
  runner = RunnerBuilder().\
             script('ising-2d-fm_mf-on-site.onerut').\
             n_max_iter(500).\
             env('temperature', 0.8).\
             build()
  runner.run()
  runner.print_outs()
  runner.print_errs()
  runner.scan()
