
LDFLAGS = -lstdc++

CXXFLAGS=-Wall -Werror -Og -g

PROGS += day1
PROGS += day2
PROGS += day3
#PROGS += day4
#PROGS += day5
#PROGS += day6
#PROGS += day7
#PROGS += day8
#PROGS += day9
#PROGS += day10
#PROGS += day11
#PROGS += day12
#PROGS += day13
#PROGS += day14
#PROGS += day15
#PROGS += day16
#PROGS += day17
#PROGS += day18
#PROGS += day19
#PROGS += day20
#PROGS += day21
#PROGS += day22
#PROGS += day23
#PROGS += day24
#PROGS += day25

TESTPROGS = ${PROGS:=-test}

all: ${PROGS} ${TESTPROGS}

test: $(TESTPROGS:-test=-test.out)

clean:
	rm -f ${PROGS} ${TESTPROGS} *.o ${DEPDIR}/* *-test.out

day1: day1.o main.o
day2: day2.o main.o
day3: day3.o main.o
#day4: day4.o main.o
#day5: day5.o main.o
#day6: day6.o main.o
#day7: day7.o main.o
#day8: day8.o main.o
#day9: day9.o main.o
#day10: day10.o main.o
#day11: day11.o main.o
#day12: day12.o main.o
#day13: day13.o main.o
#day14: day14.o main.o
#day15: day15.o main.o
#day16: day16.o main.o
#day17: day17.o main.o
#day18: day18.o main.o
#day19: day19.o main.o
#day20: day20.o main.o
#day21: day21.o main.o
#day22: day22.o main.o
#day23: day23.o main.o
#day24: day24.o main.o
#day25: day25.o main.o

day1-test: day1-test.o day1.o testmain.o -lgtest
day2-test: day2-test.o day2.o testmain.o -lgtest
day3-test: day3-test.o day3.o testmain.o -lgtest
#day4-test: day4-test.o day4.o testmain.o -lgtest
#day5-test: day5-test.o day5.o testmain.o -lgtest
#day6-test: day6-test.o day6.o testmain.o -lgtest
#day7-test: day7-test.o day7.o testmain.o -lgtest
#day8-test: day8-test.o day8.o testmain.o -lgtest
#day9-test: day9-test.o day9.o testmain.o -lgtest
#day10-test: day10-test.o day10.o testmain.o -lgtest
#day11-test: day11-test.o day11.o testmain.o -lgtest
#day12-test: day12-test.o day12.o testmain.o -lgtest
#day13-test: day13-test.o day13.o testmain.o -lgtest
#day14-test: day14-test.o day14.o testmain.o -lgtest
#day15-test: day15-test.o day15.o testmain.o -lgtest
#day16-test: day16-test.o day16.o testmain.o -lgtest
#day17-test: day17-test.o day17.o testmain.o -lgtest
#day18-test: day18-test.o day18.o testmain.o -lgtest
#day19-test: day19-test.o day19.o testmain.o -lgtest
#day20-test: day20-test.o day20.o testmain.o -lgtest
#day21-test: day21-test.o day21.o testmain.o -lgtest
#day22-test: day22-test.o day22.o testmain.o -lgtest
#day23-test: day23-test.o day23.o testmain.o -lgtest
#day24-test: day24-test.o day24.o testmain.o -lgtest
#day25-test: day25-test.o day25.o testmain.o -lgtest

%-test.out: %-test
	set -o pipefail; \
	"./$<" | tee "$@.tmp"; \
	[[ $$? -eq 0 ]] && mv "$@.tmp" "$@" || exit 1

include Makefile.inc
