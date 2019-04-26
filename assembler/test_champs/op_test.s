  .name "op_test"

.comment "op testing file"

#comment
<<<<<<< HEAD
label: #comment
live: live %1
		ld: ld 1 , r2
		ld :live,r1
		fork %1
=======
ld:live %1
		ld: ld %1, r2
		ld 2,r1
		fork %:ld
>>>>>>> d63eafbe29a298e81ad28cff8791652640504f65
