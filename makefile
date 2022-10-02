#the rule
#you should use command make * to run your rule.

src = $(wildcard ./src/*.c)
include = ./include
args = -Wall -g -pthread
#patsubst original, replacement, variabe
#means replace the all ./src/%.c in $(src) to ./obj/%.o 
obj1 = $(patsubst ./src/%.c,./obj/%.o,$(src))
obj2 = $(patsubst %.c,./obj/%.o,main.c)

#merger two variable
obj = $(obj1) $(obj2)
#if you want run the shell command, you should use @
print:
	@echo $(obj1)
	@echo $(obj2)
	@echo $(obj)

all:main

#$^ : mean all the dependent in this rule; 
#$< : means the first dependent in this rule;
#$@ : means target main in this rule;
#notice : the run rule is process will run and traverse run the next rule util get all 
#the dependent if the current rule no dependent.
main:$(obj)
	gcc $^ -o $@ $(args)

#the target is $(obj), the dependent is ./obj/%.o
#the target is ./obj/%.o, the dependent is ./src/%.c
$(obj1):./obj/%.o:./src/%.c
	gcc -c $< -o $@ $(args) -I $(include)
#because the main.c and other .c file not in one path, so here we need to 
#make the rule separately.
$(obj2):./obj/%.o:./%.c
	gcc -c $< -o $@ $(args) -I $(include)

clean:
	rm -rf $(obj) main

run:
	./main

.PHONY:
	clean all