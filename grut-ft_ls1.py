# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    grut-ft_ls.py                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/14 09:55:22 by akharrou          #+#    #+#              #
#    Updated: 2019/06/09 14:46:10 by akharrou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

try:
	import os
	import sys

	# COLORIZATION — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — #

	RED        = '\033[31m'
	GREEN      = '\033[32m'
	YELLOW     = '\033[38;2;247;249;94m'
	GOLD       = '\033[38;2;218;171;119m'

	DEFAULT    = '\033[0m'
	ITALTIC    = '\033[3m'
	UNDELRINED = '\033[4m'
	BACKGROUND = '\033[0m'
	STRIPS     = GOLD

	RED_BACKGROUND    = '\033[41m'

	# TITLES — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — #

	TITLE    = 'GENERALIZED RAMBO UNIT-TESTER ™️'

	FILENAME='grut-ft_ls.py'
	EDITION='ft_ls Edition'

	# EXTENSION — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — #

	import time

	BAR_LEN  = 38 + (110 * 2) + 11 + 16
	COL1_LEN = 38
	COL2_LEN = 110
	COL3_LEN = 110
	COL4_LEN = 11

	FILE_A = f'/tmp/__output_A__'
	FILE_B = f'/tmp/__output_B__'

	def GRUTBody__ft_ls(program_A, program_B):

		i = 0
		total_trues = 0
		total_args = len(arguments)
		width = len(str(total_args))

		print(f' {f"—" * (BAR_LEN + width)}')
		print(f'| {"":{width}} |  {"INPUT:":{COL1_LEN}}|   {"PROGRAM A:":{COL2_LEN}}|   {"PROGRAM B:":{COL3_LEN}}|  {"IDENTICAL":{COL4_LEN}}|')
		print(f'|-{"-" * width}-|{"-" * (COL1_LEN + 2)}|{"-" * (COL2_LEN + 3)}|{"-" * (COL2_LEN + 3)}|{"-" * 13}|')

		with open(f"{FILE_A}", 'w+') as fd_A:
			with open(f"{FILE_B}", 'w+') as fd_B:

					for arg in arguments:

						try:

							arg = arg.strip('\n').replace('\t', '    ')

							test_trues = 0

							i += 1

							print(f"""| {'':{width}} |  {f'':{COL1_LEN}}|   {'':{COL2_LEN}}|   {'':{COL3_LEN}}| """, end="")
							print(f'  {"":{COL4_LEN - 1}}|')

							print(f"""| {i:0{width}} |  PATH: {f'{UNDELRINED}{arg}{DEFAULT}':{COL1_LEN + 2}}|   {f'':{COL2_LEN}}|   {f'':{COL3_LEN}}|   {f'':{COL4_LEN - 1}}|""")

							program_A_t1 = time.perf_counter()
							os.system(f"{program_A} {arg} > {FILE_A}")
							program_A_t2 = time.perf_counter()
							tt_program_A_time = program_A_t2 - program_A_t1

							program_B_t1 = time.perf_counter()
							os.system(f"{program_B} {arg} > {FILE_B}")
							program_B_t2 = time.perf_counter()
							tt_program_B_time = program_B_t2 - program_B_t1

							fd_A.seek(0)
							fd_B.seek(0)

							outputs = list(zip(fd_A.readlines(), fd_B.readlines()))

							programA_output = outputs[0][0].rstrip('\n')
							programB_output = outputs[0][1].rstrip('\n')

							lines_read = 1
							for lineA, lineB in outputs:

								lines_read += 1

								programA_output = lineA.rstrip('\n')
								programB_output = lineB.rstrip('\n')

								print(f"""| {'':{width}} |  {f'':{COL1_LEN}}|   {programA_output:{COL2_LEN}}|   {programB_output:{COL3_LEN}}| """, end="")

								if (programA_output == programB_output):
									print(f'  {f"[{GREEN}TRUE{DEFAULT}]":{COL4_LEN + 8}}|')
									test_trues += 1
								else:
									print(f'  {f"[{RED}FALSE{DEFAULT}]":{COL4_LEN + 8}}|')

							if (test_trues == len(outputs)):
								total_trues += 1

							print(f"""| {f'':{width}} |  {f'':{COL1_LEN}}|   {'':{COL2_LEN}}|   {'':{COL3_LEN}}|   {f'':{COL4_LEN - 1}}|""")
							print(f"""| {f'':{width}} |  {f'Time :':{COL1_LEN}}|   {f'{tt_program_A_time} seconds':{COL2_LEN}}|   {f'{tt_program_B_time} seconds':{COL3_LEN}}|   {f'':{COL4_LEN - 1}}|""")
							print(f"""| {f'':{width}} |  {f'':{COL1_LEN}}|   {'':{COL2_LEN}}|   {'':{COL3_LEN}}| """, end="")
							print(f'  {"":{COL4_LEN - 1}}|')

							print(f' {f"—" * (BAR_LEN + width)}')

						except Exception as e:
							print(f'|\n|  Something unexpected happened with the following argument : {RED_BACKGROUND}{YELLOW}💣  {arg} 💣{DEFAULT}\n|')
							print(f'|-{"-" * width}-|{"-" * (COL1_LEN + 2)}|{"-" * (COL2_LEN + 3)}|{"-" * (COL2_LEN + 3)}|{"-" * 13}|')

			print(f'\n[{total_trues} / {i}] IDENTICAL RESULTS ')

			os.remove(f'{FILE_A}')
			os.remove(f'{FILE_B}')


	# USAGE & MANUAL — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — #

	def usage():
		print(f'usage: python3 {FILENAME} {UNDELRINED}Program_A Launch Command{DEFAULT} {UNDELRINED}Program_B Launch Command{DEFAULT} [ {UNDELRINED}--help{DEFAULT} | {UNDELRINED}--manual{DEFAULT} | -d {UNDELRINED}directory(ies){DEFAULT} ... | -f {UNDELRINED}file(s){DEFAULT} ... | {UNDELRINED}input_argument(s){DEFAULT} ...]')
		sys.exit(1)

	def manual():
		print(f'{UNDELRINED}Coming soon...{DEFAULT}')
		sys.exit(1)

	# FLAG HANDLING — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — #

	# '--help' Flag :

	if (  len(sys.argv) < 4            or
		  sys.argv[3] == '-h'          or
		  sys.argv[3] == '--help'      or
		  sys.argv[3] == ''                 ):

		usage()

	# '--manual' Flag :

	elif (  sys.argv[3] == '-m'        or
		    sys.argv[3] == '-man'      or
		    sys.argv[3] == '-manual'   or
		    sys.argv[3] == '--manual'      ):

		manual()

	# '-f' Flag :

	elif (sys.argv[3] == '-f'):

		if (len(sys.argv[4:]) < 1):
			usage()

		try:

			arguments = []
			for argsFile in sys.argv[4:]:

				try:

					with open(argsFile, 'r') as fd:
						arguments.extend(fd.readlines())

				except Exception:
					print(f'{argsFile}: Invalid Input File')
					sys.exit(1)

		except Exception as e:
			usage()

	# '-d' Flag :

	elif (sys.argv[3] == '-d'):

		if (len(sys.argv[4:]) < 1):
			usage()

		try:

			arguments = []

			for dir in sys.argv[4:]:

				try:

					for dirfile in os.listdir(dir):

						try:

							dirfile = f'./{dir}/{dirfile}'

							if os.path.isfile(dirfile) == True:
								with open(dirfile, 'r') as fd:
									arguments.extend(fd.readlines())

						except Exception:
							print(f'{dirfile}: Invalid Input File')
							sys.exit(1)

				except Exception:
					print(f'{dir}: Invalid Directory')
					sys.exit(1)

		except Exception as e:
			usage()

	# No Flag :

	else:
		arguments = sys.argv[3:]

	# DYNAMIC INPUT — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — #

	try:

		launch_command_programA = sys.argv[1]
		launch_command_programB = sys.argv[2]

	except NameError as err:
		print(f'\nMissing Programs')
		sys.exit(1)

	# HEADER — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — #

	print(f'{STRIPS}{f"=" * (BAR_LEN + 2)}')
	print(f'|{DEFAULT}{BACKGROUND}{f" " * (BAR_LEN)}{DEFAULT}{STRIPS}|')
	print(f'|{DEFAULT}{BACKGROUND}{f" " * (int((BAR_LEN - 3) / 2) - int(len(TITLE) / 2))}⚜️  {DEFAULT}{TITLE}{DEFAULT}{BACKGROUND}  ⚜️{f" " * (int((BAR_LEN - 3) / 2) - int(len(TITLE) / 2) - 2)}{DEFAULT}{STRIPS}|')
	print(f'|{DEFAULT}{BACKGROUND}{f" " * int((BAR_LEN - 3) / 2 - int(len(EDITION) / 2))}~ {ITALTIC}{EDITION}{DEFAULT}{BACKGROUND} ~{f" " * (int((BAR_LEN - 3) / 2 - int(len(EDITION) / 2)) - 1 - (len(EDITION) % 2))}{DEFAULT}{STRIPS}|')
	print(f'|{DEFAULT}{BACKGROUND}{f" " * (BAR_LEN)}{DEFAULT}{STRIPS}|')
	print(f'{STRIPS}{f"=" * (BAR_LEN + 2)}{DEFAULT}')

	print(f'\nProgram A Launch Command: {launch_command_programA}')
	print(f'Program B Launch Command: {launch_command_programB}')
	print('')

	# BODY — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — #

	try:

		GRUTBody__ft_ls(launch_command_programA, launch_command_programB)

	except KeyboardInterrupt:
		print(f'{UNDELRINED}\n\n🚨  You abruptly quit ! 🚨{DEFAULT}')
		sys.exit(1)

	# FOOTER — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — #

	print(f'️\n{UNDELRINED}Share if you found it useful !{DEFAULT} :: 42 G.R.U.T -- © 2019')
	print('')

except Exception as e:
	print(f' {f"—" * (BAR_LEN)}\n')
	print(f'{RED_BACKGROUND}{YELLOW}💣  G.R.U.T CRASHED 💣{DEFAULT}\n')
	print(f'{UNDELRINED}\n🚨  Please Check Your Input  |OR|  Report the Issue ! 🚨{DEFAULT}  :: 42 G.R.U.T -- © 2019')
	print(f'{DEFAULT}Copy paste the following and {YELLOW}report or dm{DEFAULT} @akharrou or @kmira the issue\n\n')
	print(f'{UNDELRINED}GRUT ISSUE:\n{DEFAULT}{RED_BACKGROUND}{ITALTIC}')
	raise e
