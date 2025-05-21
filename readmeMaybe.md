to_do
	- change out libft
	challenge: It contains gnl & printf wich i both use for importing the map.
				so those need to be added to, and the makefile needs updating.

where does that debug print come from ? it announces type the player is 'standing' on.
	-> In input_handler is a function called check_for_wall that does this.
		- function is first step to hopefully figure out wall collisions.
