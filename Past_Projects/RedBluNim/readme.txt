Rudy Orozco 1001864902

Language/Version: Python 3.10.12

Code is structured in a single file, where all functions are separated with several being the minmax function call, max and min functions, and all the main functionality happens 
in global space. Takes in user input from command line and checks for flags and the specified number of marbles such as version of the game, who plays first, and a specified depth limit

[DEPTH LIMIT IS IMPLEMENTED]

abMinMax():
    ---
abMax():
    ---
abMin():
    ---
main functionality starts

To run the code:
python3 red_blue_nim.py <# of RED marbles> <# of BLUE marbles> <version> <first player> <depth limit>

Flag Options:
- version: standard / misere
- first player: computer / human
- depth limit: value > 1

[Example 1] Run Standard nim with 3 red and 5 blue marbles with no depth limit, where computer starts: 
            python3 expense_8_puzzle.py 3 5 standard computer

[Example 2] Run Misere nim with 5 red and 3 blue marbles with depth limit of 4, where human starts: 
            python3 expense_8_puzzle.py 5 3 misere human 4

NOTE: Number of marbles are required to run the game, you can run the program at minimum with this. They are ordered as specified.

[Minimum Ex.] python3 red_blue_nim.py <# of RED marbles> <# of BLUE marbles>

Version, first player, and depth limit flags can be left out
    - Default value for Version is Standard
    - Default value for First player is Computer
    - Depth limit will not be set and will run normally if not assigned
        - Depth limit value must always be the last argument in the command line.
        [Bad Example: python3 expense_8_puzzle.py 5 3 misere 4 human]

Prompts will show on your turn what you want to do.
- Choose b/B or r/R Marbles: type b or B for blue, r or R for red
- Choose 1 or 2 Marbles: type 1 or 2 for the amount of marbles (If a pile has 1 marble left, if chosen, will automatically take one marble)

Game ends when either pile reaches 0 and depending on the version, person with the empty pile wins (misere) or loses (standard) the game.