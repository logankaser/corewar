.name "karthus"

.comment "dead alive"

top:
	st r1,6
	live %42
	and r2,r2,r2
	zjmp %:top
