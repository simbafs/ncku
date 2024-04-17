.DEFAULT_GOAL: check
.PHONY: check
check: checkq1 checkq2

.PHONY: Q1
Q1-ans: 
	riscv64-unknown-linux-gnu-gcc -march=rv64gc -static -O0 ./Q1/testbench_driver.c ./Q1/conv2d.S -o ./Q1/a.out
	spike  --isa=RV64GC --dc=8:4:32 /opt/riscv/riscv64-unknown-linux-gnu/bin/pk ./Q1/a.out ./Q1/ans.output

Q1-stu:
	riscv64-unknown-linux-gnu-gcc -march=rv64gc -static -O0 ./Q1/testbench_driver.c ./Q1/conv2d-better.S -o ./Q1/a.out
	spike -d --isa=RV64GC --dc=8:4:32 /opt/riscv/riscv64-unknown-linux-gnu/bin/pk ./Q1/a.out ./Q1/stu.output

Q2-ans:
	riscv64-unknown-linux-gnu-gcc -march=rv64gc -static -O0 ./Q2/testbench_driver.c ./Q2/mm.c -o ./Q2/a.out
	spike  --isa=RV64GC --dc=8:4:32 /opt/riscv/riscv64-unknown-linux-gnu/bin/pk ./Q2/a.out #./Q2/ans.output

Q2-stu:
	riscv64-unknown-linux-gnu-gcc -march=rv64gc -static -O0 ./Q2/testbench_driver.c ./Q2/mm-better.c -o ./Q2/a.out
	spike --isa=RV64GC --dc=8:4:32 /opt/riscv/riscv64-unknown-linux-gnu/bin/pk ./Q2/a.out #./Q2/stu.output

.PHONY: checkq1
checkq1:
	@printf "=============== Q1 ===============\n"
	@python3 testq1.py

.PHONY: checkq2
checkq2:
	@printf "=============== Q2 ===============\n"
	@python3 testq2.py

.PHONY: diffq1
diffq1:
	@git diff --color-words --no-index -U0 -G. Q1/ans.output Q1/stu.output

.PHONY: diffq2
diffq2:
	@git diff --color-words --no-index -U0 -G. Q2/ans.output Q2/stu.output

.PHONY: clean
clean:
	$(RM) Q1/*.out* Q2/*.out*
