DILITHIUM_PATH = ../../dilithium/ref
LPLIB_PATH ?= ../..
LPSOLVE_LIBDIR ?= $(LPLIB_PATH)/lp_solve_5.5/lpsolve55/bin/ux64

CC ?= /usr/bin/cc
CFLAGS += -Wall -Wextra -Wmissing-prototypes -Wno-unused-variable\
  -Wshadow -Wvla -Wpointer-arith -O3 -fomit-frame-pointer \
  -I$(DILITHIUM_PATH)
SOURCES = sign.c packing.c polyvec.c poly.c ntt.c reduce.c rounding.c randombytes.c
HEADERS = config.h params.h api.h sign.h packing.h polyvec.h poly.h ntt.h \
  reduce.h rounding.h symmetric.h randombytes.h randombytes.h
KECCAK_SOURCES = $(SOURCES) fips202.c symmetric-shake.c
KECCAK_HEADERS = $(HEADERS) fips202.h

ALL_SOURCES = $(patsubst %,$(DILITHIUM_PATH)/%,$(KECCAK_SOURCES)) additional_fct.c
ALL_HEADERS = $(patsubst %,$(DILITHIUM_PATH)/%,$(KECCAK_HEADERS)) additional_fct.h
EQ_SOURCES = noisy_equality.c
EQ_HEADERS = noisy_equality.h
EQ_CFLAGS = -DT0_NOISY_EQUALITY

sign_rdm_msg_and_save2: sign_rdm_msg_and_save.c $(ALL_SOURCES) $(ALL_HEADERS)
	$(CC) $(CFLAGS) -DDILITHIUM_MODE=2 -o $@ $< $(ALL_SOURCES)

sign_rdm_msg_and_save3: sign_rdm_msg_and_save.c $(ALL_SOURCES) $(ALL_HEADERS)
	$(CC) $(CFLAGS) -DDILITHIUM_MODE=3 -o $@ $< $(ALL_SOURCES)

sign_rdm_msg_and_save5: sign_rdm_msg_and_save.c $(ALL_SOURCES) $(ALL_HEADERS)
	$(CC) $(CFLAGS) -DDILITHIUM_MODE=5 -o $@ $< $(ALL_SOURCES)

build_solve_t0_lp2: build_solve_t0_lp.c $(ALL_SOURCES) $(ALL_HEADERS)
	$(CC) $(CFLAGS) -DDILITHIUM_MODE=2 -o $@ $< $(ALL_SOURCES) -I$(LPLIB_PATH)/lp_solve_5.5/ -L$(LPSOLVE_LIBDIR) -llpsolve55

build_solve_t0_lp3: build_solve_t0_lp.c $(ALL_SOURCES) $(ALL_HEADERS)
	$(CC) $(CFLAGS) -DDILITHIUM_MODE=3 -o $@ $< $(ALL_SOURCES) -I$(LPLIB_PATH)/lp_solve_5.5/ -L$(LPSOLVE_LIBDIR) -llpsolve55

build_solve_t0_lp5: build_solve_t0_lp.c $(ALL_SOURCES) $(ALL_HEADERS)
	$(CC) $(CFLAGS) -DDILITHIUM_MODE=5 -o $@ $< $(ALL_SOURCES) -I$(LPLIB_PATH)/lp_solve_5.5/ -L$(LPSOLVE_LIBDIR) -llpsolve55

build_solve_t0_eq_lp2: build_solve_t0_lp.c $(EQ_SOURCES) $(EQ_HEADERS) $(ALL_SOURCES) $(ALL_HEADERS)
	$(CC) $(CFLAGS) $(EQ_CFLAGS) -DDILITHIUM_MODE=2 -o $@ $< $(EQ_SOURCES) $(ALL_SOURCES) -I$(LPLIB_PATH)/lp_solve_5.5/ -L$(LPSOLVE_LIBDIR) -llpsolve55

build_solve_t0_eq_lp3: build_solve_t0_lp.c $(EQ_SOURCES) $(EQ_HEADERS) $(ALL_SOURCES) $(ALL_HEADERS)
	$(CC) $(CFLAGS) $(EQ_CFLAGS) -DDILITHIUM_MODE=3 -o $@ $< $(EQ_SOURCES) $(ALL_SOURCES) -I$(LPLIB_PATH)/lp_solve_5.5/ -L$(LPSOLVE_LIBDIR) -llpsolve55

build_solve_t0_eq_lp5: build_solve_t0_lp.c $(EQ_SOURCES) $(EQ_HEADERS) $(ALL_SOURCES) $(ALL_HEADERS)
	$(CC) $(CFLAGS) $(EQ_CFLAGS) -DDILITHIUM_MODE=5 -o $@ $< $(EQ_SOURCES) $(ALL_SOURCES) -I$(LPLIB_PATH)/lp_solve_5.5/ -L$(LPSOLVE_LIBDIR) -llpsolve55

build_solve_t0_greedy2: build_solve_t0_greedy.c $(ALL_SOURCES) $(ALL_HEADERS)
	$(CC) $(CFLAGS) -DDILITHIUM_MODE=2 -o $@ $< $(ALL_SOURCES)

build_solve_t0_greedy2_matched: build_solve_t0_greedy.c $(ALL_SOURCES) $(ALL_HEADERS)
	$(CC) $(CFLAGS) -DDILITHIUM_MODE=2 -o $@ $< $(ALL_SOURCES)

build_solve_t0_greedy3: build_solve_t0_greedy.c $(ALL_SOURCES) $(ALL_HEADERS)
	$(CC) $(CFLAGS) -DDILITHIUM_MODE=3 -o $@ $< $(ALL_SOURCES)

build_solve_t0_greedy3_matched: build_solve_t0_greedy.c $(ALL_SOURCES) $(ALL_HEADERS)
	$(CC) $(CFLAGS) -DDILITHIUM_MODE=3 -o $@ $< $(ALL_SOURCES)

build_solve_t0_greedy5: build_solve_t0_greedy.c $(ALL_SOURCES) $(ALL_HEADERS)
	$(CC) $(CFLAGS) -DDILITHIUM_MODE=5 -o $@ $< $(ALL_SOURCES)

build_solve_t0_greedy5_matched: build_solve_t0_greedy.c $(ALL_SOURCES) $(ALL_HEADERS)
	$(CC) $(CFLAGS) -DDILITHIUM_MODE=5 -o $@ $< $(ALL_SOURCES)

build_solve_t0_eq_greedy2: build_solve_t0_greedy.c $(EQ_SOURCES) $(EQ_HEADERS) $(ALL_SOURCES) $(ALL_HEADERS)
	$(CC) $(CFLAGS) $(EQ_CFLAGS) -DDILITHIUM_MODE=2 -o $@ $< $(EQ_SOURCES) $(ALL_SOURCES)

build_solve_t0_eq_greedy3: build_solve_t0_greedy.c $(EQ_SOURCES) $(EQ_HEADERS) $(ALL_SOURCES) $(ALL_HEADERS)
	$(CC) $(CFLAGS) $(EQ_CFLAGS) -DDILITHIUM_MODE=3 -o $@ $< $(EQ_SOURCES) $(ALL_SOURCES)

build_solve_t0_eq_greedy5: build_solve_t0_greedy.c $(EQ_SOURCES) $(EQ_HEADERS) $(ALL_SOURCES) $(ALL_HEADERS)
	$(CC) $(CFLAGS) $(EQ_CFLAGS) -DDILITHIUM_MODE=5 -o $@ $< $(EQ_SOURCES) $(ALL_SOURCES)

test_noisy_equality2: test_noisy_equality.c $(EQ_SOURCES) $(EQ_HEADERS)
	$(CC) $(CFLAGS) -DDILITHIUM_MODE=2 -o $@ $< $(EQ_SOURCES)

test_noisy_equality3: test_noisy_equality.c $(EQ_SOURCES) $(EQ_HEADERS)
	$(CC) $(CFLAGS) -DDILITHIUM_MODE=3 -o $@ $< $(EQ_SOURCES)

test_noisy_equality5: test_noisy_equality.c $(EQ_SOURCES) $(EQ_HEADERS)
	$(CC) $(CFLAGS) -DDILITHIUM_MODE=5 -o $@ $< $(EQ_SOURCES)

check-noisy-equality: test_noisy_equality2 test_noisy_equality3 test_noisy_equality5
	./test_noisy_equality2
	./test_noisy_equality3
	./test_noisy_equality5

clean:
	rm -f sign_rdm_msg_and_save2 sign_rdm_msg_and_save3 sign_rdm_msg_and_save5 \
	  build_solve_t0_lp2 build_solve_t0_lp3 build_solve_t0_lp5 \
	  build_solve_t0_greedy2 build_solve_t0_greedy2_matched \
	  build_solve_t0_greedy3 build_solve_t0_greedy3_matched \
	  build_solve_t0_greedy5 build_solve_t0_greedy5_matched \
	  build_solve_t0_eq_lp2 build_solve_t0_eq_lp3 build_solve_t0_eq_lp5 \
	  build_solve_t0_eq_greedy2 build_solve_t0_eq_greedy3 \
	  build_solve_t0_eq_greedy5 test_noisy_equality2 \
	  test_noisy_equality3 test_noisy_equality5 build_solve_t0_spbp2

format:
	clang-format-15 -i sign_rdm_msg_and_save.[ch] additional_fct.[ch] \
	  noisy_equality.[ch] test_noisy_equality.c build_solve_t0_lp.c \
	  build_solve_t0_greedy.c

.PHONY: check-noisy-equality clean format
