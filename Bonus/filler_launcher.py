import os
import sys

def maps_menu():
	choice = input("""
			A: maps00
			B: maps01
			C: maps02
			D: Perso
			Tape your choice : """)
	if choice == "A" or choice =="a":
		return 'resources/maps/map00'
	elif choice == "B" or choice =="b":
		return 'resources/maps/map01'
	elif choice == "C" or choice =="c":
		return 'resources/maps/map02'
	elif choice == "D" or choice == "d":
		orig_string = 'resources/maps/'
		maps = orig_string + input('name of your map: ')
		return (maps)
	else:
	    print("You must only select either A,B,C or D")
	    print("Please try again")
	    maps_menu()
	    print('\n')

def players_menu():
	choice = input("""
			A: auguyon
			B: abanlin
			C: carli
			D: champely
			E: grati
			F: hcao
			G: superjeannot 
			Tape your choice : """)
	if choice == "A" or choice =="a":
		return './auguyon.filler'
	elif choice == "B" or choice =="b":
		return 'resources/players/abanlin.filler'
	elif choice == "C" or choice =="c":
		return 'resources/players/carli.filler'
	elif choice == "D" or choice == "d":
		return 'resources/players/champely.filler'
	elif choice == "E" or choice == "e":
		return 'resources/players/grati.filler'
	elif choice == "F" or choice == "f":
		return 'resources/players/hcao.filler'
	elif choice == "G" or choice == "g":
		return 'resources/players/superjeannot.filler'
	else:
		print("You must only select either A,B,C,D,E,F or G")
		print("Please try again")
		players_menu()
		print('\n')

def choose_exit():
	choice = input("""
			A: Standard Output
			B: Standard Output with quiet mode
			C: File Output
			D: Visual Output Bonus
			Tape your choice : """)
	if choice == "A" or choice == "a":
		return
	elif choice == "B" or choice == "b":
		return ("B")
	elif choice == "C" or choice =="c":
		name = input("File name ? :")
		if not name:
			name = " > filler_output"
		else:
			name = orig_string = ' > ' + name 
		return name
	elif choice == "D" or choice =="d":
		return (' | ./visual_filler')
	else:
		print("You must only select either A,B or C")
		print("Please try again")
		choose_exit()
		print('\n')

cmd = 'resources/./filler_vm'
print('\nWhich map ?')
maps = maps_menu()
maps = orig_string = ' -f ' + maps
os.system("clear")

print("\nWhich First Player ?")
player_one = players_menu()
player_one = orig_string = ' -p1 ' + player_one
os.system("clear")

print("\nWhich Second Player ?")
player_two = players_menu()
player_two = orig_string = ' -p2 ' + player_two
os.system("clear")

print("\nWhich Output ?")
output = choose_exit()
if not output:
	output = ""
elif output == 'B':
	output = " -q"
os.system("clear")	

argc = len(sys.argv)
if argc > 1:
	if sys.argv[1] == "-printcmd":
		print (cmd + maps + player_one + player_two + output)
os.system(cmd + maps + player_one + player_two + output)