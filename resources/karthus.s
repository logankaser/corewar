.name 		"Karthus"
.comment	"The Deathsinger"

; r12 = char Q
; r13 = char U
; r14 = char A
; r15 = char !


start:
	ld		%0, r9
	sti		r1, %21, %1
	sti		r2, %:global_taunt, %42
	zjmp	%:death_defied

fall:
	sti		r1, %10, %1
	fork	%88
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

death_defied: # Passive
	fork	%:defile # E
	live	%0
	fork	%:lay_waste # Q
	live	%0
	fork	%:wall_of_pain # W
	live	%0
	fork	%:requiem # R (ult)
	zjmp	%:death_defied
lay_waste: # Q
wall_of_pain: # W
defile: # E
requiem: # R (ult)
