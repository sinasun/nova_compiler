#
# CMakeList.txt : CMake project for Compilers, include source and define project specific logic here.
#

# =---------------------------------------=
# |  COMPILERS - ALGONQUIN COLLEGE (F23)  |
# =---------------------------------------=
# |              ....                     |
# |          ........::.::::::.           |
# |        .:........::.:^^^~~~:          |
# |        :^^::::::^^^::^!7??7~^.        |
# |       .:^~~^!77777~~7?YY?7??7^.       |
# |       :.^~!??!^::::^^~!?5PY??!~.      |
# |       ~!!7J~.:::^^^^~!!~~?G5J?~       |
# |       :^~?!~7?Y57^^?PP5YJ!J5Y?:       |
# |       .~!!.:^!7!:.:7JYYJ7~7Y7^        |
# |       .~77..    . .~^:^^^~7?:         |
# |       .^!^~:::.:^!7?~^~!77J:          |
# |        ^^!Y~^^^^~?YJ77??7JJ^          |
# |       .^7J?~^~~^~7??7??7JY?~:         |
# |        ::^^~^7?!^~~!7???J?J7~:.       |
# |         ^~~!.^7YPPPP5Y?7J7777~.       |
# |        ..:~..:^!JPP5YJ?!777!^.        |
# | .~?JJJJJJJJJJYYYYYPPPPPPPPPPPP5PPYY~  |
# |  :!Y5GGG.___ YYYYYY__._.PPGGGGGG5!.   |
# |   :!Y5G / __| ___ / _(_)__ _ PGP5.    |
# |    :~75 \__ \/ _ \  _| / _` | 5?.     |
# |     7~7 |___/\___/_| |_\__,_| Y5?.    |
# |    .^~!~.....................P5YY7.   |
# |   .:::::::::::::?JJJJYYYYYYYYYJJJJ7.  |
# |                                       |
# =---------------------------------------=

cmake_minimum_required (VERSION 3.8)

project ("Compiler")

# Add source to this project's executable: check name and dependences
add_executable (Compiler
	"Compilers.h"	"Compilers.c"
	"Reader.h"		"Reader.c"		"MainReader.c"
	#"Scanner.h"		"Scanner.c"		"MainScanner.c"
	#"Parser.h"		"Parser.c"		"MainParser.c"
	# TO_DO: Add A22 (Scanner) and A32 (Parser)
)

# TO_DO: Add tests and install targets if needed.
