# 
# By IceRiver
# v0 2019年9月17日 

import os,sys
import colorama
from colorama import Fore, Back, Style

colorama.init()

# init
max_clear_count = 10

# title
print(Fore.RED + 'COCA PRATICE' + Style.RESET_ALL)
print('  :qq exit\n')
# get user store data
input_index = 0
user_store = open('coca_store.ini', 'r')
input_index_str = user_store.readline()
if(input_index_str):
	input_index = int(input_index_str)
user_store.close()

user_store = open('coca_store.ini', 'w')
user_store.write(str(input_index))
user_store.flush()

# get input data
coca_file = open('COCA20000.csv', 'r')
all_words = []
while True:
	word_line = coca_file.readline()
	if word_line:
		word_line = word_line.strip()
		word_list = word_line.split(',')
		all_words.append(word_list)
	else:
		break
	
coca_file.close()

# input loop
clear_screen_count = 0
while True:
	if input_index >= len(all_words):
		break
		
	clear_screen_count += 1
	if clear_screen_count == max_clear_count:
		clear_screen_count = 0
		os.system('cls')
		print(Fore.RED + 'COCA PRATICE' + Style.RESET_ALL)
		print('  :qq exit.\n')
	
	word = all_words[input_index]
	
	#word_definition = str(word[0]) + '\t' + word[1] + '\t' + word[2]
	#print('%s' % word_definition)
	print(str(word[0]) + '\t', end="")
	print(Fore.RED + str(word[1]) + '\t' + Style.RESET_ALL, end="")
	print(str(word[2]))
	
	input_word = input('>>\t')
	if input_word == word[1]:
		input_index += 1
		user_store.seek(0,0)
		user_store.write(str(input_index))
		user_store.flush()
		print(Fore.GREEN + '\t\tOK' + Style.RESET_ALL)
		#print('\t\tOK')
	elif input_word == 'qq':
		print('Exit')
		break
	else:
		#print(FORE.GREEN + 'Try' + Style.RESET_ALL)
		#print('\t\tTry')
		pass
		
user_store.close()

