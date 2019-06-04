.name 		"Karthus"
.comment	"The Deathsinger"

# r1 = Q ability
# r2 = W ability
# r3 = E ability
# r4 = Ult

# r6 = Write position
# r7 = Copy position
# r8 = Length to copy
# r9 = Available space

# r12 = char 'Q'
# r13 = char 'U'
# r14 = char 'A'
# r15 = char '!''

start:
	ld		%:end, r8
	ld		%:start, r9
	sub		r8, r9, r8
	and		r8, %3, r9
	add		r8, r7, r8
	and		r8, -4, r4
	ld		%0, r16
	sti		r6, %:global_taunt, %42
	zjmp	%:death_defied

fall:
	sti		r1, %10, %1
	fork	%:global_taunt
	live	%0
	fork	%10

global_taunt:			# One of his taunts (spammable)
	ld		%81, r12	# Q
	ld		%85, r13	# U
	ld		%65, r14	# A
	ld		%33, r15	# !
	aff		r12			# comments r12
	aff		r13			# comments r13
	aff		r14			# comments r14
	aff		r14			# comments r14
	aff		r14			# comments r14
	aff		r14			# comments r14
	aff		r15			# comments r15
	aff		r15			# comments r15
	ld		%81, r12	# Q
	ld		%85, r13	# U
	ld		%65, r14	# A
	ld		%33, r15	# !
	aff		r12			# comments r12
	aff		r13			# comments r13
	aff		r14			# comments r14
	aff		r14			# comments r14
	aff		r14			# comments r14
	aff		r14			# comments r14
	aff		r15			# comments r15
	aff		r15			# comments r15
	ld		%81, r12	# Q
	ld		%85, r13	# U
	ld		%65, r14	# A
	ld		%33, r15	# !
	aff		r12			# comments r12
	aff		r13			# comments r13
	aff		r14			# comments r14
	aff		r14			# comments r14
	aff		r14			# comments r14
	aff		r14			# comments r14
	aff		r15			# comments r15
	aff		r15			# comments r15
	live	%1337		# hax
	zjmp	%:global_taunt

cooldown_q:
	live	%1
	fork	%:lay_waste
	zjmp	%:cooldown_q

cooldown_w:
	live	%10
	fork	%:wall_of_pain
	zjmp	%:cooldown_w

cooldown_e:
	live	1000
	fork	%:defile
	zjmp	%:cooldown_e

cooldown_r:
	live	%120
	fork	%:requiem
	zjmp	%:cooldown_r

death_defied: 				# Passive
	fork	%:defile		# E
	live	%0
	fork	%:lay_waste		# Q
	live	%0
	fork	%:wall_of_pain	# W
	live	%0
	fork	%:requiem		# R (ult)
	fork	%:global_taunt
	zjmp	%:death_defied

lay_waste: # Q
	live	%1
	zjmp	%:lay_waste
wall_of_pain: # W
	live	%1
	ld		%20, r2
	st		r2, 0
	st		r2, -11
	st		r2, -22
	st		r2, -33
	st		r2, -44
	st		r2, -55
	st		r2, -66
	st		r2, -77
	st		r2, -88
	st		r2, -99
	st		r2, -110
	st		r2, -122
	st		r2, -133
	st		r2, -144
	st		r2, -155
	st		r2, -166
	st		r2, -177
	st		r2, -188
	st		r2, -199
	st		r2, -211
	st		r2, -222
	st		r2, -233
	st		r2, -244
	st		r2, -255
	st		r2, -266
	st		r2, -277
	st		r2, -288
	st		r2, -299
	st		r2, -311
	st		r2, -322
	st		r2, -333
	st		r2, -344
	st		r2, -355
	st		r2, -366
	st		r2, -377
	st		r2, -388
	st		r2, -399
	st		r2, -411
	st		r2, -422
	st		r2, -433
	st		r2, -444
	st		r2, -455
	st		r2, -466
	st		r2, -477
	st		r2, -488
	st		r2, -499
	fork	%:cooldown_w
	zjmp	%12

defile: # E
	live	%1
	zjmp	%:defile
requiem: # R (ult)
	live	%1
	zjmp	%:requiem
end:
