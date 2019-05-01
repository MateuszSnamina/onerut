#!/usr/bin/python3

import os
import subprocess
import re
import numpy as np
import matplotlib.pyplot as plt

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
    #print("[COMMAND] " + command)
    self.proc = subprocess.Popen(command,
                                 shell=True,
                                 stdout=subprocess.PIPE,
                                 stderr=subprocess.PIPE,
                                 env = self.env)
    self.outs, self.errs = self.proc.communicate()
    returncode = self.proc.returncode
    #print("[COMMAND] " + "returncode = " + str(returncode) + ".")

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

  def scan(self, lookup_variabe_names):
    # Container for result
    lookup_variabe_dict = dict()
    # if something went wrong:
    if self.returncode() != 0:
      return lookup_variabe_dict
    # Output syntax:
    SYMMARY_HEADER = b"[DECLARATIVE MODE] [STEP] [SELF-CONSISTENT LOOP] [SUMMARY]"
    PRINT_VALUE_REQUEST_HEADER = \
      lambda variable_name: b"[PRINT VALUE REQUEST] {:anonymous:|`VALUE(" + variable_name.encode() + b")`}"
    # Split out bytes:
    out_lines = self.outs.split(b'\n')
    # Iterate over bytes lines:
    out_lines_iterator = iter(out_lines)
    in_summary = False
    while True:
      try: 
        line = next(out_lines_iterator)
      except:
        break
      if SYMMARY_HEADER in line:
        in_summary = True
        continue
      for lookup_variable_name in lookup_variabe_names:
        if in_summary and PRINT_VALUE_REQUEST_HEADER(lookup_variable_name) in line:
          output_line = next(out_lines_iterator)
          pattern = re.compile(b"\[request\] \[value\] (?:.*) = (.*)")
          match = pattern.search(output_line)
          if match:
            lookup_variable_value = float(match.group(1))
            #debug_message = "[SCAN  ] [VALUE] " + lookup_variable_name + " = " + str(lookup_variable_value)
            #print(debug_message)
            lookup_variabe_dict[lookup_variable_name] = lookup_variable_value
    return lookup_variabe_dict

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
  # Set the heat task params:
  #script_path = 'ising-2d-fm_mf-on-site.onerut'
  #script_path = 'ising-2d-fm_mf-on-cross.onerut'
  script_path = 'ising-2d-fm_mf-on-plaquette.onerut'
  temaperatures = list(np.arange(0, 1.4, 0.05))
  # Set the lookup_variabe_names:
  lookup_variabe_names = ['mean_Sz', 'specific_heat']
  map_temperature_to_lookup_variabe_dict = dict() # keys: temperature, value: lookup_variabe_maps
  # Run the calculations:
  print("╠═╗ Calculations:")
  start_mean_Sz = 0.5
  for temaperature in temaperatures:
    print("║ ╠═╗ Calculations for temaperature = {:12.6f}.".format(temaperature))
    runner = RunnerBuilder().\
               script(script_path).\
               n_max_iter(500).\
               env('temperature', temaperature).\
               env('start_mean_Sz', start_mean_Sz).\
               build()
    runner.run()
    returncode = runner.returncode()
    if returncode != 0:
      runner.print_outs() # for debug
      runner.print_errs() # for debug
      print("║ ║ ║ [ERROR] Error during running with temperature {:12.6f}. Onerut returncode = {:3d}.".format(temaperature, returncode))
      exit(1)
    lookup_variabe_dict = runner.scan(lookup_variabe_names)
    print("║ ║ ╠══╗ lookup_variabe_dict: " + str(lookup_variabe_dict))     
    map_temperature_to_lookup_variabe_dict[temaperature] = lookup_variabe_dict
    start_mean_Sz = lookup_variabe_dict['mean_Sz'] # use the result value as a starting one in the next iteration
  # Prepare and show plots:
  print("╠═╗ Plot:")
  for lookup_variabe_name in lookup_variabe_names:
    print("║ ╠═╗ Plot for lookup_variabe_name: " + lookup_variabe_name)
    X, Y = [], []
    for temaperature in temaperatures:
      lookup_variabe_dict = map_temperature_to_lookup_variabe_dict.get(temaperature)
      if lookup_variabe_dict:
        lookup_variabe_value = lookup_variabe_dict.get(lookup_variabe_name)
        if lookup_variabe_value != None:
          X.append(temaperature)
          Y.append(lookup_variabe_value)
          print("║ ║ ╠══╗  {:12.6f} =  {:12.6f}.".format(temaperature, lookup_variabe_value))
    fig, ax = plt.subplots()
    ax.plot(X,Y)
    plot_title = lookup_variabe_name.replace("_", " ")
    ax.set_title(plot_title, fontdict = {'fontsize' : 40})
    plt.show()
